#include "../stack.hpp"
#include <deque>
#include <stack>
#include <vector>
#include <iostream>

#include "../containers_test/srcs/stack/common.hpp"

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define t_stack_ TESTED_NAMESPACE::stack<TESTED_TYPE>
typedef t_stack_::container_type container_type;

template <class T_STACK>
void	cmp(const T_STACK &lhs, const T_STACK &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) /* << " | ne: " << (lhs != rhs) */ << std::endl;
	// std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	// std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{
	container_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	t_stack_	stck(ctnr);
	t_stack_	stck2(ctnr);

	cmp(stck, stck);  // 0
	// cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
	return (0);
}

// ############### [0] ###############
// eq: 1 | ne: 0
// lt: 0 | le: 1
// gt: 0 | ge: 1
// ############### [1] ###############
// eq: 1 | ne: 0
// lt: 0 | le: 1
// gt: 0 | ge: 1
// ############### [2] ###############
// eq: 0 | ne: 1
// lt: 1 | le: 1
// gt: 0 | ge: 0
// ############### [3] ###############
// eq: 0 | ne: 1
// lt: 0 | le: 0
// gt: 1 | ge: 1
// ############### [4] ###############
// eq: 0 | ne: 1
// lt: 1 | le: 1
// gt: 0 | ge: 0
// ############### [5] ###############
// eq: 0 | ne: 1
// lt: 0 | le: 0
// gt: 1 | ge: 1
// ############### [6] ###############
// eq: 0 | ne: 1
// lt: 1 | le: 1
// gt: 0 | ge: 0
// ############### [7] ###############
// eq: 0 | ne: 1
// lt: 0 | le: 0
// gt: 1 | ge: 1
