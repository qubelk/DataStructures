#ifndef _SMARTPTR_UNIQUE_H_
#define _SMARTPTR_UNIQUE_H_

#include <utility>
#include <type_traits>

template<typename T>
class Unique {
	static_assert(std::is_array_v<T> == true, "Use Unique<T[]> for arrays, not Unique<T[N]>");

private:
	T* data_ = new T;

public:
	explicit Unique(T data) {
		*data_ = data;
	}

	explicit Unique(T* data = nullptr) noexcept : data_(data) {}

	Unique(const Unique&) = delete;

	Unique(Unique&& u) noexcept : data_(u.data_) {
		u.data_ = nullptr;
	}

	~Unique() {
		delete data_;
	}

	Unique& operator=(const Unique&) = delete;

	Unique& operator=(std::nullptr_t) noexcept {
		reset();
		return *this;
	}

	Unique& operator=(Unique&& u) noexcept {
		if (this != &u) {
			reset();
			data_ = u.data_;
			u.data_ = nullptr;
		}

		return *this;
	}

	void reset(T* data = nullptr) noexcept {
		T* old = data_;
		data_ = data;

		delete old;
	}

	T* release() noexcept {
		T* tmp = data_;
		data_ = nullptr;
		return tmp;
	}

	void swap(Unique& u) noexcept {
		std::swap(data_, u.data_);
	}

	T* get() noexcept {
		return data_;
	}

	const T* get() const noexcept {
		return data_;
	}

	T& operator*() {
		return *data_;
	}

	const T& operator*() const {
		return *data_;
	}

	T* operator->() {
		return data_;
	}

	const T* operator->() const {
		return data_;
	}

	friend bool operator==(const Unique& a, std::nullptr_t) {
		return a.get() == nullptr;
	}

	friend bool operator!=(const Unique& a, std::nullptr_t) {
		return a.get() != nullptr;
	}
};

template<typename T>
class Unique<T[]> {
private:
	T* data_;

public:
	explicit Unique(T* data = nullptr) noexcept : data_(data) {}

	Unique(const Unique&) = delete;

	Unique(Unique&& u) noexcept : data_(u.data_) {
		u.data_ = nullptr;
	}

	~Unique() {
		delete[] data_;
	}

	Unique& operator=(const Unique&) = delete;

	Unique& operator=(std::nullptr_t) noexcept {
		reset();
		return *this;
	}

	Unique& operator=(Unique&& u) noexcept {
		if (this != &u) {
			reset();
			data_ = u.data_;
			u.data_ = nullptr;
		}

		return *this;
	}

	void reset(T* data = nullptr) noexcept {
		T* old = data_;
		data_ = data;

		delete[] old;
	}

	T* release() noexcept {
		T* tmp = data_;
		data_ = nullptr;
		return tmp;
	}

	void swap(Unique& u) noexcept {
		std::swap(data_, u.data_);
	}

	T* get() noexcept {
		return data_;
	}

	const T* get() const noexcept {
		return data_;
	}

	T& operator[](size_t index) {
		return data_[index];
	}

	const T& operator[](size_t index) const {
		return data_[index];
	}

	friend bool operator==(const Unique& a, std::nullptr_t) {
		return a.get() == nullptr;
	}

	friend bool operator!=(const Unique& a, std::nullptr_t) {
		return a.get() != nullptr;
	}
};

#endif
