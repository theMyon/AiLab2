#include <iostream>

#include "CrocGame.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::wstring groupName = L"Test";
	bool isOk = false;

	std::wcout << "Staring game using group name " << groupName.c_str() << std::endl;
	CrocSession* crocSession = new CrocSession(groupName, isOk);

	crocSession->StartGame();

	std::cin.get();

	delete crocSession;
	return 0;
}