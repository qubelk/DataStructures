#ifndef _SMARTPTR_CONCURRENT_LAZY_H_
#define _SMARTPTR_CONCURRENT_LAZY_H_

#include <mutex>

#include "smartptr/lazy.h"

template<typename T>
class ConcurrentLazy : public Lazy<T> {
private:
	mutable std::once_flag once_;
	mutable std::function<T()> factory_ = getFactory();
	std::optional<T> cached_result_ = getCachedResult();

	void ensureInitialized() const override {
		std::call_once(once_, [this] {
			cached_result_ = factory_();
		});
	}
};

#endif
