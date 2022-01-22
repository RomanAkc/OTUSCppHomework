#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using IPPool = std::vector<std::vector<std::string>>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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

//reverse lexicographically sort
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

IPPool filter(const IPPool& sorted_ip_pool, int first, int second = -1)
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

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        reverseLexicographicallySort(ip_pool);
        outputIPPool(ip_pool);

        outputIPPool(filter(ip_pool, 1));
        outputIPPool(filter(ip_pool, 46, 70));
        outputIPPool(filter_any(ip_pool, 46));

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
