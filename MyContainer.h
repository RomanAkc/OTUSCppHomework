#pragma once
#include <memory>

template<typename T, class Alloc = std::allocator<T>>
struct MyContainer
{
	MyContainer() {};
	MyContainer(const MyContainer& rhs) = delete;
	MyContainer(MyContainer&& rhs) = delete;
	MyContainer& operator=(const MyContainer& rhs) = delete;
	MyContainer& operator=(MyContainer&& rhs) = delete;
	virtual ~MyContainer() { clear(); }

	void push_back(const T& obj) {
		auto p = alloc.allocate(1);
		alloc.construct(p, obj);

		if (pBegin)
			pEnd->ptrNext = p;
		else
			pBegin = p;

		pEnd = p;
	}

	void clear() {
		if (empty())
			return;

		while (true) {
			if (pBegin->ptrNext) {
				auto p = pBegin;
				pBegin = pBegin->ptrNext;
				alloc.destroy(p);
				alloc.deallocate(p, 1);
			} else {
				alloc.destroy(pBegin);
				alloc.deallocate(pBegin, 1);
				pBegin = nullptr;
				break;
			}
		}
	}

	bool empty() const {
		return pBegin == nullptr;
	}

	template<typename T, typename Alloc>
	struct iterator {
	private:
		typename MyContainer<T, Alloc>::template Node<T>* p{ nullptr };

	public:
		iterator(typename MyContainer<T, Alloc>::template Node<T>* p) {
			this->p = p;
		}
		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		iterator& operator=(const iterator&) = default;
		iterator& operator=(iterator&&) = default;

		bool operator!=(const iterator& rhs) {
			return p != rhs.p;
		}

		iterator& operator++() {
			p = p->ptrNext;
			return *this;
		}

		T& operator*() {
			return p->data;
		}
	};

	iterator<T, Alloc> begin() {
		return iterator<T, Alloc>(pBegin);
	}

	iterator<T, Alloc> end() {
		return iterator<T, Alloc>(nullptr);
	}

private:
	template<typename T>
	struct Node {
		Node(const T& d) : data(d) {}
		Node(const Node&) = default;
		Node(Node&&) = default;
		Node& operator=(const Node&) = default;
		Node& operator=(Node&&) = default;

		Node* ptrNext{ nullptr };
		T data;
	};

	Node<T>* pBegin{ nullptr };
	Node<T>* pEnd{ nullptr };

	typename Alloc::template rebind<Node<T>>::other alloc;
};