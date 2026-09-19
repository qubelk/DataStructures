#ifndef _COLLECTIONS_ARRAY_H_
#define _COLLECTIONS_ARRAY_H_

#include <algorithm>
#include <exception>
#include <format>
#include <initializer_list>

template<typename T, size_t N>
struct ArrayData {
	T data_[N];
};

template<typename T>
struct ArrayData<T, 0> {};

template<typename T, size_t N>
class Array : public ArrayData<T, N> {
private:
	size_t size_ = 0;

public:
	Array() {
		std::fill(begin(), end(), 0);
	}

	Array(const Array<T, N>& arr) : size_(arr.size_) {
		std::copy(arr.data_, arr.data_ + arr.size_, data_);
	}

	Array(std::initializer_list<T> list) : Array() {
		for (auto&& v : list) {
			if (size_ < N) {
				data_[size_++] = v;
			}
		}
	}

	Array<T, N>& operator=(const Array<T, N>& arr) {
		if (this != &arr) {
			Array<T, N> tmp{arr};
			swap(tmp);
		}

		return *this;
	}

	constexpr T* data() noexcept {
		if constexpr (N == 0) {
			return nullptr;
		} else {
			return data_;
		}
	}

	T* begin() noexcept {
		return data_;
	}

	T* end() noexcept {
		return data_ + N;
	}

	const T* begin() const noexcept {
		return data_;
	}

	const T* end() const noexcept {
		return data_ + N;
	}

	void swap(Array<T, N>& arr) {
		std::swap(data_, arr.data_);
	}

	size_t size() const noexcept {
		return size_;
	}

	size_t maxSize() const noexcept {
		return N;
	}

	void fill(T value) {
		std::fill(begin(), end(), value);
	}

	T& at(size_t index) {
		if (index >= N) {
			throw std::out_of_range(std::format("Index {} out of range for Array with size {}", index, N));
		}

		return data_[index];
	}

	const T& at(size_t index) const {
		if (index >= N) {
			throw std::out_of_range(std::format("Index {} out of range for Array with size {}", index, N));
		}

		return data_[index];
	}

	T& operator[](size_t index) {
		return at(index);
	}

	const T& operator[](size_t index) const {
		return at(index);
	}
};

#endif
