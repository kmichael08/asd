// Sortowanie komorkowe - Michał Kuźba
#include<iostream>
using namespace std;

const int MODULO = 1000000000;
const int SIZE = 1001;

int ciag[SIZE];

/*
 * 0 - konczy sie z lewej
 * 1 - konczy sie z prawej
 * t[i][j] - zaczyna sie w i, dlugosci j
 * tablica wyzerowana - globalna
 */
int t[SIZE][SIZE][2];


void calculate(int n) {
	for (int i = 1; i <= n; i++) {
		t[i][1][0] = 1;
		t[i][1][1] = 1;
	}
	
	for (int j = 2; j <= n; j++)
		for (int i = 1; i <= n - j + 1; i++)
			{	
				// dokladamy z lewej strony do ciagu "lewego"
				if (ciag[i] < ciag[i + 1]) {
					t[i][j][0] += t[i + 1][j - 1][0];
					t[i][j][0] %= MODULO;
				}
				
				// dokladamy z lewej strony do ciagu "prawego"
				if (j > 2 && ciag[i] < ciag[i + j - 1]) {
					t[i][j][0] += t[i + 1][j - 1][1];
					t[i][j][0] %= MODULO;
				}
				
				// dokladamy z prawej strony do ciagu "lewego"
				if (ciag[i + j - 1] > ciag[i]) {
					t[i][j][1] += t[i][j - 1][0];
					t[i][j][1] %= MODULO;
				}
				
				// dokladamy z prawej strony do ciagu "prawego"
				if (j > 2 && ciag[i + j - 1] > ciag[i + j - 2]) {
					t[i][j][1] += t[i][j - 1][1];
					t[i][j][1] %= MODULO;
				}
				
			}	
}

void array_test(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << t[i][j][0] << " ";
		cout << endl;		
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << t[i][j][1] << " ";
		cout << endl;		
	}
}

int main() {
	int n;
	cin >> n;
	
	for (int i = 1; i <= SIZE; i++)
		cin >> ciag[i];
	
	calculate(n);
	
	// debug
	// array_test(n);
	
	if (n == 1)
		cout << 1 << endl;
	else	
		cout << (t[1][n][0] + t[1][n][1]) % MODULO << endl;
	
	
	
	return 0;
}
