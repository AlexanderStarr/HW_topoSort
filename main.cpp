#include <iostream>
#include <list>
#include <stack>
#include <string>

using namespace std;

// To represent a graph, you use an array of graphNodes.  successors is a
// C++ list of the integer index of each node that the current node points to.
// Thus, you can access any successor in constant time.
template <class T>
struct graphNode {
	T nodeID;
	bool isAssigned;
	bool isExplored;
	list<int> *successors;
	graphNode(){isAssigned=false; isExplored=false; successors=new list<int>;};
	void printNode();
	void addSuccessor(int new_index){successors->push_back(new_index);}
};

template <class T>
void graphNode<T>::printNode() {
	cout << nodeID << " --> [";
	if (isAssigned) {
		for (list<int>::iterator it=successors->begin(); it != successors->end(); ++it){
			cout << *it;
			if (++it != successors->end()) {
				cout << ", ";
			}
			--it;
		}
	}
	cout << ']';
}

template <class T>
class Graph {
	int size;
	graphNode<T> *arr;
	stack<int> order;
public:
	Graph(){};
	Graph(int init_size){arr = new graphNode<T>[init_size]; size = init_size;};
	void printGraph();
	int findNode(T search_ID);
	int addOrFindNode(T init_ID);
	void addSuccessor(int pre, int suc) {arr[pre].addSuccessor(suc);};
	void addArc(T pre, T suc);
};

template <class T>
void Graph<T>::printGraph() {
	for (int i=0; i<size; i++) {
		if (arr[i].isAssigned) {
			arr[i].printNode();
			cout << endl;
		}
		else {
			break;
		}

	}
}

template <class T>
int Graph<T>::findNode(T search_ID) {
	for (int i=0; i<size; i++) {
		if (not arr[i].isAssigned) {
			break;
		}
		if (arr[i].nodeID == search_ID) {
			return i;
		}
	}
	return -1;
}

template <class T>
int Graph<T>::addOrFindNode(T init_ID) {
	for (int i=0; i<size; i++) {
		if (not arr[i].isAssigned) {
			arr[i].nodeID = init_ID;
			arr[i].isAssigned = true;
			return i;
		};
		if (arr[i].nodeID == init_ID) {
			return i;
		};
	}
	return 0;
}

template <class T>
void Graph<T>::addArc(T pre, T suc) {
	int pre_loc = addOrFindNode(pre);
	int suc_loc = addOrFindNode(suc);
	arr[pre_loc].addSuccessor(suc_loc);
}

int main () {
	Graph<char> myGraph = Graph<char>(11);
	myGraph.addArc('S', 'A');
	myGraph.addArc('S', 'D');
	myGraph.addArc('S', 'G');
	myGraph.addArc('G', 'D');
	myGraph.addArc('G', 'E');
	myGraph.addArc('G', 'H');
	myGraph.printGraph();
	return 0;
}
