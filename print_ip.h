#pragma once
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <tuple>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
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
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(const T& str) {
	std::cout << str << std::endl;
}

template < template <typename, typename> typename Container
	, typename T
	, typename Allocator = std::allocator<T>
>
typename std::enable_if<
	std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value ||
	std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
	, void>::type
print_ip(const Container<T, Allocator>& cont) {
	for(auto it = cont.begin(); it != cont.end(); ++it) {
		if(it != cont.begin())
			std::cout << ".";

		std::cout << *it;
	}
	std::cout << std::endl;
}

//WORK WITH TUPLE

//Checking tuple has all alements are the same type (badly, because isn't working with less then two elements)
template<typename Prev, typename Cur, typename... Rest>
struct is_tuple_same {
	static const bool value = std::is_same_v<Prev, Cur> && is_tuple_same<Cur, Rest...>::value;
};

template<typename Prev, typename Cur>
struct is_tuple_same<Prev, Cur> {
	static const bool value = std::is_same_v<Prev, Cur>;
};

//print tuple
template <int Index = 0, typename... Args>
typename std::enable_if<
	Index >= sizeof... (Args)
	, void>::type
print_tuple(const std::tuple<Args...>& tup) {}

template <int Index = 0, typename... Args>
typename std::enable_if<
	Index == (sizeof... (Args) - 1)
	, void>::type
print_tuple(const std::tuple<Args...>& tup) {
	std::cout << std::get<Index>(tup) << std::endl;
}

template <int Index = 0, typename... Args>
typename std::enable_if<
	Index < (sizeof... (Args) - 1)
	, void>::type
print_tuple(const std::tuple<Args...>& tup) {
	std::cout << std::get<Index>(tup) << ".";
	print_tuple<Index + 1, Args...>(tup);
}

template< template <typename...> typename Tuple
	, typename... Args
>
typename std::enable_if<
	std::is_same<Tuple<Args...>, std::tuple<Args...>>::value &&
	is_tuple_same<Args...>::value
	, void>::type
print_ip(const Tuple<Args...>& tup) {
	print_tuple<0, Args...>(tup);
}
