#include<iostream>
#include<iomanip>
#include<ctime>
#include<vector>
#include"Trie.h"
#include<string.h>
#include<unordered_map>
#include<string>
#include<chrono>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

string gen_random(const int len) {
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	string s(len, 'a');

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % 62];
	}

	return s;
}

int main() {
	Trie<string> t;
	unordered_map<string, string> m;
	srand(time(0));
	vector<string> strings;
	for (int i = 0; i < 100000; i++) {
		strings.push_back(gen_random(rand() % 10 + 50));
	}
	cout << "wow" << endl;

	auto t1 = Clock::now();

	for (int i = 0; i < 100000; i++) {
		m[strings[i]] = strings[i];
	}

	auto t2 = Clock::now();
	std::cout << setw(15) << "unordered_map: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds" << std::endl;

	t1 = Clock::now();

	for (int i = 0; i < 100000; i++) {
		t.Add(strings[i].c_str(), strings[i].c_str());
	}

	t2 = Clock::now();
	std::cout << setw(15) << "trie: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds" << std::endl;

	/*for (int i = 0; i < 1000000; i++) {
		if (t.Get(strings[i].c_str()) != strings[i]) {
			cout << i << " " << t.Get(strings[i].c_str()) << " != " << strings[i] << endl;
		}
	}
*/

}