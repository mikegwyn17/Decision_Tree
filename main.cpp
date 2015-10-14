#include "Decision_Tree.h"
#inlcude <limits>

using namespace std;

int main (void)
{
	Decision_Tree* tree = new Decision_Tree();
	cout << "enter a xml file name: ";
	string file;  
	getline(cin, file);	
	tree->build(file);
	cout << tree->toString() << "\n";
	bool cont = true;
	string event;
	char type;
	string search_type;
	cout << "Event ('quit' to exit) : ";
	getline(cin, event);
	if (event == "quit")
		cont = false;
	while (cont)
	{
		int random = rand() % 2;
		(random == 0) ? (type = 'b') : (type = 'd');
		if (type == 'd')
			search_type = "Depth First Search";
		else
			search_type = "Breadth First Search";
		cout << "Response = "<< tree->init_search(type,event) << ", found using: " << search_type << "\n";
		cout << "Event ('quit' to exit) : ";
		getline(cin, event);
		if (event == "quit")
			cont = false;
	}
	cout << "Press ENTER to continue...";
  	cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

  return 0;

	return 0;
}
