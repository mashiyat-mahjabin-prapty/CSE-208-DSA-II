#include<iostream>
#include<queue>
#include<vector>
const int INF=10e7;
using namespace std;

class Edge
{
    int source;
    int destination;
    double weight;
    public:
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

class cmp
{
    public: 
    bool operator()(pair<double, int> e1, pair<double, int> e2)
    {
        return e1.first > e2.first;
    }
};

class Graph
{
    int vertices;
    int edges;
    vector<Edge> adj[10000];
    public:
    Graph(int v, int e)
    {
        vertices = v;
        edges = e;
    }

    void addEdge(int s, int d, double w)
    {
        Edge edge(s, d, w);
        adj[s].push_back(edge);
        Edge eee(d, s, w);
        adj[d].push_back(eee);
    }

    /*bool operator< (const Edge& e1, const Edge& e2)
    {
        return e1.getWeight()<e2.getWeight();
    }*/

    void prim()
    {
        priority_queue<pair<double, int>, vector<pair<double, int>>, cmp> pq;
        double key[vertices];
        for (int i = 0; i < vertices; i++)
        {
            key[i] = INF*1.0;
        }
        
        bool visited[vertices]={false};
        Result r[vertices];

        key[0] = 0.0;
        r[0].parent = -1;
        pair<double, int> p0(key[0], 0);

        pq.push(p0);

        while(!pq.empty())
        {
            pair<double, int> extract = pq.top();
            pq.pop();
            int cur = extract.second;
            visited[cur] = true;

            for (int i = 0; i < adj[cur].size(); i++)
            {
                Edge v = adj[cur].at(i);
                if(!visited[v.getDest()])
                {
                    int destination = v.getDest();
                    //cout << destination << endl;
                    double weight = v.getWeight();

                    if(key[destination] > weight)
                    {
                        key[destination] = weight;
                        pair<double, int> n(key[destination], destination);
                        pq.push(n);
                        r[destination].parent = cur;
                        r[destination].weight = weight;
                    }
                }
            }
              
        }
        printPrim(r);
    }

    void printPrim(Result r[])
    {
        cout << "List of edges selected by Prim: {";
        double total = 0.0;

        for(int i = 1; i < vertices; i++)
        {
            cout << "(" << i << "," << r[i].parent << ")" << ":" << r[i].weight << endl;
            total += r[i].weight;
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
    g.prim();
}