#include "FBullCowGame.h"
#include <map>
#define Tmap std::map;

FBullCowGame::FBullCowGame(){ Reset();}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMyHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;
	
	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (IsIsogram(Guess))// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;//TODO write function 
	}
	else if (false)// if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;//TODO write function 
	}
	else if (Guess.length() != GetMyHiddenWordLength())// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else//otherwise
	{
		return EGuessStatus::OK;
	}
}

//receives a VALID guess, incriments turns, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	
	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				//if they are in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;//increment bulls
				}
				else
				{
					BullCowCount.Cows++;//increment cows
				}
			}
		}
	}
	
	bGameIsWon = BullCowCount.Bulls == WordLength;
	
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 or 1 letter words as isogram

	//setup our map
	//loop through all the letters of the word
		//if the letter is in the map
			//we do NOT have an isogram
		//otherwise
			//add the letter to the map as seen
	return true;
}
