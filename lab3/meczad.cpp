#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int PLAYERS_NUMBER = 40001;

long long players[PLAYERS_NUMBER];

void read_and_fill(int n, int m) {
	
	int number;
	// long long power = 1;
	int exponent = 0;
	
	for (int j = 1; j <= m; j++) {
		
		for (int i = 0; i < n / 2; i++)
			cin >> number;
				
		for (int i = n / 2; i < n; i++) {
			cin >> number;
			players[number] = players[number] | (1 << exponent);	
			cout << (1 << exponent) << endl;	
		}
		
		exponent++;
	}
		
}



int main() {
	ios_base::sync_with_stdio(0);
	
	int n, m;
	
	cin >> n >> m;
		
	read_and_fill(n, m);
		
	for (int i = 1; i <= n; i++)
		cout << i << " " << players[i] << endl;
	
		
	sort(players + 1, players + n + 1);
		
	for (int i = 1; i < n; i++) 
		if (players[i] == players[i + 1]) {
			cout << "NIE" << endl;
			return 0;
		}
		
	cout << "TAK" << endl;
		
	return 0;
}
