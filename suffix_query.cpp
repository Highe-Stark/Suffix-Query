#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <time.h>

using namespace std;

string get(const string& s, size_t beg, size_t end);

int main()
{
	ifstream infile("dictionary.txt");
	if (!infile && !infile.is_open()) {
		cerr << "Error open file" << endl;
		return -1;
	}
	set<string> lexicon;
	string word;
	infile >> word;

	//readin the word from the file
	while (!infile.eof() && word != "") {
		lexicon.insert(word);
		infile >> word;
	}

	//number of letters of the suffix
	size_t num(0);
	cin >> num;
	//suffix_map sotres suffix and words with the suffix
	map<string, vector<string>> suffix_map;
	for (set<string>::iterator it = lexicon.begin(); it != lexicon.end(); ++it) {
		//skip those words
		//whose length is shorter than the length of suffix
		if (it->size() < num) continue;
		//get the suffix of the word
		string suf = get(*it,it->size() - num, it->size());
		//add the word to the map
		suffix_map[suf].push_back(*it);
	}
	
	//sotres the string
	//in order of the 
	//number of words which has the suffix
	list<string> most_suffix;
	vector<string>::size_type vol(0);
	//将后缀按照所拥有单词数由高到低放入most_suffix
	for (map<string, vector<string>>::iterator it = suffix_map.begin(); it != suffix_map.end(); ++it) {
		//get the words current suffix has
		vol = it->second.size();
		//if most_suffix is empty, push_back
		if (most_suffix.size() == 0) most_suffix.push_back(it->first);
		//if the words this suffix has is smaller than each one in the most_suffix
		//put at the bottom
		else if (suffix_map[*most_suffix.rbegin()].size() > vol) most_suffix.push_back(it->first);
		else {
			//otherwise, find the place in the row, then insert
			list<string>::iterator i = most_suffix.begin();
			while (suffix_map[*i].size() > vol) i++;
			most_suffix.insert(i, it->first);
		}
	}
	
	int time(0);
	for (list<string>::iterator i = most_suffix.begin(); ;++i) {
		if (time++ == 10) break;
		//output the suffix and the number of words it has
		cout << *i << "\t" << suffix_map[*i].size() << endl;
		vector<string>& vec = suffix_map[*i];
		//output the words in the descend order
		for (vector<string>::reverse_iterator ix = vec.rbegin(); ix !=vec.rend(); ++ix) {
			cout << *ix << "\t";
		}
		cout << "\n-------------------------------------------------------" << endl;
	}
	return 0;
}

string get(const string& s, size_t beg, size_t end)
{
	string sub;
	for (; beg != end; ++beg) {
		sub += s[beg];
	}
	return sub;
}