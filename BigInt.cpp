﻿#include "BigInt.h"


//------------------------------------------------------------------------------------------------------//
//                                   Khởi tạo Constructors cho BigINT                                   //
//------------------------------------------------------------------------------------------------------//

// Khởi tạo BigInt từ một chuỗi ký tự (string)
BigInt::BigInt(string& s)
{
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
// Khởi tạo BigInt từ một số nguyên không dấu (unsigned long long)
BigInt::BigInt(unsigned long long n)
{
    do {
        digits.push_back(n % 10);
        n /= 10;
    } while (n);
}
// Khởi tạo BigInt từ một chuỗi ký tự (const char*)
BigInt::BigInt(const char* s)
{
    digits = "";
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
// Copy constructor
BigInt::BigInt(const BigInt& other)
{
    digits = other.digits;
}

//------------------------------------------------------------------------------------------------------//
//                                   Cài đặt hàm phụ trợ                                                //
//------------------------------------------------------------------------------------------------------//

// Kiểm tra BigInt = 0 
bool Null(const BigInt& a)
{
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}

// Trả về số lượng chữ số của BigInt
int Size(const BigInt& a)
{
    return a.digits.size();
}

// Cho phép truy cập một chữ số trong BigInt như a[index].
int BigInt::operator[](const int index)const
{
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}


//------------------------------------------------------------------------------------------------------//
//                                   Cài đặt hàm so sánh số nguyên lớn                                  //
//------------------------------------------------------------------------------------------------------//

//------------------- So sánh = -------------------------//
bool operator==(const BigInt& a, const BigInt& b)
{
    return a.digits == b.digits;
}
bool operator!=(const BigInt& a, const BigInt& b)
{
    return !(a == b);
}

//------------------- So sánh lớn/bé -------------------------//
bool operator<(const BigInt& a, const BigInt& b)
{
    int n = Size(a), m = Size(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}
bool operator>(const BigInt& a, const BigInt& b)
{
    return b < a;
}
bool operator>=(const BigInt& a, const BigInt& b)
{
    return !(a < b);
}
bool operator<=(const BigInt& a, const BigInt& b)
{
    return !(a > b);
}

//---------------------- Phép gán ------------------------//
BigInt& BigInt::operator=(const BigInt& other)
{
    digits = other.digits;
    return *this;
}


//------------------------------------------------------------------------------------------------------//
//                                     Cài đặt hàm +/- cho BigINT                                       //
//------------------------------------------------------------------------------------------------------//

//----------------------- Tăng thêm 1 -----------------------//
BigInt& BigInt::operator++() 
{
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++)
        digits[i] = 0;
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}

//----------------------- Giảm đi 1 -----------------------//
BigInt& BigInt::operator--()
{
    if (digits[0] == 0 && digits.size() == 1)
        throw("ERROR: A < 0");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++)
        digits[i] = 9;
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}


//----------------------------------- Cộng 2 số nguyên lớn ------------------------------- //
BigInt& operator+=(BigInt& a, const BigInt& b)
{
    int t = 0, s, i;
    int n = Size(a), m = Size(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Size(a);
    for (i = 0; i < n; i++) {
        if (i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt& a, const BigInt& b)
{
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

//----------------------------------- Trừ 2 số nguyên lớn ------------------------------- //

BigInt& operator-=(BigInt& a, const BigInt& b)
{
    if (a < b)
        throw("ERROR: A < B");
    int n = Size(a), m = Size(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(),
        n--;
    return a;
}

BigInt operator-(const BigInt& a, const BigInt& b)
{
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}


//------------------------------------------------------------------------------------------------------//
//                                   Cài đặt Nhân/Chia cho BigInt                                       //
//------------------------------------------------------------------------------------------------------//

//--------------------------------------- Nhân 2 số nguyên lớn ----------------------------------//
BigInt& operator*=(BigInt& a, const BigInt& b)
{
    if (Null(a) || Null(b)) {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            v[i + j] += (a.digits[i]) * (b.digits[j]);
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        a.digits.pop_back();
    return a;
}
BigInt operator*(const BigInt& a, const BigInt& b)
{
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}

//--------------------------------------- Chia 2 số nguyên lớn ----------------------------------//

BigInt& operator/=(BigInt& a, const BigInt& b)
{
    if (Null(b))
        throw("Error: Division By 0");
    if (a < b) {
        a = BigInt();
        return a;
    }
    if (a == b) {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Size(a), m = Size(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
    {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    return a;
}
BigInt operator/(const BigInt& a, const BigInt& b)
{
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}


//------------------------------------------------------------------------------------------------------//
//                                        Hàm modulo cho BigINT                                         //
//------------------------------------------------------------------------------------------------------//
BigInt& operator%=(BigInt& a, const BigInt& b)
{
    if (Null(b))
        throw("Error: Division By 0");
    if (a < b)
    {
        return a;
    }
    if (a == b)
    {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Size(a), m = Size(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
    {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}
BigInt operator%(const BigInt& a, const BigInt& b)
{
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}


//------------------------------------------------------------------------------------------------------//
//                                       Cài đặt hàm mũ cho BigInt                                      //
//------------------------------------------------------------------------------------------------------//
BigInt& operator^=(BigInt& a, const BigInt& b)
{
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent))
    {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        Exponent /= 2;
    }
    return a;
}
BigInt operator^(BigInt& a, BigInt& b)
{
    BigInt temp(a);
    temp ^= b;
    return temp;
}

//------------------------------------------------------------------------------------------------------//
//                                   Cài đặt toán tử đọc/xuất BigInt                                    //
//------------------------------------------------------------------------------------------------------//

// Biến chuỗi thành BigInt
istream& operator>>(istream& in, BigInt& a) 
{
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i] - '0';
    }
    return in;
}

// Xuất ra BigInt 
ostream& operator<<(ostream& out, const BigInt& a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        cout << (short)a.digits[i];
    return cout;
}

//------------------------------------------------------------------------------------------------------//
//                                   So sánh số nguyên tố lớn với số nguyên tố thường                   //
//------------------------------------------------------------------------------------------------------//

bool operator==(const BigInt& a, const int& b) {
	if (a.digits.size() > 1)
		return false;
    return a.digits[0] == b;
}

BigInt BigInt::operator<<(int shift) {
    BigInt result = *this;
    for (int i = 0; i < shift; i++) {
        result = result * 2; // Dịch bit sang trái tương đương với nhân với 2
    }
    return result;
}

BigInt& BigInt::operator|=(const BigInt& other) {
    // Chúng ta cần đảm bảo rằng BigInt của cả hai đối tượng có cùng số lượng chữ số
    // Nếu không thì sẽ phải thêm chữ số để đảm bảo độ dài bằng nhau

    int size_left = this->digits.size();
    int size_right = other.digits.size();

    // Đảm bảo đối tượng bên trái (this) có đủ độ dài để thực hiện phép toán
    if (size_left < size_right) {
        this->digits.insert(this->digits.begin(), size_right - size_left, '0');
    }
    if (size_right < size_left) {
        const_cast<BigInt&>(other).digits.insert(other.digits.begin(), size_left - size_right, '0');
    }

    // Thực hiện phép OR giữa các chữ số tương ứng
    for (int i = 0; i < this->digits.size(); i++) {
        this->digits[i] = (this->digits[i] - '0') | (other.digits[i] - '0') + '0';
    }

    return *this;
}

string to_String(const BigInt& a)
{
    string result = "";
    for (int i = a.digits.size()-1;i>=0;--i){
        result += char((int)a.digits[i] + '0');
    }
    return result;
}