# Build and run Phase 11 aggressive tests.
# No hardware required — nn_host.c emulates accelerator in software.

CC       := gcc
CFLAGS   := -O2 -Wall -Wextra -Wpedantic -DTEST_HOST -I.
BUILD    := ./build
BIN      := $(BUILD)/test_nn
TOOLS    := ../../tools

HEAP_DIR := ../freertos
HEAP_BIN := $(BUILD)/test_heap

.PHONY: all run vectors run_quantize run_heap run_all clean

all: $(BIN) $(HEAP_BIN)

vectors: test_vectors.h
test_vectors.h:
	python3 $(TOOLS)/gen_test_vectors.py --output test_vectors.h

$(BIN): test_nn.c nn_host.c test_vectors.h
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) test_nn.c nn_host.c -o $(BIN)

$(HEAP_BIN): $(HEAP_DIR)/test_heap.c $(HEAP_DIR)/heap_4.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -I$(HEAP_DIR) \
	    $(HEAP_DIR)/test_heap.c $(HEAP_DIR)/heap_4.c -o $(HEAP_BIN)

run: $(BIN)
	@echo ""; @echo "=== C nn tests ==="; ./$(BIN)

run_heap: $(HEAP_BIN)
	@echo ""; @echo "=== heap_4 allocator tests ==="; ./$(HEAP_BIN)

run_quantize:
	@echo ""; @echo "=== Python quantize.py tests ==="; python3 $(TOOLS)/test_quantize.py

run_all: run run_heap run_quantize

clean:
	rm -rf $(BUILD) test_vectors.h
