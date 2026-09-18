#include <gtest/gtest.h>
#include <string>

#include "collections/array/array.h"

class ArrayTest : public testing::Test {
protected:
	Array<int, 5> arr0_{1, 2, 3, 4, 5};
	Array<std::string, 3> arr1_{"Foo", "Boo", "Bar"};
};

TEST_F(ArrayTest, IntegerArrSizeIs5) {
	EXPECT_EQ(arr0_.size(), 5);
}

TEST_F(ArrayTest, Index1ForStringArrIsBoo) {
	EXPECT_EQ(arr1_.at(1).value(), "Boo");
}

TEST_F(ArrayTest, IndexOutOfRangeForStringArr) {
	EXPECT_EQ(arr1_.at(3).has_value(), false);
}
