#pragma once

template <typename T, std::size_t N>
struct MyAllocator {

	MyAllocator() {
		pMemory = reinterpret_cast<T*>(std::malloc(N * sizeof(T)));
	}

	~MyAllocator() {
		std::free(pMemory);
	}

	using value_type = T;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	value_type* allocate(std::size_t n) {
		index++;

		if (index > N)
			throw std::bad_alloc();

		return &pMemory[index - 1];
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
	T* pMemory{ nullptr };
	std::size_t index{ 0 };
};