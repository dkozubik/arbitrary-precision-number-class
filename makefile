CXX      = /packages/run.64/gcc-9.2/bin/c++
TIDY     = /packages/run.64/llvm-9.0.1/bin/clang-tidy
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
BIN      = number

all: $(BIN) tidy
tidy:
	$(TIDY) --header-filter='.*' --warnings-as-errors='*' --quiet $(BIN).cpp -- $(CXXFLAGS)

$(BIN): $(BIN).hpp $(BIN).cpp test.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN) $(BIN).cpp test.cpp

check: $(BIN)
	./$(BIN)
	valgrind --leak-check=full ./$(BIN)

clean:
	rm -f $(BIN) core *.core

.PHONY: all clean tidy
