#include<iostream>
#include<fstream>
const int INF=10e7;
using namespace std;

class Graph
{
    int vertices;
    int edges;
    int adj[100][100];
    int fw[100][100];
    public:
    Graph(int v, int e)
    {
        vertices = v;
        edges = e;
    
        for(int i = 0; i < vertices; i++)
        {
            for(int j = 0; j < vertices; j++)
            {
                if(i == j) adj[i][j] = 0;
                else adj[i][j] = INF;
            }
        }
    }

    void addEdge(int s, int d, int w)
    {
        adj[s-1][d-1] = w;
    }
  
    void Floyd_Warshall()
    {
        for(int i = 0; i < vertices; i++)
        {
            for(int j = 0; j < vertices; j++)
            {
                fw[i][j] = adj[i][j];
            }
        }
        
        for (int k = 0; k < vertices; k++)
        {
            for(int i = 0; i < vertices; i++)
            {
                for(int j = 0; j < vertices; j++)
                {
                    if (fw[i][k] + fw[k][j] < fw[i][j])
                        fw[i][j] = fw[i][k] + fw[k][j];
                }
            }
        }
        printresult();
    } 

    void printresult()
    {
        cout << "Shortest distance matrix:" << endl;
        for(int i = 0; i < vertices; i++)
        {
            for(int j = 0; j < vertices; j++)
            {
                if(fw[i][j] == INF) printf("%4s", "INF");
                else printf("%4d", fw[i][j]);
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    int v, e;
    cin >> v >> e;
    int s, d, w;
    Graph g(v, e);
    for(int i = 0; i < e; i++)
    {
        cin >> s >> d >> w;
        g.addEdge(s, d, w);
    }
    g.Floyd_Warshall();
}