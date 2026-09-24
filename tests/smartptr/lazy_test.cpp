#include <gtest/gtest.h>

#include "smartptr/lazy.h"

struct Dummy {
	std::string data_;
	Dummy(std::string data) : data_(std::move(data)) {}

	std::string something() const {
		return data_ + " some";
	}
};

TEST(LazyTest, DefaultConstructor) {
	Lazy<Dummy> l{[] {
		return Dummy("Default");
	}};

	EXPECT_EQ(l.isInitialized(), false);
}

TEST(LazyTest, MoveConstructor) {
	Lazy<Dummy> l{std::move([]() {
		return Dummy("Moved");
	})};

	EXPECT_EQ(l.isInitialized(), false);
}

TEST(LazyTest, MethodCall) {
	Lazy<Dummy> l{[]() {
		return Dummy("Method call");
	}};

	l->something();
	EXPECT_EQ(l.isInitialized(), true);
	EXPECT_EQ(l->data_, "Method call some");
}
