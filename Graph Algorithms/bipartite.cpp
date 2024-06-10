#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
using std::vector;
using std::queue;

#define MAX 100010

vector <ll> color(MAX, 0);

bool bipartite(vector<vector<ll> > &adj, ll x)
{
	queue <ll> q;
	q.push(x);
	color[x] = 1;
	while(!q.empty()){
		ll n = q.front();
		q.pop();
		for(ll i=0;i<adj[n].size();i++){
			if(!color[adj[n][i]]){
				color[adj[n][i]] = 3 - color[n];
				q.push(adj[n][i]);
			}
			else{
				if(color[n] == 1 && color[adj[n][i]] == 1) return true; // V niche to dekho V
				if(color[n] == 2 && color[adj[n][i]] == 2) return true; // if matches then returns true
			}
		}
	}
	return false;
}

int main() {
  	ll n, m;
  	std::cin >> n >> m;
  	vector<vector<ll> > adj(n, vector<ll>());
  	for (ll i = 0; i < m; i++) {
    	ll x, y;
    	std::cin >> x >> y;
    	adj[x - 1].push_back(y - 1);
    	adj[y - 1].push_back(x - 1);
  	}
  	cout << (bipartite(adj, 0) ? "NOPE" : "YUP") << endl;
  	return 0;
}
