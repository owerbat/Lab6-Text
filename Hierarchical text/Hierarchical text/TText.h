#pragma once
#include <iostream>
#include <stack>
#include <fstream>

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

	TLink *ReadRec(ifstream& file);
	void Read(char *fn);

	void PrintText(TLink *tmp);
	void Print();

	void SaveText(TLink *tmp, ofstream& f);
	void Save(char *name);

	TLink *CopyRec(TLink *first);
	TLink *Copy();

	void Reset();
	bool IsEnd();
	void GoNext();
};