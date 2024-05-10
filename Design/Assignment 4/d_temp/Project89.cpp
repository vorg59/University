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

	void DijkstraRun(char character = 'D')
	{
		Node* a = new Node(character);
		Dijkstra_1_2(a);
	}

	void Dijkstra_1_2(Node* r)
	{
		start[r->data - 'A']->weight = 0;
		deque<Node*> q;
		q.push_back(start[r->data - 'A']);

		while (!q.empty())
		{
			Node* u = q.front();
			q.pop_front();

			start[u->data - 'A']->color = "gray";

			Node* v = adjList[u->data - 'A'];

			while (v != NULL)
			{
				int w = getWeight(u, v);
				int p_w = start[u->data - 'A']->weight;
				w += p_w;
				if (w < start[v->data - 'A']->weight && start[v->data - 'A']->color == "white")
				{
					v->parent = u;
					start[v->data - 'A']->parent = start[u->data - 'A'];
					v->weight = w;
					start[v->data - 'A']->weight = w;
					if (getWeight(u, v) == 1)
						q.push_front(v);
					else
						q.push_back(v);
				}
				v = v->next;
			}
		}
	}

	void nodeInfo(char source = 'D', char destination = 'D')
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
		pathPrint(source, destination);
	}

	void pathPrint(char source, char destination)
	{
		bool inf = false;
		cout << "\033[36mDijkstra Algo Info\033[0m\n";
		cout << "\x1b[31m" << source << " -> " << destination << " Path:\x1b[0m\n\t";
		stack<char>s;
		Node* v = start[destination - 'A'];
		while (v->data != 'A')
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
			cout << "\b\b\b  \n\tcost = " << start[destination - 'A']->weight << endl;
		}
		inf = false;
	}
};

int main()
{
	{
		cout << "\033[36mDirected Graph\033[0m\n";
		cout << "\t\033[36mFirst Dijkstra Lecture Notes Example\033[0m\n";
		Graph g(5);
		g.addEdge('A', 'C', 1);
		g.addEdge('A', 'B', 2);

		g.addEdge('B', 'E', 1);
		g.addEdge('B', 'D', 1);
		g.addEdge('B', 'C', 2);

		g.addEdge('C', 'E', 2);
		g.addEdge('C', 'D', 2);
		g.addEdge('C', 'B', 1);

		g.addEdge('E', 'D', 1);

		cout << "\033[31mAdjacency List\033[0m\n";
		g.Print();

		g.DijkstraRun('A');
		g.nodeInfo('A', 'D');
	}
}