#include <iostream>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;
const int SIZE = 100001;
int n, m, k;

// number of coders required for a project
int projects[SIZE];

// Projects dependent on us
vector<int> dependent[SIZE];

// how many other projects are still required
int requirements[SIZE];

void read_input() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		cin >> projects[i];
		
	int a, b;
	
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		dependent[b].push_back(a);
		requirements[a]++;
	}
}

struct Compare {
	bool operator()(int pr1, int pr2) {
		return projects[pr1] > projects[pr2];
	}
};

int calculate() {
	int result = 0;
	int finishedProjects = 0;
	
	// projects indexes, order - descending number of coders
	priority_queue<int, vector<int>, Compare> q;
	
	for (int i = 1; i <= n; i++)
		if (!requirements[i])
			q.push(i);
			
	while (finishedProjects < k) {
		int index = q.top();
		q.pop();
		result = max(result, projects[index]);
		finishedProjects++;
		
		for (vector<int>::iterator it = dependent[index].begin(); it != dependent[index].end(); it++) {
			requirements[(*it)]--;
			if (!requirements[(*it)])
				q.push((*it));
		}
		
	}
			
	return result;
}

int main() {
	ios_base::sync_with_stdio(0);
	
	read_input();
		
	cout << calculate() << endl;
	
	return 0;
}
