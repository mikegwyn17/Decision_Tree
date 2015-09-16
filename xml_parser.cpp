#include <iostream>
#include <fstream>

using namespace std;

// method used to find everyting between the two "" found in the given string
string find_value (string& line)
{
	string first = line.substr(line.find_first_of('"')+1);
	int location_first = line.find_first_of('"');
	int location_second = first.find_first_of('"');
	string value = line.substr(location_first+1, location_second);
	line = first.substr(location_second+1);
	if (value.length() == 0)
	{
		value = "empty string";
	}
	return value;
}

int main ()
{
	string line;
	string node;
	string behavior;
	string response;
	string temp;
	int parent = 0;
	int past_parent = 0;
	int node_number = 0;
	string value;

	ifstream file ("example.xml");
	if (file.is_open())
	{
		while ( getline (file, line))
		{
			if (line.compare("<root>") == 0)
			{
				// create empty decision_tree
				cout << "root node" << '\n';
				continue;
			}
			else if (line.compare("</node>") == 0)
			{
				parent = past_parent;
				continue;
			}
			node = line.substr(1,4);

			if (node.compare("node") == 0)
			{
				node_number++;
				
				// add code to add a new node here
				behavior = find_value(line);
				response = find_value(line);

				cout << "node number: " << node_number << " parent: " 
					<< parent << " previous parent " << past_parent << '\n';

				if (line.compare(">") == 0)
				{
					past_parent = parent;
					parent = node_number;
				}
			}
		}
		file.close();
	}
	else cout << "unable to open file";

	return 0;
}