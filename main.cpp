#include "BigInt.h"
#include <random>
#include <sstream>
#include <iostream>

using namespace std;

// A: Triển khai hàm luỹ thừa module
// Hàm cần thực hiện: (base^exponent) % mod
BigInt modular_exponentiation(BigInt base, BigInt exponent, const BigInt &mod)
{
    BigInt result = 1;
    base = base % mod;

    BigInt temp("0");

    while (exponent > temp) // exponent > 0
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;

        divide_by_2(exponent);
    }
    return result;
}

// Hàm chuyển BigInt thành uint64_t nếu toán tử << có sẵn
uint64_t bigIntToUInt64(const BigInt &bigInt)
{
    stringstream ss;
    ss << bigInt;
    return std::stoull(ss.str());
}

// Hàm tạo khoá riêng ngẫu nhiên trong phạm vi [2, p-2]
BigInt generatePrivateKey(const BigInt &p)
{
    // Chuyển BigInt thành uint64_t
    uint64_t pValue = bigIntToUInt64(p);

    uint64_t lowerLimit = 2;
    uint64_t upperLimit = pValue - 2;

    // Tạo bộ sinh số ngẫu nhiên
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<uint64_t> dist(lowerLimit, upperLimit);

    // Tạo số ngẫu nhiên
    uint64_t randomNumber = dist(generator);

    // Chuyển số ngẫu nhiên thành BigInt
    BigInt privateKey(randomNumber);

    return privateKey;
}

int main()
{

    // TEST
    BigInt base("123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");
    BigInt exponent("987654321987654321987654321987654321123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");
    BigInt mod("10000000000000000000000123456789123456789123456789123456789123456789123456789123456789123456789");

    BigInt result = modular_exponentiation(base, exponent, mod);

    cout << "Result of (" << base << "^" << exponent << ") % " << mod << " is: " << result << endl;

    BigInt p("10000000000000000000000123456789123456789123456789123456789123456789123456789123456789123456789");

    BigInt privateKey = generatePrivateKey(p);

    cout << "Private key generated: " << privateKey << endl;

    return 0;
}
