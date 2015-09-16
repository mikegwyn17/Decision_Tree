#include "stirng"
#include "vector"
#ifndef Decision_Tree.h
#define Decision_Tree.h

using namespace std;

class Decision_Tree
{
	private struct node
	{
		int node_number;
		string behavior;
		string response;
		vector<node> next;
		
	};
}