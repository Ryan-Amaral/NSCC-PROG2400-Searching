//  File: SpellChecker.h
//	Purpose: Header file for SpellChecker.cpp
//  Project: SpellChecker
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#ifndef _SPELL_CHECKER_H
#define _SPELL_CHECKER_H

#include "AvlTree.h"
#include <string>

class SpellChecker
{
private:
	AvlTree* _dictionaryTree; // contains all correctly spelled words
public:
	SpellChecker();
	~SpellChecker();
	void addWord(std::string const& word);
	bool spellCheck(std::string const& word) const;
};

#endif