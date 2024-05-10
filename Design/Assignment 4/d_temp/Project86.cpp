#include <iostream>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Node
{
	friend class Graph;
private:
	Node* next;
	Node* parent;
	char data;
	string color;
	int comp;
	int weight;

public:
	Node(char d)
	{
		weight = INT_MAX;
		next = NULL;
		parent = NULL;
		data = d;
		color = "white";
		comp = 0;
	}
};

class Graph
{
private:
	stack<char>GLB;
	int V;
	Node** start;
	Node** adjList;

public:
	Graph(int size)
	{
		V = size;
		adjList = new Node * [V];
		start = new Node * [V];

		for (int i = 0; i < V; i++)
		{
			start[i] = new Node(i + 'A');
			start[i]->weight = INT_MAX;
			start[i]->parent = NULL;
			adjList[i] = NULL;
		}
	}

	void finEdge()
	{
		for (int i = 0; i < V; i++)
		{
			start[i]->next = adjList[i];
		}
	}

	void setWeight(Node* v, Node* u, int w)
	{
		{
			// Find the edge between nodes v and u and set its weight
			Node* curr = adjList[v->data - 'A'];
			while (curr != nullptr && curr->data != u->data)
			{
				curr = curr->next;
			}

			if (curr != nullptr)
			{
				curr->weight = w;
			}
		}

		{
			// Find the edge between nodes v and u and set its weight
			Node* curr = adjList[u->data - 'A'];
			while (curr != nullptr && curr->data != v->data)
			{
				curr = curr->next;
			}

			if (curr != nullptr)
			{
				curr->weight = w;
			}
		}
	}

	int getWeight(Node* v, Node* u)
	{
		Node* curr = adjList[u->data - 'A'];
		while (curr != nullptr && curr->data != v->data)
			curr = curr->next;

		if (curr != nullptr)
			return curr->weight;

		return -1;
	}

	void addEdge(char v1, char v2, int weight = 0)
	{
		Node* newNode1 = new Node(v2);
		newNode1->next = adjList[v1 - 'A'];
		adjList[v1 - 'A'] = newNode1;

		Node* newNode2 = new Node(v1);
		newNode2->next = adjList[v2 - 'A'];
		adjList[v2 - 'A'] = newNode2;

		setWeight(newNode1, newNode2, weight);

	}

	void Print()
	{
		cout << "  ------\n";
		for (int i = 0; i < V; i++)
		{
			cout << start[i]->data << " | " << "*" << " -|-> ";
			Node* curr = adjList[i];
			while (curr != NULL)
			{
				cout << curr->data <<"("<<curr->weight<<")" << " -> ";
				curr = curr->next;
			}
			cout << "\b\b\b  " << endl;
			cout << "  ------\n";
		}
	}

	void MST_Prims(Node* r)
	{
		start[r->data - 'A']->weight = 0;
		priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> minHeap;

		for (int i = 0; i < V; i++)
			minHeap.push({ start[i]->weight, start[i]->data });

		while (!minHeap.empty())
		{
			char u_data = minHeap.top().second;
			minHeap.pop();

			Node* u = start[u_data - 'A'];
			start[u->data - 'A']->color = "gray";

			Node* v = adjList[u->data - 'A'];

			while (v != NULL)
			{
				int w = getWeight(u, v);
				if (w < start[v->data - 'A']->weight && start[v->data - 'A']->color == "white") 
				{
					v->parent = u;
					start[v->data - 'A']->parent = start[u->data - 'A'];
					v->weight = w;
					start[v->data - 'A']->weight = w;
					minHeap.push({ v->weight, v->data });
				}
				v = v->next;
			}
		}
	}

	void nodeInfo()
	{
		cout << "\033[36mPrims Algo Info\033[0m\n";
		cout << "Node\t[ Cost\tParent\t]\n";
		for (int i = 0; i < V; i++)
		{
			if(start[i]->parent!=NULL)
				cout << start[i]->data << "\t[ " << start[i]->weight << "\t" << start[i]->parent->data << "\t]" << endl;
			else
				cout << start[i]->data << "\t[ " << start[i]->weight << "\tNULL\t]" << endl;
		}
	}


	void PrimsRun(char character = 'D')
	{
		Node* a = new Node(character);
		MST_Prims(a);
	}
};

int main()
{

	{
		cout << "\033[36mUndirected Graph\033[0m\n";
		Graph g1(4);
		cout << "\t\033[36mFirst Prims Lecture Notes Example\033[0m\n";
		g1.addEdge('A', 'C', 1);
		g1.addEdge('A', 'B', 1);

		g1.addEdge('B', 'C', 2);
		g1.addEdge('B', 'D', 5);

		g1.addEdge('C', 'D', 3);
		g1.finEdge();

		cout << "\033[31mAdjacency List\033[0m\n";
		g1.Print();

		g1.PrimsRun();
		g1.nodeInfo();
	}
	cout << endl;
	{
		cout << "\033[36mUndirected Graph\033[0m\n";
		Graph g(10);
		cout << "\t\033[36mAssignment 4 Problem 1.1 Example\033[0m\n";

		g.addEdge('A', 'B', 4);
		g.addEdge('A', 'C', 2);
		g.addEdge('A', 'J', 7);

		g.addEdge('B', 'G', 2);
		g.addEdge('B', 'H', 4);

		g.addEdge('C', 'D', 2);
		g.addEdge('C', 'F', 1);
		g.addEdge('C', 'J', 6);

		g.addEdge('D', 'F', 3);

		g.addEdge('E', 'J', 6);
		g.addEdge('E', 'H', 3);

		g.addEdge('F', 'E', 2);
		g.addEdge('F', 'J', 5);

		g.addEdge('G', 'H', 1);
		g.addEdge('G', 'I', 1);

		g.addEdge('H', 'I', 1);



		cout << "\033[31mAdjacency List\033[0m\n";
		g.Print();

		g.PrimsRun('A');
		g.nodeInfo();


	}
}