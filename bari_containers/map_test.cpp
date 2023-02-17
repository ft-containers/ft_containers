#include "containers/map/map.hpp"

#include <map>
#include <iomanip>
#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
	std::cout << first1->second << ", " << last1->second << ", "
				<< first2->second << ", " << last2->second << std::endl;
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		std::cout << first1->second << ", " << last1->second << ", "
				<< first2->second << ", " << last2->second << std::endl;
        if (first1->first != first2->first || first1->second != first2->second)
		{
			std::cout << "false!"<< std::endl;
		std::cout << first1->second << ", " << last1->second << ", " << first2->second << ", " << last2->second << std::endl;
            return false;
		}
	}
    return true;
}

int main()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method "
              << "] --------------------]\t\t\033[0m\n";
    {
        bool cond(false);
        // {
        //     time_t start, end, diff;
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m1;
        //     ft::map<int, std::string> ft_m1;

        //     for (size_t i = 0; i < 1e6; i++)
        //         m1.insert(std::make_pair(i, "string2"));
        //     diff = end - start;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::maps ---------------------*/
        //     for (size_t i = 0; i < 1e6; i++)
        //         ft_m1.insert(ft::make_pair(i, "string2"));

        //     /*----------------------------------------------------*/
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m_range;
        //     ft::map<int, std::string> ft_m_range;

        //     m_range.insert(m1.begin(), m1.end());
        //     diff = end - start;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::maps ---------------------*/
        //     ft_m_range.insert(ft_m1.begin(), ft_m1.end());
        //     /*----------------------------------------------------*/
        // }

        // {
        //     time_t start, end, diff;
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m1;
        //     ft::map<int, std::string> ft_m1;

        //     m1.insert(std::make_pair(1e9, "string2"));
        //     diff = end - start;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::maps ---------------------*/
        //     ft_m1.insert(ft::make_pair(1e9, "string2"));
        //     /*----------------------------------------------------*/
        // }

        std::map<char, int> m;
        ft::map<char, int> ft_m;

        cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();
	    std::cout << cond << "------0----" << std::endl;

        // first insert function version (single parameter):
        m.insert(std::pair<char, int>('a', 100));
        m.insert(std::pair<char, int>('z', 200));

        ft_m.insert(ft::pair<char, int>('a', 100));
        ft_m.insert(ft::pair<char, int>('z', 200));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

	    std::cout << cond << "------1----" << std::endl;

        std::pair<std::map<char, int>::iterator, bool> ret;
        ft::pair<ft::map<char, int>::iterator, bool> ft_ret;

        ret = m.insert(std::pair<char, int>('z', 500));
        ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

        cond = cond && ret.second == ft_ret.second;

	    std::cout << cond << "------2----" << std::endl;


        // second insert function version (with hint position):
        std::map<char, int>::iterator it = m.begin();
        ft::map<char, int>::iterator ft_it = ft_m.begin();
        m.insert(it, std::pair<char, int>('b', 300));
        m.insert(it, std::pair<char, int>('c', 400));
        std::cout << it->second << std::endl;
        ++it;
        std::cout << it->second << std::endl;
        ++it;
        std::cout << it->second << std::endl;
        ++it;
        std::cout << it->second << std::endl;


        ft_m.insert(ft_it, ft::pair<char, int>('b', 300));
        // ft_m.insert(ft::pair<char, int>('b', 300));
        ft_m.insert(ft_it, ft::pair<char, int>('c', 400));
        // ft_m.insert(ft::pair<char, int>('c', 400));
        std::cout << ft_it->second << std::endl;
        ++ft_it;
        std::cout << ft_it->second << std::endl;
        ++ft_it;
        std::cout << ft_it->second << std::endl;
        ++ft_it;
        std::cout << ft_it->second << std::endl;

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());


	    std::cout << cond << "------3----" << std::endl;

        // third insert function version (range insertion):
        std::map<char, int> anothermap;
        ft::map<char, int> ft_anothermap;
        anothermap.insert(m.begin(), m.find('c'));
        ft_anothermap.insert(ft_m.begin(), ft_m.find('c'));
        cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());
	    std::cout << cond << "------4----" << std::endl;
		std::cout << "std::" << anothermap.size() << std::endl;
		std::cout << "ft::" <<ft_anothermap.size() << std::endl;
		std::cout << "ft::" <<(++ft_anothermap.begin())->second << std::endl;
		std::cout << (anothermap.size() == ft_anothermap.size()) << std::endl;

        //cond = cond && compareMaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && compareMaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
	    std::cout << cond << "------5----" << std::endl;
		// std::cout << (ft_m.begin()->second) << std::endl;
		// std::cout << (m.begin()->second) << std::endl;
		// std::cout << (ft_m.end()->second) << std::endl;
		// std::cout << (m.end()->second) << std::endl;
        
		EQUAL(cond);
    }
}