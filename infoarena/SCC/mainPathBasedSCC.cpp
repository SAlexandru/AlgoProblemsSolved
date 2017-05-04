#include <stack>
#include <array>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100011;

int C;
stack<int> S, P;
vector<vector<int>> SCC;
array<bool, NMAX> assigned;
array<int, NMAX> idxPreord;
array<vector<int>, NMAX> G;

void dfs(int x) {
    S.push(x);
    P.push(x);
    idxPreord[x] = ++C;

    for (const auto& y: G[x]) {
        if (idxPreord[y] == 0) {
            dfs(y);
        }
        else if (!assigned[y]) {
            for (; !P.empty() && idxPreord[y] < idxPreord[P.top()]; P.pop()); 
        }
    }

    if (!P.empty() && x == P.top()) { //found the root of the SCC
        P.pop();
        assigned[x] = true;
        SCC.emplace_back(0);
        for (SCC.back().push_back(x); S.top() != x; S.pop()) {
            SCC.back().push_back(S.top());
            assigned[S.top()] = true;
        }

        S.pop();
    }
}

int main() {
    int N, M, x, y;
    ifstream in  {"ctc.in"};
    ofstream out {"ctc.out"};

    in >> N >> M;
    while (M--) {
        in >> x >> y;
        G[x].push_back(y);
    }

    fill(idxPreord.begin(), idxPreord.end(), 0);
    fill(assigned.begin(), assigned.end(), false);
    for (int i = 1; i <= N; ++i) {
        if (0 == idxPreord[i]) {
            dfs(i);
        }
    }

    out << SCC.size() << '\n';
    for (size_t i = 0; i < SCC.size(); ++i) {
        copy(SCC[i].begin(), SCC[i].end(), ostream_iterator<int>{out, " "});
        out << '\n';
    }

    in.close();
    out.close();

    return 0;
}



