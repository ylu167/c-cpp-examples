/********************************************************************************* 
* BigInteger.cpp
* Implementation file for BigInteger ADT
*********************************************************************************/
#include "BigInteger.h"

ListElement base = 1000000000;
int power = 9; 

BigInteger::BigInteger()
{
	signum = 0;
}

BigInteger::BigInteger(std::string s)
{
	signum = 1;
	int i = 0, j =0;
	int p = 0;
	ListElement t = 0, tmp = 0;
	for(i = s.size() - 1; i >= 0; i--)
	{
		if(s[i] >= '0' && s[i] <= '9')
		{
			if (p > 0)
			{
				tmp = (s[i] - '0');
				for (j = 0; j < p; j++)
				{
					tmp *= 10;
				}
				t = tmp + t;
			}
			else
			{
				t = (s[i] - '0');
			}
			p++;
			if(p >= power)
			{
				digits.insertBefore(t);
				p = 0;
				t = 0;
			}		
		}
		else
		{
			if(s[i] == '+' && i == 0)
			{
				signum = 1;
			}
			else if(s[i] == '-' && i == 0)
			{
				signum = -1;
			}
			else
			{
				throw std::invalid_argument("non-numeric string");
			}
		}
	}
	if(t > 0)
	{
		digits.insertBefore(t);
	}
	if (digits.length() <= 0)
	{
		throw std::invalid_argument("non-numeric string");
	}
}

BigInteger::BigInteger(const BigInteger& N)
{
	signum = N.signum;
	List ls = N.digits;
	int i = 0;
	ls.moveFront();
	while(i < ls.length())
	{
		digits.insertAfter(ls.moveNext());
		i++;
	}
}

int BigInteger::sign() const
{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const
{
	if(*this < N)
	{
		return -1;
	}
	else if(*this == N)
	{
		return 0;
	}
	return 1;
}

void BigInteger::makeZero()
{
	signum = 0;
	digits.clear();
}

void BigInteger::negate()
{
	if(signum == 1)
	{
		signum = -1;
	}
	else if(signum == -1)
	{
		signum = 1;
	}
}

BigInteger BigInteger::BigInteger::add(const BigInteger& N) const
{
	return *this + N;
}

BigInteger BigInteger::sub(const BigInteger& N) const
{
	return *this - N;
}

BigInteger BigInteger::mult(const BigInteger& N) const
{
	return *this * N;
}

std::string BigInteger::to_string()
{
	std::string s;
	if(signum == 0)
	{
		return "0";
	}
	int idx = 0;
	digits.moveFront();
	//std::cout << digits << std::endl;
	while (idx < digits.length())
	{
		if (idx == 0)
		{
			s.append(std::to_string(digits.moveNext()));
		}
		else
		{
			std::string ostr = std::to_string(digits.moveNext());
			std::string str = std::string(power - ostr.length(), '0') + ostr;
			s.append(str);
		}
		idx++;
	}
	int len = 0;
	while(s[len] == '0')
	{
		len++;
	}
	if(len > 0)
	{
		s = s.substr(len);
	}
	if(signum == -1)
	{
		s = "-" + s;
	}
	return s;
}


std::ostream& operator<<( std::ostream& stream, BigInteger N )
{
	stream << N.to_string();
	return stream;
}

   // operator==()
   // Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B )
{
	if(A.signum == B.signum && A.digits.length() == B.digits.length())
	{
		if(A.digits == B.digits)
		{
			return true;
		}
	}
	return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B )
{
	if(A.signum < B.signum)
	{
		return true;
	}
	else if(A.signum > B.signum)
	{
		return false;
	}
	List lsa = A.digits;
	List lsb = B.digits;
	
	if(lsa.length() != lsb.length())
	{
		if(A.signum < 0)
		{
			return lsa.length() < lsb.length() ? false:true;
		}
		else
		{
			return lsa.length() < lsb.length() ? true:false;
		}
	}
	lsa.moveBack();
	lsb.moveBack();
	ListElement t1;
	ListElement t2;
	int idx =0;
	while(idx < lsa.length())
	{
		t1 = lsa.movePrev();
		t2 = lsb.movePrev();
		if(t1 != t2)
		{
			if(A.signum < 0)
			{
				return t1 < t2?false:true;
			}
			else
			{
				return t1 < t2?true:false;
			}
		}
		idx++;
	}
	return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B )
{
	if(A == B)
	{
		return true;
	}
	if(A < B)
	{
		return true;
	}
	return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B )
{
	if(A <= B)
	{
		return false;
	}
	return true;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B )
{
	if(A < B)
	{
		return false;
	}
	return true;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B )
{
	BigInteger res;
	if(A.signum == B.signum)
	{
		res.signum = A.signum;
	}
	else
	{
		if(A.signum > 0)
		{
			res = B;
			// std::cout << res << std::endl;
			// std::cout << B << std::endl;
			res.signum = 1;
			return A - res;
		}
		else
		{
			res = A;
			res.signum = 1;
			return B - res;
		}
	}
	List lsa = A.digits;
	List lsb = B.digits;
	lsa.moveFront();
	lsb.moveFront();
	int idx = 0;
	int flag = 0;
	while (idx < lsa.length() || idx < lsb.length())
	{
		ListElement ta = 0;
		ListElement tb = 0;
		if (idx < lsa.length())
		{
			ta = lsa.moveNext();
		}
		if (idx < lsb.length())
		{
			tb = lsb.moveNext();
		}
		ListElement tc = ta + tb + flag;
		flag = tc / base;
		tc = tc % base;
		res.digits.insertAfter(tc);
		idx++;
	}
	if (flag > 0)
	{
		res.digits.insertAfter(flag);
	}
	return res;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B )
{
	A = A + B;
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B )
{
	BigInteger res;
	if (A == B)
	{
		return res;
	}
	if (A.signum != B.signum)
	{
		res = B;
		res.signum = A.signum;
		return A + res;
	}
	List lsa = A.digits;
	List lsb = B.digits;
	if (A > B)
	{
		if (A.signum == 1)
		{
			res.signum = 1;
		}
		else
		{
			res.signum = 1;
			lsb = A.digits;
			lsa = B.digits;
		}
	}
	else
	{
		if (A.signum == 1)
		{
			res.signum = -1;
			lsb = A.digits;
			lsa = B.digits;
		}
		else
		{
			res.signum = -1;
		}
	}
	lsa.moveFront();
	lsb.moveFront();
	int idx = 0;
	int flag = 0;
	while (idx < lsa.length() || idx < lsb.length())
	{
		ListElement ta = 0;
		ListElement tb = 0;
		if (idx < lsa.length())
		{
			ta = lsa.moveNext();
		}
		if (idx < lsb.length())
		{
			tb = lsb.moveNext();
		}
		ListElement tc = ta - tb + flag;
		flag = 0;
		while (tc < 0)
		{
			tc += base;
			flag--;
		}
		res.digits.insertAfter(tc);
		idx++;
	}
	while (res.digits.front() == 0)
	{
		res.digits.moveFront();
		res.digits.moveNext();
		res.digits.eraseBefore();
	}
	return res;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B )
{
	A = A - B;
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B )
{
	BigInteger res;
	if (A.signum == 0 || B.signum == 0)
	{
		return res;
	}
	if (A.signum == B.signum)
	{
		res.signum = 1;
	}
	else
	{
		res.signum = -1;
	}
	List lsa = A.digits;
	List lsb = B.digits;
	lsa.moveFront();
	int idxa = 0;
	int idxb = 0;
	int flag = 0;
	unsigned long* tmp = new unsigned long[lsa.length() + lsb.length()];
	int i = 0;
	for (i = 0; i < lsa.length() + lsb.length(); i++)
	{
		tmp[i] = 0;
	}
	while (idxa < lsa.length())
	{
		idxb = 0;
		lsb.moveFront();
		ListElement ta = lsa.moveNext();
		while (idxb < lsb.length())
		{
			ListElement tb = lsb.moveNext();
			//std::cout << "ta:" << ta << " tb:" << tb << std::endl;
			tmp[idxa + idxb] += ta * tb;
			//std::cout << "get " << tmp[idxa + idxb] << std::endl;
			idxb++;
		}
		idxa++;
		flag = 0;
		//std::cout << "start" << std::endl;
		for (i = 0; i < lsa.length() + lsb.length(); i++)
		{
			flag = tmp[i] / base;
			tmp[i] = tmp[i] % base;
			tmp[i + 1] += flag;
			//std::cout << tmp[i] <<  " ";
		}
		//std::cout << std::endl;
	}
	for (i = 0; i < lsa.length() + lsb.length(); i++)
	{
		res.digits.insertBefore(tmp[i]);
	}
	if (flag > 0)
	{
		res.digits.insertAfter(flag);
	}
	while (res.digits.back() == 0)
	{
		res.digits.moveBack();
		res.digits.movePrev();
		res.digits.eraseAfter();
	}
	delete tmp;
	return res;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B )
{
	A = A * B;
	return A;
}
