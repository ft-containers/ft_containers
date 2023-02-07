#include "../vector.hpp"
#include <iostream>
#include <vector> 
#include <iomanip>

int _ratio = 100;


int main()
{
    {
        std::vector<int> vector;
        std::vector<int> v;
        vector.assign(9900 * _ratio, 1);
        vector.resize(5000 * _ratio);
        vector.reserve(5000 * _ratio);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.resize(7000 * _ratio);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.resize(15300 * _ratio, int());
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        v.push_back(vector[65]);
    }
   
    {
        ft::vector<int> vector;
        std::vector<int> v;
        vector.assign(9900 * _ratio, 1);
        vector.resize(5000 * _ratio);
        vector.reserve(5000 * _ratio);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.resize(7000 * _ratio);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.resize(15300 * _ratio, int());
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        v.push_back(vector[65]);
    }

    return 0;
}