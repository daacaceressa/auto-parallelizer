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

    int sum2 = 0, sum3 = 0, sum4 = 1, sum5 = 0, sum6 = 0;
    for (int i = 1; i < n; ++i) {
        sum2 -= f(i);
        sum3 += 2 * i + i * i + f(i);
        sum4 *= i;
        sum5 = min( sum5 , max(i+i, i*i) ) ;
        sum6 = ( ( ( ( max( sum6 , i*i*i ) ) ) ) );
    }

    cout << sum2 << ' ' << sum3 << ' ' << sum4 << ' ' << sum5 << ' ' << sum6 << endl;
}