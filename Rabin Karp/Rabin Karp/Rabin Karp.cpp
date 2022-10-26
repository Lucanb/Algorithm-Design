#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

vector <int> matches;

const int BASE = 131;
const int MOD = 1e9 + 7;

int main() {

    unsigned long i;
    string A, B;

    fin >> A >> B;

    int BASE_POW = 1;
    for (i = 0; i < A.size(); i++)
        BASE_POW = (long long)BASE_POW * BASE % MOD;

    int ha = 0;
    for (int i = 0; i < A.size(); i++)
        ha = ((long long)ha * BASE + A[i]) % MOD;

    int h1 = 0, h2 = 0;
    for (i = 0; i < A.size() - 1; i++)
        h1 = ((long long)h1 * BASE + B[i]) % MOD;

    int hi = 0;

    for (i = A.size() - 1; i < B.size(); i++) {

        h1 = ((long long)h1 * BASE + B[i]) % MOD;

        hi = (h1 - (long long)h2 * BASE_POW % MOD + MOD) % MOD;

        h2 = ((long long)h2 * BASE + B[i - A.size() + 1]) % MOD;

        if (hi == ha)
            matches.push_back(i - A.size() + 1);

    }

    fout << matches.size() << "\n";

    for (i = 0; i < matches.size() && i < 1000; i++)
        fout << matches[i] << " ";

}