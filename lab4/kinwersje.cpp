/**
 * Zadanie k-inwersje
 * Michał Kuźba
 */
 #include<iostream>
 using namespace std;
 const int SIZE = 20001;
 const int INV = 10;
 const int MOD = 1000000000;
 
 int values[SIZE];
 int inversions[INV + 1][SIZE];
 int interval_tree[4 * SIZE];
 int n, k;
   
// wsadz do drzewa wartosc val na pozycji pos
void insert (int pos, int val, int size);
 
// suma na indeksach wiekszych od pos w drzewie
int total (int pos, int size);
 
// wyzeruj drzewo przedzialowe
void clear_tree (int size); 
 
int tree_position (int pos, int size) {
	return size - 1 + pos;
}

void clear_tree(int size) {
	for (int i = 1; i < 2 * size; i++)
		interval_tree[i] = 0;
}
   
   
void insert (int pos, int val, int size) {
	int position = tree_position(pos, size);
	
	while (position) {
		interval_tree[position] += val;
		interval_tree[position] %= MOD;
		position >>= 1;
	}
	
}
   

int total (int pos, int size) {
	int suma = 0;
	
	int position = tree_position(pos, size);
	
	while (position) {
		if (position % 2 == 0) {
			suma += interval_tree[position + 1];
			suma %= MOD;
		}		
		
		position >>= 1;
	}
	
	return suma;
}

// najmniejsza potega dwojki nieprzekraczajaca n
int power (int liczba) {
	int n = liczba;
	int pot = 1;
	
	while (n) {
		n >>= 1;
		pot <<= 1;
	}
	
	if (pot == liczba << 1)
		return liczba;
	else
		return pot;
}

void read_input() {
	cin >> n >> k;
	 
	for (int i = 1; i <= n; i++)
		cin >> values[i];

}
 
void calculate_inversions() {
	// "1-inwersje"	
	for (int i = 1; i <= n; i++)
		inversions[1][i] = 1;
	
	int tree_size = power(n);
		
	for (int i = 2; i <= k; i++) {
		
		for (int j = 1; j <= n; j++) {
			inversions[i][j] = total(values[j], tree_size);
			insert(values[j], inversions[i - 1][j], tree_size);
		}
			
		
		clear_tree(tree_size);
	} 
} 
 
int k_inversions() {
	int wynik = 0;
	
	for (int i = 1; i <= n; i++) {
		wynik += inversions[k][i];
		wynik %= MOD;
	}
	
	return wynik;
} 
 
 void debug_print() {
	 for (int i = 1; i <= k; i++) {
		 for (int j = 1; j <= n; j++)
			cout << inversions[i][j] << " ";
		 cout << endl;
	 }
 }
 
 int main() {
	
	read_input();
	
	calculate_inversions();		
		
	// debug_print();
	
	cout << k_inversions() << endl;
	 
	 
	 return 0;
 }
