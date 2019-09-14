#include<iostream>

using namespace std;

char Leftmost(char c) {
	c |= (c >> 1);
	c |= (c >> 2);
	c |= (c >> 4);
	return ((c + 1) >> 1);
}

int main() {
	cout << int(Leftmost(0x0F)) << endl;
}