#include <iostream>
#include <deque> 
#include <vector> 
#include <string>
#include <math.h>
#include <algorithm>
#include <windows.h>
using namespace std;

class BigNumberOperations {
private:
	vector<int> BigNumber = {};
	bool Flag_minus = false; //false '+', true '-'
	int b = 10;
	bool Flag_work = false;
	void add(BigNumberOperations Big2) {
		vector<int> BigNumber_buf = {  };
		int min_n = min(BigNumber.size(), Big2.BigNumber.size());
		int c = 0, buf = 0;
		for (int i = 1; i <= min_n; i++) {
			buf = BigNumber[BigNumber.size() - i] + Big2.BigNumber[Big2.BigNumber.size() - i] + c;
			if (buf >= b) {
				c = 1;
				buf -= b;
			}
			else c = 0;
			BigNumber_buf.push_back(buf);
		}
		if (min_n == BigNumber.size()) {
			for (int i = min_n + 1; i <= Big2.BigNumber.size(); i++) {
				buf = Big2.BigNumber[Big2.BigNumber.size() - i] + c;
				if (buf >= b) {
					c = 1;
					buf -= b;
				}
				else c = 0;
				BigNumber_buf.push_back(buf);
			}
		}
		else {
			for (int i = min_n + 1; i <= BigNumber.size(); i++) {
				buf = BigNumber[BigNumber.size() - i] + c;
				if (buf >= b) {
					c = 1;
					buf -= b;
				}
				else c = 0;
				BigNumber_buf.push_back(buf);
			}
		}
		if (c == 1)BigNumber_buf.push_back(1);
		reverse(BigNumber_buf.begin(), BigNumber_buf.end());
		while (true) {
			if (BigNumber[0] == 0 && BigNumber.size() > 1) {
				BigNumber.erase(BigNumber.begin());
			}
			else break;
		}
		BigNumber = BigNumber_buf;
	}
	int compare(BigNumberOperations Big2) { //1 |this|>|Big2|, 2 |this| < |Big2|, 3 |this| = |Big2|
		if (BigNumber.size() > Big2.BigNumber.size()) {
			return 1;
		}
		if (BigNumber.size() < Big2.BigNumber.size()) {
			return 2;
		}
		for (int i = 0; i < BigNumber.size(); i++) {
			if (BigNumber[i] > Big2.BigNumber[i]) {
				return 1;
			}
			if (BigNumber[i] < Big2.BigNumber[i]) {
				return 2;
			}
		}
		return 3;
	}
	int sub(BigNumberOperations Big2) {
		vector<int> BigNumber_buf = {  };
		int min_big = compare(Big2);
		int c = 0, buf = 0;
		int min_n = 0;
		switch (min_big) {
		case 1:
			min_n = Big2.BigNumber.size();
			for (int i = 1; i <= min_n; i++) {
				buf = BigNumber[BigNumber.size() - i] - Big2.BigNumber[Big2.BigNumber.size() - i] - c;
				if (buf < 0) {
					c = 1;
					buf += b;
				}
				else c = 0;
				BigNumber_buf.push_back(buf);
			}
			if (min_n != BigNumber.size()) {
				for (int i = min_n + 1; i < BigNumber.size(); i++) {
					buf = BigNumber[BigNumber.size() - i] - c;
					if (buf < 0) {
						c = 1;
						buf += b;
					}
					else c = 0;
					BigNumber_buf.push_back(buf);
				}
				buf = BigNumber[0] - c;
				if (buf != 0) {
					BigNumber_buf.push_back(buf);
				}
			}
			break;
		case 2:
			min_n = BigNumber.size();
			for (int i = 1; i <= min_n; i++) {
				buf = Big2.BigNumber[Big2.BigNumber.size() - i] - BigNumber[BigNumber.size() - i] - c;
				if (buf < 0) {
					c = 1;
					buf += b;
				}
				else c = 0;
				BigNumber_buf.push_back(buf);
			}
			if (min_n != Big2.BigNumber.size()) {
				for (int i = min_n + 1; i < Big2.BigNumber.size(); i++) {
					buf = Big2.BigNumber[Big2.BigNumber.size() - i] - c;
					if (buf < 0) {
						c = 1;
						buf += b;
					}
					else c = 0;
					BigNumber_buf.push_back(buf);
				}
				buf = Big2.BigNumber[0] - c;
				if (buf != 0) {
					BigNumber_buf.push_back(buf);
				}
			}
			break;
		case 3:
			BigNumber_buf = { 0 };
			break;
		}
		reverse(BigNumber_buf.begin(), BigNumber_buf.end());
		BigNumber = BigNumber_buf;
		while (true) {
			if (BigNumber[0] == 0 && BigNumber.size() > 1) {
				BigNumber.erase(BigNumber.begin());
			}
			else break;
		}
		return min_big;
	}
	void mult(BigNumberOperations Big2) {
		vector<int> BigNumber_buf = {  };
		int c = 0, buf = 0, k = BigNumber.size(), l = Big2.BigNumber.size();
		reverse(BigNumber.begin(), BigNumber.end());
		reverse(Big2.BigNumber.begin(), Big2.BigNumber.end());
		for (int i = 0; i < k + l; i++) {
			BigNumber_buf.push_back(0);
		}
		for (int i = 0; i < l; i++) {
			c = 0;
			for (int j = 0; j < k; j++) {
				buf = BigNumber_buf[i + j] + BigNumber[j] * Big2.BigNumber[i] + c;
				c = (buf - buf % b) / b;
				BigNumber_buf[i + j] = buf % b;
				BigNumber_buf[i + k] = c;
			}
		}
		reverse(BigNumber_buf.begin(), BigNumber_buf.end());
		while (true) {
			if (BigNumber_buf[0] == 0 && BigNumber_buf.size() > 1) {
				BigNumber_buf.erase(BigNumber_buf.begin());
			}
			else break;
		}
		BigNumber = BigNumber_buf;
	}
	vector<BigNumberOperations> div(BigNumberOperations Big2) {
		BigNumberOperations U, V;
		U = *this;
		V = Big2;
		U.Flag_minus = false;
		V.Flag_minus = false;
		BigNumberOperations Q, R, d, q, b_ik, vb_ik, qvb_ik, one;
		
		one.create("1", b);
		long long int k, l, step, bufq;
		d.create("" + to_string((b / (V.BigNumber[0] + 1))), b);

		q.b = b;
		q.Flag_work = true;
		Q = q;
		R = q;
		b_ik = q;
		U.mult(d);
		V.mult(d);

		k = V.BigNumber.size();
		l = U.BigNumber.size() - k + 1;
		U.BigNumber.insert(U.BigNumber.begin(), 0);

		for (int i = 0; i < l; i++) {
			bufq = min(((U.BigNumber[i] * b + U.BigNumber[i + 1]) / V.BigNumber[0]), b - 1);
			q.BigNumber.push_back(bufq);
			while (bufq * (V.BigNumber[0] * b + V.BigNumber[1]) > U.BigNumber[i] * b * b + U.BigNumber[i+1] * b + U.BigNumber[i+2])
			{
				bufq--;
				q -= one;
			}
			step = pow(b, l - i - 1);
			b_ik.BigNumber.push_back(1);
			while (step != 0) {
				if (step == 1)
					break;
				step /= b;
				b_ik.BigNumber.push_back(0);
			}
			vb_ik = V;
			vb_ik *= b_ik;
			qvb_ik = q;
			qvb_ik *= vb_ik;
			U.BigNumber.erase(U.BigNumber.begin());
			U -= qvb_ik;
			while (true) {
				if (U.Flag_minus) {
					q -= one;
					bufq--;
					while (true) {
						if (U.BigNumber[0] == 0 && U.BigNumber.size() > 1) {
							U.BigNumber.erase(U.BigNumber.begin());
						}
						else break;
					}
					U += vb_ik;
					while (true) {
						if (U.BigNumber.size() != (k + l - 1)) {
							U.BigNumber.insert(U.BigNumber.begin(), 0);
						}
						else break;
					}
				}
				else break;
			}
			while (true) {
				if (U.BigNumber.size() != (k + l)) {
					U.BigNumber.insert(U.BigNumber.begin(), 0);
				}
				else break;
			}
			Q.BigNumber.push_back(bufq);

			b_ik.BigNumber.clear();
			q.BigNumber.erase(q.BigNumber.begin());

		}
		q = Q;
		q *= Big2;
		q.Flag_minus = false;
		R = *this;
		R.Flag_minus = false;
		R -= q;
		while (true) {
			if (Q.BigNumber[0] == 0 && Q.BigNumber.size() > 1) {
				Q.BigNumber.erase(Q.BigNumber.begin());
			}
			else break;
		}

		while (true) {
			if (R.BigNumber[0] == 0 && R.BigNumber.size() > 1) {
				R.BigNumber.erase(R.BigNumber.begin());
			}
			else break;
		}
		return { Q, R };
	}
	vector<BigNumberOperations> div_1(int number_2) {
		BigNumberOperations U;
		U = *this;
		U.Flag_minus = false;
		if (number_2 <= 0 || number_2 >= b) {
			return { *this };
		}
		BigNumberOperations Q, R;
		Q.b = b;
		Q.Flag_work = true;
		R = Q;
		int buf, buf_q, buf_r, size = U.BigNumber.size();
		buf = U.BigNumber[0];
		buf_r = buf % number_2;
		buf_q = (buf - buf_r) / number_2;
		Q.BigNumber.push_back(buf_q);
		buf = buf_r;
		for (int i = 1; i < size; i++) {
			buf *= 10;
			buf += U.BigNumber[i];
			buf_r = buf % number_2;
			buf_q = (buf - buf_r) / number_2;
			Q.BigNumber.push_back(buf_q);
			buf = buf_r;
		}
		R.BigNumber.push_back(buf_r);
		while (true) {
			if (Q.BigNumber[0] == 0 && Q.BigNumber.size() > 1) {
				Q.BigNumber.erase(Q.BigNumber.begin());
			}
			else break;
		}
		while (true) {
			if (R.BigNumber[0] == 0 && R.BigNumber.size() > 1) {
				R.BigNumber.erase(R.BigNumber.begin());
			}
			else break;
		}
		return { Q, R };
	}
	vector<BigNumberOperations> div_operation(BigNumberOperations Big2) {
		//Sleep(1);
		vector <BigNumberOperations> Q_div_R_vec;
		BigNumberOperations Null_, one;
		Null_.Flag_work = true;
		Null_.b = b;
		one = Null_;
		Null_.BigNumber = { 0 };
		one.BigNumber = { 1 };
		if (Big2.BigNumber.size() == 1) {
			if (Big2.BigNumber[0] != 0) {
				Q_div_R_vec = div_1(Big2.BigNumber[0]);
			}
		}
		else if (BigNumber.size() < Big2.BigNumber.size()) {
			Q_div_R_vec = {Null_, *this };
			Q_div_R_vec[1].Flag_minus = false;
		}
		else
			Q_div_R_vec = div(Big2);
		Q_div_R_vec[1].Flag_minus = false;
		if (Q_div_R_vec.size() < 2) 
			return { *this, Null_ };
		while (true) {
			if (Q_div_R_vec[0].BigNumber[0] == 0 && Q_div_R_vec[0].BigNumber.size() > 1) {
				Q_div_R_vec[0].BigNumber.erase(Q_div_R_vec[0].BigNumber.begin());
			}
			else break;
		}

		if (!Flag_minus && !Big2.Flag_minus) {
			return { Q_div_R_vec[0], Q_div_R_vec[1] };
		}
		if (!Flag_minus && Big2.Flag_minus) {
			if(Q_div_R_vec[0].BigNumber[0] != 0)
				Q_div_R_vec[0].Flag_minus = true;
			return { Q_div_R_vec[0], Q_div_R_vec[1] };
		}
		if (Flag_minus && Big2.Flag_minus) {
			Q_div_R_vec[0] += one;
			Q_div_R_vec[1] += Big2;
			Q_div_R_vec[1].Flag_minus = false;
			return { Q_div_R_vec[0], Q_div_R_vec[1] };
		}
		if (Flag_minus && !Big2.Flag_minus) {
			Q_div_R_vec[0] += one;
			Q_div_R_vec[0].Flag_minus = true;
			Q_div_R_vec[1].Flag_minus = true;
			Q_div_R_vec[1] += Big2;
			return { Q_div_R_vec[0], Q_div_R_vec[1] };
		}
		return { Q_div_R_vec[0], Q_div_R_vec[1] };
	}
	int comparison(BigNumberOperations Big2) { //1 this>Big2, 2 this < Big2, 3 this = Big2
		if (Flag_minus != Big2.Flag_minus) {
			if (!Flag_minus)
				return 1;
			else
				return 2;
		}
		int comp = compare(Big2);
		if (!Flag_minus) {
			return comp;
		}
		else {
			if (comp == 1)
				return 2;
			if (comp == 2)
				return 1;
			return comp;
		}
	}
public:
	BigNumberOperations(){};
	BigNumberOperations(string number_, int b_);
	~BigNumberOperations();
	bool create(string number_, int b_);
	void operator=(BigNumberOperations Big);
	void operator+=(BigNumberOperations Big2);
	void operator-=(BigNumberOperations Big2);
	void operator*=(BigNumberOperations Big2);
	void operator/=(BigNumberOperations Big2);
	void operator%=(BigNumberOperations Big2);
	BigNumberOperations operator+(BigNumberOperations Big);
	BigNumberOperations operator-(BigNumberOperations Big);
	BigNumberOperations operator*(BigNumberOperations Big);
	BigNumberOperations operator/(BigNumberOperations Big);
	BigNumberOperations operator%(BigNumberOperations Big);
	bool operator>(BigNumberOperations Big2);
	bool operator<(BigNumberOperations Big2);
	bool operator==(BigNumberOperations Big2);
	bool operator>=(BigNumberOperations Big2);
	bool operator<=(BigNumberOperations Big2);
	bool operator!=(BigNumberOperations Big2);
	BigNumberOperations rand_max();
	vector<string> div_r(BigNumberOperations Big2);
	bool get_work() { return Flag_work; }
	int get_b() { return b; }
	string get_number() {
		if (!Flag_work)
			return "0";
		string str;
		for (int i = 0; i < BigNumber.size(); i++) {
			str += to_string(BigNumber[i]);
		}
		if (Flag_minus) return ("-" + str);
		else return (str);
	}
};
BigNumberOperations::BigNumberOperations(string number_, int b_) {
	create(number_, b_);
}

BigNumberOperations::~BigNumberOperations() {
}

inline void BigNumberOperations::operator=(BigNumberOperations Big)
{
	BigNumber = Big.BigNumber;
	Flag_minus = Big.Flag_minus;
	b = Big.b;
	Flag_work = Big.Flag_work;
}

inline void BigNumberOperations::operator+=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return;
	}
	if (Flag_minus && Big2.Flag_minus) {
		add(Big2);
		return;
	}
	if (!Flag_minus && !Big2.Flag_minus) {
		add(Big2);
		return;
	}
	int Flag_big = sub(Big2);
	if(Flag_big == 1) return;
	if (Flag_big == 2) {
		if (!Flag_minus && Big2.Flag_minus) {
			Flag_minus = true;
			return;
		}
		if (Flag_minus && !Big2.Flag_minus) {
			Flag_minus = false;
			return;
		}
	}
	if(Flag_big == 3)
		Flag_minus = false;
}

inline void BigNumberOperations::operator-=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return;
	}
	if (!Flag_minus && Big2.Flag_minus) {
		add(Big2);
		return;
	}
	if (Flag_minus && !Big2.Flag_minus) {
		add(Big2);
		return;
	}
	int Flag_big = sub(Big2);
	if (Flag_big == 1) return;
	if (Flag_big == 2) {
		if (!Flag_minus && !Big2.Flag_minus) {
			Flag_minus = true;
			return;
		}
		if (Flag_minus && Big2.Flag_minus) {
			Flag_minus = false;
			return;
		}
	}
	if (Flag_big == 3)
		Flag_minus = false;
}

inline void BigNumberOperations::operator*=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return;
	}
	if (BigNumber.size() == 1 && BigNumber[0] == 0 || Big2.BigNumber.size() == 1 && Big2.BigNumber[0] == 0) {
		BigNumber = { 0 };
		Flag_minus = false;
		return;
	}
	mult(Big2);
	if (Flag_minus == Big2.Flag_minus) {
		Flag_minus = false;
		return;
	}
	else Flag_minus = true;
}

inline void BigNumberOperations::operator/=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b || Big2.BigNumber[0] == 0) {
		return;
	}
	*this = div_operation(Big2)[0];
}

inline void BigNumberOperations::operator%=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b || Big2.BigNumber[0] == 0) {
		return;
	}
	*this = div_operation(Big2)[1];
}

inline vector<string> BigNumberOperations::div_r(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b || Big2.BigNumber[0] == 0) {
		return {"0", "0"};
	}
	vector<BigNumberOperations> Q_div_R_vec = div_operation(Big2);
	return { Q_div_R_vec[0].get_number(), Q_div_R_vec[1].get_number() };
}

inline bool BigNumberOperations::create(string number_, int b_)
{
	if (b_ <= 1 || b_ > 10) {
		Flag_work = false;
		return false;
	}
	b = b_;
	if (number_.size() == 0) {
		Flag_work = false;
		b = 10;
		return false;
	}
	if (number_.size() == 1 && number_[0] == '-') {
		Flag_work = false;
		b = 10;
		return false;
	}
	int buf_n;
	if (number_[0] == '-') {
		Flag_minus = true;
		number_.erase(0, 1);
	}
	Flag_work = true;
	for (int i = 0; i < number_.size(); i++) {
		if (!(isdigit(number_[i]))) {
			Flag_work = false;
		}
	}
	if (!Flag_work) {
		b = 10;
		Flag_minus = false;
		return false;
	}
	for (int i = 0; i < number_.size(); i++) {
		buf_n = number_[i] - '0';
		if (buf_n < b)
			BigNumber.push_back(buf_n);
		else {
			Flag_work = false;
		}
	}
	if (!Flag_work) {
		b = 10;
		Flag_minus = false;
		BigNumber.clear();
		BigNumber = { };
		return false;
	}
	else {
		while (true) {
			if (BigNumber[0] == 0 && BigNumber.size() > 1) {
				BigNumber.erase(BigNumber.begin());
			}
			else break;
		}
	}
	return true;
}

inline BigNumberOperations BigNumberOperations::operator+(BigNumberOperations Big)
{
	BigNumberOperations A = *this;
	A += Big;
	return A;
}
inline BigNumberOperations BigNumberOperations::operator-(BigNumberOperations Big)
{
	BigNumberOperations A = *this;
	A -= Big;
	return A;
}
inline BigNumberOperations BigNumberOperations::operator*(BigNumberOperations Big)
{
	BigNumberOperations A = *this;
	A *= Big;
	return A;
}
inline BigNumberOperations BigNumberOperations::operator/(BigNumberOperations Big)
{
	BigNumberOperations A = *this;
	A /= Big;
	return A;
}
inline BigNumberOperations BigNumberOperations::operator%(BigNumberOperations Big)
{
	BigNumberOperations A = *this;
	A %= Big;
	return A;
}

inline bool BigNumberOperations::operator>(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return false;
	}
	int comp = comparison(Big2);
	if (comp == 1)
		return true;
	return false;
}
inline bool BigNumberOperations::operator<(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return false;
	}
	int comp = comparison(Big2);
	if (comp == 2)
		return true;
	return false;
}
inline bool BigNumberOperations::operator==(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return false;
	}
	int comp = comparison(Big2);
	if (comp == 3)
		return true;
	return false;
}
inline bool BigNumberOperations::operator>=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return false;
	}
	int comp = comparison(Big2);
	if (comp == 1 || comp == 3)
		return true;
	return false;
}
inline bool BigNumberOperations::operator<=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return false;
	}
	int comp = comparison(Big2);
	if (comp == 2 || comp == 3)
		return true;
	return false;
}
inline bool BigNumberOperations::operator!=(BigNumberOperations Big2)
{
	if (!Flag_work || !Big2.Flag_work || b != Big2.b) {
		return false;
	}
	int comp = comparison(Big2);
	if (comp == 1 || comp == 2)
		return true;
	return false;
}

inline BigNumberOperations BigNumberOperations::rand_max()
{
	BigNumberOperations Big_Rand;
	int rand_int, rand_size_ = BigNumber.size();
	rand_size_ /= 5;
	if (rand_size_ < 1) {
		rand_size_ = 2;
	}
	rand_size_++;
	rand_size_ = (rand() % rand_size_);
	rand_int = rand();
	Big_Rand.create(to_string(rand_int), b);
	for (int i = 0; i < rand_size_; i++) {
		rand_int = rand();
		BigNumberOperations Buf_Rand(to_string(rand_int), b);
		Big_Rand *= Buf_Rand;
	}
	Big_Rand %= *this;
	return Big_Rand;
}

ostream& operator<<(ostream& cout, BigNumberOperations big) {
	return cout << big.get_number();
}