/**
* Generated by Auto Parallelizer
*
* Auto Parallelizer supports Task parallelization and reduction recognition
* in for statements
*
* For further information see the -help of the executable file or 
* the source code at https://github.com/milderhc/auto-parallelizer
*
* Developed by:
* Milder Hernandez Cagua
* Daniel Augusto Caceres Salas
*
* Universidad Nacional de Colombia
* May 2017
*
*/

#include <omp.h>
#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long double lf;
typedef complex<lf> cp;
const lf eps = 1e-8;
const int MAXN = 1<<19;
cp a1[ MAXN ], a2[ MAXN ], a3[ MAXN ], a4[ MAXN ];
cp b1[ MAXN ], b2[ MAXN ], b3[ MAXN ], b4[ MAXN ];
int c1[ MAXN ], c2[ MAXN ], c3[ MAXN ], c4[ MAXN ];
int get_power_2( int p ) {
	int n = 1;
	while( n < p ) n <<= 1;
	return n;
}
void preSet( string s1, string s2, int n) {
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for( int i = 0; i < n; ++i ) {
			        c4[ i ] = 0.0;
			        if( i >= int( s1.size( ) ) )
			            a4[ i ] = { 0.0, 0.0 };
			        else
			            a4[ i ] = { s1[ i ] == 'T' ? 1.0 : 0.0, 0.0 };
			        if( i >= int( s2.size( ) ) )
			            b4[ i ] = { 0.0, 0.0 };
			        else
			            b4[ i ] = { s2[ i ] == 'T' ? 1.0 : 0.0, 0.0 };
			    }
		}
		#pragma omp section
		{
			for( int i = 0; i < n; ++i ) {
			        c3[ i ] = 0.0;
			        if( i >= int( s1.size( ) ) )
			            a3[ i ] = { 0.0, 0.0 };
			        else
			            a3[ i ] = { s1[ i ] == 'A' ? 1.0 : 0.0, 0.0 };
			        if( i >= int( s2.size( ) ) )
			            b3[ i ] = { 0.0, 0.0 };
			        else
			            b3[ i ] = { s2[ i ] == 'A' ? 1.0 : 0.0, 0.0 };
			    }
		}
		#pragma omp section
		{
			for( int i = 0; i < n; ++i ) {
			        c2[ i ] = 0.0;
			        if( i >= int( s1.size( ) ) )
			            a2[ i ] = { 0.0, 0.0 };
			        else
			            a2[ i ] = { s1[ i ] == 'C' ? 1.0 : 0.0, 0.0 };
			        if( i >= int( s2.size( ) ) )
			            b2[ i ] = { 0.0, 0.0 };
			        else
			            b2[ i ] = { s2[ i ] == 'C' ? 1.0 : 0.0, 0.0 };
			    }
		}
		#pragma omp section
		{
			for( int i = 0; i < n; ++i ) {
			        c1[ i ] = 0.0;
			        if( i >= int( s1.size( ) ) )
			            a1[ i ] = { 0.0, 0.0 };
			        else
			            a1[ i ] = { s1[ i ] == 'G' ? 1.0 : 0.0, 0.0 };
			        if( i >= int( s2.size( ) ) )
			            b1[ i ] = { 0.0, 0.0 };
			        else
			            b1[ i ] = { s2[ i ] == 'G' ? 1.0 : 0.0, 0.0 };
			    }
		}
	}
}
void rev(cp *a,int n) {
	int i,j,k;
	for (i=1,j=n>>1;i<n-1;i++){
	        if(i<j)swap(a[i],a[j]);
	        for (k=n>>1;j>=k;j-=k,k>>=1);j+=k;
	    }
}
void dft(cp *a,int n,int flag=1) {
	rev(a,n);
	for (int m=2;m<=n;m<<=1)
	    {
	        cp wm(cos(flag*2*M_PI/m),sin(flag*2*M_PI/m));
	        for (int k=0;k<n;k+=m)
	        {
	            cp w(1.0,0.0);
	            for (int j=k;j<k+(m>>1);j++,w=w*wm)
	            {
	                cp u=a[j],v=a[j+(m>>1)]*w;
	                a[j]=u+v;
	                a[j+(m>>1)]=u-v;
	            }
	        }
	    }
}
void mul(cp* a, cp* b, int* c,int n) {
	dft(a,n);
	dft(b,n);
	for (int i=0;i<n;i++)a[i]=a[i]*b[i];
	for( int i = 0; i < 1; ++i ) {
	        dft(a,n,-1);
	        for (int i=0;i<n;i++) c[i] += int( round( a[i].real()/n ) );
	    }
}
void fft( string s1, string s2, int n ) {
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			mul( a4, b4, c4, n );
		}
		#pragma omp section
		{
			mul( a3, b3, c3, n );
		}
		#pragma omp section
		{
			mul( a2, b2, c2, n );
		}
		#pragma omp section
		{
			mul( a1, b1, c1, n );
		}
	}
}
void print_ans( string s1, string s2, int n ) {
	string ans;
	int id = 0;
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			reverse( s2.begin( ), s2.end( ) );
			ans = string( int( s2.size( ) )-1, ' ' )+s1+string( int( s2.size( ) )-1, ' ' );
		}
		#pragma omp section
		{
			for( int i = 0; i < n; ++i )
			        c4[ i ] += c1[ i ] + c2[ i ] + c3[ i ];
		}
	}
	for( int i = 0; i < n; ++i )
	        if( real( c4[ i ] ) >= real( c4[ id ] ) )
	            id = i;
	if( c4[ id ] == 0 ) cout << "0\nNo matches\n";
	    else {
	        cout << c4[ id ] << '\n';
	        for( int i = 0; i < int( s2.size( ) ); i++ ) {
	            if( ans[ id+i ] == ' ' || ans[ id+i ] == s2[ i ] )
	                ans[ id+i ] = s2[ i ];
	            else ans[ id+i ] = 'X';
	        }
	        for( auto e : ans )
	            if( e != ' ' )
	                cout << e;
	        cout << '\n';
	    }
}
int main() {
	freopen("input", "r", stdin);
	freopen("output2", "w", stdout);

	struct timeval start, end;
	gettimeofday(&start, 0);

	string s1, s2;
	while( cin >> s1 >> s2 ) {
	        int p = int( s1.size( )+s2.size( )-1 ), n = get_power_2( p );
	        reverse( s2.begin( ), s2.end( ) );
	        preSet( s1,s2, n );
	        fft( s1, s2, n );
	        print_ans( s1, s2, n );
	        cout << endl;
	    }

	gettimeofday(&end, 0);
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	cout << "Time difference: " << delta;

	return 0;
}
