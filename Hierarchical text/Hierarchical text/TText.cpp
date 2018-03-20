#include "TText.h"

TLink::TLink(char *_str, TLink *pN, TLink *pD) {
	pNext = pN;
	pDown = pD;
	if (_str == NULL)
		str[0] = '\0';
	else
		strncpy_s(str, _str, 80);
}



//----------------------------------------------------------------------------------------------------



TText::TText(TLink *first) {
	pCurr = pFirst = first;
}

// необходимо присвоить каждое звено в результат
/*TText TText::operator=(TText &t) {
	TText res;

	res.pFirst = t.pFirst;
	res.pCurr = t.pCurr;
	res.st = t.st;

	return res;
}*/


void TText::GoNextLink() {
	if (pCurr->pNext != NULL) {
		st.push(pCurr);
		pCurr = pCurr->pNext;
	}
}

TLink TText::GetCurr() {
	return *pCurr;
}

void TText::GoDownLink() {
	if (pCurr->pDown != NULL) {
		st.push(pCurr);
		pCurr = pCurr->pDown;
	}
}

void TText::GoPrevLink() {
	if (!st.empty()) {
		pCurr = st.top();
		st.pop();
	}
}



void TText::InsNextLine(char *s) {
	TLink *NewLink = new TLink(s, pCurr->pNext, NULL);
	pCurr->pNext = NewLink;
}

void TText::InsNextSection(char *s) {
	TLink *NewLink = new TLink(s, NULL, pCurr->pNext);
	pCurr->pNext = NewLink;
}

void TText::InsDownLine(char *s) {
	TLink *NewLink = new TLink(s, pCurr->pDown, NULL);
	pCurr->pDown = NewLink;
}

void TText::InsDownSection(char *s) {
	TLink *NewLink = new TLink(s, NULL, pCurr->pDown);
	pCurr->pDown = NewLink;
}



void TText::DelNext() {
	if (pCurr->pNext != NULL) {
		TLink *tmp = pCurr->pNext;
		pCurr->pNext = tmp->pNext;
		delete tmp;
	}
}

void TText::DelDown() {
	if (pCurr->pDown != NULL) {
		TLink *tmp = pCurr->pDown;
		pCurr->pDown = tmp->pNext;
		delete tmp;
	}
}

char *TText::GetLine() {
	TLink *tmp = pCurr;
	char *res = tmp->str;
	return res;
}

void TText::SetLine(char *s) {
	strncpy_s(pCurr->str, s, 80);
}

TLink *TText::ReadRec(ifstream& file) {
	char buf[80];
	TLink *tmp, *first = NULL;

	while (!file.eof()) {
		file.getline(buf, 80, '\n');

		if (buf[0] == '}')
			break;
		else if (buf[0] == '{')
			tmp->pDown = ReadRec(file);
		else if (first == NULL) {
			first = new TLink(buf);
			tmp = first;
		}
		else {
			tmp->pNext = new TLink(buf);
			tmp = tmp->pNext;
		}
	}

	return first;
}

void TText::Read(char *fn) {
	ifstream ifs(fn);
	if(fn)
		pCurr = pFirst = ReadRec(ifs);
}

void TText::PrintText(TLink *tmp) {
	if (tmp != NULL) {
		if (tmp == pCurr) {
			SetColor(ConsoleColor::LightCyan, ConsoleColor::Black);
			cout << "->";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		}
		else {
			cout << "  ";
		}

		for (int i = 0; i < level; i++)
			cout << "   ";

		cout << tmp->str << endl;
		level++;
		PrintText(tmp->pDown);
		level--;
		PrintText(tmp->pNext);
	}
}

void TText::Print() {
	level = 0;
	PrintText(pFirst);
}

void TText::SaveText(TLink *tmp, ofstream& f) {
	f << tmp->str << endl;

	if (tmp->pDown != NULL) {
		f << "{\n";
		SaveText(tmp->pDown, f);
		f << "}\n";
	}

	if (tmp->pNext != NULL)
		SaveText(tmp->pNext, f);
}

void TText::Save(char *name) {
	ofstream ofs(name);
	SaveText(pFirst, ofs);
}

TLink *TText::CopyRec(TLink *first) {
	TLink *pN = NULL, *pD = NULL;

	if (first->pDown != NULL)
		pD = CopyRec(first->pDown);
	if (first->pNext != NULL)
		pN = CopyRec(first->pNext);

	TLink *res = new TLink(first->str, pN, pD);

	return res;
}

TLink *TText::Copy() {
	return CopyRec(pFirst);
}

void TText::Reset() {
	pCurr = pFirst;

	while (!st.empty())
		st.pop();
	
	st.push(pCurr);

	if (pCurr->pNext != NULL)
		st.push(pCurr->pNext);
	if (pCurr->pDown != NULL)
		st.push(pCurr->pDown);
}

bool TText::IsEnd() {
	return st.empty();
}

void TText::GoNext() {
	pCurr = st.top();
	st.pop();

	if (pCurr != pFirst) {
		if (pCurr->pNext != NULL)
			st.push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			st.push(pCurr->pDown);
	}
}