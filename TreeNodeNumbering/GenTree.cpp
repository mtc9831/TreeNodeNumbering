#include "stdafx.h"
#include "GenTree.h"
#include <list>

void GenTree::Clear(GTNode* node)
{		
		if (node == NULL) 
			return;
		else if ((node->Parent() == NULL) && (node->GetNoOfChildren() == 0))
		{
			delete node;
		}
		else
		{
			std::vector<GTNode *> vec = node->Children();
			int i = 0; 
			while(i < vec.size())
			{
				if (vec[i]->IsLeaf())
				{
					node->RemoveSpecificChild(node, i);
					vec.clear();
					vec = node->Children();
				}
				else
				{
					this->Clear(vec[i]);
					++i;
				}
			}
		}
}


GTNode* GenTree::Root()
{
	return this->_root;
}


void GenTree::PrintByPreOrder(GTNode* root)
{
	if (root->IsLeaf()) cout << "Leaf: ";
	else cout << "Internal: ";
	cout << root->Value() << "[" << root->ID() << "]\n";

	// Now process the children of "root"
	
	for (GTNode* temp = root->LeftmostChild();
		temp != NULL; temp = temp->RightSibling())
	{
		PrintByPreOrder(temp);
	}	
}

void GenTree::PrettyPrint(GTNode* node)
{
	if (node->GetLevel() >= 1)
	{
		for (int i = 0; i < node->GetLevel(); i++)
		{
			cout << "    ";
		}
	}
	if (node->IsLeaf())
		cout << " |--";
	else
		cout << " +--";
	cout << node->Value() << "((" <<node->Serial() << "))" "[" << node->ID() << "] " << node->GetNodeChildrenRange().PrintRange() << "\n";

	// Now process the children of "root"

	for (GTNode* temp = node->LeftmostChild();
		temp != NULL; temp = temp->RightSibling())
	{
		PrettyPrint(temp);
	}
}


GenTree::GenTree(std::string t)
:_root(NULL)
{
	GTNode * node = new GTNode();
	if (NULL != node)
	{
		int rootID = Range::GenerateID(0,0,1);  //Level = 0, index = 0, id = 1
		node->SetValue(t);
		node->SetNodeID(rootID);
		node->SetParent(NULL);
		Range range(0, 0);
		range.GenerateRange(1, 0);  //Level = 1, index = 0
		node->SetNodeChildrenRange(range);
		this->_root = node;
	}	
}



void GenTree::SingleInsertWithRenumbering(GTNode* root, GTNode* node, std::string newVal)
{
	UInt32 level = node->GetLevel();
	UInt32 nodeId = Range::GenerateID(level + 1, node->Serial() , node->GetNoOfChildren() + 1);
	if (node->GetNodeChildrenRange().IsInRange(nodeId))
	{
		GTNode *newNode = new GTNode();
		newNode->SetNodeID(nodeId);
		UInt32 serial = this->mapOfSerial[level + 1].serial + this->mapOfSerial[level + 1].distance;
		this->mapOfSerial[level + 1].serial = serial;
		newNode->SetSerial(serial);
		newNode->SetValue(newVal);
		Range definedRange(0, 0);
		UInt32 childSerial = this->mapOfSerial[level + 1].serial;
		this->mapOfSerial[level + 2].serial = childSerial;
		definedRange.GenerateRange(node->GetLevel() + 2, childSerial);
		newNode->SetNodeChildrenRange(definedRange);
		this->mapOfSerial[level + 1].distance = definedRange.GetDistance();
		node->InsertChild(newNode);
		newNode->SetParent(node);
	}
	else
	{
		// Change the range of the parent node
		Range myRange = node->GetNodeChildrenRange();
		myRange.UpdateRange(1);
		node->SetNodeChildrenRange(myRange);
		SingleInsert(root, node, newVal);
	}
}


void GenTree::SingleInsert(GTNode* root,  GTNode* node, std::string newVal)
{
	UInt32 level = node->GetLevel();
	UInt32 nodeId = Range::GenerateID(level +1, node->Serial(), node->GetNoOfChildren() + 1);
	if (node->GetNodeChildrenRange().IsInRange(nodeId))
	{
		GTNode *newNode = new GTNode();
		newNode->SetNodeID(nodeId);
		UInt32 serial = this->mapOfSerial[level+1].serial + this->mapOfSerial[level+1].distance;
		this->mapOfSerial[level + 1].serial = serial;
		newNode->SetSerial(serial);
		newNode->SetValue(newVal);
		Range definedRange(0, 0);
   	    UInt32 childSerial = this->mapOfSerial[level + 1].serial; 

		this->mapOfSerial[level + 2].serial = childSerial;
		
		definedRange.GenerateRange(node->GetLevel() + 2, childSerial);
		newNode->SetNodeChildrenRange(definedRange);
		this->mapOfSerial[level + 1].distance = definedRange.GetDistance();
		node->InsertChild(newNode);
		newNode->SetParent(node);
	}
}

void GenTree::BulkInsert(GTNode* root, UInt32 level, std::vector<std::string> listOfItems)
{
	//Get a list of all nodes in the tree with Level = level-1
	this->listOfNodesAtLevel.clear();
	this->GetAllNodes(root, level - 1);

	// Try to bulk insert without renumbering
	std::vector<std::string>::iterator it1 = listOfItems.begin();
	std::list<GTNode *>::iterator it2 = this->listOfNodesAtLevel.begin();
	while(it1 != listOfItems.end())
	{
		while (it2 != this->listOfNodesAtLevel.end())  //Fill nodes one after another
		{			
			UInt32 proposedId = Range::GenerateID(level, (*it2)->Serial(), (*it2)->GetNoOfChildren() + 1);		
			Range myRange = (*it2)->GetNodeChildrenRange();
			
			if (myRange.IsInRange(proposedId))
			{
				this->SingleInsert(root, *it2, *it1);
				listOfItems.erase(it1);
				it1 = listOfItems.begin();
				break;
			}
			++it2;
		}
		if (it2 == this->listOfNodesAtLevel.end()) break;
	}

	//Try to insert after renumbering for remaining nodes
	UInt32 remItemsCount = listOfItems.size();

	if (remItemsCount > 0)
	{
		std::list<GTNode *>::iterator it3 = listOfNodesAtLevel.end();
		it3--;
		Range myRange = (*it3)->GetNodeChildrenRange();
		myRange.UpdateRange(remItemsCount);
		(*it3)->SetNodeChildrenRange(myRange);

		for (std::vector<std::string>::iterator it4 = listOfItems.begin();
			it4 != listOfItems.end(); ++it4)
		{
			SingleInsert(root, *it3, *it4);
		}
	}
}


void GenTree::GetAllNodes(GTNode* node, UInt32 level)
{
	if (node->GetLevel() == level)
	{
		listOfNodesAtLevel.push_back(node);
	}	
	else {
		// Process the children of "node"

		for (GTNode* temp = node->LeftmostChild();
			temp != NULL; temp = temp->RightSibling())
		{
			if (temp->GetLevel() == level)
			{
				listOfNodesAtLevel.push_back(temp);    // No recursive call to children from the current node, level already found
			}
			else
			{
				GetAllNodes(temp, level);
			}
		}
	}
}


