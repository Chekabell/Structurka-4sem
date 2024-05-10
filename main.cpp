#include <iostream>

typedef struct Node* pNode;
typedef void(*pFunction)(pNode);
typedef int Item;
const char* ALPHABET[] = { "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ", "ф", "ы", "в",
	"а", "п", "р", "о", "л", "д", "ж", "э", "я", "ч", "с", "м", "и", "т", "ь", "б", "ю",
	"Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Ч", "Ъ", "Ф", "Ы", "В",
	"А", "П", "Р", "О", "Л", "Д", "Ж", "Э", "Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю" };
struct Node {
	Item key;
	int size;
	pNode left;
	pNode right;
	Node(Item k) { key = k; left = right = nullptr; size = 1; }
};

pNode search(pNode node, Item key) {
	if (!node) return nullptr;
	if (key == node->key)
		return node;
	return (key < node->key) ? search(node->left, key) : search(node->right, key);
}

pNode getMax(pNode node) {
	if (!node) return nullptr;
	if (!node->right) return node;
	return getMax(node->right);
}

int getSize(pNode node) {
	if (!node) return 0;
	return node->size;
}

void fixsize(pNode node) {
	node->size = getSize(node->left) + getSize(node->right) + 1;
}

pNode insert(pNode root, Item key) {
	if (!root) return new Node(key);
	pNode newNode = root;
	pNode newNodeParent = nullptr;
	while(newNode){
		if (newNode->key > key) {
			newNodeParent = newNode;
			newNode = newNode->left;
		}
		else {
			newNodeParent = newNode;
			newNode = newNode->right;
		}
	}
	if (newNodeParent->key > key)
		newNodeParent->left = new Node(key);
	else
		newNodeParent->right = new Node(key);
	fixsize(root);
	return root;
}


/* Given a binary search tree and a key, this function
   deletes the key and returns the new root */
pNode removeNode(pNode root, Item k){
	// Base case
	if (!root)
		return root;

	// If the key to be deleted is smaller than the root's key,
	// then it lies in the left subtree
	if (k < root->key) {
		root->left = removeNode(root->left, k);
		return root;
	}
	// If the key to be deleted is greater than the root's key,
	// then it lies in the right subtree
	else if (k > root->key) {
		root->right = removeNode(root->right, k);
		return root;
	}

	// If key is same as root's key, then this is the node to be deleted
	// Node with only one child or no child
	if (!root->left) {
		pNode temp = root->right;
		delete root;
		fixsize(temp);
		return temp;
	}
	else if (!root->right) {
		pNode temp = root->left;
		delete root;
		fixsize(temp);
		return temp;
	}

	// Node with two children: Get the inorder successor (smallest
	// in the right subtree)
	Node* succParent = root;
	Node* succ = root->left;
	while (succ->left != NULL) {
		succParent = succ;
		succ = succ->left;
	}

	// Copy the inorder successor's content to this node
	root->key = succ->key;
	root->size = succ->size;
	// Delete the inorder successor
	if (succParent->left == succ)
		succParent->left = succ->right;
	else
		succParent->right = succ->right;
	delete succ;
	fixsize(succParent);
	fixsize(root);
	return root;
}

void swap(pNode a, pNode b) {
	Item a_key = a->key;
	a->key = b->key;
	b->key = a_key;
}

pNode rotateRight(pNode node) {
	pNode buffer = node->left;
	if (!buffer) return node;
	node->left = buffer->right;
	buffer->right = node;
	buffer->size = node->size;
	fixsize(node);
	return buffer;
}

pNode rotateLeft(pNode node) {
	pNode buffer = node->right;
	if (!buffer) return node;
	node->right = buffer->left;
	buffer->left = node;
	buffer->size = node->size;
	fixsize(node);
	return buffer;
}


pNode insertRoot(pNode node,Item key) {
	if (!node) return new Node(key);
	if (key < node->key) {
		node->left = insertRoot(node->left, key);
		fixsize(node);
		return rotateRight(node);
	}
	else {
		node->right = insertRoot(node->right, key);
		fixsize(node);
		return rotateLeft(node);
	}
}

int height(pNode node) {
	if (!node) return 0;
	return 1 + std::max(height(node->left), height(node->right));
}

pNode insertRand(pNode node, int key) {
	if (!node) return new Node(key);
	if (rand() % (node->size + 1) == 0) 
		return insertRoot(node, key);
	if (node->key > key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);
	fixsize(node);
	return node;
}

void printTree(pNode node) {
	if (!node) return;
	printTree(node->left);
	std::cout << node->key << std::endl;
	printTree(node->right);
}

const char* ALPHABETGLAS[] = { "У","у","Е","е","Ы","ы","А","а","О","о","Э","э","Я","я","И","и","Ю","ю","Ё","ё" };
int _countSogl(pNode node, int high) {
	if (!node) return 0;
	if (high < 3) {
		for (int i = 0; i < 20; i++) {
			if (node->key == *ALPHABETGLAS[i]) {
				return 0 + _countSogl(node->left, high + 1) + _countSogl(node->right, high + 1);
			}
		}
		return 1 + _countSogl(node->left, high + 1) + _countSogl(node->right, high + 1);
	}
	return 0;
}

int countSogl(pNode node) {
	if (!node) return 0;
	return _countSogl(node->left, 1) + _countSogl(node->right, 1);
}

pNode genTree(pNode functionInsert(pNode,Item), const int length, bool mode) {
	pNode root = nullptr;
	if (length > 0)
		for (int i = 0; i < length; i++)
			root = functionInsert(root, mode ? i : rand() % length);
	return root;
}

void checkHeight(pNode functionGen(pNode,Item),const int step) {
	pNode root = nullptr;
	const int maxLen = step * 10;
	int iters;
	int summ;
	std::cout << "--RANDOM KEY--" << std::endl;
	for (int i = step; i <= maxLen; i += step) {
		iters = 0;
		summ = 0;
		while (iters < 10) {
			root = genTree(functionGen, i, false);
			summ += height(root);
			iters++;
		}
		std::cout << "Size tree: " << i << " Height: " << summ/iters << std::endl;
	}
	std::cout << "--ORDERED KEY--" << std::endl;
	for (int i = step; i <= maxLen; i += step) {
		iters = 0;
		summ = 0;
		while (iters < 10) {
			root = genTree(functionGen, i, true);
			summ += height(root);
			iters++;
		}
		std::cout << "Size tree: " << i << " Height: " << summ / iters << std::endl;
	}
}

int main(void) {

	setlocale(LC_ALL, "russian");
	srand(time(NULL));
	const int step = 100;
	std::cout << "---Orderer insert---" << std::endl;
	checkHeight(insert,step);
	std::cout << "---Random insert---" << std::endl;
	checkHeight(insertRand, step);

	return 0;
}