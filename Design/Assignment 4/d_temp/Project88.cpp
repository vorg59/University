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
	int edgeCost;

public:
	Node(char d)
	{
		weight = INT_MAX;
		edgeCost = INT_MAX;
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

	void setWeight(Node* v, Node* u, int w)
	{
		Node* curr = adjList[u->data - 'A'];
		while (curr != nullptr && curr->data != v->data)
			curr = curr->next;

		if (curr != nullptr)
			curr->weight = w;
	}

	int getWeight(Node* u, Node* v)
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
				cout << curr->data << "(" << curr->weight << ")" << " -> ";
				curr = curr->next;
			}
			cout << "\b\b\b  " << endl;
			cout << "  ------\n";
		}
	}

	void DijkstraRun(char source = 'D')
	{
		Node* a = new Node(source);
		minEdgeDijkstra(a);
	}

	void minEdgeDijkstra(Node* r) 
	{
		start[r->data - 'A']->weight = 0;
		start[r->data - 'A']->edgeCost = 0;

		priority_queue<pair<pair<int, int>, char>, vector<pair<pair<int, int>, char>>, greater<pair<pair<int, int>, char>>> minHeap;

		for (int i = 0; i < V; i++)
			minHeap.push({ {start[i]->weight, start[i]->edgeCost}, start[i]->data });

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
				int p_w = start[u->data - 'A']->weight;
				w += p_w;
				int edgeCount = start[u->data - 'A']->edgeCost + 1;

				if (w < start[v->data - 'A']->weight || (w == start[v->data - 'A']->weight && edgeCount < start[v->data - 'A']->edgeCost)) 
				{
					v->parent = u;
					start[v->data - 'A']->parent = start[u->data - 'A'];
					v->weight = w;
					start[v->data - 'A']->weight = w;
					v->edgeCost = edgeCount; 
					start[v->data - 'A']->edgeCost = edgeCount;
					minHeap.push({ {v->weight, v->edgeCost}, v->data });
				}

				v = v->next;
			}
		}
	}

	void nodeInfo(char source = 'D')
	{
		cout << "\033[36mNode Info\033[0m\n";
		cout << "\x1b[31mNode\t[ Cost\tParent\t]\x1b[0m\n";
		for (int i = 0; i < V; i++)
		{
			if (start[i]->parent != NULL)
				cout << start[i]->data << "\t[ " << start[i]->weight << "\t" << start[i]->parent->data << "\t]" << endl;
			else
				cout << start[i]->data << "\t[ " << start[i]->weight << "\tNULL\t]" << endl;
		}
		pathPrint(source);
	}

	void pathPrint(char source)
	{
		bool inf = false;
		cout << "\033[36mDijkstra Algo Info\033[0m\n";
		for (int i = 0; i < V; i++)
		{
			cout << "\x1b[31m" << source << " -> " << start[i]->data << " Path:\x1b[0m\n\t";
			stack<char>s;
			Node* v = start[i];
			while (v->data != source)
			{
				s.push(v->data);
				v = v->parent;
				if (v == NULL)
				{
					inf = true;
					cout << "INFINITY\n";
					break;
				}
			}
			if (!inf)
			{
				s.push(source);
				while (!s.empty())
				{
					cout << s.top() << " -> ";
					s.pop();
				}
				cout << "\b\b\b  \n\tcost = " << start[i]->weight << endl;
				cout << "\tedgeCost = " << start[i]->edgeCost << endl;
			}
			inf = false;
		}
	}

};

int main()
{
	{
		cout << "\033[36mDirected Graph\033[0m\n";
		cout << "\t\033[36mGeeks For Geeks Example\033[0m\n";
		Graph g(5);

		g.addEdge('A', 'E', 10);
		g.addEdge('A', 'B', 1);

		g.addEdge('B', 'C', 4);

		g.addEdge('C', 'D', 7);

		g.addEdge('E', 'D', 2);

		cout << "\033[31mAdjacency List\033[0m\n";
		g.Print();

		g.DijkstraRun('A');
		g.nodeInfo('A');
	}

	{
		cout << "\033[36mDirected Graph\033[0m\n";
		cout << "\t\033[36mGeeks For Geeks Example Modded\033[0m\n";
		Graph g(5);

		g.addEdge('A', 'E', 10);
		g.addEdge('A', 'B', 1);

		g.addEdge('B', 'D', 11);
		g.addEdge('B', 'C', 4);

		g.addEdge('C', 'D', 7);

		g.addEdge('E', 'D', 2);

		cout << "\033[31mAdjacency List\033[0m\n";
		g.Print();

		g.DijkstraRun('A');
		g.nodeInfo('A');
	}
}