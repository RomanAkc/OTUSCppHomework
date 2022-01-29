#include <iostream>
#include <map>
#include <vector>

#include<MyAllocator.h>

int main(int, char **) {
	
	std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> myMap;

	for (int i = 0; i < 9; ++i) {
		myMap.insert({ i,i });
	}

	std::cout << "Hello, world!" << std::endl;
	return 0;
}
