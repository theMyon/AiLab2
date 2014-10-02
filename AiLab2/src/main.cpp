#include <iostream>

#include "CrocGame.h"

#define NUM_GAMES 100

struct GameState
{
	int score;
	int playerLocation;
	int backpacker1Activity;
	int backpacker2Activity;
	double calciumReading;
	double salineReading;
	double alkalinityReading;

	GameState() :
		score(0),
		playerLocation(0),
		backpacker1Activity(0),
		backpacker2Activity(0),
		calciumReading(0.0),
		salineReading(0.0),
		alkalinityReading(0.0)
	{}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::wstring groupName = L"Test";
	bool isOk = false;

	unsigned int numGamesFinished = 0;

	std::wcout << "Staring game using group name " << groupName.c_str() << std::endl;
	CrocSession* crocSession = new CrocSession(groupName, isOk);

	// Game paths
	std::vector<std::vector<int>> paths;
	paths = crocSession->getPaths(); // Paths are constant from game to game

	// Play a certain amount of games before posting results
	while(numGamesFinished < NUM_GAMES)
	{
		crocSession->StartGame();

		bool gameIsRunning = true;

		// Game distributions
		// Distributions differ from game to game
		std::vector<std::pair<double,double>> calciumDist;
		std::vector<std::pair<double,double>> salinityDist;
		std::vector<std::pair<double,double>> alkalinityDist;

		crocSession->GetGameDistributions(
			calciumDist,
			salinityDist,
			alkalinityDist);

		// Game state
		GameState curGameState;

		//--------------------------------------------
		// Game session loop
		//--------------------------------------------
		while (gameIsRunning)
		{
			// Get current game state
			crocSession->GetGameState(
				curGameState.score,
				curGameState.playerLocation,
				curGameState.backpacker1Activity,	// 0 if eaten (negative if being eaten)
				curGameState.backpacker2Activity,	// 0 if eaten (negative if being eaten)
				curGameState.calciumReading,		// Calcium reading at Croc location
				curGameState.salineReading,			// Saline reading at Croc location
				curGameState.alkalinityReading);	// Alkalinity reading at Croc location

			// The two moves to be made, assume player only searches for Croc
			std::wstring playerMove = L"S";
			std::wstring playerMove2 = L"S";
			int outScore;

			// A backpacker is currently being eaten, this reveals the Crocs location
			if (curGameState.backpacker1Activity < 0)
			{
				// Save this location and try to predict where the Croc will move next
				int crocLoc = curGameState.backpacker1Activity * -1;
			}
			else if (curGameState.backpacker2Activity < 0)
			{
				// Save this location and try to predict where the Croc will move next
				int crocLoc = curGameState.backpacker2Activity * -1;
			}

			// After predicting the Crocs location and where the Croc is moving,
			// make moves (2 moves per 1 Croc/backpacker move)
			if (!crocSession->makeMove(playerMove, playerMove2, outScore))
			{
				// Croc was found, game ends
				gameIsRunning = false;
				numGamesFinished++;
			}
		}
	}

	// Post results after playing 100 games or more
	crocSession->PostResults();
	delete crocSession;

	return 0;
}