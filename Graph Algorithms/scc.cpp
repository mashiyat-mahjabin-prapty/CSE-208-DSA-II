/*
question f1, f2 [1, n] thakleo zero diye kaaj kora easy so, protome 1 minus korsi then abar answer e 1 plus korsi
*/

#include <bits/stdc++.h>

#define MAX_N 20001
#define ll long long int
using namespace std;
int n, s;

vector < int > adj[MAX_N];
vector < int > rev_adj[MAX_N];

stack < int > S;
bool visited[MAX_N];

int component[MAX_N];
vector < int > components[MAX_N];
int numComponents = 0;

void dfs_1(int x) {
  visited[x] = true;
  for (int i = 0; i < adj[x].size(); i++) {
    if (!visited[adj[x][i]]) dfs_1(adj[x][i]);
  }
  S.push(x);
}

void dfs_2(int x) {
  component[x] = numComponents;
  components[numComponents].push_back(x);
  visited[x] = true;
  for (int i = 0; i < rev_adj[x].size(); i++) {
    if (!visited[rev_adj[x][i]]) dfs_2(rev_adj[x][i]);
  }
}

void Kosaraju() {
  for (int i = 0; i < n; i++)
    if (!visited[i]) dfs_1(i);

  for (int i = 0; i < n; i++)
    visited[i] = false;

  while (!S.empty()) {
    int v = S.top();
    S.pop();
    if (!visited[v]) {
      dfs_2(v);
      numComponents++;
    }
  }
}

int main() {

  cin >> n >> s;
  int f1, f2;
  while (s--) {
    cin >> f1 >> f2;
    f1--; f2--;
    adj[f1].push_back(f2);
    rev_adj[f2].push_back(f1);
  }

  Kosaraju();
  for(ll i=0;i<numComponents;i++) {
  	if(components[i].size() < 2) continue;
  	for(auto x : components[i]) cout << x + 1 << ' ';
  	cout << endl;
  }

  return 0;
}
