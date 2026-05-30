#!/usr/bin/env python3
"""
train_mnist.py — train a 784→128→10 INT8-quantization-friendly MLP on MNIST.

Usage:
    python3 tools/train_mnist.py                     # train + save model.pth
    python3 tools/train_mnist.py --epochs 5          # fewer epochs for quick test
    python3 tools/train_mnist.py --quantize          # train + quantize → weights.h

Requirements:
    pip install torch torchvision

Output:
    tools/model.pth            trained float32 weights
    sw/weights.h               INT8 header (with --quantize)
"""

import argparse
import os
import sys

try:
    import torch
    import torch.nn as nn
    import torch.optim as optim
    from torch.utils.data import DataLoader
    import torchvision
    import torchvision.transforms as transforms
except ImportError:
    print("[ERROR] PyTorch / torchvision not installed.")
    print("        pip install torch torchvision")
    sys.exit(1)

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(SCRIPT_DIR)


# ── Model ─────────────────────────────────────────────────────────────────────

class MnistMLP(nn.Module):
    """784 → 128 (ReLU) → 10 MLP.  Matches the layer layout expected by nn.h."""
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(784, 128, bias=True)
        self.fc2 = nn.Linear(128,  10, bias=True)

    def forward(self, x):
        x = x.view(-1, 784)
        x = torch.relu(self.fc1(x))
        x = self.fc2(x)
        return x


# ── Training ──────────────────────────────────────────────────────────────────

def train(model, loader, optimizer, criterion, device):
    model.train()
    total_loss = 0.0
    for images, labels in loader:
        images, labels = images.to(device), labels.to(device)
        optimizer.zero_grad()
        loss = criterion(model(images), labels)
        loss.backward()
        optimizer.step()
        total_loss += loss.item() * len(images)
    return total_loss / len(loader.dataset)


def evaluate(model, loader, device):
    model.eval()
    correct = 0
    with torch.no_grad():
        for images, labels in loader:
            images, labels = images.to(device), labels.to(device)
            preds = model(images).argmax(dim=1)
            correct += (preds == labels).sum().item()
    return 100.0 * correct / len(loader.dataset)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--epochs",    type=int, default=10)
    parser.add_argument("--batch",     type=int, default=256)
    parser.add_argument("--lr",        type=float, default=1e-3)
    parser.add_argument("--data-dir",  default=os.path.join(SCRIPT_DIR, "mnist_data"))
    parser.add_argument("--model-out", default=os.path.join(SCRIPT_DIR, "model.pth"))
    parser.add_argument("--quantize",  action="store_true",
                        help="Also run quantize.py to produce sw/weights.h")
    args = parser.parse_args()

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"Device: {device}")

    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])

    train_ds = torchvision.datasets.MNIST(args.data_dir, train=True,
                                          download=True, transform=transform)
    test_ds  = torchvision.datasets.MNIST(args.data_dir, train=False,
                                          download=True, transform=transform)
    train_loader = DataLoader(train_ds, batch_size=args.batch, shuffle=True,
                              num_workers=2, pin_memory=True)
    test_loader  = DataLoader(test_ds,  batch_size=1024, shuffle=False)

    model = MnistMLP().to(device)
    optimizer = optim.Adam(model.parameters(), lr=args.lr)
    criterion = nn.CrossEntropyLoss()

    print(f"Training MnistMLP for {args.epochs} epoch(s)...")
    for epoch in range(1, args.epochs + 1):
        loss = train(model, train_loader, optimizer, criterion, device)
        acc  = evaluate(model, test_loader, device)
        print(f"  Epoch {epoch:2d}/{args.epochs}  loss={loss:.4f}  test_acc={acc:.2f}%")

    final_acc = evaluate(model, test_loader, device)
    print(f"\nFinal test accuracy: {final_acc:.2f}%")
    if final_acc < 96.0:
        print("[WARN] Accuracy below 96% — consider more epochs or lower LR.")

    os.makedirs(os.path.dirname(args.model_out), exist_ok=True)
    torch.save(model, args.model_out)
    print(f"Saved model: {args.model_out}")

    if args.quantize:
        weights_out = os.path.join(PROJECT_ROOT, "phase12_validation", "sw", "weights.h")
        quantize_py = os.path.join(PROJECT_ROOT, "phase11_sw", "tools", "quantize.py")
        import subprocess
        r = subprocess.run([
            sys.executable, quantize_py,
            "--model", args.model_out,
            "--output", weights_out,
            "--class-name", "mnist_net",
            "--validate",
        ], check=True)
        print(f"Quantized weights → {weights_out}")


if __name__ == "__main__":
    main()
