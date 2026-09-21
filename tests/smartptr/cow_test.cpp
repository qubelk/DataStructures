#include <gtest/gtest.h>

#include "smartptr/cow.h"

TEST(CowTest, Constructor) {
	Cow<int> c{42};

	EXPECT_EQ(c.read(), 42);
}

TEST(CowTest, CopyAssignment) {
	Cow<int> c1{42};
	Cow<int> c2{8};

	c2 = c1;
	EXPECT_EQ(c2.read(), 42);
	EXPECT_EQ(c1.read(), 42);
}

TEST(CowTest, MoveAssignment) {
	Cow<int> c1{42};
	Cow<int> c2{8};

	c2 = std::move(c1);
	EXPECT_EQ(c2.read(), 42);
	EXPECT_EQ(c1.get(), nullptr);
}

TEST(CowTest, SelfAssignment) {
	Cow<int> c1{42};
	c1 = c1;

	EXPECT_EQ(c1.read(), 42);
}

TEST(CowTest, CopyingDataOnWrite) {
	Cow<int> c1{42};
	Cow<int> c2{c1};

	*c1 *= 2;
	EXPECT_EQ(*c1, 84);
	EXPECT_EQ(*c2, 42);
}

TEST(CowTest, Equal) {
	Cow<int> c1{42};
	Cow<int> c2{c1};

	EXPECT_TRUE(c1 == c2);
}

TEST(CowTest, NotEqual) {
	Cow<int> c1{42};
	Cow<int> c2{42};

	EXPECT_TRUE(c1 != c2);
}
