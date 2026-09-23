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

	delete tmp;
}

TEST(UniqueTest, Swap) {
	Unique<int> u1{42};
	Unique<int> u2{15};

	u1.swap(u2);
	EXPECT_EQ(*u1, 15);
	EXPECT_EQ(*u2, 42);
}

TEST(UniqueTest, ArrayDefaultConstructor) {
	Unique<int[]> u;

	EXPECT_EQ(u.get(), nullptr);
	EXPECT_EQ(u, nullptr);
	EXPECT_TRUE(u == nullptr);
}

TEST(UniqueTest, ArrayPointerConstructor) {
	int* arr = new int[]{1, 2, 3, 4, 5};
	Unique<int[]> u{arr};

	EXPECT_EQ(u[0], 1);
	EXPECT_EQ(u[4], 5);
}

TEST(UniqueTest, ArrayInPlacePointerConstructor) {
	Unique<int[]> u{new int[]{1, 2, 3, 4, 5}};

	EXPECT_EQ(u[0], 1);
	EXPECT_EQ(u[4], 5);
}

TEST(UniqueTest, ArrayMoveConstructor) {
	Unique<int[]> u1{new int[]{1, 2, 3, 4, 5}};
	Unique<int[]> u2{std::move(u2)};

	EXPECT_EQ(u2[0], 1);
	EXPECT_EQ(u2[4], 5);
}

TEST(UniqueTest, ArrayNullptrAssignment) {
	Unique<int[]> u{new int[]{1, 2, 3, 4, 5}};
	EXPECT_EQ(u[0], 1);
	EXPECT_EQ(u[4], 5);

	u = nullptr;

	EXPECT_EQ(u, nullptr);
}

TEST(UniqueTest, ArrayMoveAssignment) {
	Unique<int[]> u1{new int[]{1, 2, 3, 4, 5}};
	Unique<int[]> u2;

	u2 = std::move(u1);

	EXPECT_EQ(u2[0], 1);
	EXPECT_EQ(u2[4], 5);
}

TEST(UniqueTest, ArrayReset) {
	Unique<int[]> u{new int[]{1, 2, 3, 4, 5}};
	EXPECT_EQ(u[0], 1);
	EXPECT_EQ(u[4], 5);

	u.reset();

	EXPECT_EQ(u, nullptr);
}

TEST(UniqueTest, ArrayRelease) {
	Unique<int[]> u{new int[]{1, 2, 3, 4, 5}};
	int* tmp = u.release();

	EXPECT_EQ(u, nullptr);
	EXPECT_EQ(tmp[0], 1);
	EXPECT_EQ(tmp[4], 5);

	delete[] tmp;
}

TEST(UniqueTest, ArraySwap) {
	Unique<int[]> u1{new int[]{1, 2, 3, 4, 5}};
	Unique<int[]> u2{new int[]{5, 4, 3, 2, 1}};

	u1.swap(u2);
	EXPECT_EQ(u1[0], 5);
	EXPECT_EQ(u1[4], 1);

	EXPECT_EQ(u2[0], 1);
	EXPECT_EQ(u2[4], 5);
}
