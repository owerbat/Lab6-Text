#pragma once
#include <iostream>
#include <stack>

using namespace std;

class TLink {
public:
	char str[80];
	TLink *pNext, *pDown;

	TLink(char *_str = NULL, TLink *pN = NULL, TLink *pD = NULL);
	~TLink() {}
};



class TText {
	TLink *pFirst, *pCurr;
	stack<TLink *> st;
	int level;
public:
	TText() {}

	void GoNextLink();
	void GoDownLink();
	void GoPrevLink();

	void InsNextLine(char *s);
	void InsNextSection(char *s);
	void InsDownLine(char *s);
	void InsDownSection(char *s);

	void DelNext();
	void DelDown();

	char *GetLine();
	void SetLine(char *s);
};