#pragma once
#include <memory>

template <typename T, std::size_t N>
struct MyAllocator {
	MyAllocator() {
		m_pMemory = reinterpret_cast<T*>(std::malloc(N * sizeof(T)));
	}

	~MyAllocator() {
		std::free(m_pMemory);
	}

	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	value_type* allocate(std::size_t) {
		if (m_nIndex >= N)
			throw std::bad_alloc();

		m_nIndex++;

		return m_pMemory + (m_nIndex - 1);
	}

	void deallocate(value_type*, std::size_t) {}

	template <typename U, typename... Args>
	void construct(U* p, Args&&... args) {
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(value_type* p) {
		p->~T();
	}

	template <typename O>
	struct rebind {
		using other = MyAllocator<O, N>;
	};

private:
	T* m_pMemory{ nullptr };
	std::size_t m_nIndex{ 0 };
};