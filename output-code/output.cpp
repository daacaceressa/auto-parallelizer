#include <bits/stdc++.h>
#define pb      push_back
#define show(x) cout << #x << ": " << x << endl;
using namespace std;
typedef long long ll;
typedef double lf;
typedef complex<lf> pt;
typedef vector<vector<int>> graph;
const int MAX = 200007;
int f (int a) {
	return a + 2;
}
int main( ) {
	int sum = 0;
	int n = 10;
	int sum2 = 0, sum3 = 0, sum4 = 1;
	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < n; ++i)
        sum += i;
	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < n; ++i) {
        sum += i;
    }
	#pragma omp parallel for reduction(*:sum4) reduction(+:sum,sum3) reduction(-:sum2)
	for (int i = 1; i < n; ++i) {
        sum += i;
        sum2 -= f(i);
        sum3 += 2 * i + i * i + f(i);
        sum4 *= i;
    }
	cout << sum << ' ' << sum2 << ' ' << sum3 << ' ' << sum4 << endl;
}
