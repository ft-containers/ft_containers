#include "../containers_test/srcs/map/common.hpp"
#include <map>
#define T1 int
#define T2 int

int		main(void)
{
	TESTED_NAMESPACE::Map<T1, T2> const mp;
	TESTED_NAMESPACE::Map<T1, T2>::iterator it = mp.begin(); // <-- error expected

	(void)it;
	return (0);
}
