#include "big_uint.h"

namespace _BIG_UINT_AG 
{
	void Big_uint::read_num_str(std::string& num_str)
	{
		int l = num_str.length(), pos = 0, start;
		for (int i = 0; i < l; i += DIGIT_SIZE)
		{		
			start = l-i-DIGIT_SIZE;
			if (start < 0)
				start = 0;
			number[pos++] = atoi(num_str.substr(start, l-start-i).c_str());
		}	
		length = pos;
		num_str_ptr = num_str;
	}

	Big_uint::Big_uint(std::string num_str)
	{
		memset(number, 0, MAX_SIZE*sizeof(bui_digit));
		read_num_str(num_str);	
	}

	Big_uint::Big_uint(const bui_digit& num)
	{	
		memset(number, 0, MAX_SIZE*sizeof(bui_digit));
		char buff[BASE_TYPE_MAX_LENGTH + 1];

		#ifdef __linux__
			snprintf(buff, sizeof(buff), "%lld", num);
		#elif defined(_WIN32) || defined(WIN32)
			_itoa_s(static_cast<int>(num), buff, 10);
		#endif

		std::string s = buff;
		read_num_str(s);	
	}

	Big_uint operator + (const Big_uint& left, const Big_uint& right)
	{
		Big_uint res;
		bui_digit carry = 0; size_t i = 0, l = std::max(left.length, right.length);
		for (i = 0; i < l || carry; i++)
		{			
			res[i] = left.number[i] + right.number[i] + carry;
			carry = res[i] / BASE;
			res[i] -= BASE*carry;		
		}

		res.length = i;
		return res;
	}

	//  left >= right
	Big_uint operator - (const Big_uint& left, const Big_uint& right)
	{
		assert(left >= right);
		Big_uint res;
		bui_digit carry = 0; size_t i = 0, l = left.length;
		for (i = 0; i < l; i++)
		{
			res[i] = left.number[i] - right.number[i] + carry;
			if (res[i] < 0)
			{		
				res[i] += BASE;
				carry = -1;
			}
			else 
			{
				carry = 0;
			}		
		}
	
		while (i > 1 && res.number[i-1] == 0)
		{
			--i;
		}

		res.length = i;
		return res;
	}

	Big_uint& operator += (Big_uint& left, const Big_uint& right) 
	{
		left = left + right;
		return left;
	}

	Big_uint& operator -= (Big_uint& left, const Big_uint& right)
	{
		assert(left >= right);
		left = left - right;
		return left;
	}

	Big_uint& Big_uint::operator ++ ()
	{
		*this = *this + 1;
		return *this;
	}	

	Big_uint& Big_uint::operator -- ()
	{
		assert(*this > 0);
		*this = *this - 1;
		return *this;
	}

	Big_uint Big_uint::operator ++ (int)
	{
		Big_uint t = *this;
		++*this;
		return t;
	}

	Big_uint Big_uint::operator -- (int)
	{
		Big_uint t = *this;
		--*this;
		return t;
	}

	//	untested
	Big_uint karatsuba_mul(const Big_uint& x, const Big_uint& y) 
	{
		int n = x.num_str_ptr.length(),
				m = y.num_str_ptr.length();

		if (std::max(n, m) < _THRESHOLD)
		{
			return x * y;
		}
		else 
		{
			std::string as="", bs="", cs="", ds="";
	
			as = x.num_str_ptr.substr(0, n - DIGIT_SIZE <= 0 ? 0 : n - DIGIT_SIZE);
			bs = x.num_str_ptr.substr(n - DIGIT_SIZE <= 0 ? 0 : n - DIGIT_SIZE, n);

			cs = y.num_str_ptr.substr(0, m - DIGIT_SIZE <= 0 ? 0 : m - DIGIT_SIZE);
			ds = y.num_str_ptr.substr(m - DIGIT_SIZE <= 0 ? 0 : m - DIGIT_SIZE, m);

			Big_uint a = as.empty() ? "0" : as, 
					b = bs.empty() ? "0" : bs,
					c = cs.empty() ? "0" : cs,
					d = ds.empty() ? "0" : ds;

			Big_uint ac = karatsuba_mul(a, c);
			Big_uint bd = karatsuba_mul(b, d);
			Big_uint z = karatsuba_mul(a + b, c + d);

			return ac*T_square + T*(z - (ac + bd)) + bd;
		}
	}

	Big_uint operator * (const Big_uint& left, const Big_uint& right)
	{	
		Big_uint res;
		bui_digit carry = 0; size_t i = 0, j = 0;
		for (i = 0; i < left.length; i++)
		{
			carry = 0;
			for (j = 0; j < right.length || carry; j++)
			{			
				res.number[i+j] += left.number[i] * right.number[j] + carry; 			
				carry = res.number[i+j] / BASE; 
				res.number[i+j] -= BASE*carry;
			}
		}
		res.length = left.length + right.length;
		while (res.length > 1 && res.number[res.length-1] == 0)
			res.length--;
		return res;
	}

	Big_uint operator * (const Big_uint& left, const bui_digit& right)
	{
		Big_uint res;
		bui_digit carry = 0; size_t l = 0;
		for (size_t i = 0; i < left.length || carry; i++, l++)
		{
			res[l] = left.number[i] * right + carry;
			carry = res[l] / BASE;
			res[l] -= carry*BASE;
		}
		res.length = l;
		return res;
	}

	// left >= right
	Big_uint operator / (const Big_uint& left, const bui_digit& right)
	{
		//assert(left >= right);
		if (right == 0)
			throw std::overflow_error("division by zero");
	
		Big_uint res;
		res.length = left.length;
		bui_digit left_part = 0, r = 0, q = 0;
		int i=0;
		for (i = (int)left.length-1; i >= 0; i--)
		{
			left_part = r*BASE + left.number[i];
			q = left_part / right;
			res.number[i] = q;
			r = left_part - q*right;		
		}
	
		i = res.length;
		while (i > 1 && res.number[i-1] == 0)
		{		
			i--;
		}
		res.length = i;
		return res;
	}

	//left >= right
	//	untested
	Big_uint operator / (const Big_uint& left, const Big_uint& right)
	{
		assert(left >= right);
		if (right == 0)
			throw std::overflow_error("division by zero");
	
		Big_uint res;
		res.length = left.length;
		bui_digit mid, q, low = 0, high = BASE;	
		Big_uint left_part = left, r=0;
		int i = 0;
		for (i = (int)left.length-1; i >= 0; --i, q = 0, low = 0, high = BASE)
		{
			left_part = r*BASE + left.number[i];
			while (low <= high)
			{
				mid = (low + high) >> 1;
				if ( right*mid < left_part )
				{
					low = mid+1;
					q = mid;
				}
				else high = mid-1;					
			}

			res.number[i] = q;
			r = left_part - right*q;		
		}

		i = res.length;
		while (i > 1 && res.number[i-1] == 0)
		{		
			i--;
		}
		res.length = i;
		return res;
	}

	bool operator < (const Big_uint& left, const Big_uint& right)
	{
		if (left.length < right.length)
		{
			return true;
		}
		else
		{
			if (left.length > right.length)
				return false;
			for (int i = left.length-1; i >= 0; --i)
			{			
				if (left.number[i] != right.number[i])
				{
					return (left.number[i] < right.number[i]);
				}
			}
			return false;
		}
	}

	bool operator > (const Big_uint& left, const Big_uint& right)
	{
		return !(left < right) && !(left == right);
	}

	bool operator == (const Big_uint& left, const Big_uint& right)
	{
		for (int i = (int)left.length-1; i >= 0; --i)
		{
			if (left.number[i] != right.number[i])		
				return false;		
		}
		return true;
	}

	bool operator != (const Big_uint& left, const Big_uint& right)
	{
		return !(left == right);
	}

	bool operator <= (const Big_uint& left, const Big_uint& right)
	{
		return left < right || left == right;
	}

	bool operator >= (const Big_uint& left, const Big_uint& right)
	{
		return left > right || left == right;
	}

	bui_digit& Big_uint::operator[](size_t at)
	{
		return number[at];
	}

	Big_uint Big_uint::sqrt_newthon()
	{
		Big_uint xn = *this/2;
		Big_uint xn1 = (xn + *this/xn) / 2;
		while (xn1 < xn)
		{
			xn = xn1;
			xn1 = (xn + *this/xn) / 2;
		}
		return xn1;
	}

	Big_uint Big_uint::sqrt_bin()
	{
		Big_uint lo("1"), hi = *this, mid;
		while (lo <= hi)
		{
			mid = lo + (hi - lo) / 2;
			if (*this < mid * mid)
			{
				hi = mid - 1;
			}
			else
			{
				lo = mid + 1;
			}
		}
		return lo - 1;
	}

	Big_uint Big_uint::pow_bin(unsigned long long n)
	{
		Big_uint res("1");
		Big_uint a = *this;
		while (n)
		{
			if (n & 1)
				res = res * a;

			a = a * a;
			n >>= 1;
		}
		return res;
	}

	std::ostream& operator << (std::ostream& os, const Big_uint& n)
	{
		os << n.number[n.length-1];
		for (int i = (int)n.length-2; i >= 0; i--)
		{
			os << std::setw(DIGIT_SIZE) 
			   << std::setfill('0')
			   << n.number[i];
		}
		return os;
	}

	std::istream& operator >> (std::istream& is, Big_uint& n)
	{
		std::string s; is >> s;
		for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
		{
			if (!isdigit((*it)) )
				throw("Invalid integer in input stream");
		}

		n = s;
		return is;
	}

	void Big_uint::print(std::ofstream& file) 
	{	
		for (int i = 0; i < (int)length; ++i)
		{
			file << number[length-i-1];
		}
	}

	void Big_uint::print()
	{
		printf("%lld", number[length-1]);
		for (int j = length - 2; j >= 0; j--)
			printf("%0*lld", DIGIT_SIZE, number[j]);
	}

};