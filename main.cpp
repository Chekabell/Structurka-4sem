#include <iostream>

typedef struct Node* pNode;
typedef void(*pFunction)(pNode);
typedef int Item;
struct Node {
	pNode left;
	pNode right;
	Item key;
};

//---------------------Создание узла----------------------------------------
pNode createNode(Item key){
	pNode pN = new Node;
	pN->left = nullptr;
	pN->right = nullptr;
	pN->key = key;
	return pN;
}

pNode getMax(pNode node) {
	if (!node) return nullptr;
	if (!node->right) return node;
	return getMax(node->right);
}

pNode getMin(pNode node) {
	if (!node) return nullptr;
	if (!node->left) return node;
	return getMin(node->left);
}

pNode insert(pNode node, Item key) {
	pNode newNode = nullptr;
	if (key >= node->key) {
		if (!node->right) {
			newNode = createNode(key);
			node->right = newNode;
		}
		else insert(node->right, key);
	}
	else {
		if (!node->left) {
			newNode = createNode(key);
			node->left = newNode;
		}
		else insert(node->left, key);
	}
	return newNode;
}

pNode search(pNode node, Item key) {
	if (!node) return nullptr;
	if (node->key == key) return node;
	return (key >= node->key) ? search(node->right, key) : search(node->left, key);
}

pNode remove(pNode node, Item key) {
	if (!node) return nullptr;
	else if (key < node->key) node->left = remove(node->left, key);
	else if (key > node->key) node->right = remove(node->right, key);
	else {
		if (!node->left || !node->right) node = (!node->left) ? node->right : node->left;
		else {
			pNode maxInLeft = getMax(node->left);
			node->key = maxInLeft->key;
			remove(node->left,maxInLeft->key);
		}
	}
}

//pNode insertRoot(pNode node,Item key) {
//	pNode newNode = createNode(key);
//	if (!node) return newNode;
//	if (key > node->key) newNode->left = node;
//	else newNode->right = node;
//	return newNode;
//}

void printTree(pNode node) {
	if (!node) return;
	printTree(node->left);
	std::cout << node->key << std::endl;
	printTree(node->right);
}

int height(pNode node){
	if (!node) return 0;
	return 1 + std::max(height(node->left), height(node->right));
}

int size(pNode node) {
	if (!node) return 0;
	return 1 + size(node->left) + size(node->right);
}

int main(void) {
	srand(time(NULL));
	pNode root = createNode(1);
	int key = 0;

	std::cout << "R : " << 1 << std::endl;
	for (int i = 0; i < 5; i++) {
		key = rand() % 10;
		insert(root, key);
		std::cout << i+1 << " : " << key << std::endl;
	}
	printTree(root);
	std::cout << std::endl << "H : " << height(root) << std::endl;
	std::cout << "S : " << size(root) << std::endl;
	std::cout << remove(root, 1) << std::endl;
	printTree(root);
	std::cout << std::endl << "H : " << height(root) << std::endl;
	std::cout << "S : " << size(root) << std::endl;

	return 0;
}