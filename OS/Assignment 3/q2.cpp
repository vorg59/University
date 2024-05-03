#include<iostream>
#include<vector>
using namespace std;

class Node {
	friend class LinkedList;         //make "LinkedList" his friend so that Linkedlist class can use its attributes and functions
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

class LinkedList {
private:
	Node* head;
	int id;
public:
	LinkedList()
	{
		id = 0;
		head = nullptr;            //empty linked list which points to NOTHING
	}

	void enqueue(int newLength)
	{
		id++;
		Node* newNode = new Node(newLength, id);      //Step1: make a new node
		if (head == nullptr) {               //Step2: first possibility
			head = newNode;
			return;
		}
		else {                           //Step2: second possibility
			//we should set the name of the last node to be able to access it!
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
			//Step3: link last node to the new one. This is how it will be added in the list
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
		while (curr != 0)            //to reach at the end of the list and traverse EVERY node.
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

// #include <iostream>
// #include <queue>
// #include <vector>

// using namespace std;

// // Structure to represent a job
// struct Job {
//     int id;
//     int length;

//     // Constructor
//     Job(int _id, int _length) : id(_id), length(_length) {}

//     // Overloading the less-than operator to compare based on job length
//     bool operator<(const Job& other) const {
//         // Shorter jobs have higher priority
//         return length > other.length;
//     }
// };

// // Function to simulate SJF scheduling
// void simulateSJF(const vector<int>& jobLengths) {
//     // Priority queue to store jobs, sorted by job length (shortest job first)
//     priority_queue<Job> pq;

//     // Enqueue all jobs into the priority queue
//     cout<<"\nJobs:\n";
//     for (int i = 0; i < jobLengths.size(); ++i) {
//         cout<<"Job "<<i+1<<": Length = "<<jobLengths[i]<<" units\n";
//         pq.push(Job(i + 1, jobLengths[i]));
//     }
//     cout<<endl;

//     // Processing jobs from the priority queue
//     cout << "-- Starting SJF Scheduling Simulation --" << endl;
//     while (!pq.empty()) {
//         Job currentJob = pq.top();  // Get the shortest job
//         pq.pop();                   // Remove the shortest job from the queue

//         cout << "Processing Job " << currentJob.id << " (Length = " << currentJob.length << " units)" << endl;

//         // Simulate processing of the current job
//         // In a real system, you would perform actual processing here

//         // For simulation purposes, we simply print the job being processed

//         // Sleep for the length of the job to simulate processing time
//         // This can be replaced with actual processing code
//         // This is just for demonstration purposes
//         // std::this_thread::sleep_for(std::chrono::seconds(currentJob.length));
//     }
//     cout << "-- SJF Scheduling Simulation Complete --" << endl;
// }

// int main() 
// {
//     {
//         // Set of jobs represented by their lengths (in time units)
//         vector<int> jobLengths = {5, 2, 7, 1, 4};

//         // Simulate SJF scheduling with the given job lengths
//         simulateSJF(jobLengths);
//     }
//     {
//         // Set of jobs represented by their lengths (in time units)
//         vector<int> jobLengths = {7, 4, 1, 4};

//         // Simulate SJF scheduling with the given job lengths
//         simulateSJF(jobLengths);
//     }

//     return 0;
// }
