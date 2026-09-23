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

TEST(UniqueTest, NullptrAssignment) {
	Unique<int> u{42};
	EXPECT_EQ(*u, 42);

	u = nullptr;
	EXPECT_EQ(u, nullptr);
}

TEST(UniqueTest, MoveAssginment) {
	Unique<int> u1{42};
	Unique<int> u2{15};

	u2 = std::move(u1);
	EXPECT_EQ(*u2, 42);
}

TEST(UniqueTest, Reset) {
	Unique<int> u{42};
	EXPECT_EQ(*u, 42);

	u.reset();
	EXPECT_EQ(u, nullptr);
}

TEST(UniqueTest, Release) {
	Unique<int> u{42};
	int* tmp = u.release();

	EXPECT_EQ(u, nullptr);
	EXPECT_EQ(*tmp, 42);
}
