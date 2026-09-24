#include <gtest/gtest.h>

#include "smartptr/lazy.h"

struct Dummy {
	std::string data_;
	Dummy(std::string data) : data_(std::move(data)) {}

	void something() {
		data_ += " some";
	}
};

Dummy funcToMove() {
	return Dummy("Moved");
}

TEST(LazyTest, DefaultConstructor) {
	Lazy<Dummy> l{[] {
		return Dummy("Default");
	}};

	EXPECT_EQ(l.isInitialized(), false);
}

TEST(LazyTest, MoveConstructor) {
	Lazy<Dummy> l1{[]() {
		return Dummy("Moved");
	}};

	l1->something();
	EXPECT_EQ(l1.isInitialized(), true);

	Lazy<Dummy> l2{std::move(l1)};

	EXPECT_EQ(l2.isInitialized(), true);
	EXPECT_EQ(l2->data_, "Moved some");
}

TEST(LazyTest, MoveAssignment) {
	Lazy<Dummy> l1{[]() {
		return Dummy("Lazy 1");
	}};

	Lazy<Dummy> l2{[]() {
		return Dummy("Lazy 2");
	}};

	l2 = std::move(l1);
	EXPECT_EQ(l2->data_, "Lazy 1");
}

TEST(LazyTest, MethodCall) {
	Lazy<Dummy> l{[]() {
		return Dummy("Method call");
	}};

	l->something();
	EXPECT_EQ(l->data_, "Method call some");
	EXPECT_EQ(l.isInitialized(), true);
}

TEST(LazyTest, Dereference) {
	Lazy<Dummy> l{[]() {
		return Dummy("Some Data");
	}};

	EXPECT_EQ(*l, "Some Data");
}

TEST(LazyTest, Reset) {
	Lazy<Dummy> l{[]() {
		return Dummy("Reset");
	}};

	l->something();
	l->something();
	EXPECT_EQ(l->data_, "Reset some some");

	l.reset();

	EXPECT_EQ(l->data_, "Reset");
}
