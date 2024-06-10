#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Node
{
	public:
		int key;
		Node * left;
		Node * right;
		int height;
};

// Calculate height
int height (Node * N)
{
	if (N == NULL)
		return -1;
	return N->height;
}

// New node creation
Node * newNode (int key)
{
	Node * node = new Node ();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 0;
	return (node);
}

// Rotate right
Node * rightRotate (Node * y)
{
	Node * x = y->left;
	Node * z = x->right;
	x->right = y;
	y->left = z;
	y->height = max (height (y->left), height (y->right)) + 1;
	x->height = max (height (x->left), height (x->right)) + 1;  
	return x;
}

// Rotate left
Node * leftRotate (Node * x)
{  
	Node * y = x->right;
	Node * z = y->left;
	y->left = x;
	x->right = z;
	x->height = max (height (x->left), height (x->right)) + 1;
	y->height = max (height (y->left), height (y->right)) + 1;
	return y;
}

// Get the balance factor of each node
int getBalanceFactor (Node * N)
{
	if (N == NULL)
		return 0;
	return height (N->left) - height (N->right);
}

Node * rebalance (Node * node) 
{
	node->height = 1 + max (height (node->left), height (node->right));
	int balanceFactor = getBalanceFactor (node);
	if(balanceFactor > 1 || balanceFactor < -1)
	{
		cout << "Height Invariant Violated\n";
		cout << "After rebalancing:";
	}
	if (balanceFactor > 1)
    {
		if (height(node->left->left) > height(node->left->right))
		{
			return rightRotate (node);
		}
		else
		{
			node->left = leftRotate (node->left);
			return rightRotate (node);
		}
    }
  
	if (balanceFactor < -1)
    {
		if (height(node->right->right) > height(node->right->left))
		{
			return leftRotate (node);
		}
		else
		{
			node->right = rightRotate (node->right);
			return leftRotate (node);
		}
	}
	return node;
}

bool find(Node* root, int key)
{
	Node *current = root;
	while(current != NULL)
	{
		if(current->key == key)
		{
			return true;
		}
		current = current->key < key ? current->right : current->left;
	}
	return false;
}

// Insert a node
Node * insertNode (Node * node, int key)
{
	// Find the correct postion and insert the node
	if (node == NULL)
		return (newNode (key));
	if (key < node->key)
		node->left = insertNode (node->left, key);
	else if (key > node->key)
		node->right = insertNode (node->right, key);
	else
		return node;
    // Update the balance factor of each node and
    // balance the tree
    return rebalance(node);
}


 
// Node with minimum value
Node * nodeWithMimumValue (Node * node)
{  
	Node * current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

// Delete a node
Node * deleteNode (Node * root, int key)
{  
    // Find the node and delete it
	if (root == NULL)
		return root;
	if (key < root->key)
		root->left = deleteNode (root->left, key);
	else if (key > root->key)
		root->right = deleteNode (root->right, key);
	else
    { 
		if ((root->left == NULL) || (root->right == NULL))
		{
			Node * temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free (temp);
		}
		else
		{
			Node * temp = nodeWithMimumValue (root->right);
			root->key = temp->key;
			root->right = deleteNode (root->right, temp->key);
		}
	}
	if (root == NULL)
		return root;

	return rebalance(root);
}


 
// Print the tree
void printTree (Node * root)
{
	if(root == NULL)
	{
		return;
	}
	cout << root->key;
	if(root->left != NULL || root->right != NULL)
	{            
		 cout << "(";        
	}        
	printTree(root->left);        
	if(root->left != NULL || root->right != NULL)        
	{            
		cout << ")";        
	}        
	if(root->left != NULL || root->right != NULL)        
	{            
		cout << "(";        
	}        
	printTree(root->right);        
	if(root->left != NULL || root->right != NULL)        
	{            
		cout << ")";        
	}
}


 
int main ()
{
	Node * root = NULL;
	ifstream myfile("input.txt");
	char c;
	int key;
	while(!myfile.eof())
	{
		myfile >> c >> key;
		if(c == 'I')
		{
			root = insertNode (root, key);
			printTree(root);
			cout << endl;
		}
		else if(c == 'D')
		{
			root = deleteNode (root, key);
			printTree(root);
			cout << endl;
		}
		else if(c == 'F')
		{
			bool found = find(root, key);
			if(found)
			cout << "True" << endl;
			else
			cout << "False" << endl;
		}
	}
}
