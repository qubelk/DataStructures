CPP := g++
BUILDDIR := build
BIN := libcollections.so
TESTBIN := run_tests

WARNFLAGS := -Wall -Wextra -Werror -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 \
	-Wunused -Wunused-function -Wunused-const-variable -Wunused-macros -Wunused-parameter -Wunused-result \
	-Wunreachable-code -Wuninitialized -Wundef -Wunused-label -Wunused-variable

DEBUGFLAGS := -ggdb -g -Og

SANITIZERS := -fsanitize=address -fsanitize=undefined

CPPFLAGS := -std=c++23 -I. -fPIC $(WARNFLAGS) $(DEBUGFLAGS)

TESTLIBS := -lgtest -lgtest_main -pthread

SRCS := tests/collections/array_test.cpp tests/smartptr/cow_test.cpp tests/smartptr/unique_test.cpp \
	tests/smartptr/lazy_test.cpp

OBJS := $(SRCS:.cpp=.o)

all: clean $(TESTBIN) test

$(TESTBIN): $(OBJS)
	mkdir $(BUILDDIR)
	$(CPP) $(CPPFLAGS) $(SANITIZERS) -o $(BUILDDIR)/$@ $^ $(TESTLIBS)

$(TESTBIN)-valgrind: $(OBJS)
	mkdir $(BUILDDIR)
	$(CPP) $(CPPFLAGS) -o $(BUILDDIR)/$(TESTBIN) $^ $(TESTLIBS)

$(BIN): $(OBJS)
	mkdir $(BUILDDIR)
	$(CPP) $(CPPFLAGS) $(SANITIZERS) -shared -o $(BUILDDIR)/$@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(SANITIZERS) -c $< -o $@

test: $(TESTBIN)
	./$(BUILDDIR)/$(TESTBIN)

clean:
	rm -rf $(BUILDDIR) $(OBJS)

check-leak: $(TESTBIN)-valgrind
	valgrind --leak-check=full ./$(BUILDDIR)/$(TESTBIN)
