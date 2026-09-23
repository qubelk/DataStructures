#include <gtest/gtest.h>

#include "smartptr/unique.h"

TEST(UniqueTest, DefaultConstructor) {
	Unique<int> u;

	EXPECT_EQ(u.get(), nullptr);
	EXPECT_EQ(u, nullptr);
	EXPECT_TRUE(u == nullptr);
}

TEST(UniqueTest, LiteralConstructor) {
	Unique<int> u{42};

	EXPECT_EQ(*u, 42);
}

TEST(UniqueTest, PointerConstructor) {
	int* ptr = new int;
	*ptr = 42;

	Unique<int> u{ptr};

	EXPECT_EQ(*u, 42);

	delete ptr;
}

TEST(UniqueTest, InPlacePointerConstructor) {
	Unique<int> u{new int(42)};

	EXPECT_EQ(*u, 42);
}

TEST(UniqueTest, MoveConstructor) {
	Unique<int> u1{42};
	Unique<int> u2{std::move(u1)};

	EXPECT_EQ(*u2, 42);
	EXPECT_EQ(u1, nullptr);
}
