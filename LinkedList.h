#pragma once
#include "List.h"
#include <iostream>
template <typename T>

class LinkedList :public List<T>
{
private:

	struct Node {
		T* item;
		Node* next;

		Node(T* item) {
			this->item = item;
			this->next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:

	virtual int get_size() {
		int size = 0;

		Node* iterator = this->head;

		while (iterator != nullptr) {
			size++;
			iterator = iterator->next;
		}

		return size;
	}

	virtual bool is_empty() {
		return this->head == nullptr;
	}

	virtual void add(T* value) {
		Node* node = new Node(value);

		if (this->is_empty()) {
			this->head = this->tail = node;
			return;
		}

		this->tail->next = node;
		this->tail = this->tail->next;
	}

	virtual bool insert(int index, T* value) {
		if (index < 0) {
			return false;
		}

		Node** iterator = &this->head;
		int i = 0;

		while (i < index && *iterator != nullptr) {
			iterator = &((*iterator)->next);
			i++;
		}

		if (*iterator == nullptr) {
			return false;
		}

		Node* node = new Node(value);

		node->next = *iterator;
		*iterator = node;

		return true;
	}

	virtual T* get(int index) {
		if (index < 0) {
			return nullptr;
		}

		Node* iterator = this->head;

		int i = 0;
		while (i < index) {
			iterator = iterator->next;
			i++;
		}

		if (iterator == nullptr) {
			return nullptr;
		}

		return iterator->item;
	}

	virtual T* remove(int index) {
		if (index < 0) {
			return nullptr;
		}

		Node** iterator = &this->head;
		Node* previous = nullptr;
		int i = 0;

		while (i < index && (*iterator)->next != nullptr) {
			previous = *iterator;
			iterator = &((*iterator)->next);
			i++;
		}

		if ((*iterator)->next == nullptr) {
			this->tail = previous;
		}

		T* item = (*iterator)->item;

		*iterator = (*iterator)->next;

		return item;
	}

	virtual void for_each(void (*action)(T*)) {
		Node* iterator = this->head;

		while (iterator != nullptr) {
			action(iterator->item);
			iterator = iterator->next;
		}
	}
	virtual void for_each_funcion(string (*action)(T*)) {
		Node* iterator = this->head;

		while (iterator != nullptr) {
			action(iterator->item);
			iterator = iterator->next;
		}
		return iterator->item;
	}
};
