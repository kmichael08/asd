#include <iostream>
using namespace std;

const int MAX_WIDTH = 41, MAX_HEIGHT = 501;
const int NEG_INF = -2000000000;

int n, m;
int values[MAX_HEIGHT][MAX_WIDTH];

/** 
 * row, position on the path upwards, position on the path downwards, 
 * time from the last stop on the downwards path
 */
int para[MAX_HEIGHT][MAX_WIDTH][MAX_WIDTH][3];


void read_data() {
	cin >> m >> n;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> values[i][j];
}

/**
 * return the value if coordinates are valid, otherwise minus infinity.
 */
int get(int i, int j, int k, int l) {
	if (i < 1 || i > m || j < 1 || j > n || k < 1 || k > n) 
		return NEG_INF;
		
	return para[i][j][k][l];
}

/**
 * max of an array excluding given index
 */
int max_part(int array[], int index) {
	int result = NEG_INF;
		
	for (int i = 1; i <= n; i++)
		if (i != index && array[i] > result)
			result = array[i];
	
	return result;
}

void initial_array() {
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				for (int l = 0; l <= 2; l++)
					para[i][j][k][l] = NEG_INF;
	
}

int total() {
	int wynik = 0;

	// first row
	for (int j = 1; j <= n; j++)
		for (int k = 1; k <= n; k++)
			// paths must be disjoint
			if (j == k)
				continue;
			else 
				// maximum value in the row which is free
				para[1][j][k][0] = values[1][k] + values[1][j];
	

	for (int i = 2; i <= m; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				for (int l = 0; l <= 2; l++) {
					if (l == 0) {
						// paths must be disjoint
						if (j == k)
							continue;
						for (int ft = -2; ft <= 2; ft++)
							for (int sd = -1; sd <= 1; sd++)
								for (int th = 1; th <= 2; th++)
									para[i][j][k][l] = max( para[i][j][k][l],
									get(i - 1, j + ft, k + sd, th) +
									values[i][j] + values[i][k]);	
					}
					else {
						for (int ft = -2; ft <= 2; ft++)
							para[i][j][k][l] = max(para[i][j][k][l],
							get(i - 1, j + ft, k, l - 1) + values[i][j]);			
					}
				}
			
	
	/*
	// last row
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			if (i != j)
			// change the value in last row of descending movement
				para[m][i][j][0] += max_part(values[m], i) - values[m][j];
	*/
	
			
	// maximum total; must end in the last row
	for (int j = 1; j <= n; j++)
		for (int k = 1; k <= n; k++) {
				if (j != k)
					wynik = max(wynik, para[m][j][k][0]);
		}
		
	return wynik;
}

int main() {
		
	ios_base::sync_with_stdio(0);
	
	read_data();
	
	initial_array();
		
	cout << total() << endl;
		
	return 0;
}
