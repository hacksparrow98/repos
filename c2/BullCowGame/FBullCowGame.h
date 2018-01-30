#pragma once
using int32 = int;
using Fstring = string;

static bool checkInsogramm(Fstring w)
{
	bool flag = true;
	int32 len = w.length();
	for (int32 i = 0; i < len; i++)
	{
		for (int32 j = i+1; j < len; j++)
		{
			if (w[i] == w[j])
			{
				flag = false;
				break;
			}
		}
	}
	return flag;
}

static bool checkLoweCase (Fstring w) 
{
	bool flag1 = true;
	int32 len = w.length();
	for (int32 i = 0; i < len; i++)
	{
		if (!islower(w[i]))
		{
			flag1 = false;
			break;
		}
	}
	return flag1;
}


struct FBullCowCount
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};

enum class EWordStatus
{
	INVALID_GUESS,
	OK,
	WRONG_LENGHT,
	NOT_ISOGRAMM,
	NOT_LOWERCASE
};
class FBullCowGame
{
public:
	FBullCowGame();//constructor

	int32 GetMaxTries() const;//returns no. of tries
	int32 GetCurrentTry() const;//returns current no. of tries
	int32 GetHWordLength() const;//returns hidden word length
	bool IsGameWon();
	EWordStatus CheckGuess(Fstring);//TODO return more rich value

	void reset();
	FBullCowCount SubmitGuess(Fstring);//recieves a valid guess and returns bull & cow count

private:
	bool bGameStatus;
	int32 CurrentTry=1;
	int32 MaxTries;
	Fstring HiddenWord;
	FBullCowCount BCcount;

};

