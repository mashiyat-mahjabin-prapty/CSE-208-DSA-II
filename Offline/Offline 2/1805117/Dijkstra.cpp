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

class cmp
{
    public: 
    bool operator()(pair<int, int> e1, pair<int, int> e2)
    {
        return e1.first > e2.first;
    }
};

class Graph
{
    int vertices;
    int edges;
    vector<Edge> adj[10000];
    int *parent;
    int *distance;
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> pq;

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
    }

    void Dijkstra(int source, int destination)
    {
        init(source);
        while(!pq.empty())
        {
            int temp = pq.top().second;
            pq.pop();
            for (int i = 0; i < adj[temp].size(); i++)
            {
                relax(adj[temp][i]);
            }
        }
        printResult(source, destination);
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
            pq.push({distance[to], to});
        }
        
    }

    void init(int source)
    {
        distance[source] = 0;
        for(int i = 0; i < vertices; i++)
        {
            if(i != source) distance[i] = INF;
            parent[i] = -1;
            pair<int, int> t;
            t.second = i;
            t.first = distance[i];
            pq.push(t);
        }
    }

    void printResult(int source, int destination)
    {
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
    g.Dijkstra(s, d);
}
