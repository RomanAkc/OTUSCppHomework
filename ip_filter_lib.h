#pragma once
#include <vector>
#include <string>

using IPPool = std::vector<std::vector<std::string>>;

std::vector<std::string> split(const std::string &str, char d);
void reverseLexicographicallySort(IPPool& ip_pool);
void outputIPPool(const IPPool& ip_pool);
IPPool filter(const IPPool& sorted_ip_pool, int first, int second = -1);
IPPool filter_any(const IPPool& sorted_ip_pool, int byte);