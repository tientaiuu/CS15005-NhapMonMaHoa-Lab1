#include <iostream>
#include <random>

using namespace std;

long long generate_private_key(long long p) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(2, p - 2);
    return dis(gen);
}

int main() {
    long long p = 32416190071; 
    long long private_key = generate_private_key(p);
    cout << "Khoa rieng duoc sinh: " << private_key << "\n";
    return 0;
}
