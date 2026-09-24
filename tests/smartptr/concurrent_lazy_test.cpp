#include <gtest/gtest.h>
#include <vector>
#include <thread>
#include <mutex>
#include <latch>

#include "smartptr/concurrent_lazy.h"

TEST(ConcurrentLazyTest, FactoryCalledOnce) {
	std::atomic<int> call_count{0};

	ConcurrentLazy<int> c{[&call_count] {
		call_count.fetch_add(1, std::memory_order_relaxed);
		return 42;
	}};

	constexpr size_t kThreadsCount = 4;

	std::vector<std::thread> threads{kThreadsCount};
	threads.reserve(kThreadsCount);

	std::latch start{kThreadsCount};

	for (size_t i = 0; i < kThreadsCount; ++i) {
		threads.emplace_back([&] {
			start.arrive_and_wait();
			EXPECT_EQ(*c, 42);
		});
	}

	for (auto&& t : threads) {
		t.join();
	}

	EXPECT_EQ(call_count.load(), 1);
	EXPECT_EQ(c.isInitialized(), true);
}

TEST(ConcurrentLazyTest, ThrowThenSucces) {
	std::atomic<int> attempts{0};

	ConcurrentLazy<int> c{[&attempts] {
		if (attempts.fetch_add(1) == 0) {
			throw std::runtime_error("Fail");
		}

		return 42;
	}};

	EXPECT_THROW(*c, std::runtime_error);
	EXPECT_EQ(*c, 42);
}
