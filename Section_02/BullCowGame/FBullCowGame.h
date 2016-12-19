#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialize to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();//constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetMyHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	// counts bulls & cows, and increases try # asuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructior for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};