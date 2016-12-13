#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

const int SIZE = 1000001;
int manifestacje[SIZE];

int n, m;

struct query {
    int time;
    int index;
    int number = 1;
    int how_many;
};

/**
 * Compare for the priority queue, maximize the number of people, then minimize
 * the number of manifestation
 */
struct Compare {
    bool operator() (pair<int, int> v1, pair<int, int> v2) {
        if (v1.first == v2.first)
            return v1.second > v2.second;
        return v1.first < v2.first;
    }
};

/**
 * Moments when new person comes, number of manifestation.
 */
vector<pair<int, int> > starts;
/**
 * Moments when a person ends a manifestation, and number of this manifestation.
 */
vector<pair<int, int> > endings;
/**
 * Queries, processed offline.
 */
vector<query> queries;

void read_input() {
    cin >> n >> m;
    int p, k, r;

    for (int i = 1; i <= n; i++) {
        cin >> p >> k >> r;
        starts.push_back(make_pair(p, r));
        endings.push_back(make_pair(k, r));
    }

    int t;

    for (int i = 1; i <= m; i++) {
        cin >> t;
        query q;
        q.time = t;
        q.index = i;
        queries.push_back(q);

    }

}

bool comp(query q1, query q2) {
    return q1.time < q2.time;
}

/**
 * Sort starts, ends and queries.
 */
void process_input() {
    sort(starts.begin(), starts.end());
    sort(endings.begin(), endings.end());
    sort(queries.begin(), queries.end(), comp);
}

/**
 * Answer all queries.
 */
void answer_queries() {
    /**
     *  Keeps the size and the number of the manifestation. Values may be not actual.
     *  We need to check it.
     */
    priority_queue<pair<int, int>, vector<pair<int, int> >, Compare> values;

    for (int i = 1; i <= SIZE; i++) {
        values.push(make_pair(0, i));
    }

    vector<pair<int, int> >::iterator it_st = starts.begin(), it_end = endings.begin();
    vector<query>::iterator it_q = queries.begin();

    while (it_q != queries.end()) {
        int st_man = (it_st == starts.end() ? SIZE + 1 : (*it_st).first);
        int end_man = (it_end == endings.end() ? SIZE + 1 : (*it_end).first);
        int q_man = (*it_q).time;

        vector<int> v = {st_man, end_man, q_man};
        int mini = *min_element(v.begin(), v.end());

        /**
         * Order is important. First new people come. Then we answer the query
         * for the given moment, then people end demonstrating.
         */

        // new person comes
        if (st_man == mini) {
            int nr = (*it_st).second;
            manifestacje[nr]++;
            values.push(make_pair(manifestacje[nr], nr));
            it_st++;
        }
        else if(q_man == mini) // respond a query
        {
            while (!values.empty()) {
                pair<int, int> p = values.top();
                // Validate the correctness of the item.
                if (p.first == manifestacje[p.second]) {
                    (*it_q).number = p.second;
                    (*it_q).how_many = p.first;
                    break;
                }
                values.pop();
            }
            it_q++;
        }

        else // person ends a manifestation
         {
            int nr = (*it_end).second;
            manifestacje[nr]--;
            values.push(make_pair(manifestacje[nr], nr));
            it_end++;
        }
    }
}

bool comp_final(query q1, query q2) {
    return q1.index < q2.index;
}

/**
 * Print the answers for the queries in the order of coming
 * on the input.
 */
void print_results() {
    sort(queries.begin(), queries.end(), comp_final);
    for (auto it = queries.begin(); it != queries.end(); it++)
        cout << (*it).number << " " << (*it).how_many << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    read_input();
    process_input();
    answer_queries();
    print_results();

    return 0;
}
