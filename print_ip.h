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

//Check tuple
/*
template <typename T, typename Tuple>
struct all_type_are_same;

template <typename T>
struct all_type_are_same<T, std::tuple<>> : std::false_type {};

template <typename T>
struct all_type_are_same<T, std::tuple<T>> : std::true_type {};

template <typename T, typename... Ts>
struct all_type_are_same<T, std::tuple<T, Ts...>> : all_type_are_same<T, std::tuple<Ts...>> {};

//template <typename Tuple>
//using tuple_types_are_same = typename all_type_are_same<std::tuple_element_t<0, Tuple>, Tuple>::type;

//template <typename T, typename Tuple>


template<typename Orig, typename Cur, typename... Rest>
struct is_same_recursive {
	static const bool value = std::is_same_v<Orig, Cur> && is_same_recursive<Cur, Rest...>;
};

template<typename Orig, typename Cur>
struct is_same_recursive<Orig, Cur> {
	static const bool value = std::is_same_v<Orig, Cur>;
};

template<typename Orig>
struct is_same_recursive<Orig> {
	static const bool value = true;
};


/*
template<typename Orig>
struct is_same_recursive<Orig> {
	static const bool value = true;
};

/*template<>
struct is_same_recursive<> {
	static const bool value = false;
};



template < template <typename...> typename Tuple
	, typename... Args
>
typename std::enable_if_t<
	std::is_same_v<Tuple<Args...>, std::tuple<Args...>> 
	//&& all_type_are_same<Args...>::type
	, void>
	print_ip(const Tuple<Args...>& tup) {
	std::cout << "This is tuple";
}


/*template < template <typename...> typename Tuple
	, typename... Args
>
typename std::enable_if_t<
	std::is_same_v<Tuple<Args...>, std::tuple<Args...>>
	, void>
print_ip(const Tuple<Args...>& tup) {
	std::cout << "This is tuple";
}

//std::tuple_element_t


//std::tuple_size<>



/*template <typename T, typename Tuple>
struct all_type_are_same;

template <typename T>
struct all_type_are_same<T, std::tuple<>> : std::true_type {};

template <typename T, typename U, typename... Ts>
struct all_type_are_same<T, std::tuple<U, Ts...>> : std::false_type {};

template <typename T, typename... Ts>
struct all_type_are_same<T, std::tuple<T, Ts...>> : all_type_are_same<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct all_type_are_same<T, std::tuple<T, Ts...>> : all_type_are_same<T, std::tuple<Ts...>> {};*/


/*
template< template <typename...> typename Tuple >
struct is_tuple_has_all_the_same_type {
	using bool value = typename all_type_are_same<Tuple>::type;
};


template< template <typename...> typename Tuple >
bool is_type_same_tuple(Tuple<Args...> tup) {
	return std::is_same_v<T, std::get<N>(tup)> && 
}

template<typename T, int N, typename Tuple>
bool is_type_same(T t, ) {
	return std::is_same_v<T, std::get<N>(tup)>&&
}

template <typename T>
bool is_type_same(T t, int n = 0) {
	return true;
}


template< template <typename...> typename Tuple >
struct is_tuple_has_all_the_same_type {
	using bool value = true;
};*/