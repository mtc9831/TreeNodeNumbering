#ifndef _GTNODE_H
#define _GTNODE_H 1

using namespace std;
#include <string>
#include <vector>
#include <array>
#include <iostream>

#include "Range.h"
#include "stdafx.h"

// General tree node ADT
 class GTNode 
{
private:
	UInt32 nodeID;
	UInt32 serial;
	std::string nodeValue;
	Range nodeChildrenRange;
	GTNode *_parent;
	std::vector<GTNode *> _children;
public:
	GTNode() :nodeID(0), nodeValue(""), nodeChildrenRange(0, 0), _parent(NULL){ _children.clear();};
	~GTNode(){ _parent = NULL;  _children.clear(); }

	UInt32 const& ID(); // Return node's Unique ID
	std::string const&  Value(); // Return node’s value
	bool IsLeaf(); // True if node is a leaf
	GTNode* Parent(); // Return parent
	std::vector<GTNode *> Children(){
		return _children;
	}
	GTNode* LeftmostChild();         // Return first child
	GTNode* LeftChild();			 // Return left child
	GTNode* LeftSibling();           // Return left sibling
	GTNode* RightSibling();          // Return right sibling
	UInt32 GetLevel();               // Return level of the node in the tree (starts qith 0)
	UInt32 Serial();                 // Return serial no 
	UInt32 GetIndex();               // Return position of a child node in parent node 

	void SetParent(GTNode *);
	void SetNodeID(const UInt32 id);       // Set node's identifier   
	void SetNodeChildrenRange(const Range range);  // Set node's range
	void SetValue(std::string&);				 // Set node’s value
	void SetSerial(UInt32);

	void InsertChild(GTNode *p){
		_children.push_back(p);
	}

	void RemoveSpecificChild(GTNode*, UInt32 index){ // Remove specific child
		_parent = NULL;
		_children.erase(_children.begin() + index);
	}
	void RemoveAllChildren(GTNode*){                 // Remove All children
		_children.clear(); 
	}	 

	UInt32 GetNoOfChildren() {
		return _children.size();
	}

	Range GetNodeChildrenRange() const {
		return this->nodeChildrenRange;
	}

	bool operator == (GTNode *node){ return (this->ID() == node->ID()) ? true : false; }
	bool operator != (GTNode *node){ return (this->ID() != node->ID()) ? true : false; }
 };


#endif