# Build and run host-side nn_fc_forward unit tests.
# No hardware required — uses nn_host.c emulation.

CC      := gcc
CFLAGS  := -O2 -Wall -Wextra -DTEST_HOST -I.
BUILD   := ./build
BIN     := $(BUILD)/test_nn

.PHONY: all run vectors clean

all: $(BIN)

vectors: test_vectors.h

test_vectors.h:
	python3 ../../tools/gen_test_vectors.py --output test_vectors.h

$(BIN): test_nn.c nn_host.c test_vectors.h
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) test_nn.c nn_host.c -o $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BUILD)
