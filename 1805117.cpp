#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

class Node
{
    char color;
    //Node predecessor;
    int start_time, end_time;
    int adjuncts;

public:
    int adj[1000];
    Node()
    {
        this->color = 'W';
        //this->predecessor = NULL;
        adjuncts = 0;
    }

    void updateList(int n)
    {
        adj[adjuncts] = n;
        adjuncts++;
    }

    void setColor(char s)
    {
        color = s;
    }
    /*void setPred(Node n)
    {
        predecessor = new Node();
        predecessor = n;
    }*/

    void setStart(int t)
    {
        start_time = t;
    }

    void setEnd(int t)
    {
        end_time = t;
    }
    int get_adj()
    {
        return adjuncts;
    }
    char get_color()
    {
        return color;
    }
    int getStart()
    {
        return start_time;
    }
    int getEnd()
    {
        return end_time;
    }
};

class Graph
{
private:
    Node *arr;
    int vertex, edges;
    int time;

public:
    Graph()
    {
        cout << "Creating a graph" << endl;
    }

    void input(int F, int S)
    {
        vertex = F;
        edges = S;
        arr = new Node[vertex];
    
        int i, j;
        for (i = 0; i < edges; i++)
        {
            cin >> i >> j;

            arr[i].updateList(j);
        }
    }

    void DFSVisit(Node u)
    {
        time = time+1;
        u.setStart(time);
        u.setColor('G');
        for(int i = 0; i < u.get_adj(); i++)
        {
            if(arr[u.adj[i]].get_color() == 'W')
            {
                //arr[u.adj[i]].setPred(u);
                DFSVisit(arr[u.adj[i]]);
            }
        }
        u.setColor('B');
        time = time+1;
        u.setEnd(time);
    }

    void DFS()
    {
        //cout << "In DFS" << endl;
        time = 0;
        cout << time << endl;
        for (int i = 0; i < vertex; i++)
        {
            if (arr[i].get_color() == 'W')
            {
                DFSVisit(arr[i]);
            }
        }
        cout << time << endl;
    }

    
    ~Graph()
    {
        delete arr;
	}
};

int main ()
{
    Graph g1;
    int firms, share;
    cin >> firms >> share;
    g1.input(firms, share);
    g1.DFS();
}
