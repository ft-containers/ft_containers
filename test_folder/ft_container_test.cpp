#include "../vector.hpp"
#include <iostream>
#include <vector> 
#include <iomanip>


// using allocator

#include "../ft_containers-unit-test/sources/system/system_methods.ipp"
#include "../ft_containers-unit-test/sources/vector_tests/__service.ipp"

// int _test_passed_cnt = 0;

// using std::string;
// using std::cout;
// using std::endl;

// const std::string GREEN = "\x1B[1;32m";
// const std::string REDD = "\x1B[1;31m";
// const std::string YELLOW = "\x1B[1;33m";
// const std::string WHITE = "\x1B[1;39m";
// const std::string RESET = "\033[0m";

// void printElement(std::string t)
// {
// 	if (t == "OK")
// 	    t = GREEN + t + RESET;
// 	else if (t == "FAILED") t = REDD + t + RESET;
// 	cout << std::left << std::setw(30) << std::setfill(' ') << t;
// }

template <class T, class A>
int run_vector_allocator_unit_test(std::string test_name, void (func)(std::vector<T, A>))
{
    std::vector<T, A> my_vector();

    printElement(test_name);
    func(my_vector);
    if (_allocator_used) {
        printElement("OK");
        cout << endl;
        return (0);
    }
    else {
        printElement("FAILED");
        cout << endl;
        return (1);
    }
}


template <class T, class A>
void allocator_test(std::vector<T, A> vector)
{
    for (int i = 0; i < 10; ++i) {
        vector.push_back(i);
    }
};

int main()
{
    exit(run_vector_allocator_unit_test<int, Alloc<int> >("using allocator", allocator_test));
}