#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>

using namespace std;

template<typename T>
struct Node {
	char *path = nullptr;
	T value;
	Node *Left = nullptr;
	Node *Right = nullptr;
};

template <typename T>
class Trie {
public:
	Trie(){
		root = nullptr;
	}

	void Add(char *key, const T& val) {
		if (root == nullptr) {
			root = new Node<T>;
			memcpy(root->path, key, sizeof key);
			root->value = val;
			return;
		}

	}
private:
	Node<T> *root;
	
private:
	static char Leftmost(char c) {
		c |= (c >> 1);
		c |= (c >> 2);
		c |= (c >> 4);
		return ((c + 1) >> 1);
	}
	
	void DeleteNode(Node<T>* node){
		if (node == nullptr) return;
		
		DeleteNode(node->Left);
		DeleteNode(node->Right);

		if (node->path != nullptr)delete node->path;

		delete node;

		return;
	}
	~Trie() {
		DeleteNode(root);
	}
};