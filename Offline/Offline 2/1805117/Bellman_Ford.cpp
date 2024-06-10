#include<iostream>
#include<queue>
#include<vector>
#include<stack>
const int INF=10e7;
using namespace std;

class Edge
{
    int source;
    int destination;
    int weight;
    public:
    Edge(int s, int d, int w)
    {
        source = s;
        destination = d;
        weight = w;
    }
    int getWeight()
    {
        return weight;
    }
    int getDest()
    {
        return destination;
    }
    int getSource()
    {
        return source;
    }
};

class Graph
{
    int vertices;
    int edges;
    vector<Edge> adj[10000];
    int *parent;
    int *distance;
    vector<Edge> edge_arr;

    public:
    Graph(int v, int e)
    {
        vertices = v;
        edges = e;
        parent = new int[vertices];
        distance = new int[vertices];
    }

    void addEdge(int s, int d, int w)
    {
        Edge edge(s, d, w);
        adj[s].push_back(edge);
        edge_arr.push_back(edge);
    }

    bool BF(int source, int destination)
    {
        init(source);
        for (int i = 0; i < vertices-1; i++)
        {
            for (int j = 0; j < edge_arr.size(); j++)
            {
                relax(edge_arr[j]);
            }
        }
        for (int i = 0; i < edges; i++)
        {
            int from = edge_arr[i].getSource();
            int to = edge_arr[i].getDest();
            int w = edge_arr[i].getWeight();

            if(distance[to] > distance[from] + w)
            return false;
        }
        return true;
        
    }

    void relax(Edge e)
    {
        int from = e.getSource();
        int to = e.getDest();
        int w = e.getWeight();
        if(distance[to] > distance[from]+w)
        {
            distance[to] = distance[from]+w;
            parent[to] = from;
        }
        
    }

    void init(int source)
    {
        distance[source] = 0;
        for(int i = 0; i < vertices; i++)
        {
            if(i != source) distance[i] = INF;
            parent[i] = -1;
        }
    }

    void Bellman_Ford(int source, int destination)
    {
        if(!BF(source, destination))
        {
            cout << endl << "The graph contains a negative cycle" << endl;
            return;
        } 

    	//for(int i = 0; i < vertices; i++) cout << distance[i] << " ";
    	cout << endl;
        stack<int> s;
        s.push(destination);
        int m = destination;
        while(m != source)
        {
        	m = parent[m];
            s.push(m);
        }
        cout << "The graph does not contain a negative cycle" << endl;
        cout << "Cost: " << distance[destination] << endl;
        while(!s.empty())
        {
            cout << s.top() << " ";
            if(s.size() != 1) cout << "->";
            else cout << endl;
            s.pop();
        }
    }
};

int main()
{
    int v, e;
    cin >> v >> e;
    int s, d;
    int w;
    Graph g(v, e);
    for(int i = 0; i < e; i++)
    {
        cin >> s >> d >> w;
        g.addEdge(s, d, w);
    }
    cin >> s >> d;
    g.Bellman_Ford(s, d);
}
