# Build and run Phase 11 aggressive tests.
# No hardware required — nn_host.c emulates accelerator in software.

CC       := gcc
CFLAGS   := -O2 -Wall -Wextra -Wpedantic -DTEST_HOST -I.
BUILD    := ./build
BIN      := $(BUILD)/test_nn
TOOLS    := ../../tools

.PHONY: all run vectors run_quantize clean

all: $(BIN)

vectors: test_vectors.h
test_vectors.h:
	python3 $(TOOLS)/gen_test_vectors.py --output test_vectors.h

$(BIN): test_nn.c nn_host.c test_vectors.h
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) test_nn.c nn_host.c -o $(BIN)

run: $(BIN)
	@echo ""; @echo "=== C tests ==="; ./$(BIN)

run_quantize:
	@echo ""; @echo "=== Python quantize.py tests ==="; python3 $(TOOLS)/test_quantize.py

run_all: run run_quantize

clean:
	rm -rf $(BUILD) test_vectors.h
