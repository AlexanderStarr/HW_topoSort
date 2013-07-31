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

string getNextNode(string raw_string, int i)
{
	string nodeID = "";
	const string DELIM = " ,()";
	while (i<raw_string.length()) {
		// Iterate through equation until you hit a delimiter.
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
	string pre = "", suc = "";
	const string DELIM = " ,()";
	int i = 0;
	while (i<raw_string.length()) {
		if (DELIM.find(raw_string[i]) != -1) {
			i++;
		}
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
