#include "ip_filter_lib.h"
#include <algorithm>
#include <iostream>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void reverseLexicographicallySort(IPPool& ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& lhs, const auto& rhs) {
        const int ipsize = 4;
        for (int i = 0; i < ipsize; ++i)
        {
            int lhs_num = std::stoi(lhs[i]);
            int rhs_num = std::stoi(rhs[i]);

            if (rhs_num == lhs_num)
                continue;

            return rhs_num < lhs_num;
        }

        return false;
    });
}

void outputIPPool(const IPPool& ip_pool)
{
    for (auto& ip : ip_pool)
    {
        bool first{ true };
        for (auto& ip_part : ip)
        {
            if (!first)
                std::cout << ".";
            else
                first = false;

            std::cout << ip_part;
        }
        std::cout << std::endl;
    }
}

IPPool filter(const IPPool& sorted_ip_pool, int first, int second /*= -1*/)
{
    IPPool result;
    std::copy_if(sorted_ip_pool.begin(), sorted_ip_pool.end()
        , std::back_inserter(result)
        , [first, second](const auto& ip) { 
            return std::stoi(ip.at(0)) == first
                && (second == -1 || std::stoi(ip.at(1)) == second);
        }
    );
    return result;
}

IPPool filter_any(const IPPool& sorted_ip_pool, int byte)
{
    IPPool result;
    std::copy_if(sorted_ip_pool.begin(), sorted_ip_pool.end()
        , std::back_inserter(result)
        , [byte](const auto& ip) {
            for (auto& part : ip)
            {
                if (std::stoi(part) == byte)
                    return true;
            }

            return false;
        }
    );
    return result;
}