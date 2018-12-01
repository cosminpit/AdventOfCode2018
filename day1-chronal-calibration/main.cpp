#include <set>
#include <vector>
#include <cstdint>
#include <fstream>
using namespace std;

int main() {
    ifstream    f("in.txt");
    ofstream    g("out.txt");
    vector<int> delta;
    int         sum = 0, x;
    
    while (f >> x) sum += x, delta.push_back(x);
    g << sum << "\n";
    
    set<int64_t>    cache;
    int64_t         freq    = 0;
    int             i       = 0;
    while (cache.find(freq) == cache.end()) {
        cache.insert(freq);
        freq += delta[i];
        i = (i + 1) % delta.size();
    }
    g << freq << "\n";
    
    return 0;
}
