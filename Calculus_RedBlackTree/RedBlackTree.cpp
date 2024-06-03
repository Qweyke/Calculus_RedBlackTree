#include "RedBlackTree.h"


RedBlackTree::Node::Node() : color('B'), data(0), parent(nullptr), left(nullptr), right(nullptr) {}
RedBlackTree::Node::Node(int init_data) : color('R'), data(init_data), parent(nullptr), left(nullptr), right(nullptr) {}

RedBlackTree::RedBlackTree() 
{
	root = nullptr;
	deep = 0;
}

void RedBlackTree::Insert(int data) 
{
	if (root == nullptr) 
	{
		root = new Node(data);
		return;
	}

	else
	{
		Node* new_node = new Node(data);
		Node* curr_level = root;
		Node* new_node_parent = nullptr;

		while (curr_level != nullptr)
		{
			new_node_parent = curr_level;
			if (new_node->data > curr_level->data)
			{
				curr_level = curr_level->right;
			}
			else curr_level = curr_level->left;
		}
		new_node->parent = new_node_parent;
		if (new_node->data > new_node_parent->data)
		{
			new_node_parent->right = new_node;
		}
		else new_node_parent->left = new_node;
		
		Balance(new_node);
	}
}

void RedBlackTree::Balance(Node* broken_node) 
{
	if (broken_node->parent->color == 'R')
	{
		Node* dad = broken_node->parent;

		if (dad->parent != nullptr)
		{
			Node* grand_d = dad->parent;
			if (grand_d->left == dad)
			{
				if (grand_d->right->color == 'R' && grand_d->right != nullptr)
				{
					grand_d->color = 'R';
					grand_d->right->color = 'B';
					dad->color = 'B';
					Balance(grand_d);
				}
				else if (grand_d->right->color == 'B' && grand_d->right != nullptr)
				{
					if (broken_node == dad->left)
					{
						LLImbalance(dad);
						if (dad->color == 'B')
						{
							dad->color = 'R';
							broken_node->color = 'B';
							dad->right->color = 'B';
						}
						Balance(dad);
					}
					else if (broken_node == dad->right)
					{
						LRImbalance(broken_node);
						if (broken_node->color = 'B')
						{
							broken_node->color = 'R';
							broken_node->left->color = 'B';
							broken_node->right->color = 'B';
						}
						Balance(broken_node);
					}						
				}
			}
			else if (grand_d->right == dad) 
			{
				if (grand_d->left->color == 'R' && grand_d->left != nullptr)
				{
					grand_d->color = 'R';
					grand_d->left->color = 'B';
					dad->color = 'B';
					Balance(grand_d);
				}
				else if (grand_d->left->color == 'B' && grand_d->left != nullptr)
				{
					if (broken_node == dad->right)
					{
						RRImbalance(dad);
						if (dad->color = 'B')
						{
							dad->color = 'R';
							broken_node->color = 'B';
							dad->right->color = 'B';
						}
						Balance(dad);
					}
					else if (broken_node == dad->left)
					{
						LRImbalance(broken_node);
						if (broken_node->color = 'B')
						{
							broken_node->color = 'R';
							broken_node->left->color = 'B';
							broken_node->right->color = 'B';
						}
						Balance(broken_node);
					}
				}
			}
			
		}
	}
	root->color = 'B';
}

void RedBlackTree::LLImbalance(Node* pull) // LEFT-LEFT imbalance
{
	Node* ex_dad = pull->parent; // бывший папа (А), будет поменян местом
	ex_dad->left = pull->right; // меняем левый узел бывшего папы(А) на правый узел его сына (B)
	
	if (ex_dad->left != nullptr) ex_dad->left->parent = ex_dad; // проверяем перешедший узел на пустоту, перестраиваем связь в ином случае
	
	pull->parent = ex_dad->parent; // связываем pull и родителя ex_dad 
	if (ex_dad->parent == nullptr) root = pull;
	else if (ex_dad == ex_dad->parent->left) ex_dad->parent->left = pull;
	else if (ex_dad == ex_dad->parent->right) ex_dad->parent->right = pull;
	
	ex_dad->parent = pull; 	// смена связи ex_dad и pull 
	pull->right = ex_dad;

	pull->color = ex_dad->color; // обмен цветами
	ex_dad->color = 'R';
	
}

void RedBlackTree::RRImbalance(Node* pull) // RIGHT-RIGHT imbalance
{
	Node* ex_dad = pull->parent; // бывший папа (А), будет поменян местом
	ex_dad->right = pull->left; // меняем правый узел бывшего папы(А) на левый узел его сына (B)

	if (ex_dad->right != nullptr) ex_dad->right->parent = ex_dad; // проверяем перешедший узел на пустоту, перестраиваем связь в ином случае
	
	pull->parent = ex_dad->parent; // связываем pull и родителя ex_dad 
	if (ex_dad->parent == nullptr) root = pull;
	else if (ex_dad == ex_dad->parent->left) ex_dad->parent->left = pull;
	else if (ex_dad == ex_dad->parent->right) ex_dad->parent->right = pull;

	ex_dad->parent = pull; // смена связи ex_dad и pull 
	pull->left = ex_dad;

	pull->color = ex_dad->color; // обмен цветами
	ex_dad->color = 'R';
}

void RedBlackTree::LRImbalance(Node* son_C)
{
	Node* dad_B = son_C->parent;
	Node* grand_A = dad_B->parent;

	dad_B->right = son_C->left;
	if (dad_B->right != nullptr) dad_B->right->parent = dad_B;
	grand_A->left = son_C->right;
	if (grand_A->left != nullptr) grand_A->left->parent = grand_A;

	son_C->parent = grand_A->parent;
	if (grand_A->parent == nullptr) root = son_C;
	else if (grand_A == grand_A->parent->left) grand_A->parent->left = son_C;
	else if (grand_A == grand_A->parent->right) grand_A->parent->right = son_C;

	son_C->left = dad_B;
	dad_B->parent = son_C;
	son_C->right = grand_A;
	grand_A->parent = son_C;

	son_C->color = grand_A->color;
	grand_A->color = 'R';

}

void RedBlackTree::RLImbalance(Node* son_C)
{
	Node* dad_B = son_C->parent;
	Node* grand_A = dad_B->parent;

	grand_A->right = son_C->left;
	if (grand_A->right != nullptr) grand_A->right->parent = grand_A;
	dad_B->left = son_C->right;
	if (dad_B->left != nullptr) dad_B->left->parent = dad_B;
	

	son_C->parent = grand_A->parent;
	if (grand_A->parent == nullptr) root = son_C;
	else if (grand_A == grand_A->parent->left) grand_A->parent->left = son_C;
	else if (grand_A == grand_A->parent->right) grand_A->parent->right = son_C;

	son_C->left = grand_A;
	grand_A->parent = son_C;
	son_C->right = dad_B;
	dad_B->parent = son_C;

	son_C->color = grand_A->color;
	grand_A->color = 'R';
}

void RedBlackTree::InsertRandom(int count, int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	std::set<int> unique_values;

	while (unique_values.size() < count)
	{
		int value = dis(gen);
		if (unique_values.find(value) == unique_values.end())
		{
			unique_values.insert(value);
			Insert(value);
		}
	}
}

// Отображение дерева
void RedBlackTree::DisplayTree()
{
	DisplayTreeHelper(root, 0);
}

void RedBlackTree::DisplayTreeHelper(Node* node, int indent)
{
	if (node != nullptr)
	{
		if (node->right)
		{
			DisplayTreeHelper(node->right, indent + 4);
		}
		if (indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		if (node->right) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << node->data << "(" << node->color << ")" << "\n ";
		if (node->left)
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			DisplayTreeHelper(node->left, indent + 4);
		}
	}
}

// Получение глубины дерева
int RedBlackTree::GetDepth()
{
	return GetDepthHelper(root);
}

int RedBlackTree::GetDepthHelper(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		int left_depth = GetDepthHelper(node->left);
		int right_depth = GetDepthHelper(node->right);
		return std::max(left_depth, right_depth) + 1;
	}
}