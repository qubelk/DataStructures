#ifndef _SMARTPTR_LAZY_H_
#define _SMARTPTR_LAZY_H_

#include <optional>
#include <functional>

template<typename T>
class Lazy {
private:
	std::function<T()> factory_;
	mutable std::optional<T> cached_result_;

	void ensureInitialized() const {
		if (cached_result_.has_value() == false) {
			cached_result_ = factory_();
		}
	}

public:
	template<typename F>
	explicit Lazy(F&& factory) : factory_(std::forward(factory)) {}

	Lazy(const Lazy&) = delete;
	Lazy& operator=(const Lazy&) = delete;

	Lazy(Lazy&&) = default;
	Lazy& operator=(Lazy&&) = default;

	T& operator*() {
		ensureInitialized();
		return *cached_result_;
	}

	const T& operator*() const {
		ensureInitialized();
		return *cached_result_;
	}

	T* operator->() {
		ensureInitialized();
		return &*cached_result_;
	}

	const T* operator->() const {
		ensureInitialized();
		return &*cached_result_;
	}

	bool isInitialized() const noexcept {
		return cached_result_.has_value();
	}

	void reset() {
		cached_result_.reset();
	}
};

#endif
