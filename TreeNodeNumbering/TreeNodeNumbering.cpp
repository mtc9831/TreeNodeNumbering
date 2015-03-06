#include "stdafx.h"
#include "GenTree.h"
#include "GTNode.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GenTree* tree = new GenTree("Root");
	tree->SingleInsertWithRenumbering(tree->Root(), tree->Root(), "Hello");
	tree->SingleInsertWithRenumbering(tree->Root(), tree->Root(), "World");
	tree->SingleInsertWithRenumbering(tree->Root(), tree->Root(), "To");
	tree->SingleInsertWithRenumbering(tree->Root(), tree->Root(), "All");
	tree->SingleInsertWithRenumbering(tree->Root(), tree->Root(), "Of");
	tree->SingleInsertWithRenumbering(tree->Root(), tree->Root(), "You!!");
	//tree->PrettyPrint(tree->Root());

	std::vector<std::string> v;
	v.push_back("It");
	v.push_back("is");
	v.push_back("truely");
	v.push_back("a");
	v.push_back("beautiful");
	v.push_back("and");
	v.push_back("kind");
	v.push_back("world");
	tree->BulkInsert(tree->Root(), 2, v);
	//tree->PrettyPrint(tree->Root());
	
	v.clear();
	v.push_back("I");
	v.push_back("am");
	v.push_back("here");
	v.push_back("to");
	v.push_back("enjoy");
	v.push_back("my");
	v.push_back("innings");
	v.push_back("and");
	v.push_back("the");
	v.push_back("game");
	tree->BulkInsert(tree->Root(), 3, v);
	//tree->PrettyPrint(tree->Root());
	
	cout <<"\n\n\n";
	v.clear();
	v.push_back("No");
	v.push_back("one");
	v.push_back("can");
	v.push_back("get");
	v.push_back("me");
	v.push_back("out");
	v.push_back("unless");
	v.push_back("I");
	v.push_back("want");
	v.push_back("to");
	v.push_back("do");
	v.push_back("so");
	tree->BulkInsert(tree->Root(), 3, v);
	
	v.clear();
	v.push_back("I");
	v.push_back("have");
	v.push_back("it");
	v.push_back("enough");
	v.push_back("now");
	v.push_back("I");
	v.push_back("can");
	v.push_back("say");
	v.push_back("goodbye");
	v.push_back("world");
	tree->BulkInsert(tree->Root(), 4, v);

	v.clear();
	v.push_back("But");
	v.push_back("I");
	v.push_back("would");
	v.push_back("like");
	v.push_back("to");
	v.push_back("come");
	v.push_back("back");
	v.push_back("again");
	v.push_back("to");
	v.push_back("this");
	v.push_back("world");
	tree->BulkInsert(tree->Root(), 4, v);
	//tree->PrettyPrint(tree->Root());

	v.clear();
	v.push_back("I");
	v.push_back("am");
	v.push_back("an");
	v.push_back("allien");
	v.push_back("and");
	v.push_back("I");
	v.push_back("am");
	v.push_back("here");
	tree->BulkInsert(tree->Root(), 3, v);

	v.clear();
	v.push_back("Here");
	v.push_back("it");
	v.push_back("is");
	v.push_back("another");
	v.push_back("marvellous");
	v.push_back("world");
	v.push_back("of");
	v.push_back("alliens");
	tree->BulkInsert(tree->Root(), 5, v);
	tree->PrettyPrint(tree->Root());

	tree->Clear(tree->Root());
	return 0;
}

