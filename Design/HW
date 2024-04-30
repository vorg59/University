#include <iostream>
#include <queue>
#include <stack>
using namespace std;

stack<char>GLB;

class Node
{
	friend class Graph;
private:
	Node* next;
	char data;
	string color;
	Node* parent;
	int dist;
	int comp;

public:
	Node(char d)
	{
		next = NULL;
		data = d;
		color = "white";
		parent = NULL;
		dist = 0;
		comp = 0;
	}
};

class Graph
{
private:
	int V;
	Node** start;
	Node** adjList;
	Node** Rev;

public:
	Graph(int size)
	{
		V = size;
		adjList = new Node * [V];
		Rev = new Node * [V];
		start = new Node * [V];

		for (int i = 0; i < V; i++)
		{
			start[i] = new Node(i + 'A');
			adjList[i] = NULL;
			Rev[i] = NULL;
		}
	}

	void addEdge(char v1, char v2, bool ListNo = 0)
	{
		if (ListNo == 0)
		{
			Node* newNode = new Node(v2);
			newNode->next = adjList[v1 - 'A'];
			adjList[v1 - 'A'] = newNode;
		}
		else
		{
			if (Rev[v1 - 'A'] == NULL)
			{
				Node* newNode = new Node(v2);
				newNode->next = Rev[v1 - 'A'];
				Rev[v1 - 'A'] = newNode;
				return;
			}
			else
			{
				Node* newNode = new Node(v2);
				Node* curr = Rev[v1 - 'A'];
				while (curr->next != NULL)
				{
					curr = curr->next;
				}
				curr->next = newNode;
			}
		}
	}

	void Print(bool ListNo = 0)
	{
		if (ListNo == 0)
		{
			cout << "  ------\n";
			for (int i = 0; i < V; i++)
			{
				cout << start[i]->data << " | " << "*" << " -|-> ";
				Node* curr = adjList[i];
				while (curr != NULL)
				{
					cout << curr->data << " -> ";
					curr = curr->next;
				}
				cout << "\b\b\b  " << endl;
				cout << "  ------\n";
			}
		}
		else
		{
			cout << "  ------\n";
			for (int i = 0; i < V; i++)
			{
				cout << start[i]->data << " | " << "*" << " -|-> ";
				Node* curr = Rev[i];
				while (curr != NULL)
				{
					cout << curr->data << " -> ";
					curr = curr->next;
				}
				cout << "\b\b\b  " << endl;
				cout << "  ------\n";
			}
		}
	}

	void DFS(Node* G)
	{
		Node* u = NULL;
		for (int i = 0; i < V; i++)
		{
			u = start[G->data - 'A'];
			if (u->color == "white")
				DFSVisit(G, u);
		}
	}

	void DFSVisit(Node* G, Node* u)
	{
		u->color = "gray";
		start[u->data - 'A']->color = "gray";
		Node* v = adjList[u->data - 'A'];

		while (v != NULL)
		{
			if (start[v->data - 'A']->color == "white")
			{
				DFSVisit(G, v);
			}
			v = v->next;
		}
		//cout << u->data << " ";
		GLB.push(u->data);
		start[u->data - 'A']->color = "black";
	}

	void Reverse()
	{
		for (int i = 0; i < V; i++)
		{
			Node* curr = adjList[i];
			while (curr != NULL)
			{
				addEdge(curr->data, start[i]->data, true);
				curr = curr->next;
			}
		}
	}

	void Modded_DFS()
	{
		for (int i = 0; i < V; i++)
		{
			start[i]->color = "white";
		}
		int SSC = 1;
		Node* u = NULL;
		while (!GLB.empty())
		{
			Node* G = new Node(GLB.top());
			GLB.pop();
			u = start[G->data - 'A'];
			if (u->color == "white")
			{
				Modded_DFSVisit(G, u, SSC);
				SSC++;
			}
		}
	}

	void Modded_DFSVisit(Node* G, Node* u, int SSC)
	{
		start[u->data - 'A']->comp = SSC;
		u->color = "gray";
		start[u->data - 'A']->color = "gray";
		Node* v = Rev[u->data - 'A'];

		while (v != NULL)
		{
			if (start[v->data - 'A']->color == "white")
			{
				Modded_DFSVisit(G, v, SSC);
			}
			v = v->next;
		}
		//cout << u->data << " ";
		GLB.push(u->data);
		start[u->data - 'A']->color = "black";
	}

	void AssignRegions()
	{
		Node* S = new Node('A');
		DFS(S);

		Reverse();
		cout << "\n\033[36mReversed Adjacency List\033[0m\n";
		Print(1);

		Modded_DFS();

		cout << "\n\033[36mComponent Information\033[0m\n";
		for (int i = 0; i < V; i++)
			cout << start[i]->data << " Lies In Region " << start[i]->comp << endl;
	}

	void BFSCycle(Node* S)
	{
		Node* v = NULL;
		Node* u = NULL;
		S->color = "gray";
		queue<Node*> q;
		q.push(S);
		while (!q.empty())
		{
			u = q.front();
			q.pop();
			v = start[u->data - 'A']->next;
			while (v != NULL)
			{
				if (v->color == "white" && start[v->data - 'A']->color == "white")
				{
					start[v->data - 'A']->color = "gray";
					start[v->data - 'A']->dist = start[u->data - 'A']->dist + 1;
					start[v->data - 'A']->parent = start[u->data - 'A'];
					q.push(start[v->data - 'A']);
				}
				else if (start[v->data - 'A']->color == "gray" && start[v->data - 'A']->parent != u)
				{
					cout << "Cycle Detected: " << u->data << " - " << v->data << endl;
				}
				v = v->next;
			}
			start[u->data - 'A']->color = "black";
		}
	}
};

int main()
{
	{
		Graph g(8);
		g.addEdge('A', 'B');

		g.addEdge('B', 'E');
		g.addEdge('B', 'C');

		g.addEdge('C', 'G');
		g.addEdge('C', 'D');

		g.addEdge('D', 'H');
		g.addEdge('D', 'C');

		g.addEdge('E', 'F');
		g.addEdge('E', 'A');

		g.addEdge('F', 'G');

		g.addEdge('G', 'F');

		g.addEdge('H', 'G');
		g.addEdge('H', 'D');

		cout << "\033[36mAdjacency List\033[0m\n";
		g.Print();

		g.AssignRegions();
	}
}
