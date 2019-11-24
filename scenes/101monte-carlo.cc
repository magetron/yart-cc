#include<iostream>
#include<iomanip>
#pragma GCC optimize ("Ofast")

using namespace std;

int main () {
	int n = 1e8;
	int inside = 0;
	for (int i = 0; i < n; i++) {
		double x = drand48();
		double y = drand48();
		if (x * x + y * y < 1) inside++;
	}
	cout << setprecision(9) << 4 * (double)inside / n << endl;
	return 0;
}

