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



void TText::GoNextLink() {
	if (pCurr->pNext != NULL) {
		st.push(pCurr);
		pCurr = pCurr->pNext;
	}
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