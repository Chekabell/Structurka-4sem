#include <iostream>

typedef struct Node* pNode;
typedef void(*pFunction)(pNode);
typedef char Item;
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


pNode removeNode(pNode root, Item k){
	//Если был отправлен nullptr, то сразу возвращаем его.
	if (!root)
		return root;

	//Если ключ меньше, чем ключ узла, то уходим в левого потомка.
	if (k < root->key) {
		root->left = removeNode(root->left, k);
		return root;
	}
	//Если ключ больше, чем ключ узла, то уходим в правого потомка.
	else if (k > root->key) {
		root->right = removeNode(root->right, k);
		return root;
	}

	//Если нашли нужный ключ, то проверяем есть ли у него дети
	//Если есть один ребёнок, то заменяем им удаляемый узел, 
	//обновляем size и очищаем память заменённого узла.
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

	//Если потомка два, то необходимо найти элемент которым мы заменим удаляемый элемент.
	//Находим максимальный элемент из левого поддерева и его родителя.
	pNode succParent = root;
	pNode succ = root->left;
	while (succ->right) {
		succParent = succ;
		succ = succ->right;
	}

	//Копируем данные из узла максимального потомка слева в удаляемый узел.
	root->key = succ->key;
	root->size = succ->size;
	
	//Заменяем указатель родителя перемещённого потомка на nullptr.
	if (succParent->left == succ)
		succParent->left = nullptr;
	else
		succParent->right = nullptr;

	//Освобождаем память исключённого узла и обновляем размер
	//сначала для родителя максимального потомка, а потом и для
	//узла, в котором произошло удаление.
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

pNode insertRand(pNode node, Item key) {
	if (!node) return new Node(key);
	if (rand() % (node->size + 1) == 0) 
		return insertRoot(node, key);
	if (node->key > key)
		node->left = insertRand(node->left, key);
	else
		node->right = insertRand(node->right, key);
	fixsize(node);
	return node;
}

void _printTree(pNode node , int lvl) {
	if (!node) return;
	_printTree(node->left, lvl + 1);
	std::cout << "lvl:" << lvl << " - " << node->key << std::endl;
	_printTree(node->right, lvl + 1);
}

void printTree(pNode node) {
	_printTree(node,1);
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
	const int step = 8;
	pNode root = new Node(*"А");
	for (int i = 1; i < step; i++) {
		insert(root, *ALPHABET[rand() % 66]);
	}

	printTree(root);
	std::cout << "Count vowel - " << countSogl(root);
	/*std::cout << "---Orderer insert---" << std::endl;
	checkHeight(insert,step);
	std::cout << "---Random insert---" << std::endl;
	checkHeight(insertRand, step);*/
	
	

	return 0;
}