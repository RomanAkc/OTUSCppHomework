#pragma once
#include <iostream>

template <typename T, std::size_t N = 10>
struct MyAllocator {
	MyAllocator() {
		pMemory = reinterpret_cast<T*>(std::malloc(N * sizeof(T)));
		std::cout << "ctor" << std::endl;
	}
	~MyAllocator() {
		std::free(pMemory);
		std::cout << "dctor" << std::endl;
	}

	using value_type = T;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	value_type* allocate(std::size_t n) {
		std::cout << "allocate: " << n << std::endl;

		if (index + 1 >= N)
			throw std::bad_alloc();

		index++;

		return &pMemory[index - 1];
	}

	void deallocate(value_type* p, std::size_t N) {}

	template <typename U, typename... Args>
	void construct(value_type* p, Args&&... args) {
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(value_type* p) {
		p->~T();
	}

	template <typename O>
	struct rebind {
		using other = MyAllocator<O>;
	};

private:
	T* pMemory{ nullptr };
	std::size_t index{ 0 };
};