// OracleChallenge.cpp : Defines the entry point for the console application.
//

using namespace std;
#include "stdafx.h"
#include "GTNode.h"
#include "Range.h"

UInt32 const& GTNode::ID()
{
	return this->nodeID;
}

UInt32 GTNode::Serial()
{
	return this->serial;
}

std::string const& GTNode::Value()
{
	return this->nodeValue;
}

void GTNode::SetSerial(UInt32 _serial)
{
	this->serial = _serial;
}

bool GTNode::IsLeaf()
{
	return (this->Children().size() == 0) ? true : false;
}


GTNode* GTNode::Parent()
{
	return this->_parent;
}


GTNode* GTNode::LeftmostChild()
{
	if (this->Children().size() > 0)
	{
		return this->Children()[0];
	}
	else
	{
		return NULL;
	}
}

GTNode* GTNode::LeftChild()
{
	if (this->Children().size() > 0)
	{
		return this->Children()[this->Children().size()-1];
	}
	else
	{
		return NULL;
	}
}


GTNode* GTNode::RightSibling()
{
	GTNode* parent = this->Parent();
	if (NULL != parent)
	{
		vector<GTNode*> vec = parent->Children();
		vector<GTNode*>::iterator it = vec.begin();
		while ((*it) != this)
		{
			++it;
		}
		auto index = std::distance(vec.begin(), it);
		if (vec.size() > (index+1))
			return vec[index + 1];
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

GTNode* GTNode::LeftSibling()
{
	GTNode* parent = this->Parent();
	if (NULL != parent)
	{
		vector<GTNode*> vec = parent->Children();
		vector<GTNode*>::iterator it = vec.begin();
		while ((*it) != this)
		{
			++it;
		}
		auto index = std::distance(vec.begin(), it);
		if (index > 0)
			return vec[index - 1];
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void GTNode::SetParent(GTNode *node)
{
	this->_parent = node;
}

void GTNode::SetValue(std::string& val)
{
	this->nodeValue = val;
}

UInt32 GTNode::GetLevel()
{
	UInt32 level = 0;
	GTNode *temp = this;
	while (temp->Parent() != NULL)
	{
		level++;
		temp = temp->Parent();
	}
	return level;
}

UInt32 GTNode::GetIndex()
{
	UInt32 index = 1;
	GTNode* parent = this->Parent();
	if (parent == NULL)
	{
		return index; // For root node
	}
	else
	{	
		vector<GTNode *> vec = parent->Children();
		
		vector<GTNode *>::iterator it = vec.begin();
		while (it != vec.end())
		{
			if (*it == this)
			{
				break;
			}
			else
			{
				++it;
				++index;
			}
		}
		return index;
	}
}

void GTNode::SetNodeID(const UInt32 id)
{
	this->nodeID = id;
}


void GTNode::SetNodeChildrenRange(const Range range)
{
	this->nodeChildrenRange = range;
}