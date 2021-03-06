#pragma once

#include "FBullCowGame.h"
#include <map>

//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset();}//default constractor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMyHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	
	TMap<int32, int32> WordLengthMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";//this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))// if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetMyHiddenWordLength())// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
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
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetteSeen;//setup our map
	for (auto Letter : Word)//for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case
		if (LetteSeen[Letter])//if the letter is in the map
		{
			return false;//we do NOT have an isogram
		}
		else
		{
			LetteSeen[Letter] = true;//add the letter to the map as seen
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//if NOT lowercase letter
		{
			return false;
		}
	}
	return false;
}
