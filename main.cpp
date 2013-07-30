#include <iostream>
#include <list>
#include <stack>

using namespace std;
const int DEFAULT_SIZE = 11;

template <class T>
struct Node {
	T data;
	Node<T> * next;
	Node<T> () {};
	Node<T> (T init_data, Node<T> *ptr) {data = init_data; next=ptr;};
	void print() {cout << data;};
};

template <class T>
struct countNode {
	int count;
	bool is_assigned;
	T data;
	Node<T> * next;
	countNode<T> () {is_assigned = false; next = NULL;};
	countNode<T> (int init_count, T init_data, Node<T> *ptr) {count = init_count; is_assigned = true; data = init_data; next=ptr;};
	void print() {cout << data << '[' << count << ']';};
	void addNode(T new_data);
};

template <class T>
void countNode<T>::addNode(T new_data) {
	Node<T> *tmp = next;
	if (not tmp) {
		Node<T> *new_node = new Node<T>(new_data, NULL);
		next = new_node;
	}
	else {
		bool is_duplicate = false;
		while (tmp->next) {
			if (tmp->data == new_data) {
				is_duplicate = true;
			}
			tmp = tmp->next;
		}
		if (not is_duplicate) {
			Node<T> *new_node = new Node<T>(new_data, NULL);
			tmp->next = new_node;
		}
	}
}

template <class T>
class Graph {
	countNode<T> *arr;
	int size;
public:
	Graph(){};
	Graph(int init_size){arr = new countNode<T>[init_size]; size = init_size;};
	void print();
	void addArc(T pre, T suc);
};

template <class T>
void Graph<T>::print() {
	for (int i=0; i<size; i++) {
		arr[i].print();
		cout << " -> ";
		Node<T> *tmp = arr[i].next;
		while (tmp) {
			tmp->print();
			tmp = tmp->next;
			if (tmp) {
				cout << " -> ";
			}
		};
		cout << endl;
	}
}

template <class T>
void Graph<T>::addArc(T pre, T suc) {
	bool p_found = false, s_found = false;
	for (int i=0; i<size; i++) {
		if (not arr[i].is_assigned) {
			if (not p_found) {
				arr[i].data = pre;
				arr[i].is_assigned = true;
				p_found = true;
			}
			else if (not s_found) {
				arr[i].data = suc;
				arr[i].is_assigned = true;
				s_found = true;
			}
		}
		if (arr[i].data == pre) {
			arr[i].addNode(suc);
			p_found = true;
		}
		else if (arr[i].data == suc) {
			arr[i].count++;
			s_found = true;
		}
	};
};

int main () {
	Graph<int> myGraph = Graph<int>(9);
	myGraph.addArc(1, 3);
	myGraph.addArc(3, 7);
	myGraph.addArc(7, 4);
	myGraph.addArc(7, 5);
	myGraph.addArc(4, 6);
	myGraph.addArc(5, 8);
	myGraph.addArc(8, 6);
	myGraph.addArc(9, 5);
	myGraph.addArc(9, 2);
	myGraph.addArc(2, 8);
	myGraph.print();
    return 0;
}
