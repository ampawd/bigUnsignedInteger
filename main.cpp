#include <iostream>
#include "big_uint.h"

int main()
{
	//_BIG_UINT_AG::Big_uint a="10000000000000000000000000000000000000000000000000000000000000000000000000",
	//					   b="20000000000000000000000000000000000000000000000000000000000000000000000000";
	//
	//std::cout << (a + b) / 2 << '\n';
	
	_BIG_UINT_AG::Big_uint a,
		b = "";


	std::cin >> a >> b;


	karatsuba_mul(a, b).print();

	return 0;
}