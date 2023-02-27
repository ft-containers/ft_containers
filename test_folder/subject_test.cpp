#include <iostream>
#include <string>
#include <deque>

// for std
#include <map>
#include <stack>
#include <vector>
// for ft
#include "../map.hpp"
#include "../stack.hpp"
#include "../vector.hpp"

#include <stdlib.h>
#include <sys/time.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

int main(int argc, char** argv) 
{
	time_t ft_time;
	time_t std_time;

	// ft
	{
		time_t start, end, diff;
		start = get_time();
		if (argc != 2)
		{
			std::cerr << "Usage: ./test seed" << std::endl;
			std::cerr << "Provide a seed please" << std::endl;
			std::cerr << "Count value:" << COUNT << std::endl;
			return 1;
		}
		const int seed = atoi(argv[1]);
		srand(seed);

		ft::vector<std::string> vector_str;
		ft::vector<int> vector_int;
		ft::stack<int> stack_int;
		ft::vector<Buffer> vector_buffer;
		ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
		ft::map<int, int> map_int;

		for (int i = 0; i < COUNT; i++)
		{
			vector_buffer.push_back(Buffer());
		}

		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer[idx].idx = 5;
		}
		ft::vector<Buffer>().swap(vector_buffer);

		try
		{
			for (int i = 0; i < COUNT; i++)
			{
				const int idx = rand() % COUNT;
				vector_buffer.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
			}
		}
		catch(const std::exception& e)
		{
			//NORMAL ! :P
		}
		
		for (int i = 0; i < COUNT; ++i)
		{
			map_int.insert(ft::make_pair(rand(), rand()));
		}

		int sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			int access = rand();
			sum += map_int[access];
		}
		std::cout << "should be constant with the same seed: " << sum << std::endl;

		{
			ft::map<int, int> copy = map_int;
		}
		MutantStack<char> iterable_stack;
		for (char letter = 'a'; letter <= 'z'; letter++)
			iterable_stack.push(letter);
		for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		{
			std::cout << *it;
		}
		
		end = get_time();
		ft_time = diff = end - start;
		std::cout << "\nspend time (ft) : " << diff << std::endl;
		std::cout << "===========================================" << std::endl;
	
	}

	// std
	{
		time_t start, end, diff;
		start = get_time();
		if (argc != 2)
		{
			std::cerr << "Usage: ./test seed" << std::endl;
			std::cerr << "Provide a seed please" << std::endl;
			std::cerr << "Count value:" << COUNT << std::endl;
			return 1;
		}
		const int seed = atoi(argv[1]);
		srand(seed);

		std::vector<std::string> vector_str;
		std::vector<int> vector_int;
		std::stack<int> stack_int;
		std::vector<Buffer> vector_buffer;
		std::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
		std::map<int, int> map_int;

		for (int i = 0; i < COUNT; i++)
		{
			vector_buffer.push_back(Buffer());
		}

		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer[idx].idx = 5;
		}
		std::vector<Buffer>().swap(vector_buffer);

		try
		{
			for (int i = 0; i < COUNT; i++)
			{
				const int idx = rand() % COUNT;
				vector_buffer.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
			}
		}
		catch(const std::exception& e)
		{
			//NORMAL ! :P
		}
		
		for (int i = 0; i < COUNT; ++i)
		{
			map_int.insert(std::make_pair(rand(), rand()));
		}

		int sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			int access = rand();
			sum += map_int[access];
		}
		std::cout << "should be constant with the same seed: " << sum << std::endl;

		{
			std::map<int, int> copy = map_int;
		}
		MutantStack<char> iterable_stack;
		for (char letter = 'a'; letter <= 'z'; letter++)
			iterable_stack.push(letter);
		for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		{
			std::cout << *it;
		}
		end = get_time();
		std_time = diff = end - start;
		std::cout << "\nspend time (std) : " << diff << std::endl;
	}
	if (std_time * 20 > ft_time)
		std::cout << "***************OK****************" << std::endl;
	else
		std::cout << ".....KO.....o<-<" << std::endl;

	return (0);
}
