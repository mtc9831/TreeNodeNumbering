#ifndef _GENTREE_H
#define _GENTREE_H 1
#include "GTNode.h"
#include <list>
#include <map>

typedef struct
{
	UInt32 serial;
	UInt32 distance;
} NodeInfo;

// General tree ADT
class GenTree
{
private:
	GTNode *_root;
	std::list<GTNode *> listOfNodesAtLevel;
	std::map<UInt32, NodeInfo> mapOfSerial;
public:
	GenTree() :_root(NULL){};
	GenTree(std::string);
	~GenTree(){
		try
		{
			if (_root != NULL)
			{
				this->Clear(_root);
			}
		}
		catch (...){}
	}

	// Send all nodes to free store
	void Clear(GTNode*); 
	
	// Return the root of the tree
	GTNode* Root();      

	// Single insert at a level
	void SingleInsert(GTNode*, GTNode*, std::string item);
	void SingleInsertWithRenumbering(GTNode*, GTNode*, std::string item);

	// Bulk insert at a level
	void BulkInsert(GTNode*, UInt32, std::vector<std::string>);

	//Get all nodes at a level
	void GetAllNodes(GTNode*, UInt32);

	// Rerurn position of a node with respect to a particular level
	void GetSerial(GTNode *, GTNode *);

	// Print using a preorder traversal
	void PrintByPreOrder(GTNode*);

	// Pretty Print 
	void PrettyPrint(GTNode*);
};
#endif