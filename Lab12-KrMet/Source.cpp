#include <iostream>
#include "Header.h"

BigNumberOperations num_2("2", 10), num_3("3", 10), num_5("5", 10), num_0("0", 10), num_1("1", 10);

using namespace std;

BigNumberOperations degreeRemainder2(BigNumberOperations a, BigNumberOperations degree, BigNumberOperations div) {
	a %= div;
	if (degree != num_0) {
		BigNumberOperations buf = degree % num_2;
		if (buf == num_0) {
			BigNumberOperations temp_a = degreeRemainder2(a, degree / num_2, div);
			buf = temp_a;
			buf *= temp_a;
			buf %= div;
			return buf;
		}
		else {
			BigNumberOperations temp_a = degreeRemainder2(a, (degree - num_1) / num_2, div);
			buf = temp_a;
			buf *= temp_a;
			buf %= div;
			buf *= a;
			buf %= div;
			return buf;
		}
	}
	else {
		return num_1;
	}
}
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "RUS"); 
	BigNumberOperations Big;
	long long int T;
	string buf_str;
	cout << "Enter an odd number: " << endl;
	while(true) {
		while (true) {
			BigNumberOperations cin_buf;
			cin >> buf_str;
			cin_buf.create(buf_str, 10);
			Big = cin_buf;
			if (!Big.get_work()) {
				cout << "Incorrect input. Enter again:" << endl;
			}
			else break;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if (Big == num_2 || Big == num_3) {
			cout << "The number is simple." << endl;
			system("pause");
			return 0;
		}
		if (Big < num_5 || Big % num_2 == num_0) {
			cout << "Incorrect input. Enter again:" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else break;
	}
	cout << "Enter the number of iterations: " << endl;
	cin >> T;
	long long int s = 0;
	BigNumberOperations r, u, v, buf;
	r = Big - num_1;
	while (r % num_2 == num_0)
	{
		r /= num_2;
		s += 1;
	}
	cout << Big << " representable as: 2^" << s << " * " << r << " + 1" << endl;

	for (int i = 0; i < T; ++i) {
		while (true) {
			u = Big.rand_max();
			if (u > num_1 && u < Big - num_2)
			{
				cout << "U: " << u << endl;
				break;
			}
		}
		v = degreeRemainder2(u, r, Big);
		cout << "V: " << v << endl;
		if (v == num_1 || v == Big - num_1) {
			continue;
		}
		for (int j = 1; j < s; ++j) {
			v = degreeRemainder2(v, num_2, Big);

			if (v == num_1) {
				cout << "Number " << Big << " is composite." << endl;
				system("pause");
				return 0;
			}
			if (v == Big - num_1)
				break;
		}
		if (v != Big - num_1) {
			cout << "Number " << Big << " is composite." << endl;
			system("pause");
			return 0;
		}
	}
	cout << "Number " << Big << " is probably simple." << endl;
	system("pause");
	return 0;
}
