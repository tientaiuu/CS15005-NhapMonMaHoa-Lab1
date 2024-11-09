#include "BigInt.h"
#include <random>


// A: Triển khai hàm luỹ thừa module
// Hàm cần thực hiện: (base^exponent) % mod
BigInt modular_exponentiation(BigInt base, BigInt exponent, const BigInt& mod) 
{
    BigInt result = 1;  
    base = base % mod;  

    BigInt temp("0");

    while (exponent > temp)     // exponent > 0
    {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;

        divide_by_2(exponent);  
    }
    return result;
}

long long generate_private_key(long long p) 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(2, p - 2);
    return dis(gen);
}

int main() 
{
 
    return 0;
}
