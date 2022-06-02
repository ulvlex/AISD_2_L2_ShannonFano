#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

template <typename typeInfo>

class List {
private:
	class Node { 
	public:
		typeInfo info;
		Node* prev;	
		Node* next; 
		Node(typeInfo info, Node* prev = nullptr, Node* next = nullptr) {
			this->info = info;
			this->prev = prev;
			this->next = next;
		};
	};
	Node* head; //Pointer to the beginning of the list
	Node* tail; //Pointer to the end of the list
	size_t size;

	Node* getElem(size_t index) {
		if (index < getSize() && index >= 0) {
			Node* elem = head;
			elem = head;
			for (int i = 0; i < (int)index; i++) {
				elem = elem->next;
			}
			return elem;
			elem = 0;
		}
	}
public:
	List() : head(nullptr), tail(nullptr) {}

	List(const size_t size, typeInfo* arr) : head(nullptr), tail(nullptr)
	{
		for (size_t i = 0; i < size; i++) this->PushBack(arr[i]);
	}

	~List() {
		clear();
	}
	void clear() {
		head = tail = nullptr;
		size = 0;
	}

	void push_front(typeInfo info) {
		Node* elem = new Node(info);
		if (isEmpty()) {
			head = tail = elem;
		}
		else {
			tail = elem;
			head = tail;
		}
		size++;

	}

	void push_back(typeInfo info) {
		Node* elem = new Node(info);
		if (head == nullptr) {
			head = tail = elem;
		}
		else {
			tail->next = elem;
			tail = tail->next;
		}
		size++;
	}

	void pop_front() {
		if (head == nullptr) throw logic_error("List is empty");
		if (head->next == nullptr)
		{
			delete head;
			head = tail = nullptr;
			size--;
		}
		else
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
			size--;
		}
	}

	void pop_back() {
		if (tail == nullptr) throw logic_error("List is empty");
		if (tail->prev == nullptr)
		{
			delete tail;
			head = tail = nullptr;
			size--;
		}
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
			size--;
		}
	}

	void insert(typeInfo info, size_t index) {
		if (index > getSize() && index < 0) throw invalid_argument("Index out of range");
		if (index < getSize() && index >= 0) {
			if (index == 0) pushFront(info);
			else if (index == getSize()) push_back(info);
			else {
				Node* next_elem = getElem(index);
				Node* elem = new Node(next_elem->info, next_elem, next_elem->next);
				next_elem->info = info;
				next_elem->next = elem;
				if (tail == next_elem) tail = elem;
				size++;
			}
		}
	}

	int indexPointer(size_t index) {
		if (index < getSize() && index >= 0) {
			return getElem(index)->info;
		}
		else throw invalid_argument("Index is out of range");
	}

	void remove(size_t index) {
		if (index < getSize() && index >= 0) {
			Node* elem = getElem(index);
			if (getSize() == 1) {
				delete elem;
				head = tail = nullptr;
			}
			else {
				if (index == getSize() - 1) {
					elem->prev->next = nullptr;
					tail = getElem(index);
				}
				else if (index == 0) {
					elem->next->prev = nullptr;
					head = elem;
				}
				else {

					elem->next->prev = elem->prev;
					elem->prev->next = elem->next;
				}
				delete elem;
			}
			size--;
		}
		else throw invalid_argument("Index is out of range");
	}

	size_t getSize()
	{
		int size = 0;
		Node* elem = head;
		while (elem != nullptr)
		{
			size++;
			elem = elem->next;
		}
		return size;
	}

	bool isEmpty() {
		return getSize() == false;
	}

	typeInfo getHead() {
		if (size != 0)
			return head->info;
	}

	void setNext() {
		if (head != NULL)
			head = head->next;
		else
			throw out_of_range("There is not next element");
	}

	friend ostream& operator<< (ostream& out, const List& list);
};

template<typename keyType, typename valueType>

class Map {
private:
	class Node {
	public:
		keyType key;
		valueType value;
		Node* parent;
		Node* left;
		Node* right;
		bool color;

		Node(Node* parent, Node* left, bool color, Node* right, keyType key, valueType value) : parent(parent), color(color), key(key), value(value) {}
	};
	Node* root;
	Node* NIL;

	void leftRotate(Node* current) {
		Node* noduleRight = current->right;
		current->right = noduleRight->left;
		if (noduleRight->left != NIL) {
			noduleRight->left->parent = current;
		}
		noduleRight->parent = current->parent;
		if (current->parent == nullptr) {
			this->root = noduleRight;
		}
		else
			if (current != current->parent->left) {
				current->parent->right = noduleRight;
			}
			else {
				current->parent->left = noduleRight;
			}
		noduleRight->left = current;
		current->parent = noduleRight;
	}

	void rightRotate(Node* current) {
		Node* noduleLeft = current->left;
		current->left = noduleLeft->right;
		if (noduleLeft->right != NIL) {
			noduleLeft->right->parent = current;
		}
		noduleLeft->parent = current->parent;
		if (current->parent == nullptr) {
			this->root = noduleLeft;
		}
		else
			if (current == current->parent->right) {
				current->parent->right = noduleLeft;
			}
			else {
				current->parent->left = noduleLeft;
			}
		noduleLeft->right = current;
		current->parent = noduleLeft;
	}

	void nodeChange(Node* ourNode, Node* newNode) {
		if (ourNode->parent == nullptr) {
			root = newNode;
		}
		else if (ourNode == ourNode->parent->left) {
			ourNode->parent->left = newNode;
		}
		else {
			ourNode->parent->right = newNode;
		}
		newNode->parent = ourNode->parent;
	}

	void insertFixUp(Node* current) {
		Node* uncle;
		while (current->parent->color == 1) {
			if (current->parent == current->parent->parent->right) {
				uncle = current->parent->parent->left;
				if (uncle->color == 1) {
					uncle->color = 0;
					current->parent->color = 0;
					current->parent->parent->color = 1;
					current = current->parent->parent;
				}
				else {
					if (current == current->parent->left) {
						current = current->parent;
						rightRotate(current);
					}
					current->parent->color = 0; // Parent becomes black
					current->parent->parent->color = 1;
					leftRotate(current->parent->parent);
				}
			}
			else {
				uncle = current->parent->parent->right;

				if (uncle->color == 1) {
					uncle->color = 0;
					current->parent->color = 0;
					current->parent->parent->color = 1;
					current = current->parent->parent;
				}
				else {
					if (current == current->parent->right) {
						current = current->parent;
						leftRotate(current);
					}

					current->parent->color = 0;
					current->parent->parent->color = 1;
					rightRotate(current->parent->parent);
				}
			}
			if (current == root) {
				break;
			}
		}
		root->color = 0; // Root must be black
	}

	void deleteNode(Node* node) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				deleteNode(node->right);
			if (node->left != nullptr && node->left != NIL)
				deleteNode(node->left);
			delete node;
		}
	}

	void rbChanger(Node* ourNode, Node* newNode) {
		if (ourNode->parent == nullptr) {
			root = newNode;
		}
		else if (ourNode == ourNode->parent->left) {
			ourNode->parent->left = newNode;
		}
		else {
			ourNode->parent->right = newNode;
		}
		newNode->parent = ourNode->parent;
	}

	List<keyType> getListOfKeys(Node* node, List<keyType>& list) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				list = getListOfKeys(node->right, list);
			if (node->left != nullptr && node->left != NIL)
				list = getListOfKeys(node->left, list);
			list.push_back(node->key);
			return list;
		}
	}
	List<valueType> getListOfValues(Node* node, List<valueType>& list) {
		if (node != NIL) {
			if (node->right != nullptr && node->right != NIL)
				list = getListOfValues(node->right, list);
			if (node->left != nullptr && node->left != NIL)
				list = getListOfValues(node->left, list);
			list.push_back(node->value);
			return list;
		}
	}

	void printNode(Node* node) {
		bool colorStr;

		if (node == NULL)
			return;

		if (node->color == 0) colorStr = "black";
		else colorStr = "red";

		if (node->parent == NULL)
			cout << node->key << "(" << colorStr << ") is root" << endl;
		else {
			if (node->parent->left == node)
			{
				cout << node->key << "(" << colorStr << ") is " << node->parent->key << "'s " << "left child" << endl;
			}
			else
			{
				cout << node->key << "(" << colorStr << ") is " << node->parent->key << "'s " << "right child" << endl;
			}
		}

		if (node->left != NIL) printNode(node->left);
		if (node->right != NIL) printNode(node->right);
	}

	bool containsAlgorithm(Node* current, keyType key) {
		if (key == current->key) {
			return true;
		}

		if (current == NIL) {
			return false;
		}

		if (key < current->key) {
			return containsAlgorithm(current->left, key);
		}
		return containsAlgorithm(current->right, key);
	}

public:
	Map() {
		NIL = new Node(NULL, NULL, 0, NULL, NULL, NULL);
		NIL->color = 0;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}

	~Map() {
		clear();
	}

	void insert(keyType key, valueType value) {

		Node* newNode = new Node(NULL, NULL, 0, NULL, NULL, NULL);
		newNode->parent = nullptr;
		newNode->key = key;
		newNode->value = value;
		newNode->left = NIL;
		newNode->right = NIL;
		newNode->color = 1; 

		Node* y = nullptr;
		Node* x = root;

		while (x != NIL) {
			y = x;
			if (newNode->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		newNode->parent = y;
		if (y == nullptr) {
			root = newNode;
		}
		else if (newNode->key < y->key) {
			y->left = newNode;
		}
		else {
			y->right = newNode;
		}

		if (newNode->parent == nullptr) {
			newNode->color = 0;
			return;
		}

		if (newNode->parent->parent == nullptr) {
			return;
		}

		insertFixUp(newNode); 
	}

	void remove(keyType key) {
		Node* nodeToBeDeleted = NIL;
		Node* x;
		Node* y;

		nodeToBeDeleted = find(key);

		y = nodeToBeDeleted;
		int OriginalColorOfY = y->color;
		if (nodeToBeDeleted->left == NIL) {
			x = nodeToBeDeleted->right;
			nodeChange(nodeToBeDeleted, nodeToBeDeleted->right);
		}
		else if (nodeToBeDeleted->right == NIL) {
			x = nodeToBeDeleted->left;
			nodeChange(nodeToBeDeleted, nodeToBeDeleted->left);
		}
		else {
			y = nodeToBeDeleted->right;
			while (y->left != NIL) {
				y = y->left;
			}
			OriginalColorOfY = y->color;
			x = y->right;
			if (y->parent == nodeToBeDeleted) {
				x->parent = y;
			}
			else {
				nodeChange(y, y->right);
				y->right = nodeToBeDeleted->right;
				y->right->parent = y;
			}

			nodeChange(nodeToBeDeleted, y);
			y->left = nodeToBeDeleted->left;
			y->left->parent = y;
			y->color = nodeToBeDeleted->color;
		}
		delete nodeToBeDeleted;


		if (OriginalColorOfY == 0) {
			Node* brother;
			while (x != root && x->color == 0) {
				if (x == x->parent->left) {
					brother = x->parent->right;
					if (brother->color == 1) {
						brother->color = 0;
						x->parent->color = 1;
						leftRotate(x->parent);
						brother = x->parent->right;
					}

					if (brother->left->color == 0 && brother->right->color == 0) {
						brother->color = 1;
						x = x->parent;
					}
					else {
						if (brother->right->color == 0) {
							brother->left->color = 0;
							brother->color = 1;
							rightRotate(brother);
							brother = x->parent->right;
						}

						brother->color = x->parent->color;
						x->parent->color = 0;
						brother->right->color = 0;
						leftRotate(x->parent);
						x = root;
					}
				}
				else {
					brother = x->parent->left;
					if (brother->color == 1) {
						brother->color = 0;
						x->parent->color = 1;
						rightRotate(x->parent);
						brother = x->parent->left;
					}

					if (brother->right->color == 0 && brother->left->color == 0) {
						brother->color = 1;
						x = x->parent;
					}
					else {
						if (brother->left->color == 0) {
							brother->right->color = 0;
							brother->color = 1;
							leftRotate(brother);
							brother = x->parent->left;
						}
						brother->color = x->parent->color;
						x->parent->color = 0;
						brother->left->color = 0;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = 0;
		}
	}

	List <keyType> getKeys() {
		List<keyType> list;
		return getListOfKeys(this->root, list);
	}

	List <valueType> getValues() {
		List <valueType> list;
		return getListOfValues(this->root, list);
	}

	void print() {
		if (this->root == NIL) {
			throw invalid_argument("Map is empty");
		}
		else {
			printNode(root);
		}
	}

	Node* find(keyType key) {
		Node* find = nullptr;
		Node* current = this->root;

		while (current != NIL) {
			if (current->key == key) {
				find = current;
				break;
			}
			if (current->key <= key)
				current = current->right;
			else
				current = current->left;
		}
		return find;
	}

	bool contains(keyType key) {
		return containsAlgorithm(root, key);
	}

	void clear() {
		deleteNode(this->root);
		this->root = NIL;
	}

};