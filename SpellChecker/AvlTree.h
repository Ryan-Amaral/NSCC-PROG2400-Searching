//  File: AvlTree.h
//	Purpose: Header file for AvlTree.cpp
//  Project: SpellChecker
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <string>
#include <iostream>

class Node
{
public:
	Node(std::string data, Node* parent) :
		data(data), parent(parent), left(nullptr), right(nullptr)
	{
	};
	std::string data; // the data in the node
	Node* parent; // the parent of the node
	Node* left; // left child
	Node* right; // right child
};

class AvlTree
{
private:
	

	bool findRec(const std::string& data, const Node& node) const;
	void insertRec(const std::string& data, Node& node);
	int height(const Node* node) const;
	void balance(Node& node);
	void rotateLeft(Node& node);
	void rotateRight(Node& node);
	void deleteNodesRec(Node& node);

	Node* _root;
public:
	AvlTree();
	~AvlTree();
	bool find(const std::string& data) const;
	void insert(const std::string data);

	friend std::ostream& operator <<(std::ostream& output, const AvlTree& tree);
	friend void recTraverseNode(std::ostream& output, const Node& node, const int lvlToPrint, const int curLvlChg);
};

#endif