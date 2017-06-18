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
#include <vector>
#include <algorithm>
#include <cassert>


#ifdef __linux__
	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
#endif


namespace AG
{
	#define THRESHOLD 50
	#define BASE_TYPE_MAX_LENGTH 20

	typedef long long bui_digit;

	class Big_uint
	{
		private:
			
			static unsigned long BASE;
			static unsigned DIGIT_SIZE;
			static bui_digit T_square;

			std::vector< bui_digit > number;
			bui_digit& operator [] (size_t);
			void read_num_str(const std::string&);
			std::string num_str_ptr;
			size_t length;

		public:
			static void initNumSystem(unsigned long = 1000000000UL, unsigned = 9);

			void reserveDigitsRaw(size_t);			//	let user specify size of the number

			Big_uint(const std::string& = "0");
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
			size_t getLength() const;

			void print(std::ofstream&);	//	ouput to a file
			void print();				//	output to standtard stream
	};

};




#endif