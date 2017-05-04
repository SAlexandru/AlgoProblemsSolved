#include <array>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100011;

vector<int> L;
array<bool, NMAX> visited;
array<vector<int>, NMAX> G, Gt;
array<vector<int>, NMAX> SCC;

void dfs(int x) {
    visited[x] = true;

    for (const auto& y: G[x]) {
        if (!visited[y]) 
            dfs(y);
    }

    L.push_back(x);
}

void findSCC(int x, const int& number) {
    visited[x] = true;
    SCC[number].push_back(x);

    for (const auto& y: Gt[x]) {
        if (!visited[y]) {
            findSCC(y, number);
        }
    }
}

int main() {
    int N, M, x, y, scc;
    ifstream in  {"ctc.in"};
    ofstream out {"ctc.out"};

    in >> N >> M;
    while (M--) {
        in >> x >> y;
        G[x].push_back(y);
        Gt[y].push_back(x);
    }

    fill(visited.begin(), visited.end(), false);
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) 
            dfs(i);
    }

    scc = 0;
    reverse(L.begin(), L.end());
    fill(visited.begin(), visited.end(), false);
    for (const auto& x: L) {
        if (!visited[x]) {
          findSCC(x, scc++);
        }
    }

    out << scc << '\n';
    for (int i = 0; i < scc; ++i) {
        copy(SCC[i].begin(), SCC[i].end(), ostream_iterator<int>{out, " "});
        out << '\n';
    }

    in.close();
    out.close();

    return 0;
}


