
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* A long-term queue based on priorities.
 * Authors: Christian Jiminez, Richard Williams, Stephanie Van Dyke
 */


 //use process in all queues
struct process
{
	string id;
	int num;
};

//allows for easy making of a process
process pMaker(int c)
{
	stringstream s;
	s << "P" << c << "";
	string a = s.str();
	int b = (rand() % 50 + 1);
	process p = { a,b };
	return  p;
};


// Wraps the priority-queue in a container to iterate over later 
template <class T, class S, class C>
S& Container(priority_queue<T, S, C>& q) {
	struct PQueue : private priority_queue<T, S, C> {
		static S& Container(priority_queue<T, S, C>& q) {
			return q.*&PQueue::c;
		}
	};
	return PQueue::Container(q);
}

//used to compare processess
struct compareProcess {
	bool operator()(process const& a, process const& b)
	{
		// return "true" if "p1" is ordered  
		// before "p2", for example: 
		return a.num < b.num;
	}
};

// print queues
void printQueue(queue<process> q)
{
	while (!q.empty())
	{
		process a = q.front();
		cout << " " << a.id << ":" << a.num << " ";
		q.pop();
	}
	cout << endl;
}

int main()
{
	priority_queue<process, vector<process>, compareProcess> pq;	// priority queue
	vector<process> &tasks = Container(pq);	// priority queue in container
	int counter = 1;

	//fills the priority queue
	for (int i = 0; i < 9; i++)
	{
		pq.push(pMaker(counter));
		counter++;
	}

	queue<process> wqueue; //creates waiting Queue using queue, FIFO

	queue<process> rqueue; //creates ready queue

	int step = 0;

	while (pq.size() > 0 || rqueue.size() > 0)
	{
		cout << "step: " << step << endl;
		cout << endl;
		step++;

		if (pq.size() < 10 && counter <= 25)
		{
			process a = pMaker(counter);
			counter++;

			cout << "the new process generated is: ";
			cout << a.id << " with priority " << a.num << endl;
			cout << endl;
			pq.push(a);
		}


		cout << "The processes in the priority queue are: ";
		if (pq.size() > 0)
		{
			for (vector<process>::iterator i = tasks.begin(); i != tasks.end(); i++)
			{
				cout << i->id << ":" << i->num << " ";
			}
			cout << endl;
		}
		cout << endl;

		cout << "the numbers in the waiting queue are: ";
		if (wqueue.size() > 0)
		{
			printQueue(wqueue);
		}
		cout << endl;


		if (wqueue.size() < 7 || wqueue.size() < 7 && (pq.size() < 10 && pq.size() >= 0))
		{
			if (pq.size() > 0)
			{
				process a = pq.top();
				pq.pop();
				wqueue.push(a);
			}
		}


		cout << "The numbers in the ready queue are: ";
		if (rqueue.size() > 0)
		{
			printQueue(rqueue);
		}
		cout << endl;

		if (rqueue.size() < 5 || rqueue.size() < 5 && (wqueue.size() >= 7 && wqueue.size() > 0))
		{
			if (wqueue.size() > 0)
			{
				process a = wqueue.front();
				wqueue.pop();
				rqueue.push(a);
			}
		}


		if (rqueue.size() > 0)
		{
			process a = rqueue.front();
			a.num = a.num - 2;
			rqueue.pop();

			if (a.num > 0)
			{
				rqueue.push(a);
			}
		}

	}

	system("pause");
}

