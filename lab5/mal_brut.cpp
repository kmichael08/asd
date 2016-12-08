/**
 * Malowanie autostrady Michał Kuźba
 * Brute version for tests.
 */
 
 #include <iostream>
 using namespace std;
 
 const int MAX_SIZE = 1000001;
 
 int tab[MAX_SIZE];
 
 // total(number of ones) on the whole interval 
 int total(int n);
 
 // fill the interval with zeroes
 void zero (int a, int b, int n);
 
 // fil the interval with ones
 void ones (int a, int b, int n);
 
 int total(int n) {
	 int result = 0;
	 
	 for (int i = 1; i <= n; i++)
		result += tab[i];
	
	return result;
 }
 
 void fill(int a, int b, int n, int val) {
	 for (int i = a; i <= b; i++)
		tab[i] = val;	 
 }
 
 void ones(int a, int b, int n) { fill(a, b, n, 1); }
 
 void zero(int a, int b, int n) { fill(a, b, n, 0); }
 
 int main() {
	 
	 int n, m;
	 cin >> n >> m;
	 
	 int a, b;
	 char c; 
	 
	 for (int i = 1; i <= m ; i++) {
		cin >> a >> b;
		cin >> c;
		 
		if (c == 'C')
			zero(a, b, n);
		else 
			ones(a, b, n);
		
		cout << total(n) << endl;		 
	 }
	 
	 
	 return 0;
 }
