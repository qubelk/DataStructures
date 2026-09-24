#ifndef _SMARTPTR_CONCURRENT_LAZY_H_
#define _SMARTPTR_CONCURRENT_LAZY_H_

#include <mutex>

#include "smartptr/lazy.h"

template<typename T>
class ConcurrentLazy : public Lazy<T> {
private:
	mutable std::once_flag once_;

	void ensureInitialized() const override {
		std::call_once(once_, [this] {
			Lazy<T>::cached_result_ = Lazy<T>::factory_();
		});
	}

public:
	using Lazy<T>::Lazy;
};

#endif
