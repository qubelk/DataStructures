#ifndef _COLLECTIONS_ARRAY_H_
#define _COLLECTIONS_ARRAY_H_

#include <algorithm>
#include <initializer_list>

template<typename T, size_t N>
class Array {
private:
	T* data_ = nullptr;
	size_t size_ = 0;

public:
	Array() : data_(new T[N]) {
		std::fill(begin(), end(), 0);
	}

	Array(const Array<T, N>& arr) : Array() {
		std::copy(arr.begin(), arr.end(), data_);
		size_ = arr.size_;
	}

	Array(std::initializer_list<T> list) : Array() {
		for (auto&& v : list) {
			if (size_ < N) {
				data_[size_++] = v;
			}
		}
	}

	~Array() {
		delete[] data_;
		data_ = nullptr;
	}

	Array<T, N>& operator=(const Array<T, N>& arr) {
		if (this != arr) {
			Array<T, N> tmp{arr};
			swap(tmp);
		}

		return *this;
	}

	T* begin() const noexcept {
		return data_;
	}

	T* end() const noexcept {
		return data_ + N;
	}

	void swap(Array<T, N>& arr) {
		std::swap(data_, arr.data_);
	}

	size_t size() const noexcept {
		return size_;
	}

	void fill(T v) {
		std::fill(begin(), end(), v);
	}
};

#endif