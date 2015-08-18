#include <iostream>
#include "big_uint.h"
#include <time.h>



int main()
{
	clock_t start = clock();	
	_BIG_UINT_AG::Big_uint a, b;
	std::cin >> a >> b;
	std::cout << a + b;
	

	std::cout << '\n' << "run time = ";
	std::cout << (double) (clock() - start) / CLOCKS_PER_SEC;
	return 0;
}