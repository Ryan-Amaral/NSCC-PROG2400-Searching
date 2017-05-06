//  File: AvlTree.cpp
//	Purpose: AVL Tree.
//  Project: SpellChecker
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#include "AvlTree.h"

/// Creates an avl tree with null root.
AvlTree::AvlTree() : _root(nullptr){}

AvlTree::~AvlTree()
{
	if (_root != nullptr)
	{
		// delete left sub tree
		if (_root->left != nullptr)
		{
			deleteNodesRec(*_root->left);
		}
		// delete right sub tree
		if (_root->left != nullptr)
		{
			deleteNodesRec(*_root->right);
		}
		// delete root node
		delete _root;
	}
}

/// Deletes all nodes in the tree recursively.
void AvlTree::deleteNodesRec(Node& node)
{
	// delete left sub tree
	if (&node.left != nullptr)
	{
		deleteNodesRec(*node.left);
	}
	// delete right sub tree
	if (&node.right != nullptr)
	{
		deleteNodesRec(*node.right);
	}
	// delete current node
	delete &node;
}

/// returns true if data is found.
bool AvlTree::find(const std::string& data) const
{
	// tree is empty
	if (_root == nullptr)
	{
		return false;
	}

	// string matches this node
	if (data.compare(_root->data) == 0)
	{
		return true;
	}
	// string compares less than, search left
	else if (data.compare(_root->data) < 0)
	{
		if (_root->left != nullptr)
		{
			return findRec(data, *_root->left);
		}
	}
	// string compares greater than, search right
	else
	{
		if (_root->right != nullptr)
		{
			return findRec(data, *_root->right);
		}
	}

	// found nothing
	return false;
}

// Recursive part of finding string.
bool AvlTree::findRec(const std::string& data, const Node& node) const
{
	// string matches this node
	if (data.compare(node.data) == 0)
	{
		return true;
	}
	// string compares less than, search left
	else if (data.compare(node.data) < 0)
	{
		if (node.left != nullptr)
		{
			return findRec(data, *node.left);
		}
	}
	// string compares greater than, search right
	else
	{
		if (node.right != nullptr)
		{
			return findRec(data, *node.right);
		}
	}

	// found nothing
	return false;
}

/// Inserts a new node with data, unless it already exists.
/// Also balances the tree.
void AvlTree::insert(const std::string data)
{
	// insert as root
	if (_root == nullptr)
	{
		_root = new Node(data, nullptr);
		return;
	}

	// string matches this node
	if (data.compare(_root->data) == 0)
	{
		return;
	}
	// string compares less than, insert left
	else if (data.compare(_root->data) < 0)
	{
		// node exists keep looking left
		if (_root->left != nullptr)
		{
			insertRec(data, *_root->left);
		}
		// no node to left, insert
		else
		{
			_root->left = new Node(data, _root);
			return;
		}
	}
	// string compares greater than, insert right
	else
	{
		// node exists keep looking right
		if (_root->right != nullptr)
		{
			insertRec(data, *_root->right);
		}
		// no node to right, insert
		else
		{
			_root->right = new Node(data, _root);
			return;
		}
	}
}

/// Recursive part of inserting.
void AvlTree::insertRec(const std::string& data, Node& node)
{
	// string matches this node
	if (data.compare(node.data) == 0)
	{
		return;
	}
	// string compares less than, insert left
	else if (data.compare(node.data) < 0)
	{
		// node exists keep looking left
		if (node.left != nullptr)
		{
			insertRec(data, *node.left);
		}
		// no node to left, insert
		else
		{
			node.left = new Node(data, &node);
			balance(*node.left); // balance tree

			return;
		}
	}
	// string compares greater than, insert right
	else
	{
		// node exists keep looking right
		if (node.right != nullptr)
		{
			insertRec(data, *node.right);
		}
		// no node to right, insert
		else
		{
			node.right = new Node(data, &node);
			balance(*node.right); // balance tree

			return;
		}
	}
}

/// Gets the depth of a specified node.
/// Deeper of left and right sub-tree.
int AvlTree::height(const Node* node) const
{
	if (node == nullptr)
	{
		return 0;
	}

	int leftHeight = height(node->left);
	int rightHeight = height(node->right);
	
	if (leftHeight > rightHeight)
	{
		return 1 + leftHeight;
	}
	else
	{
		return 1 + rightHeight;
	}
}

/// Balances the Tree if needed, starting from newly added node.
void AvlTree::balance(Node& node)
{
	// check balance of parent node,
	// if not out of range, check next parent,
	// untill parent == nullptr

	int parentBalance = height(node.parent->left) - height(node.parent->right); // parent balance

	// balance on the left side
	if (parentBalance > 1)
	{
		// right child rotate left
		if (height(node.left) - height(node.right) == -1)
		{
			rotateLeft(node);
			rotateRight(*node.parent->parent); // parent rotate right
		}
		else
		{
			rotateRight(*node.parent); // parent rotate right
		}
	}
	// balance on right side
	else if (parentBalance < -1)
	{
		// left child rotate right
		if (height(node.left) - height(node.right) == 1)
		{
			rotateRight(node);
			rotateLeft(*node.parent->parent); // parent rotate left
		}
		else
		{
			rotateLeft(*node.parent); // parent rotate left
		}
	}
	// continue if there is more to explore, untill end
	else if (node.parent != _root)
	{
		balance(*node.parent);
	}
}

void AvlTree::rotateLeft(Node& node)
{
	// rotate a node with its right child (child rotates left)

	// jump up one parent
	node.right->parent = node.parent; 

	// set the right parent child to the node
	if (node.parent != nullptr)
	{
		if (node.parent->left == &node)
		{
			node.parent->left = node.right;
		}
		else
		{
			node.parent->right = node.right;
		}
	}

	// set node parent to its right child
	node.parent = node.right;

	// set nodes right child to old child nodes left child
	node.right = node.right->left;

	// set node.rights parent to node if not null
	if (node.right != nullptr)
	{
		node.right->parent = &node;
	}

	// swap old childs left to be node
	node.parent->left = &node;

	// make node right equal root
	if (&node == _root)
	{
		_root = node.parent;
	}
}

void AvlTree::rotateRight(Node& node)
{
	// rotate a node with its left child (child rotates right)

	// jump up one parent
	node.left->parent = node.parent;

	// set the right parent child to the node
	if (node.parent != nullptr)
	{
		if (node.parent->left == &node)
		{
			node.parent->left = node.left;
		}
		else
		{
			node.parent->right = node.left;
		}
	}

	// set node parent to its right child
	node.parent = node.left;

	// set nodes left child to old child nodes right child
	node.left = node.left->right;

	// set node.rights parent to node if not null
	if (node.left != nullptr)
	{
		node.left->parent = &node;
	}

	// swap old childs right to be node
	node.parent->right = &node;

	// make node left equal root
	if (&node == _root)
	{
		_root = node.parent;
	}
}