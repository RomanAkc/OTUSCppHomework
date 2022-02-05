#pragma once
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <tuple>

template <typename T>
typename std::enable_if_t<std::is_integral_v<T>, void>
print_ip(T num) {
	int size = sizeof(num);
	unsigned char* p = reinterpret_cast<unsigned char*>(&num);

	for(int i = size - 1; i >= 0; --i) {
		if(i != size - 1){
			std::cout << ".";
		}
		
		unsigned char c = *(p + i);
		std::cout << static_cast<int>(c);
	}

	std::cout << std::endl;
}

template <typename T>
typename std::enable_if_t<std::is_same_v<T, std::string>, void>
print_ip(const T& str) {
	std::cout << str << std::endl;
}

template < template <typename, typename> typename Container
	, typename T
	, typename Allocator = std::allocator<T>
>
typename std::enable_if_t<
	std::is_same_v<Container<T, Allocator>, std::vector<T, Allocator>> ||
	std::is_same_v<Container<T, Allocator>, std::list<T, Allocator>>
	, void>
print_ip(const Container<T, Allocator>& cont) {
	for(auto it = cont.begin(); it != cont.end(); ++it) {
		if(it != cont.begin())
			std::cout << ".";

		std::cout << *it;
	}
	std::cout << std::endl;
}

//Check tuple
