#include <iostream>
#include <list>
#include <stack>
#include <string>

using namespace std;

// To represent a graph, you use an array of graphNodes.

// ========== graphNode ========== //
template <class T>
struct graphNode {
	T nodeID;
	
	// isAssigned keeps track of which nodes in an array have actually been
	// given a value.  This is necessary because the array is initialized with
	// 'empty' nodes.
	bool isAssigned;
	
	// isExplored is used when doing the topological sorting.
	bool isExplored;
	
	// successors is a C++ list of the integer index of each successor node.
	// Thus, you can access any successor in constant time.
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

// ========== Graph ========== //
template <class T>
class Graph {
	int size;
	graphNode<T> *arr;
	
	// order is used during topoSort
	stack<int> order;
public:
	Graph(){};
	Graph(int init_size){arr = new graphNode<T>[init_size]; size = init_size;};
	void printGraph();
	int findNode(T search_ID);
	int addOrFindNode(T init_ID);
	void addSuccessor(int pre, int suc) {arr[pre].addSuccessor(suc);};
	void addArc(T pre, T suc);
	void DFS(int index);
	void topoSort();
};

template <class T>
void Graph<T>::printGraph() {
	for (int i=0; i<size; i++) {
		if (arr[i].isAssigned) {
			cout << i << "\t| ";
			arr[i].printNode();
			cout << endl;
		}
		else {
			break;
		}

	}
}

// Returns the index of the node with the given ID if found.
// Otherwise, returns 0.
template <class T>
int Graph<T>::findNode(T search_ID) {
	for (int i=0; i<size; i++) {
		if (not arr[i].isAssigned) {
			// If a node isn't assigned, then the array effectively ends there.
			break;
		}
		if (arr[i].nodeID == search_ID) {
			return i;
		}
	}
	return -1;
}

// If a node with the given ID doesn't exist, it adds it and returns the index.
// Otherwise, it returns the index of the node with the given ID.
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

// Given the IDs of the predecessor and successor nodes, this adds the
// arc to the graph.
template <class T>
void Graph<T>::addArc(T pre, T suc) {
	int pre_loc = addOrFindNode(pre);
	int suc_loc = addOrFindNode(suc);
	arr[pre_loc].addSuccessor(suc_loc);
}

// A depth-first search algorithm.  First it marks the current node as
// explored.  Then it recursively performs a depth-first search on each
// successor node.  Once all successors are searched, it pushes the node
// to the order stack.  The end result of this is that it the deepest nodes
// will be the first to the stack, and thus the last nodes out of the stack.
template <class T>
void Graph<T>::DFS(int index) {
	arr[index].isExplored = true;
	list<int> *sucList = arr[index].successors;
	for (list<int>::iterator it=sucList->begin(); it != sucList->end(); ++it) {
		if (not arr[*it].isExplored) {
			DFS(*it);
		};
	};
	order.push(index);
};

// Simply ensures that DFS reaches every node, then prints each node
// from the order stack.
template <class T>
void Graph<T>::topoSort() {
	for (int i=0; i<size; i++) {
		if (not arr[i].isExplored) {
			DFS(i);
		};
	};
	while (not order.empty()) {
		cout << arr[order.top()].nodeID << ' ';
		order.pop();
	};
};

// Borrowed from the first programming assignment.  Returns a string
// consisting of all characters from i to the next delimiter.
string getNextNode(string raw_string, int i)
{
	string nodeID = "";
	const string DELIM = " ,()";
	while (i<raw_string.length()) {
		// Iterate through string until you hit a delimiter.
		if (DELIM.find(raw_string[i]) != -1) {
			break;
		}
		nodeID += raw_string[i];
		i++;
	}
	return nodeID;
}

int main () {
	cout << "Enter ordered pairs of nodes: ";
	string raw_string;
	getline(cin, raw_string);
	cout << "Enter the number of nodes: ";
	int num;
	cin >> num;
	Graph<string> myGraph = Graph<string>(num);
	
	// We will build a predecessor and successor string, in that order.
	// Once we have one of each, create an arc in the graph with them,
	// then reset each one and start again.
	string pre = "", suc = "";
	const string DELIM = " ,()";
	int i = 0;
	while (i<raw_string.length()) {
		// Simply ignore instances of the delimiter characters
		if (DELIM.find(raw_string[i]) != -1) {
			i++;
		}
		
		// If a character is not a delimiter, grab the string until the next
		// delimiter.  If there is not currently a predecessor or successor,
		// then assign the string to pre.  Otherwise, if pre is assigned,
		// then assign the string to suc, create the arc, and reset pre/suc.
		else {
			if (pre == "" && suc == "") {
				pre = getNextNode(raw_string, i);
				i += pre.length();
			}
			else if (pre != "" && suc == "") {
				suc = getNextNode(raw_string, i);
				i += suc.length();
				myGraph.addArc(pre, suc);
				pre = "";
				suc = "";
			}
		}
	}
	cout << endl;
	cout << "Your graph is represented as follows:" << endl;
	myGraph.printGraph();
	cout << endl;
	cout << "The topological sorting of your graph is:" << endl;
	myGraph.topoSort();
	return 0;
}
