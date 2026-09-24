#ifndef _SMARTPTR_LAZY_H_
#define _SMARTPTR_LAZY_H_

#include <optional>
#include <functional>

template<typename T>
class Lazy {
private:
	std::function<T()> factory_;
	mutable std::optional<T> cached_result_;

	virtual void ensureInitialized() const {
		if (cached_result_.has_value() == false) {
			cached_result_ = factory_();
		}
	}

protected:
	std::optional<T>& getCachedResult() {
		return cached_result_;
	}

	const std::optional<T>& getCachedResult() const {
		return cached_result_;
	}

	std::function<T()>& getFactory() {
		return factory_;
	}

	const std::function<T()>& getFactory() const {
		return factory_;
	}

public:
	template<typename F>
	explicit Lazy(F&& factory) : factory_(std::forward<F>(factory)) {}

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

	T& get() {
		return **this;
	}

	const T& get() const {
		return **this;
	}

	bool isInitialized() const noexcept {
		return cached_result_.has_value();
	}

	void reset() {
		cached_result_.reset();
	}
};

#endif
