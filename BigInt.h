#ifndef BIG_INT
#define BIG_INT

#include <iostream>
#include <vector>
using namespace std;


//------------------------------------------------------------------------------------------------------//
//                                          BIG INT                                                     //
//------------------------------------------------------------------------------------------------------//

class BigInt
{
private:
    string digits;
public:

    // Constructors 
    BigInt(unsigned long long n = 0);
    BigInt(string&);
    BigInt(const char*);
    BigInt(const BigInt&);

    friend void divide_by_2(BigInt& a);     // Chia đôi
    friend bool Null(const BigInt&);        // Kiểm tra = 0
    friend int Size(const BigInt&);       // Trả về độ dài
    int operator[](const int)const;         // truy cập theo a[index]
     
    BigInt& operator=(const BigInt&);

    // Tăng/giảm 1 đơn vị
    BigInt& operator++();                   // i++
    BigInt operator++(int temp);            // ++i
    BigInt& operator--();                   // i--
    BigInt operator--(int temp);            // --i

    // Cộng/Trừ số nguyên lớn
    friend BigInt& operator+=(BigInt&, const BigInt&);              // a += b
    friend BigInt operator+(const BigInt&, const BigInt&);          // c = a + b
    friend BigInt operator-(const BigInt&, const BigInt&);          // a -= b
    friend BigInt& operator-=(BigInt&, const BigInt&);              // c = a - b

    // So sánh số nguyên lớn
    friend bool operator==(const BigInt&, const BigInt&);           // a == b
    friend bool operator!=(const BigInt&, const BigInt&);           // a != b
    friend bool operator>(const BigInt&, const BigInt&);            // a > b
    friend bool operator>=(const BigInt&, const BigInt&);           // a >= b
    friend bool operator<(const BigInt&, const BigInt&);            // a < b
    friend bool operator<=(const BigInt&, const BigInt&);           // a <= b

    // Nhân/Chia số nguyên lớn
    friend BigInt& operator*=(BigInt&, const BigInt&);              // a *= b
    friend BigInt operator*(const BigInt&, const BigInt&);          // c = a * b
    friend BigInt& operator/=(BigInt&, const BigInt&);              // a /= b
    friend BigInt operator/(const BigInt&, const BigInt&);          // c = a / b

    // Modulo số nguyên lớn
    friend BigInt& operator%=(BigInt&, const BigInt&);              // a %= b
    friend BigInt operator%(const BigInt&, const BigInt&);          // c = a % b

    // Hàm luỹ thừa số nguyên lớn
    friend BigInt& operator^=(BigInt&, const BigInt&);              // a^= b
    friend BigInt operator^(BigInt&, const BigInt&);                // c = a ^ b

    // Căn bậc 2 số nguyên lớn
    friend BigInt sqrt(BigInt& a);

    // Hàm đọc và ghi
    friend ostream& operator<<(ostream&, const BigInt&);
    friend istream& operator>>(istream&, BigInt&);


};
#endif // !BIG_INT




