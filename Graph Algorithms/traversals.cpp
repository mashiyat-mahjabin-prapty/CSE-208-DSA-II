#include<iostream>
#include<queue>
#include<vector>

using namespace std;

vector<int> arr[2000];
int time;

void bfs(int u, int V, int E)
{
	queue<int> q;
	int temp;
	char color[2000];
	int predecessor[2000];
	int level[2000];
	for(int i = 0; i < V; i++)
	{
		color[i] = 'W';
		//cout << i << " vertex becomes white" << endl;
		predecessor[i] = -1;
		level[i] = 1000007; 
	}
	
	color[u] = 'G';
	cout << u << " vertex becomes grey" << endl;
	level[u] = 0;
	
	q.push(u);
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		for(int i = 0; i < arr[temp].size(); i++)
		{
			int v = arr[temp][i];
			if(color[v] == 'W')
			{
				color[v] = 'G';
				cout << v << " vertex becomes grey" << endl;
				predecessor[v] = temp;
				level[v] = level[temp]+1;
				q.push(v);
				cout << "Traversing through vertex " << v << endl;
			}
		}
		color[temp] = 'B';
		cout << temp << " vertex becomes black and level of " << temp << " is " << level[temp] << endl;
	}
}

void dfs_visit(int u, char color[], int predecessor[], int start[], int end[])
{
	time = time+1;
	start[u] = time;
	color[u] = 'G';
	for(int i = 0; i < arr[u].size(); i++)
		{
			int v = arr[u][i];
			if(color[v] == 'W')
			{
				color[v] = 'G';
				cout << v << " vertex becomes grey" << endl;
				predecessor[v] = u;
				dfs_visit(v, color, predecessor, start, end);
				cout << "Traversing through vertex " << v << endl;
			}
		}
		color[u] = 'B';
		time = time+1;
		end[u] = time;
		cout << u << " vertex becomes black" << endl;
}

void dfs(int v, int e)
{
	char color[2000];
	int predecessor[2000];
	int start[2000];
	int end[2000];
	for(int i = 0; i < v; i++)
	{
		color[i] = 'W';
		//cout << i << " vertex becomes white" << endl;
		predecessor[i] = -1; 
	}
	time = 0;
	for(int i = 0; i < v; i++)
	{
		if(color[i] == 'W')
		{
			dfs_visit(i, color, predecessor, start, end);
		}
	}
}

int main()
{
	int v, e;
	cin >> v >> e;
	
	int j, k;
	for(int i = 0; i < e; i++)
	{
		cin >> j >> k;
		arr[j].push_back(k);
		arr[k].push_back(j); 
	}

	bfs(4, v, e);	
	dfs(v, e);
}
