#include "TText.h"

int main() {
	char fileName[] = "C:\\Users\\User\Documents\GitHub projects\Lab6-Text\Test.txt";

	TText text;

	text.Read(fileName);

	cout << "\nOK\n";

	return 0;
}