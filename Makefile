CPP := g++
BUILDDIR := build
TESTBIN := tests

WARNFLAGS := -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 \
	-Wunused -Wunused-function -Wunused-const-variable -Wunused-macros -Wunused-parameter -Wunused-result \
	-Wunreachable-code -Wuninitialized -Wundef -Wunused-label -Wunused-variable

DEBUGFLAGS := -ggdb -g -Og

SANITIZERS := -fsanitize=address -fsanitize=undefined

CPPFLAGS := -I. $(WARNFLAGS) $(DEBUGFLAGS) $(SANITIZERS)

TESTLIBS := -lgtest -lgtest_main -pthread

SRCS := tests/collections/array/array_test.cpp
OBJS := $(SRCS:.cpp=.o)

all: clean $(TESTBIN) runtest

$(TESTBIN): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(TESTLIBS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

runtest: $(TESTBIN)
	./$(BUILDDIR)/$(TESTBIN)

clean:
	rm -rf build
