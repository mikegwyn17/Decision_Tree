#include "Decision_Tree.h"
#include <stdlib.h>

using namespace std;

Decision_Tree::Decision_Tree()
{
	root = new node();
}

// method used to find everyting between the two "" found in the given string
string find_value (string& line)
{
	string first = line.substr(line.find_first_of('"')+1);
	int location_first = line.find_first_of('"');
	int location_second = first.find_first_of('"');
	string value = line.substr(location_first+1, location_second);
	line = first.substr(location_second+1);
	if (value.length() == 0)
		value = "empty string";
	return value;
}
/* method used to parse the xml line by line into behavior and response
calls the find value method to get the values conatined in between the 
"" in the string and store them as either the response of behavior. counter varilable
is used to keep track of the current parent and past parent of nodes, to build the tree structure.
*/
void Decision_Tree::build (const string file_name)
{
	stack<node*> parent;
	node* current = new node();
// int main (void)
	string line;
	string node_text;
	string behavior;
	string response;
	string value;

	ifstream file (file_name.c_str());
	if (file.is_open())
	{
		while ( getline (file, line))
		{
			// case root node
			if (line.compare("<root>") == 0)
			{
				// create empty decision_tree
				//cout << "root node" << '\n';
				current = root;
				current->value = "root";
				parent.push(current);
			}
			// end of a node
			else if (line.compare("</node>") == 0)
			{
				parent.pop();
				continue;
			}
			if (line.length() == 0)
				continue;

			node_text = line.substr(1,4);

			// if the line is a node
			if (node_text.compare("node") == 0)
			{
				behavior = find_value(line);
				response = find_value(line);
				if(behavior == "empty string")
					value = response;
				else 
					value = behavior;
				current->value = value;

				// code to create new node here

				if (line.compare(">") == 0)
				{
					//cout << "node " << current->value << " parent: " << parent.top()->value << '\n';
					parent.top()->add(current);
					parent.push(current);
				}
				else 
				{
					//cout << "node " << current->value << " parent: " << parent.top()->value << '\n';
					parent.top()->add(current);
				}		
			}
			current = new node();
		}
		file.close();
		cout << "Behavior Tree Loaded" << '\n';
	}
	else cout << "unable to open file";
}

string Decision_Tree::toString() const
{
    string line = "------------------------------\n";
    return line +
           Decision_Tree::toString(root, string()) + line;
    
}

string Decision_Tree::toString(node *current, string line) const
{
    string output = line + "Behavior: " + current->value + "\n";
    line += "  ";
	for(int i = 0; i < current->size(); i++) 
    {
		if(!current->children.at(i)->children.empty()) 
			output += Decision_Tree::toString(current->children.at(i), line);
        else 
			output += line + "Response: " + current->children.at(i)->value + "\n";
    }
    return output;
}

// method used to initalize both the depth first and breadth first searches
string Decision_Tree::init_search (const char search_type, const string search_value) const
{
	srand (time(NULL));
	if (search_type == 'b')
	{
		// do breadth first search
		queue<node*> to_visit;
		to_visit.push(root);
		return (BFS(to_visit, search_value)); 
	}
	else
	{
		// do depth first search
		return (DFS(search_value, root));
	}

}

// method used to find a random node after the search has taken place
string Decision_Tree::random_traversal (const string search_value, node* current) const
{
	if (current->size() == 0)
		return current->value;
	else
	{
		int random = (rand() % current->size());
		return random_traversal(search_value, current->children.at(random));
	}
}

// recursive breadth first search
string Decision_Tree::BFS (queue<node*>& to_visit, const string search_value) const
{
	if (to_visit.empty())
		return "value not found in the tree";
	else
	{
		node* current_node = to_visit.front();
		string current = current_node->value;
		if (current == search_value && current_node->children.empty())
			return current;
		else if (current == search_value)
		{
			return random_traversal(search_value, current_node);
		}
		else
		{
			for (int i = 0; i < current_node->size(); i++)
				to_visit.push(current_node->children.at(i));
			to_visit.pop();
			return BFS(to_visit, search_value);
		}
	}
}

// iterative depth first search
string Decision_Tree::DFS (const string search_value, node* current) const
{
	stack<node*> to_visit;
	vector<node*> visited;
	to_visit.push(current);
	while (!to_visit.empty())
	{
		current = to_visit.top();
		if (current->value == search_value && current->size() == 0)
			return current->value;
		else if (current->value == search_value)
			return random_traversal(search_value, current);
		else
		{
			to_visit.pop();
			for (int i = 0; i < visited.size(); i++)
			{
				if (!(current == visited.at(i)))
					visited.push_back(current);
			}	
			for (int i = 0; i < current->size(); i++)
				to_visit.push(current->children.at(i));	
		}
	}
	return "value not conatined in tree";
}
