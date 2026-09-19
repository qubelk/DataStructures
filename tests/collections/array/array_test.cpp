#include <gtest/gtest.h>
#include <string>

#include "collections/array/array.h"

TEST(ArrayTest, DefaultConstructor) {
	Array<int, 5> arr;
	EXPECT_EQ(arr.size(), 0);
	EXPECT_EQ(arr.maxSize(), 5);
	EXPECT_EQ(arr.at(0), 0);
}

TEST(ArrayTest, ListConstructor) {
	Array<int, 5> arr{1, 2, 3, 4, 5};
	EXPECT_EQ(arr.size(), 5);
	
	for (size_t i = 0; i < arr.size(); ++i) {
		EXPECT_EQ(arr.at(i), static_cast<int>(i+1));
	}
}

TEST(ArrayTest, CopyConstructor) {
	Array<int, 3> a{1, 2, 3};
	Array<int, 3> b{a};

	EXPECT_EQ(b.size(), 3);
	EXPECT_EQ(b.at(1), 2);
}

TEST(ArrayTest, CopyAssignment) {
	Array<int, 3> a{1, 2, 3};
	Array<int, 3> b{5, 5, 5};

	b = a;
	EXPECT_EQ(b.at(0), 1);
	EXPECT_EQ(b.at(2), 3);
}

TEST(ArrayTest, SelfAssignment) {
	Array<int, 3> a{1, 2, 3};
	a = a;
	EXPECT_EQ(a.at(0), 1);
	EXPECT_EQ(a.at(2), 3);
}

TEST(ArrayTest, AtThrowsOutOfRange) {
	Array<int, 3> a{1, 2, 3};
	EXPECT_THROW(a.at(15), std::out_of_range);
}

TEST(ArrayTest, Iterators) {
	Array<int, 3> a{1, 2, 3};
	int sum = 0;

	for (auto&& v : a) {
		sum += v;
	}

	EXPECT_EQ(sum, 6);
}

TEST(ArrayTest, BeginEqualsEndWhenEmpty) {
	Array<int, 0> a;
	EXPECT_EQ(a.begin(), a.end());
}
