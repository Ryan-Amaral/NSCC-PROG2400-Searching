//  File: Source.cpp
//	Purpose: Main driver file.
//  Project: SpellChecker
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#include "AvlTree.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>

using namespace std;

void recTraverseNode(std::ostream& output, const Node& node, const int lvlToPrint, const int curLvlChg)
{
	if (&node == nullptr)
	{
		return;
	}

	if (curLvlChg == 1)
	{
		cout << "lvl:" << lvlToPrint << " ";
		for (int i = 0; i < lvlToPrint; i++)
		{
			cout << "---";
		}
		output << node.data << " (p: " <<
			((node.parent != nullptr) ? node.parent->data : "nullptr") << ", L: " <<
			((node.left != nullptr) ? node.left->data : "nullptr") << ", R: " <<
			((node.right != nullptr) ? node.right->data : "nullptr") << ")" << endl;
	}
	else if (curLvlChg > 1)
	{
		recTraverseNode(output, *node.left, lvlToPrint, curLvlChg - 1);
		recTraverseNode(output, *node.right, lvlToPrint, curLvlChg - 1);
	}

}
// help from http://www.geeksforgeeks.org/level-order-tree-traversal/

ostream& operator << (ostream& output, const AvlTree& tree)
{
	int height = tree.height(tree._root);
	for (int i = 1; i < height + 1; ++i)
	{
		recTraverseNode(output, *tree._root, i, i);
	}

	return output;
}

int main()
{
	AvlTree* tree = new AvlTree();

	// add dictionary words to tree
	ifstream* inStream = new ifstream();
	inStream->open("dictionary.txt", fstream::in);

	string curWord;

	// put each word into the dictionary stack
	while (getline(*inStream, curWord))
	{
		tree->insert(curWord);
	}

	// display tree
	cout << *tree;

	string docStringStr;
	char* stringPart;

	// compare each word in document to tree
	inStream->close();
	inStream->clear();
	inStream->open("mispelled.txt", fstream::in);
	getline(*inStream, docStringStr);

	char* docString = const_cast<char*>(docStringStr.c_str());
	char* nextToken = NULL;

	stringPart = strtok_s(docString, " ,.()#&\"123", &nextToken);

	cout << endl << endl << "Mispelled words: ";

	int counter = 0;

	while (stringPart != NULL)
	{
		// convert to lower case
		for (unsigned int i = 0; i < strlen(stringPart); ++i)
		{
			stringPart[i] = tolower(stringPart[i]);
		}

		if (!tree->find(stringPart))
		{
			cout << stringPart << ", ";
		}

		stringPart = strtok_s(NULL, " ,.()#&\"123", &nextToken);
	}
	

	_getch();
}