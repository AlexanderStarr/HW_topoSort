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
};

template <class T>
struct countNode {
	int count;
	T data;
	Node<T> * next;
	countNode<T> () {};
	countNode<T> (int init_count, T init_data, Node<T> *ptr) {count = init_count; data = init_data; next=ptr;};
};

template <class T>
class Graph {
	countNode<T> *arr;
	int size;
public:
	Graph(){};
	Graph(int init_size){arr = new countNode<T>[init_size]; size = init_size;};
	void addArc(T pre, T suc);
};

template <class T>
void Graph<T>::addArc(T pre, T suc) {
	for (int i=0; i<size; i++) {
		if (arr[i].data == pre) {
			cout << arr[i].data;
		}
	};
};

int main () {
	Graph<int> myGraph = Graph<int>(5);
    return 0;
}
