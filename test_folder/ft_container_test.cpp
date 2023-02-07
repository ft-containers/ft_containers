#include "../vector.hpp"
#include <iostream>
#include <vector> 
#include <iomanip>

int _ratio = 100;

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

int main()
{

    {
        std::vector<int> vector;
        std::vector<int> v;
        std::vector<int> tmp;
        tmp.assign(2600 * _ratio, 1);
        vector.assign(4200 * _ratio, 1);
        vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
        v.push_back(vector[3]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());

        std::unique_ptr<B> k2(new B(3));
        std::unique_ptr<B> k3(new B(4));
        std::unique_ptr<B> k4(new B(-1));
        std::vector<A> vv;
        std::vector<B*> v1;

        v1.push_back(&(*k2));
        v1.push_back(&(*k3));
        v1.push_back(&(*k4));
        try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
        catch (...)
        {
            v.push_back(vv.size());
            v.push_back(vv.capacity());
            std::cout << v.capacity() << std::endl;
            std::cout << v.size() << std::endl; 
        }
        std::cout << vv.capacity() << std::endl;
        std::cout << vv.size() << std::endl;
    }

    
    {
        ft::vector<int> vector;
        std::vector<int> v;
        ft::vector<int> tmp;
        tmp.assign(2600 * _ratio, 1);
        vector.assign(4200 * _ratio, 1);
        vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
        v.push_back(vector[3]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());

        std::unique_ptr<B> k2(new B(3));
        std::unique_ptr<B> k3(new B(4));
        std::unique_ptr<B> k4(new B(-1));
        ft::vector<A> vv;
        ft::vector<B*> v1;

        v1.push_back(&(*k2));
        v1.push_back(&(*k3));
        v1.push_back(&(*k4));
        try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
        catch (...)
        {
            v.push_back(vv.size());
            v.push_back(vv.capacity());
            std::cout << v.capacity() << std::endl;
            std::cout << v.size() << std::endl; 
        }
        std::cout << vv.capacity() << std::endl;
        std::cout << vv.size() << std::endl;
    }

    // {
    // std::vector<int> result, result_2;
    // std::vector<int> v_int1, v_int2, v_int3;	ft::vector<int> V_int1, V_int2, V_int3;
    // std::vector<std::string> v_str1, v_str2;			ft::vector<std::string> V_str1, V_str2;
    // v_int1.push_back(1);						V_int1.push_back(1);
    // v_int3.push_back(1);						V_int3.push_back(1);
    // v_str1.push_back("aa");						V_str1.push_back("aa");
    // v_str2.push_back("ab");						V_str2.push_back("ab");
    // result.push_back(v_int1 == v_int2);			result_2.push_back(V_int1 == V_int2);
    // v_int2.push_back(2);						V_int2.push_back(2);
    // result.push_back(v_int1 == v_int2);			result_2.push_back(V_int1 == V_int2);
    // result.push_back(v_int1 == v_int3);			result_2.push_back(V_int1 == V_int3);
    // result.push_back(v_str1 == v_str2);			result_2.push_back(V_str1 == V_str2);
    //     std::cout << (result == result_2) << std::endl;
    // }
    return 0;
}
