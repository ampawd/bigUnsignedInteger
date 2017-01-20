/**
 * Copyright 2015 (c)
 * Big unsinged integer class
 * @author Aram Gevorgyan
 * @version 1.0
 */


#ifndef _BIG_UINT
#define _BIG_UINT

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cassert>

#ifdef __linux__
	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
#endif



namespace _BIG_UINT_AG
{
	#define MAX_SIZE 2000
	#define BASE 1000000000
	#define DIGIT_SIZE 9				
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

			friend Big_uint& operator += (Big_uint&, const Big_uint&);		
			friend Big_uint& operator -= (Big_uint&, const Big_uint&);

			Big_uint& operator ++ ();		
			Big_uint& operator -- ();

			Big_uint operator ++ (int);		
			Big_uint operator -- (int);

			friend Big_uint karatsuba_mul(const Big_uint&, const Big_uint&);
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

			Big_uint sqrt_newthon();
			Big_uint sqrt_bin();
			Big_uint pow_bin(unsigned long long);
			size_t length;

			void print(std::ofstream&);	//	ouput to a file
			void print();				//	output to standtard stream
	};

};




#endif