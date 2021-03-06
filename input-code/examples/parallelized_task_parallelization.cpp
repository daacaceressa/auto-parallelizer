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
using namespace std;
typedef vector<vector<int>> graph;
const int MAX_N = int( 1e5 );
double board[ MAX_N ][ MAX_N ];
int arr[ MAX_N ];
void init() {
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for( int i = 1; i < MAX_N; ++i )
			        arr[ i ] = arr[ i-1 ] ^ i;
		}
		#pragma omp section
		{
			for( int i = 0; i < MAX_N; ++i )
			        for( int j = 0; j < MAX_N; j++ )
			            board[ i ][ j ] = i*j;
		}
	}
}
int main( ) {
	graph A( 10 );
	int B[100];
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for( int i = 0; i < 100; ++i ) {
			    	B[ i ] = i*i;
			    }
		}
		#pragma omp section
		{
			for( int i = 0, current = 0; i < A.size(); ++i ) {
			    	for( int j = 0; j < 20; ++j, ++current )
			    		A[ i ].push_back( current );
			    }
		}
		#pragma omp section
		{
			init();
		}
	}
}
