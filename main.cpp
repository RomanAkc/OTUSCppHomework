#include <iostream>
#include <map>

#include "additional_func.h"
#include "MyAllocator.h"
#include "MyContainer.h"

using MyCustomAllocator = MyAllocator<std::pair<const int, int>, 10>;

int main(int, char **) {
	const int cntValues = 9;

	std::map<int, int> standartMap;
	fillMapFact(standartMap, cntValues);
	printMap(standartMap);

	std::map<int, int, std::less<int>, MyCustomAllocator> myMap;
	fillMapFact(myMap, cntValues);
	printMap(myMap);

	MyContainer<int> myCont;
	fillCont(myCont, cntValues);
	printMyCont(myCont);

	MyContainer<int, MyAllocator<int, 10>> myContWithMyAlloc;
	fillCont(myContWithMyAlloc, cntValues);
	printMyCont(myContWithMyAlloc);

	return 0;
}
