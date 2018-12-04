#include <vector>
#include <cstdio>
using namespace std;

int main() {
    FILE                *f = fopen("in.txt",  "r");
    FILE                *g = fopen("out.txt", "w");
    vector<vector<int>> a(1010, vector<int>(1010));
    int                 id, x, y, w, h;
    
    while (fscanf(f, "#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) != EOF) {
        x++; y++; a[x][y]++; a[x][y+h]--; a[x+w][y]--; a[x+w][y+h]++;
    }
    
    int area = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0, s = 0; j < a.size(); j++) {
            s       += a[i][j];
            a[i][j]  = s + (i ? a[i-1][j] : 0);
            area    += (a[i][j] > 1);
        }
    }
    fprintf(g, "%d\n", area);
    
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0, s = 0; j < a.size(); j++) {
            s       += a[i][j];
            a[i][j]  = s + (i ? a[i-1][j] : 0);
        }
    }
    
    fseek(f, SEEK_SET, 0);
    while (fscanf(f, "#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) != EOF) {
        if (w*h == a[x+w][y+h] - a[x][y+h] - a[x+w][y] + a[x][y]) break;
    }
    fprintf(g, "%d\n", id);
    
    return 0;
}
