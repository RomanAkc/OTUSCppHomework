#pragma once
#include <iostream>

int fact(int p);

template<typename TMap>
void fillMapFact(TMap& dest, int cnt)
{
	for (int i = 0; i < cnt; ++i) {
		dest[i] = fact(i);
	}
}

template<typename TMap>
void printMap(const TMap& dest)
{
	for (auto& p : dest) {
		std::cout << p.first << " " << p.second << std::endl;
	}
}

template<typename TCont>
void fillMyCont(TCont& cont, int cnt) {
	for (int i = 0; i < cnt; ++i) {
		cont.push_back(i);
	}
}

template<typename TCont>
void printMyCont(TCont& cont)
{
	for (auto& obj : cont) {
		std::cout << obj << std::endl;
	}
}