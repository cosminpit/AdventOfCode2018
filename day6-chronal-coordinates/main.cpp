#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    FILE        *f = fopen("in.txt",  "r");
    FILE        *g = fopen("out.txt", "w");
    vector<int> x, y;
    int         px, py, minX = 1000, maxX = 1000, minY = 1000, maxY = 0;

    while (fscanf(f, "%d, %d\n", &px, &py) != EOF) {
        x.push_back(px); y.push_back(py);
        minX = min(minX, px); maxX = max(maxX, px);
        minY = min(minY, py); maxY = max(maxY, py);
    }
    
    vector<int> cnt(x.size());
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            int         dmin = 1000;
            vector<int> p;
            
            for (int k = 0; k < x.size(); k++) {
                int d = abs(x[k] - i) + abs(y[k] - j);
                if (d < dmin) {
                    dmin = d; p = {k};
                } else if (d == dmin) {
                    p.push_back(k);
                }
            }

            if (p.size() == 1) {
                int k = p[0];
                if (cnt[k] == -1) continue; else cnt[k]++;
                if ((i == minX || i == maxX) && (j == y[k])) cnt[k] = -1;
                if ((j == minY || j == maxY) && (i == x[k])) cnt[k] = -1;
            }
        }
    }
    fprintf(g, "%d\n", *max_element(cnt.begin(), cnt.end()));

    int area = 0, maxSum = 10000;
    for (int i = maxX - maxSum; i <= minX + maxSum; i++) {
        for (int j = maxY - maxSum; j <= minY + maxSum; j++) {
            int s = 0;
            for (int k = 0; k < x.size() && s < maxSum; k++) {
                s += abs(x[k] - i) + abs(y[k] - j);
            }
            area += (s < maxSum);
        }
    }
    fprintf(g, "%d\n", area);

    fclose(f);
    fclose(g);

    return 0;
}
