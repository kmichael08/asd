// Zadanie Bazarek - Lab1
#include<iostream>
using namespace std;
const int SIZE = 1000002;
const int INF = 2000000000;
const int NEG = -1;

int products[SIZE];
int days[SIZE];
long long suffix_sum[SIZE];
int pref_max_even[SIZE], pref_max_odd[SIZE], suff_min_even[SIZE], suff_min_odd[SIZE];

void calculate_arrays(int n) 
{
	suffix_sum[n] = products[n];	
	for (int i = n - 1; i >= 1; i--)
		suffix_sum[i] = suffix_sum[i + 1] + products[i];
	
	pref_max_even[0] = NEG;
	pref_max_odd[0] = NEG;
	
	for (int i = 1; i <= n; i++)
		if(products[i] % 2 == 0) 
		{
			pref_max_even[i] = max(pref_max_even[i - 1], products[i]);
			pref_max_odd[i] = pref_max_odd[i - 1];
		}
		else 
		{
			pref_max_odd[i] = max(pref_max_odd[i-1], products[i]);
			pref_max_even[i] = pref_max_even[i - 1];
		}
	
	suff_min_even[n + 1] = INF;
	suff_min_odd[n + 1] = INF;
	
	for (int i = n; i >= 1; i--)
		if(products[i] % 2 == 0) 
		{
			suff_min_even[i] = min(suff_min_even[i + 1], products[i]);
			suff_min_odd[i] = suff_min_odd[i + 1];
		}
		else 
		{
			suff_min_odd[i] = min(suff_min_odd[i + 1], products[i]);
			suff_min_even[i] = suff_min_even[i + 1];
		}
	
}

void print_array(long long tab[], int n) 
{
	for (int i = 1; i <= n; i++)
		cout << tab[i] << " ";
	cout << endl;
	
}

void print_array(int tab[], int n) 
{
	for (int i = 1; i <= n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

void print_arrays(int n) 
{
	print_array(suff_min_even, n);
	print_array(suff_min_odd, n);
	print_array(pref_max_even, n);
	print_array(pref_max_odd, n);
	print_array(suffix_sum, n);
}

long long money(int amount, int n) 
{
	int index = n - amount + 1;
	
	long long total = suffix_sum[index];
	
	if(total % 2 == 1)
		return total;
	
	long long total1 = NEG, total2 = NEG;
	
	if (pref_max_even[index - 1] != NEG && suff_min_odd[index] != INF)
		total1 = total + pref_max_even[index - 1] - suff_min_odd[index];
	
	if (pref_max_odd[index - 1] != NEG && suff_min_even[index] != INF)
		total2 = total + pref_max_odd[index - 1] - suff_min_even[index];
	
	return max(total1, total2);
}

int main() 
{
		
	ios_base::sync_with_stdio(0);	
		
	int n;
	
	int m;
	
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> products[i];
	
	cin >> m;
	for(int i = 1; i <= m; i++)
		cin >> days[i];
	
	calculate_arrays(n);
	
	// debug 
	// print_arrays(n);
	
	for (int i = 1; i <= m; i++)
		cout << money(days[i], n) << endl;
	
	return 0;
}
