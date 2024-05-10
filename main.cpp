#pragma once
#include <iostream>

typedef Node* pNode;
typedef int Item;

struct Node {
	Item key;
	pNode left;
	pNode right;
	pNode parent;
	bool color;
	Node(Item k) {
		key = k;
		color = false;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	};
	bool nodeExist(pNode node) {
		return (node != nul) ? true : false;
	}
};

pNode nul = new Node(0);

class RBTree {
private:
	pNode root;
	int size;
public:
	RBTree() {
		root = nul;
		size = 0;
	};
	~RBTree() {
		clear();
	}
	int getSize() {
		return size;
	};
	bool insert(Item key) {
		pNode curr = root;
		pNode parent = nul;
		while (curr->nodeExist()) {
			if (curr->key == key) {
				return false;
			}
			parent = curr;
			if ((*curr) > key) curr = curr->left;
			else curr = curr->right;
		}
		pNode newNode = new Node(key);
		newNode->left = nul;
		newNode->right = nul;
		newNode->parent = parent;
		if (parent == nul) {
			root = newNode;
		}
		else if ((*parent) > key) parent->left = newNode;
		else parent->right = newNode;
		_balanceInsert(newNode);
		size++;
		return true;
	};
	void remove(Item key) {
		pNode nodeToDelete = search(key);
		pNode child;
		bool removedNodeColor = nodeToDelete->color;
		if (_getChildrenCount(nodeToDelete) < 2) {
			child = _getChildOrMock(nodeToDelete);
			_transplantNode(nodeToDelete, child);
			delete nodeToDelete;
		}
		else {
			pNode minNode = tnode<Type>::getMin(nodeToDelete->right);
			nodeToDelete->key = minNode->key;
			nodeToDelete->data = minNode->data;
			removedNodeColor = minNode->color;
			child = _getChildOrMock(minNode);
			_transplantNode(minNode, child);
			delete minNode;
		}
		if (removedNodeColor == false) _fixAfterRemoval(child);
		nul->parent = nullptr;
		size--;
	};
	bool clear() {
		_clearTree(root);
		root = nul;
		size = 0;
		return _chekTree();
	};
	pNode search(Item key) {
		pNode curr = root;
		while (curr != nul && (*curr) != key) {
			if ((*curr) > key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return curr;
	};
protected:
	void _clearTree(pNode node) {
		if (node == nul) return;
		_clearTree(node->left);
		_clearTree(node->right);
		delete node;
	};
	void _balanceInsert(pNode newNode) {
		pNode uncle;
		while (newNode->parent->color) {
			if (newNode->parent == newNode->parent->parent->left) {
				uncle = newNode->parent->parent->right;
				if (uncle->color) {
					newNode->parent->color = false;
					uncle->color = false;
					newNode->parent->parent->color = true;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->right) {
						newNode = newNode->parent;
						_leftRotate(newNode);
						newNode = newNode->left;
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					_rightRotate(newNode->parent->parent);
				}
			}
			else {
				uncle = newNode->parent->parent->left;
				if (uncle->color) {
					newNode->parent->color = false;
					uncle->color = false;
					newNode->parent->parent->color = true;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode == newNode->parent->left) {
						newNode = newNode->parent;
						_rightRotate(newNode);
						newNode = newNode->right;
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					_leftRotate(newNode->parent->parent);
				}
			}
		}
		root->color = false;
	};
	int _getChildrenCount(pNode node) {
		int count = 0;
		if (node->left->nodeExist())count += 1;
		if (node->right->nodeExist())count += 1;
		return count;
	};
	pNode _getChildOrMock(pNode node) {
		return node->left->nodeExist() ? node->left : node->right;
	};
	bool _chekTree() {
		return root->nodeExist() ? true : false;
	};
	void _fixAfterRemoval(pNode node) {
		while (node != root && !node->color) {
			pNode brother;
			if (node == node->parent->left) {
				brother = node->parent->right;
				if (brother->color) {
					brother->color = false;
					node->parent->color = true;
					_leftRotate(node->parent);
					brother = node->parent->right;
				}
				if (!brother->left->color && !brother->right->color) {
					brother->color = true;
					node = node->parent;
				}
				else {
					if (!brother->right->color) {
						brother->left->color = false;
						brother->color = true;
						_rightRotate(brother);
						brother = node->parent->right;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->right->color = false;
					_leftRotate(node->parent);
					node = root;
				}
			}
			else {
				brother = node->parent->left;
				if (brother->color) {
					brother->color = false;
					node->parent->color = true;
					_rightRotate(node->parent);
					brother = node->parent->left;
				}
				if (!brother->left->color && !brother->right->color) {
					brother->color = true;
					node = node->parent;
				}
				else {
					if (!brother->left->color) {
						brother->right->color = false;
						brother->color = true;
						_leftRotate(brother);
						brother = node->parent->left;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->left->color = false;
					_rightRotate(node->parent);
					node = root;
				}
			}
		}
		node->color = false;
	};
	void _transplantNode(pNode toNode, pNode fromNode) {
		if (toNode == root) root = fromNode;
		if (toNode == toNode->parent->left) toNode->parent->left = fromNode;
		else toNode->parent->right = fromNode;
		fromNode->parent = toNode->parent;
	};
	void _swap(pNode a, pNode b) {
		Item a_key = a->key;
		a->key = b->key;
		b->key = a_key;
		bool a_col = a->color;
		a->color = b->color;
		b->color = a_col;
	};
	void _rightRotate(pNode node) {
		_swap(node, node->left);
		pNode buffer = node->right;
		node->right = node->left;
		node->left = node->right->left;
		node->right->left = node->right->right;
		node->right->right = buffer;
		if (node->left != nul) node->left->parent = node;
	}
	void _leftRotate(pNode node) {
		_swap(node, node->right);
		pNode buffer = node->left;
		node->left = node->right;
		node->right = node->left->right;
		node->left->right = node->left->left;
		node->left->left = buffer;
		if (node->right != nul) node->right->parent = node;
	}
};


int main(void) {

}