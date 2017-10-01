#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
	bool fileNameFound = false;
	bool m_flag = false;
	bool c_flag = false;
	bool b_flag = false;
	for (int i = 1; i < argc; i++){
		string argument = argv[i];
		if (argument[0] == '-' && i <= 3 && !fileNameFound){
			switch (argument[1]){
				case 'm': 
					m_flag = true;
					//cout << "-m";
					break;
				case 'c':
					c_flag = true;
					//cout << "-c";
					break;
				case 'b':
					b_flag = true;
					//cout << "-b";
					break;
				default:
					cout << argument << " UNRECOGNIZED FLAG.\n";
					exit(EXIT_FAILURE);
			}
		}

		ifstream infile;
		infile.open(argument);

		if (infile.is_open()){
			//To-Do: Create a hashmap for word occurance.
			cout << argument << ":";


		}else{
			cout << argument << " FILE NOT FOUND.\n";
			continue;
		}

	}

	return 0;
}
