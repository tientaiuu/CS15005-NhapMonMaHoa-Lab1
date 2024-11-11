#include "BigInt.h"
#include <random>
#include <time.h> 
#include <fstream>
#include <chrono>


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

// B: Triển khai hàm sinh số nguyên tố ngẫu nhiên
//  Hàm cần thực hiện: sinh số nguyên tố ngẫu nhiên có độ dài bit_size bit
BigInt random_between(const BigInt& low, const BigInt& high) {
	random_device rd;
	mt19937 gen(rd());

	BigInt range = high - low;
	uniform_int_distribution<unsigned long long> dis(0, Size(range));

	return low + dis(gen);
}

// Hàm kiểm tra tính nguyên tố Miller-Rabin
bool is_prime(const BigInt& n, int k = 4) {
	// Trường hợp cơ bản
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) return false;

	// Tách n - 1 thành dạng 2^s * d với d lẻ
	BigInt d = n - 1;
	int s = 0;
	while (d % 2 == 0) {
		d /= 2;
		s++;
	}

	// Thực hiện k lần thử
	for (int i = 0; i < k; i++) {
		// Chọn một cơ sở ngẫu nhiên a trong khoảng [2, n - 2]
		BigInt a = random_between(2, n - 2);
		BigInt x = modular_exponentiation(a, d, n);

		// Kiểm tra điều kiện ban đầu x == 1 hoặc x == n - 1
		if (x == 1 || x == n - 1) {
			continue;
		}

		bool continue_outer = false;
		// Lặp s - 1 lần
		for (int r = 0; r < s - 1; r++) {
			x = modular_exponentiation(x, 2, n);

			if (x == n - 1) {
				continue_outer = true;
				break;
			}
		}

		if (continue_outer) {
			continue;
		}

		// Nếu không thỏa mãn bất kỳ điều kiện nào, n là hợp số
		return false;
	}

	// Nếu qua tất cả các lần thử mà không có bằng chứng hợp số, thì n là nguyên tố
	return true;
}

// Sinh số ngẫu nhiên có độ dài bit_size bit
BigInt randomize_odds_only(int bit_size)
{
	random_device rd;						 // Thiết bị sinh số ngẫu nhiên
	mt19937 gen(rd());						 // Mảng sinh ngẫu nhiên Mersenne Twister
	uniform_int_distribution<int> dis(0, 1); // Sinh số ngẫu nhiên giữa 0 và 1

	vector<int> bits(bit_size, 1); // Lưu trữ các bit của số ngẫu nhiên

	// Sinh các bit ngẫu nhiên và lưu vào vector
	for (int i = 1; i < bit_size - 1; ++i)
	{
		// Sinh bit ngẫu nhiên
		if (dis(gen) == 0)
			bits[i] = dis(gen);
	}

	// Chuyển đổi vector các bit thành BigInt
	BigInt result;
	for (int i = 0; i < bit_size; ++i)
		result = result * 2 + bits[i]; // Dịch trái và cộng bit vào

	return result;
}

// Hàm cần thực hiện: sinh số nguyên tố ngẫu nhiên có độ dài bit_size bit
BigInt generate_safe_prime(int bit_size)
{
	BigInt prime;
	int count = 0;

	while (true)
	{
		//start time
		auto start = chrono::high_resolution_clock::now();
		prime = randomize_odds_only(bit_size);  		
		cout << "[" << ++count << "]  -  " << prime << "\n\n";

		if (is_prime(prime))
		{
			cout << "Prime!!!: " << prime << "\n\n";
			BigInt temp = (prime - 1) / 2;
			if (is_prime(temp))
			{
				cout << prime << "\n\n";
				return prime;
			}
		}
	//end time
	auto end = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = end - start;
		cout << "Time: " << elapsed.count() << " seconds\n\n";
	}
}

// C: Triển khai hàm sinh khóa riêng ngẫu nhiên
BigInt generate_random_bigint(const BigInt& lower, const BigInt& upper)
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
BigInt generate_private_key(const BigInt& p)
{
	BigInt lowerLimit("2");
	BigInt upperLimit = p - BigInt("2");

	return generate_random_bigint(lowerLimit, upperLimit);
}

// D. Hoàn thành trao đổi khóa Diffie-Hellman
int main()
{
	ios_base::sync_with_stdio(false);  // Tắt đồng bộ hóa với stdio


	auto start = chrono::high_resolution_clock::now(); // Start high-precision clock

	srand(time(NULL));
	// 1. Sinh số nguyên tố lớn p và phần tử sinh g
	int bit_size = 512;

	BigInt p = generate_safe_prime(bit_size);
	cout << "p: " << p << endl;
	BigInt g = 2;

	// 2. Sinh khóa riêng của Alice và Bob
	BigInt a = generate_private_key(p);
	BigInt b = generate_private_key(p);
	cout << "a b right here!!!\n\n";
	cout << a << "\n\n"
		<< b << "\n\n";

	// 3. Tính giá trị công khai của Alice và Bob
	BigInt A = modular_exponentiation(g, a, p);
	BigInt B = modular_exponentiation(g, b, p);

	// 4. Tính bí mật chung
	BigInt alice_shared_secret = modular_exponentiation(B, a, p);
	BigInt bob_shared_secret = modular_exponentiation(A, b, p);

	// 5. Hiển thị kết quả
	cout << "Alice Secret: " << alice_shared_secret << "\n\n";
	cout << "Bob Secret: " << bob_shared_secret << "\n\n";
	cout << "Alice-Bob Secret equal? " << (alice_shared_secret == bob_shared_secret) << "\n";

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;
	fstream file("result.txt", ios::out);

	file << "---- Result of Diffie Hellman key exchange ----\n\n"
		<< "Running Time: " << elapsed.count() << " seconds\n\n"
		<< "Result:\n\n";

	file << "Alice Secret: " << alice_shared_secret << "\n\n"
		<< "Bob Secret: " << bob_shared_secret << "\n\n"
		<< "Alice-Bob Secret equal? " << (alice_shared_secret == bob_shared_secret) << "\n";

	file.close();
	return 0;
}