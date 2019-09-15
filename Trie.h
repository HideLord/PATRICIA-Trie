#pragma once

template<typename T>
struct Node {
	char *path = nullptr;
	T value;
	Node<T> *Left = nullptr;
	Node<T> *Right = nullptr;
};

template <typename T>
class Trie {
public:
	Trie(){
		root = nullptr;
	}

	T Get(const char *key) {
		size_t lenKey = strlen(key);

		if (root == nullptr) {
			return T();
		}
		Node<T> *currnode = root;
		register char dif;

		size_t lenPath = strlen(currnode->path);
		size_t j = 0;
		for (size_t i = 0; i < lenKey; ++i) {
			dif = (key[i] ^ currnode->path[j++]);
			if (dif) {
				if ((Leftmost(dif) & key[i])) {
					if (currnode->Right == nullptr) {
						return T();
					}
					else {
						currnode = currnode->Right;
						j = 0;
						i--;
						lenPath = strlen(currnode->path);
					}
				}
				else {
					if (currnode->Left == nullptr) {
						return T();
					}
					else {
						currnode = currnode->Left;
						j = 0;
						i--;
						lenPath = strlen(currnode->path);
					}
				}
			}
		}
		if (j == lenPath) {
			return currnode->value;
		}
		return T();
	}

	void Add(const char *key, const T& val) {
		size_t lenKey = strlen(key);

		char *keyCopy = new char[lenKey+1];
		memcpy(keyCopy, key, lenKey+1);

		if (root == nullptr) {
			root = new Node<T>;
			root->path = new char[lenKey + 1];
			strcpy(root->path, key);
			//root->value = val;
			return;
		}
		register Node<T> *currnode = root;
		register char dif;

		size_t lenPath = strlen(currnode->path);
		size_t j = 0;
		for (size_t i = 0; i < lenKey; ++i) {
			if (dif = (key[i] ^ currnode->path[j++])) {
				if ((Leftmost(dif) & key[i])) {
					if (currnode->Right == nullptr) {
						currnode->Right = new Node<T>;
						//currnode->Right->path = new char[lenKey - i + 1];
						//strcpy(currnode->Right->path, (key + i));
						//memcpy(currnode->Right->path, (key + i), lenKey - i + 1);
						currnode->Right->path = (keyCopy + i);
						//currnode->Right->value = val;
						return;
					}
					else {
						currnode = currnode->Right;
						j = 0;
						--i;
						lenPath = strlen(currnode->path);
					}
				}
				else {
					if (currnode->Left == nullptr) {
						currnode->Left = new Node<T>;
						//currnode->Left->path = new char[lenKey - i + 1];
						//strcpy(currnode->Left->path, (key + i));
						//memcpy(currnode->Left->path, (key + i), lenKey - i + 1);
						currnode->Left->path = (keyCopy + i);
						//currnode->Left->value = val;
						return;
					}
					else {
						currnode = currnode->Left;
						j = 0;
						--i;
						lenPath = strlen(currnode->path);
					}
				}
			}
		}
		while (currnode->Left != nullptr) {
			currnode = currnode->Left;
		}
		currnode->Left = new Node<T>;
		currnode->Left->path = new char[1];
		//currnode->Left->value = val;
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