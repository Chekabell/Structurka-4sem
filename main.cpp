#include <iostream>

typedef struct Node* pNode;
typedef void(*pFunction)(pNode);
typedef char Item;
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

void swap(pNode a, pNode b) {
	int a_key = a->key;
	a->key = b->key;
	b->key = a_key;
}

void rotateRight(pNode node) {
	swap(node, node->left);
	pNode buffer = node->right;
	node->right = node->left;
	node->left = node->right->left;
	node->right->left = node->right->right;
	node->right->right = buffer;
}

void rotateLeft(pNode node) {
	swap(node, node->right);
	pNode buffer = node->left;
	node->left = node->right;
	node->right = node->left->right;
	node->left->right = node->left->left;
	node->left->left = buffer;
}


pNode insertRoot(pNode node,Item key) {
	if (!node) {
		node = createNode(key);
		return node;
	}
	else
		if (key < node->key) {
			insertRoot(node->left, key);
			rotateRight(node);
		}
		else {
			insertRoot(node->left, key);
			rotateLeft(node);
		}
}

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
	const char* ALPHABET[] = { "й","ц","у","к","е","н","г","ш","щ","з","х","ъ","ф","ы","в",
	"а","п","р","о","л","д","ж","э","я","ч","с","м","и","т","ь","б","ю" };

	setlocale(LC_ALL, "russian");
	srand(time(NULL));
	pNode root = createNode(*ALPHABET[rand()%32]);

	std::cout << "Root : " << root->key << std::endl;
	for (int i = 0; i < 5; i++) {
		char key = *ALPHABET[rand() % 32];
		insert(root, key);
		std::cout << i+1 << " : " << key << std::endl;
	}

	printTree(root);
	std::cout << std::endl << "High : " << height(root) << std::endl;
	std::cout << "Size : " << size(root) << std::endl;

	printTree(root);
	std::cout << std::endl << "High : " << height(root) << std::endl;
	std::cout << "Size : " << size(root) << std::endl;

	return 0;
}