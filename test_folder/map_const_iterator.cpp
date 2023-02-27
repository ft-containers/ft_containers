#include "../map.hpp"
#include <map>
#include <iostream>

int main()
{
    {
        std::map<char, int> m;
        m['a'] = 1;

        std::map<char, int>::const_iterator cit;
        cit = m.begin();

        // std::map<char, int>::iterator bit(cit);
		// ft::map<char, int>::iterator& iit = cit;

        std::map<char, int>::const_iterator cit2(cit);
        
        std::cout << "first : "<< cit2->first << std::endl;
        
    }
    std::cout << "===========================" << std::endl;
    {
        ft::map<char, int> m;
        m['a'] = 1;

        ft::map<char, int>::const_iterator cit;
        cit = m.begin();
        // cit(m.begin());

		// ft::map<char, int>::iterator& iit = cit; //<- it doesn't work,, why...?...uu

        ft::map<char, int>::const_iterator cit2(cit);
        
        std::cout << "first : "<< cit2->first << std::endl;
        
    }
}
