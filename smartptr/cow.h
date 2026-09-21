#ifndef _SMARTPTR_COW_H_
#define _SMARTPTR_COW_H_

#include <memory>

template<typename T>
class Cow {
private:
	std::shared_ptr<T> data_;

	void detach() {
		if (data_ != nullptr && data_.use_count() > 1) {
			data_ = std::make_shared<T>(*data_);
		}
	}

public:
	explicit Cow(T data) : data_(std::make_shared<T>(std::move(data))) {}

	const T& read() const {
		return *data_;
	}

	T& write() {
		detach();
		return *data_;
	}

	T& operator*() {
		return write();
	}

	const T& operator*() const {
		return read();
	}

	T* get() {
		detach();
		return data_.get();
	}

	const T* get() const {
		return data_.get();
	}

	friend bool operator==(const Cow& a, const Cow& b) = default;

	friend bool operator==(const Cow& a, std::nullptr_t) {
		return a.get() == nullptr;
	}

	friend bool operator!=(const Cow& a, const Cow& b) = default;

	friend bool operator!=(const Cow& a, std::nullptr_t) {
		return a.get() != nullptr;
	}
};

#endif
