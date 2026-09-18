CPP := g++
BUILDDIR := build
TESTBIN := run_tests

WARNFLAGS := -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 \
	-Wunused -Wunused-function -Wunused-const-variable -Wunused-macros -Wunused-parameter -Wunused-result \
	-Wunreachable-code -Wuninitialized -Wundef -Wunused-label -Wunused-variable

DEBUGFLAGS := -ggdb -g -Og

SANITIZERS := -fsanitize=address -fsanitize=undefined

CPPFLAGS := -std=c++23 -I. $(WARNFLAGS) $(DEBUGFLAGS) $(SANITIZERS)

TESTLIBS := -lgtest -lgtest_main -pthread

SRCS := tests/collections/array/array_test.cpp
OBJS := $(SRCS:.cpp=.o)

all: clean $(TESTBIN) test

$(TESTBIN): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)/$@ $^ $(TESTLIBS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

test: $(TESTBIN)
	./$(BUILDDIR)/$(TESTBIN)

clean:
	rm -rf build *.o
