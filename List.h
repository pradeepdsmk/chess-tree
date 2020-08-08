#pragma once

namespace chess {

	template <class T>
	struct ListNode
	{
		T* item;
		ListNode<T>* prev;
		ListNode<T>* next;

		ListNode(T* _item) {
			item = _item;
			prev = nullptr;
			next = nullptr;
		}

		~ListNode() {
		}
	};


	template <class T>
	struct List {
		ListNode<T>* nodes;
		unsigned char length;

		List<T>() {
			nodes = nullptr;
			length = 0;
		}

		void append(T* _item) {
			ListNode<T>* node = new ListNode<T>(_item);

			if (!nodes) {
				nodes = node;
			}
			else {
				ListNode<T>* ptr = nodes;
				while (ptr->next) {
					ptr = ptr->next;
				}
				ptr->next = node;
				node->prev = ptr;
			}

			++length;
		}

		void remove(ListNode<T>* node) {
			if (node->next) {
				node->next->prev = node->prev;
			}

			if (node->prev) {
				node->prev->next = node->next;
			}
			else {
				// this is first node
				nodes = node->next;
			}

			node->prev = nullptr;
			node->next = nullptr;

			delete node;
			node = nullptr;

			--length;
		}

		void remove(T* item) {
			ListNode<T>* node = nodes;
			while (node) {
				if (node->item == item) {
					remove(node);
					break;
				}
				node = node->next;
			}
		}

		void clear() {
			delete nodes;
			nodes = nullptr;

			length = 0;
		}

		T* getAt(unsigned char pos) {			
			if (pos >= length) {
				return nullptr;
			}
						
			unsigned char i = 0;
			ListNode<T>* node = nodes;
			bool found = false;
			for (i = 0; i < pos; ++i) {
				node = node->next;
			}
			return node->item;
		}

		~List() {
			ListNode<T>* p = nodes;
			ListNode<T>* q;
			while (p) {
				q = p->next;
				delete p;
				p = q;
			}
			nodes = nullptr;
		}
	};
}