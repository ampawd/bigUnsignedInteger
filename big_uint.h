/**
 * Copyright 2015 (c)
 * Big unsinged integer class
 * @author Aram Gevorgyan
 * @version 1.0
 */


#ifndef _BIG_UINT
#define _BIG_UINT


#include <vector>
#include <string>
#include <fstream>
#include <cassert>


namespace _BIG_UINT_AG
{
	#define MAX_SIZE 150
	#define BASE 1000000000
	#define digit_size 9				
	#define BASE_TYPE_MAX_LENGTH 18
	#define _THRESHOLD 50

	typedef long long bui_digit;

	static const bui_digit T = BASE;
	static const bui_digit T_square = T*T;

	class Big_uint
	{
		private:
			bui_digit number[MAX_SIZE];
			bui_digit& operator [] (size_t);
			void read_num_str(std::string &);
			std::string num_str_ptr;

		public:
			Big_uint(std::string = "");
			Big_uint(const bui_digit&);

			friend Big_uint operator + (const Big_uint&, const Big_uint&);		
			friend Big_uint operator - (const Big_uint&, const Big_uint&);

			friend Big_uint karatsuba_mul(Big_uint&, Big_uint&);
			friend Big_uint operator * (const Big_uint&, const Big_uint&);
			friend Big_uint operator * (const Big_uint&, const bui_digit&);

			friend Big_uint operator / (const Big_uint&, const bui_digit&);
			friend Big_uint operator / (const Big_uint&, const Big_uint&);

			friend bool operator < (const Big_uint&, const Big_uint&);
			friend bool operator > (const Big_uint&, const Big_uint&); 
			friend bool operator == (const Big_uint&, const Big_uint&); 
			friend bool operator != (const Big_uint&, const Big_uint&); 
			friend bool operator <= (const Big_uint&, const Big_uint&); 
			friend bool operator >= (const Big_uint&, const Big_uint&); 

			friend std::ostream& operator << (std::ostream& os, const Big_uint&);
			friend std::istream& operator >> (std::istream& os, Big_uint&);

			Big_uint sqrt_1();
			Big_uint sqrt_2();
			size_t length;

			void print(std::ofstream&);
			void print();
	};

};




#endif