#pragma once
#include <iostream>
#include <set>
#include <random>
#include <iomanip>
#include <locale>
class RedBlackTree
{
	class Node 
	{
	public:
		char color;
		int data;
		Node* parent;
		Node* left;
		Node* right;

		Node();
		Node(int init_data);
	};

private:
	Node* root;
	int deep;
	void DisplayTreeHelper(Node* node);
	int GetDepthHelper(Node* node);
public:
	RedBlackTree();

	void Insert(int data);
	void Balance(Node* new_node);
	void LLImbalance(Node* pull);
	void RRImbalance(Node* pull);
	void LRImbalance(Node* pull);
	void RLImbalance(Node* pull);

	void InsertRandom(int count, int min, int max);
	void DisplayTree();
	int GetDepth();
};

