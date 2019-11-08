#include "UIHelper.h"

int UIHelper::prompt(string message)
{
	cout << message;
	return 0;
}

string UIHelper::getInput()
{
	string input;
	cin >> input;
	return input;
}

void UIHelper::exit()
{
	system("Pause");
	_exit(0);
}
