#include "common.hpp"
#include <map>

#define T1 int
#define T2 int

int		main(void)
{
	std::map<T1, T2> const mp;
	std::map<T1, T2>::iterator it (mp.begin()); // <-- error expected

	(void)it;
	return (0);
}
