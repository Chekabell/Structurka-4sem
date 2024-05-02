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

pNode insert(pNode node, Item key) {
	pNode newNode = createNode(key);
	if (key >= node->key) {
		if (!node->right) node->right = newNode;
		else insert(node->right, key);
	}
	else {
		if (!node->left) node->left = newNode;
		else insert(node->right, key);
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

int main(void) {
	return 0;
}