#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Disjoint_Set
{
    vector<int> parent, rank;

    public:
    Disjoint_Set(int n)
    {
        parent.resize(n);
        rank.resize(n);
    }

    void make_Set(int v)
    {
        parent[v] = v;
        rank[v] = 0;
    }

    void union_Set(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a != b)
        {
            if(rank[a] < rank[b])
            {
                swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b])
            {
                rank[a]++;
            }
            
        }
    }

    int find(int i)
    {
        if(parent[i] == i)
        return i;
        else
        {
            int result = find(parent[i]);
            parent[i] = result;
            return result;
        }
    }
};

class Edge
{
    int source;
    int destination;
    double weight;
    public:
    Edge()
    {
        source = -1;
        destination = -1;
        weight = 0.0;
    }
    Edge(int s, int d, double w)
    {
        source = s;
        destination = d;
        weight = w;
    }
    double getWeight()
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

class Result
{
    public:
    int parent;
    double weight;
};

class Graph
{
    int vertices;
    int edges;
    vector<Edge> adj;
    public:
    Graph(int v, int e)
    {
        vertices = v;
        edges = e;
    }

    void addEdge(int s, int d, double w)
    {
        Edge edge(s, d, w);
        adj.push_back(edge);
    }

    static bool cmp(Edge &e1, Edge &e2)
    {
        return e1.getWeight() < e2.getWeight();
    }

    void kruskal()
    {
        Edge r[vertices];
        Disjoint_Set d(vertices);
        for (int i = 0; i < vertices; i++)
        {
            d.make_Set(i);
        }

        sort(adj.begin(), adj.end(), cmp);
        int j = 0;
        for(int i = 0; i < edges; i++)
        {
            Edge e = adj[i];
            if(d.find(e.getSource()) != d.find(e.getDest()))
            {
                r[j++] = e;
                d.union_Set(e.getSource(), e.getDest());
            }
        }
        printKruskal(r);
    }

    void printKruskal(Edge r[])
    {
        cout << "List of edges selected by Kruskal: {";
        double total = 0.0;

        for(int i = 0; i < vertices-1; i++)
        {
            Edge e = r[i];
            cout << "(" << e.getSource() << "," << e.getDest() << ")" << ":" << e.getWeight() << endl;
            total += e.getWeight();
        }
        cout << "Cost: " << total << endl;
    }
};

int main()
{
    int v, e;
    cin >> v >> e;
    int s, d;
    double w;
    Graph g(v, e);
    for(int i = 0; i < e; i++)
    {
        cin >> s >> d >> w;
        g.addEdge(s, d, w);
    }
    g.kruskal();
}