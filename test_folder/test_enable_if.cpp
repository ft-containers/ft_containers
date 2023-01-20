#include <iostream>
#include <type_traits>
#include <vector>

#include "../utils.hpp"

class A {};

template <typename T,
          typename = typename ft::enable_if<std::is_integral<T>::value>::type>
void test(const T& t) {
  std::cout << "t : " << t << std::endl;
}

int main() {
	A a;
	test(1);      // int
	test(false);  // bool
	test('c');    // char
	// test(a);    // class A
	/* result
	t : 1
	t : 0
	t : c
	*/
}

// class vector {
//  public:
//   vector(size_t num, const T& element) {
//     std::cout << element << " 를 " << num << " 개 만들기" << std::endl;
//   }

//   template <typename Iterator>
//   vector(Iterator start, Iterator end) {
//     std::cout << "반복자를 이용한 생성자 호출" << std::endl;
//   }
// };


// int main() { vector<int> v(10, 3); }
// ---------------------- enable_if---------------------