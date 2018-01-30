// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "main.h"
#include "FBullCowGame.h"
using Ftext = string;

void PrintGameSummary(void);
bool playAgain(void);
int32 main();
void PrintIntro(void);
Ftext GetValidGuess(void);
void play(void);

FBullCowGame PlayGame;

//MAIN

int main()
{
	do
	{
		PrintIntro();
		play();
	} while (playAgain());
	
	return 0;
}

//introduction

void PrintIntro(void)
{
	int32 word_length = PlayGame.GetHWordLength();
	cout << "\n\t\tWelcome to bull and cow game.\n";
	cout << "\tCan You Guess a " << word_length << "letter word which is an isogram?\n";
}

//get a guess

Ftext GetValidGuess(void)
{
	EWordStatus status = EWordStatus::INVALID_GUESS;
	do
	{
		int32 a = PlayGame.GetCurrentTry();
		cout << "\n\n Chance "<<a<<" out of "<<PlayGame.GetMaxTries()<<".\n What's your guess: ";
		Ftext guess;
		getline(cin, guess);

		status = PlayGame.CheckGuess(guess);
		switch (status)
		{
		case EWordStatus::WRONG_LENGHT:
			cout << " !!! Please enter a " << PlayGame.GetHWordLength() << " letter word!!! \n";
			break;
		case EWordStatus::NOT_ISOGRAMM:
			cout << " !!! Please enter a word without repeating lettrs!!! \n";
			break;
		case EWordStatus::NOT_LOWERCASE:
			cout << " !!! Please enter the word in lowercase!!! \n";
			break;
		default:
			return guess;
		}
	} while (status != EWordStatus::OK);
}

//Play Code

void play(void)
{
	PlayGame.reset();
	//displaying and validating guess
	while (!PlayGame.IsGameWon() && PlayGame.GetCurrentTry()<= PlayGame.GetMaxTries())
	{
		Ftext guess = GetValidGuess();
		cout << " Your guess was: " << guess<<endl;
				
		FBullCowCount Count=PlayGame.SubmitGuess(guess);//submitting guess

		cout <<  " Bulls: " << Count.BullCount << "\n Cows: " << Count.CowCount<<endl;
	}
	PrintGameSummary();
}

//printing game summary
void PrintGameSummary(void)
{
	if (PlayGame.IsGameWon())
	{
		cout << " ^-^Congratulations You Guessed The Correct Word^-^";
	}
	else
	{
		cout << " :( Better Luck Next Time";
	}
}

//Asking To Play Again

bool playAgain(void)
{
	Ftext ans;
	cout << "\n\nHey! Do you want to play again?\n";
	getline(cin, ans);

	return (ans == "yes" || ans == "YES" || ans == "y" || ans == "Y");
}

