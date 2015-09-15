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
	return value;
}

int main ()
{
  // ofstream myfile ("example.txt");
  // if (myfile.is_open())
  // {
  //   myfile << "This is a line.\n";
  //   myfile << "This is another line.\n";
  //   myfile.close();
  // }
  // else cout << "Unable to open file";
	string line;
	string node;
	string behavior;
	string response;
	string temp;
	int parent = 0;
	int past_parent = 0;
	int node_number = 0;
	string value;
	int child_count = 0;


	ifstream file ("example.txt");
	if (file.is_open())
	{
		while ( getline (file, line))
		{
			if (line.compare("<root>") == 0)
			{
				cout << "root node" << '\n';
				parent = 0;
				continue;
			}
			else if (line.compare("</node>") == 0)
			{
				parent = node_number - child_count;
			}
			node_number++;
			node = line.substr(1,4);

			if (node.compare("node") == 0)
			{
				
				// add code to add a new node here
				behavior = find_value(line);
				// if (behavior.length() == 0)
				// {
				// 	cout << "empty string" << '\n';
				// }
				// else
				// {
				// 	cout << behavior << '\n';
				// }
				response = find_value(line);
				// if (response.length() == 0)
				// {
				// 	cout << "empty string" << '\n';
				// }
				// else
				// {
				// 	cout << response << '\n';
				// }
				if (behavior.length() == 0)
				{
					value = response;

				}
				else
				{
					value = behavior;
				}
				cout << value << " parent " << parent << '\n';
				if (line.compare(">") == 0)
				{
					parent = node_number;
					child_count++;
				}
			}
			
		}
		file.close();
	}
	else cout << "unable to open file";

	return 0;
}