#include "stdafx.h"
#include "FBullCowGame.h"
//#include "main.h"


int32 FBullCowGame::GetMaxTries() const { return MaxTries; }

int32 FBullCowGame::GetCurrentTry() const{ return CurrentTry; }

EWordStatus FBullCowGame::CheckGuess(Fstring s)
{
	if (s.length() != GetHWordLength())
		return EWordStatus::WRONG_LENGHT;
	if (!checkLoweCase(s))
		return EWordStatus::NOT_LOWERCASE;
	if (!checkInsogramm(s))
		return EWordStatus::NOT_ISOGRAMM;
	else
		return EWordStatus::OK; 
}

//recieves a valid guess and returns bull & cow count
FBullCowCount FBullCowGame::SubmitGuess(Fstring guess)
{
	CurrentTry++;

	FBullCowCount BCcount;

	//looping through all letters in guess
	for (int HWtraverser = 0; HiddenWord[HWtraverser] != '\0'; HWtraverser++)
	{
		if (HiddenWord[HWtraverser] == guess[HWtraverser])
			BCcount.BullCount++;
		for (int GWtraverser = 0; guess[GWtraverser] != '\0'; GWtraverser++)
		{
			if (HiddenWord[HWtraverser] == guess[GWtraverser])
				BCcount.CowCount++;
		}
	}
	BCcount.CowCount = BCcount.CowCount - BCcount.BullCount;//correcting cows value
	if (BCcount.BullCount == GetHWordLength())//check if bull count is equal to word length
	{
		bGameStatus = true;//if true return true
	}
	else
	{
		bGameStatus = false;//else return false
	}
	return BCcount;
}

bool FBullCowGame::IsGameWon() 
{
	
		
	return bGameStatus; 
}

int32 FBullCowGame::GetHWordLength() const
{
	return  (int32)HiddenWord.length();
}

FBullCowGame::FBullCowGame(void)
{
	reset();
}
void FBullCowGame::reset()
{
	BCcount.BullCount = 0;
	BCcount.CowCount = 0;
	bGameStatus = false;
	MaxTries = 5;
	CurrentTry=1;
	HiddenWord = "gabriel";
}