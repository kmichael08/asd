/**
 * Task captain. ASD. Michał Kuźba
 */
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int SIZE = 200001;
int n;

struct Island {
    int number;
    long long x;
    long long y;
};

Island islands[SIZE];
// graph of distances between islands. Only between closest in each direction.
vector<int> graph[SIZE];

// distances from the node 1 to others
long long dist[SIZE];

// is the node processed in Dijkstra's algorithm
bool processed[SIZE];

// distance between two islands
long long distance(Island i1, Island i2) {
    long long d = min(abs(i1.x - i2.x), abs(i1.y - i2.y));
    return d;
}

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> islands[i].x >> islands[i].y;
        islands[i].number = i;
    }
}

bool comp(Island i1, Island i2) {
    if (i1.x == i2.x)
        return i1.y < i2.y;
    return i1.x < i2.x;
}


// compare first on the second coordinate
bool comp_rev(Island i1, Island i2) {
    if (i1.y == i2.y)
        return i1.x < i2.x;
    return i1.y < i2.y;
}

void build_graph() {
    sort(islands + 1, islands + n + 1, comp);

    for (int i = 1; i <= n; i++) {
        if (i != 1)
            graph[islands[i].number].push_back(islands[i - 1].number);
        if (i < n)
            graph[islands[i].number].push_back(islands[i + 1].number);
    }

    sort(islands + 1, islands + n + 1, comp_rev);
    // multiple edges, though it should not be a problem

    for (int i = 1; i <= n; i++) {
        if (i != 1)
            graph[islands[i].number].push_back(islands[i - 1].number);
        if (i < n)
            graph[islands[i].number].push_back(islands[i + 1].number);
    }

    // need to retrieve initial order
    for (int i = 1; i <= n; i++)
        while (i != islands[i].number)
            swap(islands[i], islands[islands[i].number]);


}

void print_graph() {
    for (int i = 1; i <= n; i++) {
        cout << i << " : " << endl;
        for (auto item : graph[i])
            cout << item << " ";
        cout << endl;
    }
}

struct Compare {
    bool operator() (pair<long long, int> p1, pair<long long, int> p2) {
        return p1.first > p2.first;
    }

};

void dijkstra() {

    // distance, node; min of distances
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, Compare> q;
    q.push(make_pair(0, 1));

    // TODO it can be made in a smarter way
    // until we determine the distance to n-th island
    while (!processed[n]) {
        auto top = q.top();
        q.pop();
        if (!processed[top.second]) {
            processed[top.second] = true;
            dist[top.second] = top.first;
            for (int neighbour : graph[top.second])
                q.push(make_pair(top.first + distance(islands[top.second], islands[neighbour]), neighbour));
        }
    }
}

int main() {
    read_input();
    build_graph();
    dijkstra();
    cout << dist[n] << endl;

    return 0;
}
