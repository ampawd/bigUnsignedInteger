#include <iostream>
#include "./include/big_uint.h"

int main()
{
	_BIG_UINT_AG::Big_uint a("2");
	for (auto i = 2; i <= 25; i++)
		std::cout << a.pow_bin(i) << '\n';
	return 0;
}