#include <map>
#include <array>
#include <vector>
#include <string>
#include <cstdio>
#include <numeric>
using namespace std;

int main() {
    FILE                        *f = fopen("in.txt",  "r");
    FILE                        *g = fopen("out.txt", "w");
    map<int, array<int, 60>>    guards;
    vector<string>              actions;
    int                         y, m, d, hh, mm, id, guard, falls;
    char                        s[256];
    
    while (fgets(s, 256, f)) actions.push_back(s);
    sort(actions.begin(), actions.end());
    
    for (const auto &a : actions) {
        sscanf(a.c_str(), "[%d-%d-%d %d:%d] %s %*c%d\n", &y, &m, &d, &hh, &mm, s, &id);
        if (string("Guard") == s) {
            guard = id;
        } else if (string("falls") == s) {
            falls = mm;
        } else if (string("wakes") == s) {
            for (int i = falls; i < mm; i++) guards[guard][i]++;
        }
     }
    
    int target1 = -1, when1 = -1, sleeps1 = -1;
    int target2 = -1, when2 = -1, sleeps2 = -1;
    for (auto &p : guards) {
        int total = accumulate(p.second.begin(), p.second.end(), 0);
        int peak  = max_element(p.second.begin(), p.second.end()) - p.second.begin();
        int times = p.second[peak];
        if (total > sleeps1) {
            target1 = p.first; when1 = peak; sleeps1 = total;
        }
        if (times > sleeps2) {
            target2 = p.first; when2 = peak; sleeps2 = times;
        }
    }
    fprintf(g, "%d\n", target1 * when1);
    fprintf(g, "%d\n", target2 * when2);

    fclose(f);
    fclose(g);

    return 0;
}
