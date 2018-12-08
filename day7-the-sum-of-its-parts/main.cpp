#include <queue>
#include <string>
#include <vector>
#include <cstdio>
#include <functional>
using namespace std;
template<typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

template<typename C>
void solve(vector<vector<int>> &graph, vector<int> &used, vector<int> degree, 
    int workers, C cost, string &order, int &t) 
{
    MinHeap<int>            a;  // the queue of available tasks
    MinHeap<pair<int, int>> e;  // the queue of events, i.e. when a certain task finishes

    // make available the tasks with no dependencies
    for (size_t u = 0; u < used.size(); u++) {
        if (degree[u] == 0 && used[u]) a.push(u);
    }

    t = 0; order.clear();
    while (a.size() || e.size()) {
        // find the next moment when a task will finish
        if (e.size()) t = e.top().first;

        // append in order the tasks finishing at moment t
        while (e.size() && e.top().first == t) {
            int u = e.top().second; e.pop(); workers++;
            order.push_back(u + 'A');

            // make available the tasks that depend on the current one
            for (auto v : graph[u]) {
                if (--degree[v] == 0) a.push(v);
            }
        }

        // assign workers to tasks
        while (workers && a.size()) {
            int u = a.top(); a.pop();
            e.push({t + cost(u), u}); workers--;
        }
    }
}

int main() {
    FILE                *f  = fopen("in.txt",  "r");
    FILE                *g  = fopen("out.txt", "w");
    vector<int>         degree(26), used(26);
    vector<vector<int>> graph(26);
    char                u, v;
    int                 t;
    string              order;

    while (fscanf(f, "Step %c must be finished before step %c can begin.\n", &u, &v) != EOF) {
        u -= 'A'; v -= 'A'; degree[v]++; used[u] = 1; used[v] = 1;
        graph[u].push_back(v);
    }
    
    // the first part
    solve(graph, used, degree, 1, [](int c) { return 1; }, order, t);
    fprintf(g, "%s\n", order.c_str());

    // the second part
    solve(graph, used, degree, 5, [](int c) { return 61 + c; }, order, t);
    fprintf(g, "%d\n", t);

    fclose(f);
    fclose(g);

    return 0;
}
