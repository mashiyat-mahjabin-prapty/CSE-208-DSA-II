#include<iostream>
#include<stack>
#include<vector>

using namespace std;

vector<int> arr[2000];
int time;

void dfs_visit(int u, char color[], int predecessor[], int start[], int end[], stack<int> &s)
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
				dfs_visit(v, color, predecessor, start, end,s);
				cout << "Traversing through vertex " << v << endl;
			}
		}
		color[u] = 'B';
		time = time+1;
		end[u] = time;
		s.push(u);
		cout << u << " vertex becomes black" << endl;
}

void dfs(int v, int e)
{
	char color[2000];
	int predecessor[2000];
	int start[2000];
	int end[2000];
	stack<int> s;
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
			dfs_visit(i, color, predecessor, start, end, s);
		}
	}
	while(!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
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
	}

	dfs(v, e);
}
