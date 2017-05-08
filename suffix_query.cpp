#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

string get(const string& s, size_t beg, size_t end);

int main()
{
	ifstream infile("dictionary.txt");
	if (!infile && !infile.is_open()) cerr << "Error open file" << endl;
	set<string> lexicon;
	string word;
	infile >> word;
	while (!infile.eof() && word != "") {
		lexicon.insert(word);
		infile >> word;
	}
	//number of letters of the suffix
	size_t num(0);
	cin >> num;
	map<string, vector<string>> suffix_map;
	for (set<string>::iterator it = lexicon.begin(); it != lexicon.end(); ++it) {
		if (it->size() < num) continue;
		string suf = get(*it,it->size() - num, it->size());
		suffix_map[suf].push_back(suf);
	}
	vector<string> most_suffix;
	//set<string> suffix;
	vector<string>::size_type vol(0);
	for (map<string, vector<string>>::iterator it = suffix_map.begin(); it != suffix_map.end(); ++it) {
		vol = it->second.size();
		if (most_suffix.size() == 0) most_suffix.push_back(it->first);
		else if (suffix_map[most_suffix[most_suffix.size() - 1]].size() > vol) most_suffix.push_back(it->first);
		else {
			vector<string>::iterator i = most_suffix.begin();
			while (suffix_map[*i].size() > vol) i++;
			most_suffix.insert(i, it->first);
		}
	}
	for (int i = 0; i != 10; ++i) {
		cout << most_suffix[i] << endl;
		vector<string>& vec = suffix_map[most_suffix[i]];
		for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
			cout << *it << "\t";
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