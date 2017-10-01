#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	bool fileNameFound = false;
	bool m_flag = false;
	bool c_flag = false;
	bool b_flag = false;

	for (int i = 1; i < argc; i++){
		string argument = argv[i];
		int flagcount = 0;
		if (argument[0] == '-' && i <= 3 && !fileNameFound){
			switch (argument[1]){
				case 'm': 
					m_flag = true;
					flagcount++;
					//cout << "-m";
					break;
				case 'c':
					c_flag = true;
					flagcount++;
					//cout << "-c";
					break;
				case 'b':
					b_flag = true;
					flagcount++;
					//cout << "-b";
					break;
				default:
					cout << argument << " UNRECOGNIZED FLAG.\n";
					exit(EXIT_FAILURE);
			}
		}else if (flagcount == argc--){ //Only flags were passed; no files.
			cout << "NO FILES\n";
		}

		ifstream infile;
		infile.open(argument.c_str());
		
		map<string, int> lo_map; //Line Occurance Map (Line -> Occurances)
		map<int, vector<string> > lo_map_bycount;

		map<string, int> wo_map; //Word Occurance Map (Word -> Occurances)
		map<int, vector<string> > wo_map_bycount;

		map<string, int> lc_map; //Line Length Map (Line Contents -> Char Count)
		map<int, vector<string> > lc_map_bycount;

		map<string, int> wc_map; //Word Length Map (Word -> Char Count)
		map<int, vector<string> > wc_map_bycount;

		map<string ,int>::iterator it;
		map<int, vector<string> >::iterator sit;

		if (infile.is_open()){
			//To-Do: Create a hashmap for word occurance.
			cout << argument << ":\n";
			vector<string> longest_words;

			while (!infile.eof()){
				string line;
				getline(infile, line);
				cout << "\nLine: "<< line << "\n";

				lc_map[line] = line.length();
				lo_map[line]++;

				for (it=lc_map.begin(); it != lc_map.end(); it++){
					lc_map_bycount[it->second].push_back(it->first);
				}

				for (it=lo_map.begin(); it != lo_map.end(); it++){
				    lo_map_bycount[it->second].push_back(it->first);
				}

				if (lc_map_bycount.rbegin() != lc_map_bycount.rend()){
					int line_longest = lc_map_bycount.rbegin()->first;
				} else {
					int line_longest = 0;
				} 

				istringstream linestream(line);
				string word;

				while (linestream >> word){
					cout << word << "\n";
					wc_map[word] = word.length();
					wo_map[word]++;
				
				}
				
				for (it=wc_map.begin(); it != wc_map.end(); it++){
					wc_map_bycount[it->second].push_back(it->first);
				}

				for (it=wo_map.begin(); it != wo_map.end(); it++){
					wo_map_bycount[it->second].push_back(it->first);
				}


				if (wc_map_bycount.rbegin() != wc_map_bycount.rend()){
					longest_words = wc_map_bycount.rbegin()->second;
				}
               
			}

		}else{
			cout << argument << " FILE NOT FOUND.\n";
			continue;
		}

		if (!m_flag && !b_flag && !c_flag){
			cout << "\n";
			for(auto i: longest_words){
				cout << i << ", ";
			}
		}

	}

	return 0;
}
