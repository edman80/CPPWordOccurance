#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){

	bool fileNameFound = false;
	//bool m_flag = false;
	bool c_flag = false;
	//bool b_flag = false;

	for (int i=1; i<=argc; i++){
		
		string argument = argv[i];
		int flagcount = 0;

		if(argument[0] == '-' && i <= 3 && !fileNameFound){
			
			switch(argument[1]){
				
				case 'm':
					//m_flag = true;
					flagcount++;
					break;
				case 'c':
					c_flag = true;
				//	cout << "c used\n";
					flagcount++;
					continue;
				case 'b':
					//b_flag = true;
					flagcount++;
					break;
				default:
					cout << argument << " UNRECOGNIZED FLAG\n";
					exit(EXIT_FAILURE);
			}
		
		}
		
		ifstream infile;
		
		infile.open(argument.c_str());

		if (infile.is_open()){
			
			map<string, int> wo;
			map<string, int> lo;

			map<int, vector<string> > wc_bycount;
			map<int, vector<string> > lc_bycount;
			
			vector<string> longest_words;
			vector<string> longest_lines;

			cout << argument << ":\n";
			
			while(!infile.eof()){
				string line;
				getline(infile, line);
			
				lc_bycount[line.length()].push_back(line);
				lo[line]++;

				istringstream linestream(line);
				string word;

				while(linestream >> word){
					wc_bycount[word.length()].push_back(word);
					wo[word]++;
				}
			}
			
			
			longest_words = wc_bycount.rbegin()->second;
			longest_lines = lc_bycount.rbegin()->second;

			sort(longest_words.begin(),longest_words.end());
			longest_words.erase(unique(longest_words.begin(),longest_words.end()), longest_words.end());
			int c = 0;
			for(auto i: longest_words){
				if (c != 0) cout << ", ";
				cout << i;
				if( c_flag) cout << "(" << wo[i] << ")";
				c++;
			}
			cout << "\n";
			for(auto i: longest_lines){
				cout << i.length();
				if( c_flag) cout << "(" << lo[i] << ")"; 
			}
			cout << "\n";

			

		}else{
			cout << argument << " FILE NOT FOUND\n";
		}
	}


	return 0;
}
