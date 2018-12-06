#include <string>
#include <fstream>
using namespace std;

int collapse(string s, char ignore) {
    int n = 0;
    for (auto c : s) {
        if (tolower(c) == ignore) continue;
        s[n++] = c;
        if (n >= 2 && abs(int(s[n-1]) - s[n-2]) == 32) n -= 2;
    }
    return n;
}

int main() {
    ifstream    f("in.txt");
    ofstream    g("out.txt");
    string      s; f >> s;

    g << collapse(s, '$') << endl;
    
    int best = s.size();
    for (char c = 'a'; c <= 'z'; c++) {
        best = min(best, collapse(s, c));
    }
    g << best << endl;

    return 0;
}
