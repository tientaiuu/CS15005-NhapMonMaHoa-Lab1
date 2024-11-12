#ifndef BIG_INT
#define BIG_INT

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

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
    BigInt(unsigned long long n = 0);   // Khởi tạo BigInt từ một số nguyên không dấu (unsigned long long)
    BigInt(string&);            // Khởi tạo BigInt từ một chuỗi ký tự (string)
    BigInt(const char*);        // Khởi tạo BigInt từ một chuỗi ký tự (const char*)
    BigInt(BigInt&);            // Khởi tạo từ BigInt    
    
    //Copy constructor
    BigInt(const BigInt& a);

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
    friend BigInt& operator+=(BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt& operator-=(BigInt&, const BigInt&);

    // So sánh số nguyên lớn
    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);
    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator>=(const BigInt&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator<=(const BigInt&, const BigInt&);

    // Nhân/Chia số nguyên lớn
    friend BigInt& operator*=(BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt& operator/=(BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);

    // Modulo số nguyên lớn
    friend BigInt operator%(const BigInt&, const BigInt&);
    friend BigInt& operator%=(BigInt&, const BigInt&);

    // Hàm luỹ thừa số nguyên lớn
    friend BigInt& operator^=(BigInt&, const BigInt&);
    friend BigInt operator^(BigInt&, const BigInt&);

    // Căn bậc 2 số nguyên lớn
    friend BigInt sqrt(BigInt& a);

    // Hàm đọc và ghi
    friend ostream& operator<<(ostream&, const BigInt&);
    friend istream& operator>>(istream&, BigInt&);
    friend string to_String(const BigInt& a);

    //So sánh số nguyên tố lớn với số thường
    friend bool operator==(const BigInt&, const int&);

    //Random số nguyên lớn
    friend BigInt randomize(int n);

    //Phép dịch bit
    BigInt operator<<(int shift);
    //Phép AND
    BigInt& operator|=(const BigInt& other);

};
#endif // !BIG_INT                                              




