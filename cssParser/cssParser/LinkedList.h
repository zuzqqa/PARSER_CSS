#pragma once

using namespace std;

template <typename T>
class LinkedList {
public:
	class Node {
	public:
		explicit Node(T data) : data(data), prev(nullptr), next(nullptr) {}
		T data;
		Node* prev;
		Node* next;
	};

	LinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	};

	LinkedList(const LinkedList<T>& other) { //konstruktor kopiujacy
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;

		for (Node* node = other.head; node != nullptr; node = node->next) {
			AddLast(node->data);
		}
	};

	size_t getListLen() {
		return size;
	};

	Node* getHead() {
		return head;
	};

	Node* getLast() {
		return tail;
	};

	void AddLast(const T& data) {
		Node* newNode = new Node(data);

		if (tail == nullptr) {
			head = newNode;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
		}
		tail = newNode;
		size++;
	};

	void RemoveLast() {
		if (tail != nullptr) {
			Node* temp = tail;
			tail = tail->prev;
			if (tail != nullptr) {
				tail->next = nullptr;
			}
			else head = nullptr;

			delete temp;
			this->size--;

		}
	};

	void RemoveNode(int index) {
		if (this->head == nullptr) {
			return;
		}

		if (index == size - 1) {
			RemoveLast();
		}

		if (index == 0) {
			this->head = this->head->next;
			this->size--;
			return;
		}

		Node* temp = this->head;
		Node* temp1 = nullptr;

		int i = 0;

		while (temp != nullptr) {
			if (index == i) break;
			temp1 = temp;
			temp = temp->next;
			i++;
		}

		if (temp == nullptr) {
			return;
		}

		temp1->next = temp->next;
		this->size--;

		delete temp;
	};

	void clearList() {
		Node* node = head;

		while (node != nullptr) {
			Node* next = node->next;
			delete node;

			node = next;
		}

		head = nullptr;
		tail = nullptr;
		size = 0;
	};

	//~LinkedList() {
	//	clearList();
	//}

	class Iterator { //iterator dla listy
		Node* current;
	public:
		Iterator(Node* current) : current(current) {}

		T& operator*() const {
			return current->data;
		};

		Iterator& operator++() {
			current = current->next;
			return *this;
		};

		bool operator==(const Iterator& other) const {
			return current == other.current;
		};

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		};
	};

	Iterator begin() const {
		return Iterator(head);
	};

	Iterator end() const {
		return Iterator(nullptr);
	};

private:
	Node* head;
	Node* tail;
	size_t size;
};