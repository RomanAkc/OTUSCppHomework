#pragma once

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