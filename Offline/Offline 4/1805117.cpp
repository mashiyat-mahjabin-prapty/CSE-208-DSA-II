#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int INF = 10e7+7;
string names[10000];
int N;
int capacity[10000][10000];
int adj[10000][10000];
vector<int> adj_temp[10000];
int won[10000], lost[10000], remaining[10000];

int bfs(int source, int sink, vector<int> &parent)
{
	for(int i = 0; i < parent.size(); i++)
	{
		parent[i] = -1;
	}
	parent[source] = -2;
	queue<pair<int, int> > q;
	q.push({source, INF});
	
	while(!q.empty())
	{
		
		int current = q.front().first;
		int flow = q.front().second;
		q.pop();
		
		for(int i = 0; i < adj_temp[current].size(); i++)
		{
			int temp = adj_temp[current][i];
			if(parent[temp] == -1 && capacity[current][temp])
			{
				parent[temp] = current;
				int cur_flow = min(flow, capacity[current][temp]);
				if(temp == sink) return cur_flow;
				q.push({temp, cur_flow});
			}
		}
	}
	return 0;
}

int maxflow(int v, int source, int sink)
{
	int flow = 0;
	vector<int> parent(v);
	int cur_flow;
	
	while(cur_flow = bfs(source, sink, parent))
	{
		flow += cur_flow;
		int current = sink;
		while(current != source)
		{
			int previous = parent[current];
			capacity[previous][current] -= cur_flow;
			capacity[current][previous] += cur_flow;
			current = previous;
		}
	}
	return flow;
}

bool edmond_karp(int n)
{
	capacity[0][0] = 0;
	int sum = 0;
	int source, sink;
	source = 0;
	int s = N-1;
	sink = ((s*s+s)/2)+1;
	for(int i = 0, j = ((s*(s-1))/2)+1; j < sink; i++)
	{
		
		if(i != n) 
		{
			int pp = won[n]+remaining[n]-won[i];
			if(pp >= 0)
			{
				capacity[j][sink] = pp;
				adj_temp[j].push_back(sink);
				j++;
			}
			else return false;
		}
	}
	
	int x = 1, y = 0, z = 0;
	for(int i = 0; i < N; i++)
	{
		if(i != n)
		{
			for(int j = 0; j < N; j++)
			{
				if(j != n && j > i)
				{
					capacity[0][x] = adj[i][j];
					sum+=capacity[0][x];
					adj_temp[0].push_back(x);
					capacity[x][sink+1-N+y] = INF;
					adj_temp[x].push_back(sink+1-N+y);
					capacity[x][sink+2-N+z] = INF;
					adj_temp[x].push_back(sink+2-N+z);
					x++, z++;
				}
			}
			y++;
			z = y;
		}
	}
	int maxfl= maxflow(sink+1, source, sink);
	
	if(sum == maxfl) return true;
	else return false;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> names[i] >> won[i] >> lost[i] >> remaining[i];
		for(int j = 0; j < N; j++)
		{
			cin >> adj[i][j];
		}
	}
	
	for(int i = 0; i < N; i++)
	{	
		if(!edmond_karp(i)) 
		{
			cout << names[i] << " is eliminated\n";
			cout << "They can win at most " << won[i] << "+" << remaining[i] << " = " << won[i]+remaining[i] << " games\n";
			
		}
	}
	
	return 0;
}

/*
4
Atlanta 83 71 8 0 1 6 1
Philadelphia 80 79 3 1 0 0 2
New_York 78 78 6 6 0 0 0
Montreal 77 82 3 1 2 0 0
*/
