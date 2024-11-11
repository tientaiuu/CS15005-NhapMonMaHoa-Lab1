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

// Hàm chuyển đổi uint64_t thành BigInt bằng cách chuyển đổi thành chuỗi ký tự trước
BigInt generate_random_bigint(const BigInt &lower, const BigInt &upper)
{
    BigInt range = upper - lower + BigInt("1"); // Thêm "1" để bao gồm giá trị upper
    BigInt randomValue("0");

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);

    // Tạo một chuỗi ngẫu nhiên và sau đó ép về trong khoảng
    for (int i = 0; i < 4; ++i)
    { // Tạo các phần 64-bit để ghép thành một số lớn
        uint64_t part = dis(gen);
        string partStr = to_string(part);
        BigInt partBigInt(partStr);                                                // Chuyển thành chuỗi trước khi khởi tạo BigInt
        randomValue = (randomValue * BigInt("18446744073709551616")) + partBigInt; // Nhân với 2^64 (18446744073709551616)
    }

    // Điều chỉnh randomValue để nằm trong phạm vi [lower, upper]
    randomValue = (randomValue % range) + lower;
    return randomValue;
}

// Hàm tạo khoá riêng ngẫu nhiên trong phạm vi [2, p-2]
BigInt generate_private_key(const BigInt &p)
{
    BigInt lowerLimit("2");
    BigInt upperLimit = p - BigInt("2");

    return generate_random_bigint(lowerLimit, upperLimit);
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
    BigInt privateKey = generate_private_key(p);

    cout << "Private key: " << privateKey << endl;

    return 0;
}
