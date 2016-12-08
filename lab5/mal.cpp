/**
 * Malowanie autostrady
 */

#include <iostream>
#include <set>
using namespace std;

int total = 0;
set<pair<int, int> > ranges;


void add_interval (int a, int b);

void delete_interval (int a, int b);

void add_interval (int a, int b) {
	set<pair<int, int> >::iterator it, pom;
	
	it = ranges.upper_bound(make_pair(a, a));
	
	if (it != ranges.begin()) 
		it--;
	
	
	if (it != ranges.end() && (*it).second < a)
		it++;
	
	pom = it;
	
	int fst = (*it).first;
	int snd = (*it).second;
		
	while (b >= fst && it != ranges.end()) {
		it++;
				
		if (a >= fst && b <= snd)
			return;
			
		
		if (a >= fst) {
			a = fst;
			ranges.erase(pom);
			total -= (snd - fst + 1);
		}
		else
		if (b <= snd) {
			b = snd;
			ranges.erase(pom);
			total -= (snd - fst + 1);
		}
		else
		if (b >= snd) {
			ranges.erase(pom);
			total -= (snd - fst + 1);
		}
		
		pom = it;
		
		fst = (*it).first;
		snd = (*it).second;
		
	}
	
	total += (b - a + 1);
	
	ranges.insert(make_pair(a, b));
}

void delete_interval (int a, int b) {
	set<pair<int, int> >::iterator it, pom;
	
	it = ranges.lower_bound(make_pair(a, a));
	
	if (it != ranges.begin()) 
		it--;
	
	
	if (it != ranges.end() && (*it).second < a)
		it++;
	
	pom = it;
	
	int fst = (*it).first;
	int snd = (*it).second;
	
		
	while (b >= fst && it != ranges.end()) {
						
		pom = it;
		
		it++;	
		
		if (a <= fst)
			a = fst;
		
		if (a > fst) {
			ranges.insert(make_pair(fst, a - 1));
			total += (a - fst);
			a = fst;
		}
		
		if (a == fst) {
			ranges.erase(pom);
			total -= (snd - fst + 1);
			
			if (b < snd) {
				ranges.insert(make_pair(b + 1, snd));
				total += (snd - b);				
			}
		}
		
		fst = (*it).first;
		snd = (*it).second;	
		
	}
	
}

// debug printing of the ranges
void print_ranges() {
	for (set<pair<int, int> >::iterator it = ranges.begin(); it != ranges.end(); it++)
		cout << (*it).first << " " << (*it).second << endl;
	
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	int a, b;
	char c;
	
	for (int i = 1; i <= m; i++) {
		
		cin >> a >> b >> c;
		
		if (c == 'C')
			delete_interval(a, b);
		else
			add_interval(a, b);
			
			
		cout << total << endl;	
	}
	
	
	return 0;
}
