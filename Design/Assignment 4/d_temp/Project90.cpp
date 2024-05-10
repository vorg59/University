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
			start[i] = new Node(i + 'M');
			adjList[i] = NULL;
		}
	}

	void addEdge(char v1, char v2)
	{
		Node* newNode = new Node(v2);
		newNode->next = adjList[v1 - 'M'];
		adjList[v1 - 'M'] = newNode;
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

	void DFS(Node* G, char startVertex, char endVertex, int& pathCount)
	{
		Node* u = start[startVertex - 'M'];
		if (u->color == "white")
			DFSVisit(G, u, endVertex, pathCount);
	}

	void DFSVisit(Node* G, Node* u, char endVertex, int& pathCount)
	{
		Node* v = adjList[u->data - 'M'];
		char Listof = start[u->data - 'M']->data;
		char at;

		while (v != NULL)
		{
			at = v->data;
			if (v->data == endVertex)
				pathCount++;
			else
				DFSVisit(G, v, endVertex, pathCount);
			v = v->next;
		}
	}

	void CountPaths(char startVertex, char endVertex)
	{
		int pathCount = 0;
		DFS(start[0], startVertex, endVertex, pathCount);
		cout << "\033[31mNumber of Paths From " << startVertex << " to " << endVertex << ":\033[0m " << pathCount << endl;
	}
};

int main()
{
	{
		cout << "\033[36mDirected Graph\033[0m\n";
		Graph g(5);

		cout << "\t\033[36mGeeks For Geeks Example\033[0m\n";

		g.addEdge('M', 'N');
		g.addEdge('M', 'O');
		g.addEdge('M', 'P');
		g.addEdge('M', 'Q');

		g.addEdge('N', 'P');

		g.addEdge('P', 'Q');

		cout << "\033[31mAdjacency List\033[0m\n";
		g.Print();


		g.CountPaths('M', 'Q');
		g.CountPaths('M', 'N');
	}
	cout << endl << endl;
	{
		cout << "\033[36mDirected Graph\033[0m\n";
		Graph g(14);
		cout << "\t\033[36mAssignment 4 Problem 2.3\033[0m\n";
		g.addEdge('M', 'R');
		g.addEdge('M', 'Q');
		g.addEdge('M', 'X');

		g.addEdge('N', 'Q');
		g.addEdge('N', 'U');
		g.addEdge('N', 'O');

		g.addEdge('O', 'R');
		g.addEdge('O', 'V');
		g.addEdge('O', 'S');

		g.addEdge('P', 'O');
		g.addEdge('P', 'S');
		g.addEdge('P', 'Z');

		g.addEdge('Q', 'T');

		g.addEdge('R', 'U');
		g.addEdge('R', 'Y');

		g.addEdge('S', 'R');

		g.addEdge('U', 'T');

		g.addEdge('V', 'X');
		g.addEdge('V', 'W');

		g.addEdge('W', 'Z');

		g.addEdge('Y', 'V');

		cout << "\033[36mAdjacency List\033[0m\n";
		g.Print();
		g.CountPaths('P', 'V');
	}
}