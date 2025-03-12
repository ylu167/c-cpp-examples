/********************************************************************************* 
* Arithmetic.cpp
* Implementation of performing arithmetic operations on arbitrarily large signed integers by using BigInterger ADT
*********************************************************************************/
#include <iostream>
#include "BigInteger.h"
#include "List.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		return 0;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	string s1, s2;
	fin >> s1 >> s2;
	fin.close();
	BigInteger A = BigInteger(s1);
	BigInteger B = BigInteger(s2);
	BigInteger C, D;
	fout << A << endl << endl;
	fout << B << endl << endl;
	C = A + B;
	fout << C << endl << endl;
	C = A - B;
	fout << C << endl << endl;
	C = A - A;
	fout << C << endl << endl;
	C = A * BigInteger("3");
	D = B * BigInteger("2");
	C = C - D;
	fout << C << endl << endl;
	C = A * B;
	fout << C << endl << endl;
	C = A * A;
	fout << C << endl << endl;
	C = B * B;
	fout << C << endl << endl;
	C = A * A * A * A * BigInteger("9");
	D = B * B * B * B * B * BigInteger("16");
	C = C + D;
	fout << C << endl << endl;
	fout.close();
	return 0;
}
