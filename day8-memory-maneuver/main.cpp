#include <vector>
#include <fstream>
using namespace std;

int parse(int pos, vector<int> &buff, int &sum, int &value) {
    int         children = buff[pos++]; // the number of children
    int         dataSize = buff[pos++]; // the metadata size
    vector<int> v(children + 1);        // the vector that will contain children values

    // recursively parse every subtree, computing the sum of the
    // metadata and also the value of the root of the subtree
    for (int i = 1; i <= children; i++) {
        pos = parse(pos, buff, sum, v[i]);
    }

    // now it is the time to parse the metadata and compute the
    // value of the current node and update the sum
    value = 0;
    for (int i = 0; i < dataSize; i++) {
        if (children == 0) {
            value += buff[pos];
        } else if (buff[pos] <= children) {
            value += v[buff[pos]];
        }
        sum += buff[pos++];
    }
    
    // return the next ready to be parsed position from buff
    return pos;
}

int main() {
    ifstream    fin("in.txt");
    ofstream    fout("out.txt");
    vector<int> buff;
    int         x, sum = 0, value;
    
    while (fin >> x) buff.push_back(x);
    parse(0, buff, sum, value);
    fout << sum << endl << value << endl;
    
    return 0;
}
