///////////////////////////////// Mastermind ///////////////////////////////////
/*******************************************************************************
Implementation file name: mastermind.cpp
Desc: The following is the source code for the functions defined in mastermind.h
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "mastermind.hpp"
#include <random>
#include <climits>

using std::cout;
using std::cin;
using std::endl;

//global variables to generate random digits
std::random_device rd;
std::default_random_engine engine(rd());

////////////////////////////// Main Functions //////////////////////////////

/****************************SetUp()*****************************
Method Name: SetUp()
Desc: Will use several private functions to start the game set-up. That is
the difficulty (pegs and colors) and the secret combination to be used.
****************************************************************/
void Mastermind::SetUp() {
	EnterDifficulty();

	DisplayDifficulty();

	//Enter secret combination
	EnterCombination(combination.secret);

	//Are we using given or random combination?
	DisplaySecretCombinationType();

}

/****************************Start()*****************************
Method Name: Start()
Desc: Will use several private functions to start guessing. That is
entering a combination, displaying it, and providing feedback by
displaying the wrong and right places.
****************************************************************/
void Mastermind::Start() {
	bool combinationsMatched, isAllZeros;
	do {
		ClearPlaces();

		//enter guessed combination
		EnterCombination(combination.guessed);
		DisplayGuesses();

		combinationsMatched = CombinationsMatched();
		isAllZeros = IsAllZeros(combination.guessed);

		if (!combinationsMatched && !isAllZeros) {
			FindPlaces();
			DisplayPlaces();
		}

	} while (!combinationsMatched && !isAllZeros);
}

/****************************End()*****************************
Method Name: End()
Desc: Will use several private functions to display the game 
results.
****************************************************************/

void Mastermind::End() {
	if (CombinationsMatched()) {
		YouWon();
	}
	else {
		YouLost();
	}
}

////////////////////////////// SetUp() //////////////////////////////


/****************************EnterDifficulty()*****************************
Method Name: EnterDifficulty()
Desc: Enter many pegs and colors, validating boundaries. 
If pegs entered is lesser than the minimum (2), then it will automatically 
set the pegs to 2. If pegs entered is greater than the maximum (8), then it 
will automatically set the pegs to 8.

If colors entered is lesser than the minimum (6), then it will automatically
set the pegs to 6. If pegs entered is greater than the maximum (20), then it
will automatically set the pegs to 20.
**************************************************************************/
void Mastermind::EnterDifficulty() {
	cin >> boundary.pegs >> boundary.colors;

	//handle pegs
	if (boundary.pegs < 2) {
		boundary.pegs = 2;
	}
	if (boundary.pegs > 8) {
		boundary.pegs = 8;
	}

	//handle colors
	if (boundary.colors < 6) {
		boundary.colors = 6;
	}
	if (boundary.colors > 20) {
		boundary.colors = 20;
	}
}

/****************************DisplayDifficulty()*****************************
Method Name: DisplayDifficulty()
Desc: Displays the boundaries set in the game. That is the boundaries of pegs
and colors to guess.
****************************************************************************/
void Mastermind::DisplayDifficulty() {
	cout << "Playing Mastermind with " << boundary.pegs << " pegs and " << boundary.colors << " possible colors." << endl;
}

/****************************EnterCombination()*****************************
Method Name: EnterCombination()
Desc: Enters a combination of numbers into the vector passed. It will also
validate it.
**************************************************************************/
void Mastermind::EnterCombination(vector<int>& combination) {
	int digit;
	do {

		combination.clear();
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		for (int pegs = 1; pegs <= boundary.pegs; pegs++) {
			cin >> digit;
			combination.push_back(digit);
		}
	} while (!CombinationIsValid(combination));
}


/****************************DisplaySecretCombinationType()*****************************
Method Name: SetUp()
Desc: Displays whether the combinations used will be random and generated by the computer
or given by the user.
**************************************************************************************/
void Mastermind::DisplaySecretCombinationType() {
	if (IsAllZeros(combination.secret)) {
		GenerateRandomSecretCombination();
		cout << "Using random secret." << endl << endl;
	}
	else {
		cout << "Using given secret." << endl << endl;
	}
}


////////////////////////////// Start() //////////////////////////////

/****************************ClearPlaces()********************************
Method Name: ClearPlaces()
Desc: It resets or clears the set of right and wrong places to start over.
*************************************************************************/
void Mastermind::ClearPlaces() {
	place.right.clear();
	place.wrong.clear();
}

/****************************DisplayGuesses()*****************************
Method Name: DisplayGuesses()
Desc: It displays the combination guessed.
****************************************************************/
void Mastermind::DisplayGuesses() {
	cout << "Guess " << ++manyGuesses << ": ";
	DisplayGuessedCombination(combination.guessed);
}

/****************************FindPlaces()*****************************
Method Name: FindPlaces()
Desc: It will determine how many right and wrong places were between
the secret combination and the guessed combination.
*********************************************************************/
void Mastermind::FindPlaces() {
	for (int digit = 0; digit < boundary.pegs; digit++) {
		//right guess
		if (combination.guessed[digit] == combination.secret[digit]) {
			place.right.insert(combination.guessed[digit]);
		}


		//wrong guess
		else {
			bool numberWasFound = false;
			for (int secretDigit = 0; secretDigit < boundary.pegs && !numberWasFound; secretDigit++) {
				if (combination.guessed[digit] == combination.secret[secretDigit]) {
					place.wrong.insert(combination.guessed[digit]);
					numberWasFound = true;
				}
			}
		}
	}

	RemoveDuplicatesFromWrongSet();
}

/****************************DisplayPlaces()*****************************
Method Name: DisplayPlaces()
Desc: It will display how many right and wrong places were between the 
secret and the guessed combination.
***********************************************************************/
void Mastermind::DisplayPlaces() {
	cout << place.right.size() << " Right place" << endl;
	cout << place.wrong.size() << " Wrong place" << endl << endl;
}

////////////////////////////// End() //////////////////////////////

/****************************CombinationsMatched()******************************
Method Name: CombinationsMatched()
Desc: Compares the secret and guessed combination to determine if they match. It
returns true if they do, otherwise false.
*******************************************************************************/
bool Mastermind::CombinationsMatched() {
	//iterate through the guessed combination
	for (int i = 0; i < boundary.pegs; i++) {
		//compare
		if (combination.guessed[i] != combination.secret[i]) {
			//if they do not match
			return false;
		}
	}
	//if they matched
	return true;

}

/****************************YouWon()*****************************
Method Name: YouWon()
Desc: Displays a "You Won!" screen and the many guesses it took
to win the game.
*****************************************************************/
void Mastermind::YouWon() {
	cout << "You won!" << endl;
	if (manyGuesses > 1) {
		cout << "It took you " << manyGuesses << " guesses." << endl;
	}
	else {
		cout << "It took you " << manyGuesses << " guess." << endl;
	}
}

/****************************YouLost()*****************************
Method Name: YouLost()
Desc: Displays a "You lost" screen and the secret combination.
****************************************************************/
void Mastermind::YouLost() {
	cout << "You lost." << endl;
	cout << "The secret was ";
	DisplaySecretCombination(combination.secret);
}

//////////////////////////////Throughout//////////////////////////////

/****************************IsAllZeros()*****************************
Method Name: IsAllZeros()
Desc: Will determine if the vector passed is a combination of only
zeros. It is, it returns true, otherwise false.
********************************************************************/
bool Mastermind::IsAllZeros(vector <int> enteredCombination) {
	for (int index = 0; index < boundary.pegs; index++) {
		if (enteredCombination[index] != 0) {
			return false;
			}
	}
	
	return true;
}

/****************************GenerateRandomDigit()*****************************
Method Name: GenerateRandomDigit()
Desc: Generate and returns a random digit.
********************************************************************/
int Mastermind::GenerateRandomDigit() {
	std::uniform_int_distribution<int> random(1, boundary.pegs);
	int digit = random(engine);
	return digit;
}

/****************************GenerateRandomSecretCombination()*****************************
Method Name: GenerateRandomSecretCombination()
Desc: Generate and returns a vector with a random combination.
********************************************************************/
void Mastermind::GenerateRandomSecretCombination() {
	for (int index = 0; index < boundary.pegs; index++) {
		int randomDigit = GenerateRandomDigit();
		combination.secret[index] = randomDigit;
	}
}

/****************************DigitIsValid()*****************************
Method Name: DigitIsValid()
Desc: Determines if the passed integer is valid, that is between the 
color boundaries provided at game set-up. If it is, then it returns
true, otherwise false.
********************************************************************/
bool Mastermind::DigitIsValid(int digit) {
	if (digit < 1 || digit > boundary.colors) {
		cout << "Numbers must be between 1 and " << boundary.colors << "." << endl << endl;
		return false;
	}

	return true;
}

/****************************CombinationIsValid()*****************************
Method Name: CombinationIsValid()
Desc: Determines if the passed vector with a certain combination is valid.
********************************************************************/
bool Mastermind::CombinationIsValid(vector<int> enteredCombination) {
	if (IsAllZeros(enteredCombination)) {
		return true;
	}

	for (int i = 0; i < enteredCombination.size(); i++) {
		if (!DigitIsValid(enteredCombination[i])) {
			return false;
		}
	}

	return true;
}

/****************************RemoveDuplicatesFromWrongSet()*****************************
Method Name: RemoveDuplicatesFromWrongSet()
Desc: Removes duplicates between the right and wrong sets. This is because a place can 
not be wrong and right at the same time. Hence, it must be right and not wrong.
**************************************************************************************/
void Mastermind::RemoveDuplicatesFromWrongSet() {
	for (int num : place.right) {
		place.wrong.erase(num);
	}
}

/****************************DisplaySecretCombination()*****************************
Method Name: DisplaySecretCombination()
Desc: Displays the secret combination with the required format.
**************************************************************************************/
void Mastermind::DisplaySecretCombination(vector <int> combination) {
	for (int index = 0; index < boundary.pegs; index++) {
		cout << combination[index];
		if (index != boundary.pegs - 1) {
		cout << " ";
		}
	};
	cout << "." << endl;
}

/****************************DisplayGuessedCombination()*****************************
Method Name: DisplayGuessedCombination()
Desc: Displays the guessed combination with the required format.
**************************************************************************************/
void Mastermind::DisplayGuessedCombination(vector <int> combination) {
	for (int index = 0; index < boundary.pegs; index++) {
		cout << combination[index];
		if (index != boundary.pegs - 1) {
			cout << " ";
		}
	};
	cout << endl;
}