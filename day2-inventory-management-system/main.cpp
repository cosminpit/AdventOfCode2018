#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
using namespace std;

int main() {
    ifstream        fin("in.txt");
    ofstream        fout("out.txt");
    vector<string>  boxes;
    string          s;
    int             cnt2 = 0, cnt3 = 0;
    
    while (fin >> s) {
        boxes.push_back(s);
        vector<int>  c(26);
        for (auto letter : s) c[letter - 'a']++;
        for (int i = 0; i < c.size(); i++) if (c[i] == 2) {
            cnt2++; break;
        }
        for (int i = 0; i < c.size(); i++) if (c[i] == 3) {
            cnt3++; break;
        }
    }
    fout << cnt2 * cnt3 << "\n";
    
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            int cnt = 0, pos = 0;
            for (int k = 0; k < boxes[i].size(); k++) {
                if (boxes[i][k] != boxes[j][k]) {
                    cnt++; pos = k;
                }
            }
            if (cnt == 1) {
                fout << boxes[i].substr(0, pos) + boxes[i].substr(pos + 1, boxes[i].size() - pos - 1) << "\n";
            }
        }
    }
    
    return 0;
}
