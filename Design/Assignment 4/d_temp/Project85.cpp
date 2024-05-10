// #include <iostream>
// #include <queue>
// #include <stack>
// using namespace std;

// struct Edge 
// {
// 	char from;
// 	char to;
// 	string type;

// 	Edge(char f, char t) : from(f), to(t) {}
// };

// class Node
// {
// 	friend class Graph;
// private:
// 	Node* next;
// 	Node* parent;
// 	char data;
// 	string color;
// 	int comp;

// public:
// 	Node(char d)
// 	{
// 		next = NULL;
// 		parent = NULL;
// 		data = d;
// 		color = "white";
// 		comp = 0;
// 	}
// };

// class Graph
// {
// private:
// 	stack<char>GLB;
// 	vector<Edge> treeEdges;
// 	vector<Edge> backEdges;
// 	vector<Edge> crossEdges;
// 	int V;
// 	Node** start;
// 	Node** adjList;

// public:
// 	Graph(int size)
// 	{
// 		V = size;
// 		adjList = new Node * [V];
// 		start = new Node * [V];

// 		for (int i = 0; i < V; i++)
// 		{
// 			start[i] = new Node(i + 'A');
// 			adjList[i] = NULL;
// 		}
// 	}

// 	void addEdge(char v1, char v2)
// 	{
// 		Node* newNode = new Node(v2);
// 		newNode->next = adjList[v1 - 'A'];
// 		adjList[v1 - 'A'] = newNode;
// 	}

// 	void Print()
// 	{
// 		cout << "  ------\n";
// 		for (int i = 0; i < V; i++)
// 		{
// 			cout << start[i]->data << " | " << "*" << " -|-> ";
// 			Node* curr = adjList[i];
// 			while (curr != NULL)
// 			{
// 				cout << curr->data << " -> ";
// 				curr = curr->next;
// 			}
// 			cout << "\b\b\b  " << endl;
// 			cout << "  ------\n";
// 		}
// 	}

// 	void DFS(Node* G)
// 	{
// 		Node* u = NULL;
// 		for (int i = 0; i < V; i++)
// 		{
// 			u = start[G->data - 'A'];
// 			if (u->color == "white")
// 				DFSVisit(G, u);
// 		}
// 	}

// 	void DFSVisit(Node* G, Node* u)
// 	{
// 		start[u->data - 'A']->color = "gray";
// 		Node* v = adjList[u->data - 'A'];

// 		while (v != NULL)
// 		{
// 			if (start[v->data - 'A']->color == "white") 
// 			{
// 				treeEdges.push_back(Edge(u->data, v->data));
// 				start[v->data - 'A']->parent = start[u->data - 'A'];
// 				DFSVisit(G, v);
// 			}
// 			else if (start[v->data - 'A']->color == "gray")
// 				backEdges.push_back(Edge(u->data, v->data));
// 			else if (start[v->data - 'A']->parent != start[u->data - 'A'] && start[u->data - 'A']->parent != start[v->data - 'A'])
// 				crossEdges.push_back(Edge(u->data, v->data));
// 			v = v->next;
// 		}
// 		GLB.push(u->data);
// 		start[u->data - 'A']->color = "black";
// 	}

// 	void PrintDFS()
// 	{
// 		Node* u = new Node('A');
// 		DFS(u);
// 		cout << "*starting from top of stack*\nStack Order: ";
// 		stack<char>b = GLB;
// 		while (!b.empty())
// 		{
// 			cout << b.top() << " ";
// 			b.pop();
// 		}
// 		cout << endl;
// 		EdgeInfo();
// 	}

// 	void EdgeInfo() 
// 	{
// 		cout << "\033[31mTree Edges:\033[0m" << endl;
// 		for (const auto& edge : treeEdges)
// 			cout << "\t" << edge.from << " -> " << edge.to << endl;

// 		cout << "\033[31mBack Edges:\033[0m" << endl;
// 		for (const auto& edge : backEdges)
// 			cout << "\t" << edge.from << " -> " << edge.to << endl;

// 		cout << "\033[31mCross Edges:\033[0m" << endl;
// 		for (const auto& edge : crossEdges)
// 			cout << "\t" << edge.from << " -> " << edge.to << endl;
// 	}
// };

// int main()
// {
// 	{//geeksforgeeks example
// 		cout << "\033[36mDirected Graph\033[0m\n";
// 		Graph g(8);
// 		cout << "\t\033[36mGeeks For Geeks Example\033[0m\n";
// 		g.addEdge('A', 'H');
// 		g.addEdge('A', 'C');
// 		g.addEdge('A', 'B');

// 		g.addEdge('B', 'D');

// 		g.addEdge('C', 'E');

// 		g.addEdge('D', 'F');

// 		g.addEdge('E', 'H');
// 		g.addEdge('E', 'G');
// 		g.addEdge('E', 'D');

// 		g.addEdge('F', 'B');

// 		cout << "\033[31mAdjacency List\033[0m\n";
// 		g.Print();
// 		g.PrintDFS();


// 	}
// 	{//first dfs cycle example
// 		cout << "\033[36mDirected Graph\033[0m\n";
// 		Graph g(5);
// 		cout << "\t\033[36mFirst DFS Cycle Lecture Notes Example\033[0m\n";
// 		g.addEdge('A', 'C');
// 		g.addEdge('A', 'B');

// 		g.addEdge('B', 'D');

// 		g.addEdge('C', 'E');
// 		g.addEdge('C', 'A');

// 		g.addEdge('D', 'C');

// 		g.addEdge('E', 'D');

// 		cout << "\033[31mAdjacency List\033[0m\n";
// 		g.Print();
// 		g.PrintDFS();


// 	}
// 	{//ssc example
// 		cout << "\033[36mDirected Graph\033[0m\n";
// 		Graph g(8);
// 		cout << "\t\033[36mSSC Lecture Notes Example\033[0m\n";
// 		g.addEdge('A', 'B');

// 		g.addEdge('B', 'E');
// 		g.addEdge('B', 'C');

// 		g.addEdge('C', 'G');
// 		g.addEdge('C', 'D');

// 		g.addEdge('D', 'H');
// 		g.addEdge('D', 'C');

// 		g.addEdge('E', 'F');
// 		g.addEdge('E', 'A');

// 		g.addEdge('F', 'G');

// 		g.addEdge('G', 'F');

// 		g.addEdge('H', 'G');
// 		g.addEdge('H', 'D');

// 		cout << "\033[31mAdjacency List\033[0m\n";
// 		g.Print();
// 		g.PrintDFS();
// 	}

// 	{//assignment 4 example
// 		cout << "\033[36mDirected Graph\033[0m\n";
// 		Graph g(11);
// 		cout << "\t\033[36mAssignment 4 Problem 1.2 Example\033[0m\n";
// 		g.addEdge('A', 'B');

// 		g.addEdge('B', 'F');
// 		g.addEdge('B', 'D');
// 		g.addEdge('B', 'C');

// 		g.addEdge('C', 'H');
// 		g.addEdge('C', 'E');
// 		g.addEdge('C', 'A');

// 		g.addEdge('D', 'G');

// 		g.addEdge('E', 'K');
// 		g.addEdge('E', 'H');
// 		g.addEdge('E', 'D');

// 		g.addEdge('F', 'D');
// 		g.addEdge('F', 'B');

// 		g.addEdge('G', 'I');

// 		g.addEdge('I', 'D');

// 		g.addEdge('J', 'E');

// 		g.addEdge('K', 'J');

// 		cout << "\033[31mAdjacency List\033[0m\n";
// 		g.Print();
// 		g.PrintDFS();
// 	}
// }

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Edge
{
	char from;
	char to;
	string type;

	Edge(char f, char t) : from(f), to(t) {}
};

class Node
{
	friend class Graph;
private:
	Node* next;
	Node* parent;
	char data;
	string color;
	int comp;

public:
	Node(char d)
	{
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
	vector<Edge> treeEdges;
	vector<Edge> backEdges;
	vector<Edge> crossEdges;
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

	void addEdge(char v1, char v2)
	{
		Node* newNode1 = new Node(v2);
		newNode1->next = adjList[v1 - 'A'];
		adjList[v1 - 'A'] = newNode1;

		Node* newNode2 = new Node(v1); // Adding reverse edge
		newNode2->next = adjList[v2 - 'A'];
		adjList[v2 - 'A'] = newNode2;
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
			{
				treeEdges.push_back(Edge(u->data, v->data));
				start[v->data - 'A']->parent = start[u->data - 'A'];
				DFSVisit(G, v);
			}
			else if (start[v->data - 'A']->color == "gray" && start[u->data - 'A']->parent!= start[v->data - 'A'])
				backEdges.push_back(Edge(u->data, v->data));
			else if (start[v->data - 'A']->color == "black")
				crossEdges.push_back(Edge(u->data, v->data));
			v = v->next;
		}
		GLB.push(u->data);
		start[u->data - 'A']->color = "black";
	}

	void PrintDFS()
	{
		Node* u = new Node('A');
		DFS(u);
		cout << "*starting from top of stack*\nStack Order: ";
		stack<char>b = GLB;
		while (!b.empty())
		{
			cout << b.top() << " ";
			b.pop();
		}
		cout << endl;
		EdgeInfo();
	}

	void EdgeInfo()
	{
		cout << "\033[31mTree Edges:\033[0m" << endl;
		for (const auto& edge : treeEdges)
			cout << "\t" << edge.from << " -> " << edge.to << endl;

		cout << "\033[31mBack Edges:\033[0m" << endl;
		for (const auto& edge : backEdges)
			cout << "\t" << edge.from << " -> " << edge.to << endl;

		cout << "\033[31mCross Edges:\033[0m" << endl;
		for (const auto& edge : crossEdges)
			cout << "\t" << edge.from << " -> " << edge.to << endl;
	}
};

int main()
{

	{
		cout << "\033[36mUndirected Graph\033[0m\n";
		Graph g1(7);
		cout << "\t\033[36mFirst Ever DFS Lecture Notes Example\033[0m\n";
		g1.addEdge('A', 'E');
		g1.addEdge('A', 'B');

		g1.addEdge('B', 'F');
		g1.addEdge('B', 'C');

		g1.addEdge('C', 'F');
		g1.addEdge('C', 'D');

		g1.addEdge('D', 'G');
		g1.addEdge('D', 'E');

		g1.addEdge('F', 'G');


		cout << "\033[31mAdjacency List\033[0m\n";
		g1.Print();
		g1.PrintDFS();
	}
}