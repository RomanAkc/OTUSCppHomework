#include <iostream>
#include <map>

#include "additional_func.h"
#include "MyAllocator.h"
#include "MyContainer.h"

using MyCustomAllocatorForMap = MyAllocator<std::pair<const int, int>, 10>;

int main(int, char **) {
	const int cntValues = 10;

	std::map<int, int> standartMap;
	fillMapFact(standartMap, cntValues);
	printMap(standartMap);

	std::map<int, int, std::less<int>, MyCustomAllocatorForMap> myMap;
	fillMapFact(myMap, cntValues);
	printMap(myMap);

	MyContainer<int> myCont;
	fillMyCont(myCont, cntValues);
	printMyCont(myCont);

	MyContainer<int, MyAllocator<int, 10>> myContWithMyAlloc;
	fillMyCont(myContWithMyAlloc, cntValues);
	printMyCont(myContWithMyAlloc);

	return 0;
}
