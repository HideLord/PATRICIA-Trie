#pragma once

template<typename T>
struct Node {
	char *path = nullptr;
	T value;
	Node<T> *Left = nullptr;
	Node<T> *Right = nullptr;
};

template <typename T> class Trie {
public:
	Trie(){
		root = nullptr;
	}

	T Get(const char *key) {
		size_t lenKey = strlen(key);

		register Node<T> *currnode = root;
		register char dif;

		size_t j = 0;
		for (size_t i = 0; i < lenKey; ++i) {
			if (dif = (key[i] ^ currnode->path[j++])) {
				if ((Leftmost(dif) & key[i])) {
					if (currnode->Right == nullptr) {
						return T();
					}
					else {
						currnode = currnode->Right;
						j = 0;
						--i;
					}
				}
				else {
					if (currnode->Left == nullptr) {
						return T();
					}
					else {
						currnode = currnode->Left;
						j = 0;
						--i;
					}
				}
			}
		}
		if (currnode->path[j] == '\0')return currnode->value;
		return T();
	}

	void Add(const char *key, const T& val) {
		size_t lenKey = strlen(key);

		if (root == nullptr) {
			root = new Node<T>;
			root->path = new char[lenKey + 1];
			strcpy(root->path, key);
			root->value = val;
			return;
		}
		register Node<T> *currnode = root;
		register char dif;

		register size_t j = 0;
		for (register size_t i = 0; i < lenKey; ++i) {
			if (dif = (key[i] ^ currnode->path[j++])) {
				if ((Leftmost(dif) & key[i])) {
					if (currnode->Right == nullptr) {
						currnode->Right = new Node<T>;
						size_t tsize = lenKey - i + 1;
						currnode->Right->path = new char[tsize];
						strcpy(currnode->Right->path, (key + i));
						currnode->Right->value = val;
						return;
					}
					else {
						currnode = currnode->Right;
						j = 0;
						--i;
					}
				}
				else {
					if (currnode->Left == nullptr) {
						currnode->Left = new Node<T>;
						size_t tsize = lenKey - i + 1;
						currnode->Left->path = new char[tsize];
						strcpy(currnode->Left->path, (key + i));
						currnode->Left->value = val;
						return;
					}
					else {
						currnode = currnode->Left;
						j = 0;
						--i;
					}
				}
			}
		}
		if (currnode->path[j]=='\0')currnode->value = val;
		else {
			Node<T> *newnode = new Node<T>;
			newnode->path = new char[strlen(currnode->path) - j + 1];
			strcpy(newnode->path,currnode->path + j);
			currnode->path[j] = '\0';

			newnode->Left = currnode->Left;
			newnode->Right = currnode->Right;
			newnode->value = currnode->value;

			currnode->value = val;
			if ((newnode->path[0] & 0x80)) {
				currnode->Left = newnode;
				currnode->Right = nullptr;
			}
			else {
				currnode->Right = newnode;
				currnode->Left = nullptr;
			}
		}
	}

	~Trie() {
		DeleteNode(root);
	}
	
private:
	Node<T> *root;
	
private:
	static char Leftmost(char c) {
		
		c |= (c >> 1);
		c |= (c >> 2);
		c |= (c >> 4);

		return (((unsigned char)c + 1) >> 1);
	}
	
	void DeleteNode(Node<T>* node){
		if (node == nullptr) return;
		
		DeleteNode(node->Left);
		DeleteNode(node->Right);

		if (node->path != nullptr)delete[] node->path;

		delete node;

		return;
	}
};