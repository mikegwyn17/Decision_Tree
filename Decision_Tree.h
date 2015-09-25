#ifndef _DECISION_TREE_H_
#define _DECISION_TREE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <time.h>
using namespace std;

class Decision_Tree
{
	public: 
	struct node
	{
		string value; // stores the string value of the node, can be a response or a behavior
		vector<node*> children;
		void add(node* n) {children.push_back(n);}
		int size() {return children.size();}
	};
	node* root;

	public:

		Decision_Tree();
		
		~Decision_Tree() {};

		// parse method
		void build(const string file_name);

		string toString() const;

    	string toString(node *parent, string indent) const;

		void clear (queue<node*>& to_visit) const;

		string init_search(const char search_type, const string search_value) const;

		string random_traversal (const string search_type, node* current) const;

		string DFS (const string search_value, node* current) const;

		string BFS (queue<node*>& to_visit, const string search_value) const;
	};

	#endif 