#include<iostream>
using namespace std;

class Node 
{
	friend class LinkedList;
public:
	int jobId;
	int length;
	Node* next;
	Node(int d, int id)
	{
		jobId = id;
		this->length = d;
		this->next = nullptr;

	}
};

class LinkedList 
{
private:
	Node* head;
	int id;
public:
	LinkedList()
	{
		id = 0;
		head = nullptr;
	}

	void enqueue(int newLength)
	{
		id++;
		Node* newNode = new Node(newLength, id);
		if (head == nullptr) 
		{
			head = newNode;
			return;
		}
		else 
		{
			Node* curr = head;
			Node* prev = head;
			while (curr != 0)
			{
				if (curr->length > newLength)
					break;
				prev = curr;
				curr = curr->next;
			}
			if (curr == head)
			{
				head = newNode;
				newNode->next = curr;
				return;
			}
			prev->next = newNode;
			if (curr != NULL)
				newNode->next = curr;
		}
	}

	Node* dequeue()
	{
		if (head != NULL)
		{
			Node* curr = head;
			head = head->next;
			return curr;
		}
		cout << "\t***All Jobs Have Been Completed***\n";
		return NULL;
	}

	void display()
	{
		Node* curr = head;
		while (curr != 0)
		{
			cout << "Job " << curr->jobId << " -> ";
			curr = curr->next;
		}
		cout << "\b\b\b   \n";
	}

};

int main()
{
	{
		int jobLengths[] = { 5, 2, 7, 1, 4 };

		LinkedList l1;
		cout << "Jobs:\n";
		for (int i = 0; i < size(jobLengths); i++)
		{
			cout << "\t" << "Job " << i + 1 << ": Length = " << jobLengths[i] << " units\n";
			l1.enqueue(jobLengths[i]);
		}
		cout << endl;

		cout << "Job Processing Order: ";
		l1.display();
		cout << endl;

		cout << "-- Starting SJF Scheduling Simulation --\n";
		for (int i = 0; i < size(jobLengths); i++)
		{
			Node* job = l1.dequeue();
			cout << "\tProcessing Job " << job->jobId << " (Length = " << job->length << " units)\n";
		}
		cout << "-- SJF Scheduling Simulation Complete --\n\n";
	}

	{
		int jobLengths[] = { 24, 3, 3 };

		LinkedList l1;
		cout << "Jobs:\n";
		for (int i = 0; i < size(jobLengths); i++)
		{
			cout << "\t" << "Job " << i + 1 << ": Length = " << jobLengths[i] << " units\n";
			l1.enqueue(jobLengths[i]);
		}
		cout << endl;

		cout << "Job Processing Order: ";
		l1.display();
		cout << endl;

		cout << "-- Starting SJF Scheduling Simulation --\n";
		for (int i = 0; i < size(jobLengths); i++)
		{
			Node* job = l1.dequeue();
			cout << "\tProcessing Job " << job->jobId << " (Length = " << job->length << " units)\n";
		}
		cout << "-- SJF Scheduling Simulation Complete --\n\n";
	}

	{
		int jobLengths[] = { 3, 8, 4, 6, 3, 1, 6, 4, 10, 4, 3, 4, 16, 15, 2 };

		LinkedList l1;
		cout << "Jobs:\n";
		for (int i = 0; i < size(jobLengths); i++)
		{
			cout << "\t" << "Job " << i + 1 << ": Length = " << jobLengths[i] << " units\n";
			l1.enqueue(jobLengths[i]);
		}
		cout << endl;

		cout << "Job Processing Order: ";
		l1.display();
		cout << endl;

		cout << "-- Starting SJF Scheduling Simulation --\n";
		for (int i = 0; i < size(jobLengths) + 1; i++)
		{
			Node* job = l1.dequeue();
			if(job!=NULL)
				cout << "\tProcessing Job " << job->jobId << " (Length = " << job->length << " units)\n";
		}
		cout << "-- SJF Scheduling Simulation Complete --\n\n";
	}
}
