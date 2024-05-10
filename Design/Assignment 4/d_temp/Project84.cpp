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
	int comp;

public:
	Node(char d)
	{
		next = NULL;
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
			adjList[i] = NULL;
		}
	}

	void addEdge(char v1, char v2, bool ListNo = 0)
	{
		Node* newNode = new Node(v2);
		newNode->next = adjList[v1 - 'A'];
		adjList[v1 - 'A'] = newNode;
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
				cout << curr->data << " -> ";
				curr = curr->next;
			}
			cout << "\b\b\b  " << endl;
			cout << "  ------\n";
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
		start[u->data - 'A']->color = "gray";
		Node* v = adjList[u->data - 'A'];

		while (v != NULL)
		{
			if (start[v->data - 'A']->color == "white")
				DFSVisit(G, v);
			v = v->next;
		}
		GLB.push(u->data);
		start[u->data - 'A']->color = "black";
	}

	void Modded_DFS()
	{
		for (int i = 0; i < V; i++)
			start[i]->color = "white";
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
		start[u->data - 'A']->color = "gray";
		Node* v = adjList[u->data - 'A'];

		while (v != NULL)
		{
			if (start[v->data - 'A']->color == "white")
				Modded_DFSVisit(G, v, SSC);
			v = v->next;
		}
		GLB.push(u->data);
		start[u->data - 'A']->color = "black";
	}

	void AssignRegions()
	{
		Node* S = new Node('A');
		DFS(S);
		stack<char>backup;
		cout << "*starting from top of stack*\n";
		cout << "Stack Order: ";
		while (!GLB.empty())
		{
			backup.push(GLB.top());
			cout << GLB.top() <<" ";
			GLB.pop();
		}
		GLB = backup;
		cout << "\nRevStack Order: ";
		while (!backup.empty())
		{
			cout << backup.top() << " ";
			backup.pop();
		}
		Modded_DFS();
		cout << "\n\n\033[36mComponent Information\033[0m\n";
		for (int i = 0; i < V; i++)
			cout << "\033[35m" << start[i]->data << "\033[0m Lies In Region \033[35m" << start[i]->comp << "\033[0m" << endl;
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

	{
		Graph g(11);
		g.addEdge('A', 'B');

		g.addEdge('B', 'F');
		g.addEdge('B', 'D');
		g.addEdge('B', 'C');

		g.addEdge('C', 'H');
		g.addEdge('C', 'E');
		g.addEdge('C', 'A');

		g.addEdge('D', 'G');

		g.addEdge('E', 'K');
		g.addEdge('E', 'H');
		g.addEdge('E', 'D');

		g.addEdge('F', 'D');
		g.addEdge('F', 'B');

		g.addEdge('G', 'I');

		g.addEdge('I', 'D');

		g.addEdge('J', 'E');

		g.addEdge('K', 'J');

		cout << "\033[36mAdjacency List\033[0m\n";
		g.Print();

		g.AssignRegions();
	}
}