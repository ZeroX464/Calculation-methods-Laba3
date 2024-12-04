#include <iostream>
#include <vector>
using namespace std;

double calculate_zn(double n, double alpha) {
	double z_n = 0;
	for (int i = 1; i <= n; i++) {
		z_n += 1 / pow(i, alpha);
	}
	return z_n;
}

double calculate_zn_1(double n, double q, double k, double alpha) {
	double z_n = calculate_zn(n, alpha);
	double z_nq = calculate_zn(n / q, alpha);
	return z_n + (z_n - z_nq) / (pow(q, k) - 1);
}

double calculate_zn_2(double z_n1, double n, double q, double k1, double k2, double alpha) {
	double z_nq_1 = calculate_zn_1(n / q, q, k1, alpha);
	return z_n1 + (z_n1 - z_nq_1) / (pow(q, k2) - 1);
}

string doubleToPow10toN(double value) {
	int exponent = 0;
	char value_str[20];
	if (value != 0) {
		exponent = static_cast<int>(std::floor(std::log10(std::abs(value))));
		value /= std::pow(10, exponent);
	}
	sprintf_s(value_str, "%.2f*10^%+d", value, exponent);
	return string(value_str);
}

int main() {
	double alpha = 1.1;
	double z_tochnoe = 10.5844484649508098;
	int q = 2;
	double k1 = alpha - 1;
	double k2 = alpha;
	int maxTerms = 50;
	double z_n = 0;
	double z_n1 = 0;
	double z_n2 = 0;
	double delta_n = 0;
	double delta_n1 = 0;
	printf("%-7s %-14s %-12s %-18s %-12s %-18s %-12s\n", "N", "z_n-z_tochnoe", "z_n-z_n^(1)", "z_n^(1)-z_tochnoe", "delta_n", "z_n^(2)-z_tochnoe", "delta_n^(1)");
	printf("%s\n", std::string(100, '-').c_str());
	for (int n = 2; n <= 131072; n *= 2) {
		z_n = calculate_zn(n, alpha);
		z_n1 = calculate_zn_1(n, q, k1, alpha);
		z_n2 = calculate_zn_2(z_n1, n, q, k1, k2, alpha);
		delta_n = (z_n1 - z_tochnoe) / (z_n - z_tochnoe);
		delta_n1 = (z_n2 - z_tochnoe) / (z_n1 - z_tochnoe);
		if (n == 2) { printf("%-7d %-14s %-12s %-18s %-12s %-18s %-12s\n", n, doubleToPow10toN(z_n - z_tochnoe).c_str(), doubleToPow10toN(z_n - z_n1).c_str(), doubleToPow10toN(z_n1 - z_tochnoe).c_str(), doubleToPow10toN(delta_n).c_str(), "-", "-"); }
		else { printf("%-7d %-14s %-12s %-18s %-12s %-18s %-12s\n", n, doubleToPow10toN(z_n - z_tochnoe).c_str(), doubleToPow10toN(z_n - z_n1).c_str(), doubleToPow10toN(z_n1 - z_tochnoe).c_str(), doubleToPow10toN(delta_n).c_str(), doubleToPow10toN(z_n2 - z_tochnoe).c_str(), doubleToPow10toN(delta_n1).c_str()); }
	}
	return 0;
}