#include <gtest/gtest.h>

#include "smartptr/unique.h"

TEST(UniqueTest, DefaultConstructor) {
	Unique<int> u;

	EXPECT_EQ(u.get(), nullptr);
	EXPECT_EQ(u, nullptr);
	EXPECT_TRUE(u == nullptr);
}
