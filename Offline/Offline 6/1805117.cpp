#include<iostream>
#include<list>
#include<algorithm>
#include<map>
#include<fstream>
using namespace std;

struct Node
{
	int data, degree;
	Node *child, *parent, *sibling;
};

class binomial_heap
{
	list<Node*> heap;
	map<int, Node*> mp;
	
	Node *mergeNodes(Node *n1, Node *n2)
	{
		if(n1->data < n2->data)
		{
			swap(n1, n2);
		}
		n2->parent = n1;
		n2->sibling = n1->child;
		n1->child = n2;
		n1->degree++;
		
		return n1;
	}
	
	void rearrange()
	{
		if(heap.size() <= 1)
		{
			return;
		}
		
		list<Node*>::iterator i1, i2, i3;
		i1 = heap.begin();
		i2 = heap.begin();
		i3 = heap.begin();
		
		if(heap.size() == 2)
		{
			i2 = i1; 
			i2++;
			i3 = heap.end();
		}
		
		else
		{
			i2++;
			i3 = i2;
			i3++;
		}
		
		while(i1 != heap.end())
		{
			if(i2 == heap.end())
			{
				i1++;
			}
			else if((*i1)->degree < (*i2)->degree)
			{
				i1++;
				i2++;
				if(i3 != heap.end())
				{
					i3++;
				}
			}
			else if(i3 != heap.end() && (*i1)->degree == (*i2)->degree 
			&& (*i1)->degree == (*i3)->degree)
			{
				i1++;
				i2++;
				i3++;
			}
			else if((*i1)->degree == (*i2)->degree)
			{
				*i1 = mergeNodes(*i1, *i2);
				i2 = heap.erase(i2);
				if(i3 != heap.end())
				{
					i3++;
				}
			}
		}
	}
	
	Node* find(Node *temp, int k) {
		Node *node = NULL;
        while (temp != NULL) {
            if (temp->data == k) {
                node = temp;
                break;
            }
  
            if (temp->child == NULL)
                temp = temp->sibling;
  
            else {
                node = find(temp->child, k);
                if (temp == NULL)
                    temp = temp->sibling;
                else
                    break;
            }
		}
            return node;
	}
	
	public:
	struct DegreeComparator
	{
		bool operator ()(Node *n1, Node *n2)
		{
			if(n1->degree < n2->degree)
				return true;
			return false;
		}
	};
	Node *initNode(int value)
	{
		Node *temp = new Node;
		temp->data = value;
		temp->degree = 0;
		temp->child = NULL;
		temp->parent = NULL;
		temp->sibling = NULL;
		mp[temp->data] = temp;
		return temp;
	}
	
	
	list<Node*> union_heaps(list<Node*> h1, list<Node*> h2)
	{
		h1.sort(DegreeComparator());
		h2.sort(DegreeComparator());
		if(h1.empty())
		{
			return h2;
		}
		list<Node*> h;
		list<Node*>::iterator i1 = h1.begin();
		list<Node*>::iterator i2 = h2.begin();
		
		while(i1 != h1.end() && i2 != h2.end())
		{
			if((*i1)->degree <= (*i2)->degree)
			{
				h.push_back(*i1);
				i1++;
			}
			else
			{
				h.push_back(*i2);
				i2++;
			}
		}
		
		while(i1 != h1.end())
		{
			h.push_back(*i1);
			i1++;
		}
		
		while(i2 != h2.end())
		{
			h.push_back(*i2);
			i2++;
		}
		
		return h;
	}
	
	void insert(int value)
	{ 
		Node* temp = initNode(value);
		
		list<Node*> singular;
		singular.push_back(temp);
		heap = union_heaps(heap, singular);
		rearrange();
		cout << "Inserted " << value << endl;
	}
	
	Node* maximum()
	{
		list<Node*>::iterator it = heap.begin();
		Node *max = *it;
		while(it != heap.end())
		{
			if((*it)->data > max->data)
			{
				max = *it;
			}
			it++;
		}
		return max;
	}
	
	int getMax()
	{
		return maximum()->data;
	}
	
	int extractMax()
	{
		list<Node*> temp, children;
		
		Node *max;
		max = maximum();
		
		list<Node*>::iterator it=heap.begin();
		while(it != heap.end())
		{
			if(*it != max)
			{
				temp.push_back(*it);
			}
			it++;
		}
		Node *max_child = max->child;
		Node *p;
		
		while(max_child)
		{
			p = max_child;
			max_child = max_child->sibling;
			p->sibling = NULL;
			p->parent = NULL;
			children.push_back(p);
		}
		heap = union_heaps(temp, children);
		rearrange();
		mp.erase(max->data);
		return max->data;
	}
	void increaseKey(int prev_value, int new_value)
	{
		Node *node = mp[prev_value];
		if(node == NULL)
		{
			cout << "Key does not exist\n";
			return;
		}
		node->data = new_value;
		Node *parent = node->parent;
		
		while(parent != NULL && node->data > parent->data)
		{
			mp.erase(parent->data);
			mp.erase(node->data);

			swap(parent->data, node->data);
			
			mp[parent->data] = parent;
			mp[node->data] = node;
			
			node = parent;
			parent = parent->parent;
		}
		cout << "Increased " << prev_value << ". The new value is " << new_value << endl;
	}  
	void printTree(Node *n)
	{
		int arr[n->degree+1];
		int p = (n->degree);
		arr[0] = 1;
		
		for(int i = 1; i < (n->degree)+1; i++)
		{
			int j = arr[i-1];
			j*= n->degree-i+1;
            j/= i;
            arr[i] = j;
		}
		int i = 0;
		while(n)
		{
			Node *temp = n;
			cout << "Level " << i << ": ";
			for(int k = 0; k < arr[i]; k++)
			{
				cout << n->data << " ";
				n = n->sibling;
			}
			cout << endl;
			i++;
			n = temp->child;
		}
	}
	void printHeap()
	{
		cout << "Printing Binomial Heap\n";
		cout << "-----------------------\n";
		list<Node*>::iterator it = heap.begin();
		while(it != heap.end())
		{
			cout << "Binomial Tree, B" << (*it)->degree << endl;
			printTree(*it);
			cout << endl;
			it++;
		}
		cout << "-----------------------\n";
		cout << endl;
	}
};

int main()
{
	binomial_heap bheap;
	
	ifstream myfile("input.txt");
	string s;
	int key;
	int prev, upd;
	while(!myfile.eof())
	{
		myfile >> s;
		if(s == "PRI")
		{
			bheap.printHeap();
		}
		else if(s == "EXT")
		{
			cout <<	"ExtractMax returned " << bheap.extractMax() << endl;
		}
		else if(s == "FIN")
		{
			cout << "FindMax returned " << bheap.getMax() << endl;
		}
		else if(s == "INS")
		{
			myfile >> key;
			bheap.insert(key);
		}
		else if(s == "INC")
		{
			myfile >> prev >> upd;
			bheap.increaseKey(prev, upd);
		}
		else
		{
			cout << "Wrong command" << endl;
		}
	}
}


