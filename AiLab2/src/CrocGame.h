#pragma once

#include <vector>

#ifndef CROC_ENGINE_DLL
#define CROC_ENGINE_DLL __declspec(dllimport)
#endif

//	Game Overview:
//	
//	You are a ranger in Wollomunga national park, in outback Australia. 
//	Crocodiles in this park have sensors attached that say where they are and the water conditions 
//	(calcium, salinity and alkalinity levels) of the water the crocodile is current swimming in. 
//	
//	The park consists of 35 waterholes, each of which is reachable only from its neighbors. 
//	
//	The park has records of the calcium, salinity and alkalinity distributions in each waterhole.
//	
//	The sensor on one crocodile, 'Croc', has broken. It no longer says where he is, however 
//	it does still provide water condition readings. You need to find Croc. 
//
//	There are also two Swedish backpackers in the park, wandering around at random visiting waterholes. 
//	If they end up in the same waterhole as Croc, they will be eaten. 
//	
//	Your score is the number of moves it takes to find Croc.

class http_pImple;
class CrocGame;
class CROC_ENGINE_DLL CrocSession
{
public:
	CrocSession (const std::wstring& GroupName,bool& OK);
	~CrocSession ();

	//	Get your session statistics
	//	-	You are ranked on your average, and lower is better.
	int getPlayed () const;
	double getAverage () const;

	//	Clear the session statistics
	void ClearRecord();

	//	Submit session statistics to the server
	//	-	Requires that you have played at least 100 games.
	void PostResults() const;

	//	Start a game
	//	-	The previous game must have finished
	void StartGame ();

	//	Get Paths
	//	-	These remain constant from game to game
	const std::vector<std::vector<int>>& getPaths () const;

	//	Make moves
	//	-	Note that you move twice for every move Croc and the backpackers make. So you can move to a square and search it before Croc moves on. 
	//	-	Valid moves are:
	//      i.  The index of a waterhole to travel to.
	//          (It must be reachable from your current location)
	//      ii. 'S', indicating that the waterhole should be search for Croc.
	//	-	Invalid moves will mean you do nothing.
	bool makeMove (
		const std::wstring& playerMove,
		const std::wstring& playerMove2,
		int& outScore);

	//	Get the current game state
	//	-	Shows location of yourself and backpackers, and readings from Croc's sensors. 
	//	-	Backpacker locations are 0 if they are eaten, and multipled by -1 if they are being eaten.
	//	-	Starting locations are different each game.		
	void GetGameState (
		int& score,
		int& playerLocation,
        int& backpacker1Activity,
	    int& backpacker2Activity,
        double& calciumReading,
		double& salineReading,
        double& alkalinityReading
		) const;

	//	Get the game distributions
	//	-	Means and standard deviations of calcium, salinity and alkalinity distributions for each waterhole. 
	//	-	These are different each game.
	void GetGameDistributions (
		std::vector<std::pair<double,double>>& calcium, // For each waterhole:  mean, std dev
		std::vector<std::pair<double,double>>& salinity, // For each waterhole:  mean, std dev
		std::vector<std::pair<double,double>>& alkalinity // For each waterhole: mean, std dev
		) const;
private:
	std::wstring Group;
	CrocGame* Game;
	http_pImple* p;
	int score;
	int total;
};
