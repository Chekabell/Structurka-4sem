#include <iostream>
#include <set>

typedef struct Node* pNode;
typedef int Item;

struct Node {
	Item key;
	pNode left;
	pNode right;
	pNode parent;
	bool color;
	Node(Item k, bool col = true) {
		key = k;
		color = col;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	};
};

class RBTree {
private:
	pNode root;
	int size;
	pNode nul;
public:
	RBTree() {
		nul = new Node(0, false);
		root = nul;
		size = 0;
	}
	~RBTree() {
		clear();
	}
	pNode getRoot() {
		return root;
	}
	int getSize() {
		return size;
	}
	bool insert(Item key) {
		pNode curr = root;
		pNode parent = nul;
		while (curr != nul) {
			parent = curr;
			if (key < curr->key) curr = curr->left;
			else curr = curr->right;
		}
		pNode newNode = new Node(key);
		newNode->left = nul;
		newNode->right = nul;
		newNode->parent = parent;
		if (parent == nul) root = newNode;
		else if (key < parent->key) parent->left = newNode;
		else parent->right = newNode;
		_balanceInsert(newNode);
		size++;
		return true;
	}
	void remove(Item key) {
		pNode nodeToDelete = (*this)[key];
		pNode child;
		bool removedNodeColor = nodeToDelete->color;
		if (_getChildrenCount(nodeToDelete) < 2) {
			child = _getChildOrMock(nodeToDelete);
			_transplantNode(nodeToDelete, child);
			delete nodeToDelete;
		}
		else {
			pNode minNode = _getMin(nodeToDelete->right);
			nodeToDelete->key = minNode->key;
			removedNodeColor = minNode->color;
			child = _getChildOrMock(minNode);
			_transplantNode(minNode, child);
			delete minNode;
		}
		if (removedNodeColor == false) _fixAfterRemoval(child);
		size--;
	}
	bool clear() {
		_clearTree(root);
		root = nul;
		size = 0;
		return true;
	};
	pNode operator [](Item key) {
		pNode curr = root;
		while (curr != nul && curr->key != key) {
			if (curr->key > key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return curr;
	}
	void _printTree(pNode node, int space){
		if (node == nul) return;
		space += 5;

		_printTree(node->right, space);
		std::cout << std::endl;
		for (int i = 5; i < space; i++)
			std::cout << " ";
		std::cout << node->key <<" c:" << node->color << std::endl;
		_printTree(node->left, space);
	}
	void printTree() {
		_printTree(root, 0);
	}
protected:
	void _clearTree(pNode node) {
		if (node == nul) return;
		_clearTree(node->left);
		_clearTree(node->right);
		std::cout << "Deleted key: " << node->key << std::endl;
		delete node;
	}
	void _balanceInsert(pNode newNode) {
		while(newNode->parent->color) {
			if (newNode->parent == newNode->parent->parent->left) {
				pNode uncle = newNode->parent->parent->right;
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
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					_rightRotate(newNode->parent->parent);
				}
			}
			else {
				pNode uncle = newNode->parent->parent->left;
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
					}
					newNode->parent->color = false;
					newNode->parent->parent->color = true;
					_leftRotate(newNode->parent->parent);
				}
			}
		}
		root->color = false;
	}
	int _getChildrenCount(pNode node) {
		int count = 0;
		if (_nodeExist(node->left))count += 1;
		if (_nodeExist(node->right))count += 1;
		return count;
	}
	pNode _getChildOrMock(pNode node) {
		return _nodeExist(node->left) ? node->left : node->right;
	}
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
	}
	void _transplantNode(pNode toNode, pNode fromNode) {
		if (toNode == root) root = fromNode;
		if (toNode == toNode->parent->left) toNode->parent->left = fromNode;
		else toNode->parent->right = fromNode;
		fromNode->parent = toNode->parent;
	}
	void _swap(pNode a, pNode b) {
		Item a_key = a->key;
		a->key = b->key;
		b->key = a_key;
	}
	void _rightRotate(pNode node) {
		_swap(node, node->left);
		pNode buffer = node->right;
		node->right = node->left;
		node->left = node->right->left;
		node->right->left = node->right->right;
		node->right->right = buffer;
		if (node->right != nul) node->right->parent = node;
		
		/*pNode buffer = node->left;
		node->left = buffer->right;

		if (node->right != nul) {
			node->right->parent = node;
		}

		buffer->parent = node->parent;

		if (node == root) {
			root = buffer;
		}
		else if (node == node->parent->right){
			node->parent->right = buffer;
		}
		else {
			node->parent->left = buffer;
		}
		buffer->right = node;
		node->parent = buffer;*/
	}
	void _leftRotate(pNode node) {
		_swap(node, node->right);
		pNode buffer = node->left;
		node->left = node->right;
		node->right = node->left->right;
		node->left->right = node->left->left;
		node->left->left = buffer;
		if (node->left != nul) node->left->parent = node;
		/*pNode buffer = node->right;
		node->right = buffer->left;

		if (node->left != nul) node->left->parent = node;

		buffer->parent = node->parent;

		if (node == root) {
			root = buffer;
		}
		else if (node == node->parent->left) {
			node->parent->left = buffer;
		}
		else {
			node->parent->right = buffer;
		}
		buffer->left = node;
		node->parent = buffer;*/
	}
	pNode _getMin(pNode node) {
		if (node == nul) return nul;
		if (node->left == nul) return node;
		return _getMin(node->left);
	}
	bool _nodeExist(pNode node) {
		return (node != nul) ? true : false;
	}
};

RBTree* genTree(const int length, const bool mode) {
	RBTree* root = new RBTree;
	
	if (length > 0) {
		if (mode) {
			for (int i = 0; i < length; i++)
				root->insert(i);
		}
		else {
			/*std::set<int> tmp;
			while (tmp.size() <= length)
				tmp.insert(rand());
			auto iterEnd = tmp.cend();
			for (auto iterBegin = tmp.begin(); iterBegin != iterEnd; iterBegin++) {
				root->insert(*iterBegin);
			}*/
			for (int i = 0; i < length; i++) {
				std::cout << i << ": ";
				int key = rand() % length;
				std::cout << key << std::endl;
				root->insert(key);
			}
		}
	}
	return root;
}

void checkHeight(const int step) {
	RBTree* tree;
	const int maxLen = step * 10;
	int iters;
	int summ;
	std::cout << "--ORDERED KEY--" << std::endl;
	for (int i = step; i <= maxLen; i += step) {
		std::cout << "Size tree: " << i << std::endl;
		tree = genTree(i, true);
		tree->printTree();
		tree->clear();
	}
	std::cout << "--RANDOM KEY--" << std::endl;
	for (int i = step; i <= maxLen; i += step) {
		std::cout << "Size tree: " << i << std::endl;
		tree = genTree(i, false);
		tree->printTree();
		tree->clear();
	}
}

int main(void) {
	srand(time(NULL));
	const int step = 2;
	checkHeight(step);

}