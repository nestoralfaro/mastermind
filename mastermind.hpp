#pragma once
/*
/*******************************************************************************
Header file name: mastermind.hpp
Desc: This header contains the function definitions for Mastermind
********************************************************************************/
#include <vector>
#include <set>
using std::vector;
using std::set;

struct combinations {
	vector <int> entered, guessed, secret;
};

struct boundaries {
	int pegs, colors;
};

struct places {
	set <int> right, wrong;
};

class Mastermind {
	private:
		combinations combination;
		boundaries boundary;
		places place;

		//SetUp()
		void EnterDifficulty();
		void DisplayDifficulty();
		void EnterCombination(vector<int>&);
		void DisplaySecretCombinationType();

		//Start()
		void ClearPlaces();
		void DisplayGuesses();
		void FindPlaces();
		void DisplayPlaces();

		//End()
		bool CombinationsMatched();
		void YouWon();
		void YouLost();

		//Throughout
		bool IsAllZeros(vector <int>);
		bool DigitIsValid(int);
		bool CombinationIsValid(vector<int>);
		int GenerateRandomDigit(), manyGuesses = 0;
		void DisplaySecretCombination(vector <int>);
		void DisplayGuessedCombination(vector <int>);
		void GenerateRandomSecretCombination();
		void RemoveDuplicatesFromWrongSet();

	public:
		void	SetUp(),
				Start(),
				End();
};