#pragma once
#include <memory>

template<typename T, class Allocator = std::allocator<T>>
struct MyContainer
{
	MyContainer() {};
	MyContainer(const MyContainer& rhs) = delete;
	MyContainer(MyContainer&& rhs) = delete;
	MyContainer& operator=(const MyContainer& rhs) = delete;
	MyContainer& operator=(MyContainer&& rhs) = delete;
	virtual ~MyContainer() { 
		clear(); 
	}

	void push_back(const T& obj) {
		auto p = m_allocator.allocate(1);
		m_allocator.construct(p, obj);

		if (m_pFirst) {
			m_pLast->m_pNext = p;
		} else {
			m_pFirst = p;
		}

		m_pLast = p;
		m_nSize++;
	}

	void clear() {
		while (m_pFirst) {
			auto p = m_pFirst;
			m_pFirst = m_pFirst->m_pNext;
			m_allocator.destroy(p);
			m_allocator.deallocate(p, 1);
		}
		m_nSize = 0;
	}

	bool empty() const {
		return size() == 0;
	}

	std::size_t size() const {
		return m_nSize;
	}

	template<typename Type, typename TypeAllocator>
	struct iterator {
	private:
		typename MyContainer<Type, TypeAllocator>::template Node<Type>* m_pCurrent{ nullptr };

	public:
		iterator(typename MyContainer<Type, TypeAllocator>::template Node<Type>* p) {
			this->m_pCurrent = p;
		}
		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		iterator& operator=(const iterator&) = default;
		iterator& operator=(iterator&&) = default;

		bool operator!=(const iterator& rhs) {
			return m_pCurrent != rhs.m_pCurrent;
		}

		iterator& operator++() {
			m_pCurrent = m_pCurrent->m_pNext;
			return *this;
		}

		T& operator*() {
			return m_pCurrent->m_data;
		}
	};

	iterator<T, Allocator> begin() {
		return iterator<T, Allocator>(m_pFirst);
	}

	iterator<T, Allocator> end() {
		return iterator<T, Allocator>(nullptr);
	}

private:
	template<typename Type>
	struct Node {
		Node(const Type& data) : m_data(data) {}
		Node(const Node&) = default;
		Node(Node&&) = default;
		Node& operator=(const Node&) = default;
		Node& operator=(Node&&) = default;

		Node* m_pNext{ nullptr };
		Type m_data;
	};

	Node<T>* m_pFirst{ nullptr };
	Node<T>* m_pLast{ nullptr };
	std::size_t m_nSize{ 0 };

	typename Allocator::template rebind<Node<T>>::other m_allocator;
};