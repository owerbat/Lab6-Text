#pragma once
#include <iostream>
#include <stack>

using namespace std;

class TLink {
public:
	char str[80];
	TLink *pNext, *pDown;

	TLink(char *_str = NULL, TLink *pN = NULL, TLink *pD = NULL) {
		pNext = pN;
		pDown = pD;
		if (_str == NULL)
			str[0] = '\0';
		else
			strncpy_s(str, _str, 80);
	}

	~TLink() {}
};



class TText {
	TLink *pFirst, *pCurr;
	stack<TLink *> st;
	int level;
public:
	TText() {}

};