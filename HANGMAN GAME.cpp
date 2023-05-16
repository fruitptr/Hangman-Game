#include <iostream>
#include <windows.h>//Allows us to perform the beep function.
#include <time.h>//Allows us to perform operations using time such as srand, loadingTime, returnToMainMenu etc.
#include <fstream>//Allows us to perform file handling.
#include <string>

using namespace std;
void faceDisplay(); //Displays the big HANGMAN text after every clear screen
void mainScreen(); //Main screen. Where the user can choose which gamemode they want to play, settings, about and quit.
void playLocal(); //To play against the computer.
void playMultiplayer(); //To play against someone next to you.
void settings(); //Settings screen.
void about(); //About screen.
void guessWord(string); //Where all the calculations for the game are done and underscores and correct letters are displayed when playing multiplayer or when guessing a random word by the computer.
void loadWordsFromFile(char); //Function to copy words to an array of 1000 size from countries, animals, things, cities, fruits files.
void saveWordsToFile(char); //Used to copy all the words within the wordList array into the appropriate file.
void addNewWord(); //Displays the user with all the categories to store the word in.
void addWordToFile(string, char); //Add a new word from the user into the wordList array.
void displayGuessedLetters(string, string); //Display all the letters guessed by the user.
void wordCzarLocal(); //Asks user to input a word for the computer to guess.
void guesserLocal(); //Asks user if they want to play with hints or without hints.
void guessWordLocal(string); //Where the computer has to guess the word inputted by the user.
void drawHangman(int); //Draws the hangman figure gradually.
void returnToMainMenu(); //Shows a countdown to the user before they are returned to the mainScreen function.
void withHintsLocal(); //Asks user which category they want to play (fruit, countries, cities, animals, things) and calls other functions to get a random word from one of the files.
void noHintsLocal(); //Calls other functions to get a random word from the main wordLibrary file.
void loadWordsFromMainLibrary(); //Function to copy words to an array of 1000 size from the main wordLibrary file.
void changeBackground(); //Changes the background color and text of the console window.

string wordList[1000]; //This is a global variable. We used a global variable so it can be accessed from any function. We used an array so we can get a random word using the index of the array.
int wordListLength = 0; //Used to assign the array's length according to each text file. (Suppose the countriesLibrary text file could have 400 words, while animalsLibrary text file could have 800 words).

int main()
{
	srand(time(NULL)); //So a new word from the list is picked every time.

	time_t loadingTime = time(NULL);
	char dot = 46;
	int j = 1;
	int display = 0;

	faceDisplay();
	std::cout << "Loading";
	//The for loop below shows the Loading... at the start. We are basically making an illusion for the user as the screen is cleared after a dot in the Loading... and a new screen is displayed with the number of dots increased by 1. Once the number of dots are 3, the main screen is displayed.
	for (int i = 0; i < 3; i++)
	{
		while (time(NULL) - loadingTime < j) {}
		std::cout << dot;
		j++;
		if (j == 4)
		{
			system("CLS");
			j = 1;
			loadingTime = time(NULL);
			faceDisplay();
			std::cout << "Loading";
		}
		else
			continue;
	}

	system("CLS");
	mainScreen();

	system("pause");
	return 0;
}

void loadWordsFromFile(char option)
{
	int count = 0;
	string word;
	ifstream file; //Variable for the file so we can perform further functions to it (such as .open).
	switch (option)
	{
	case '1':
	{
		file.open("countriesLibrary.txt");
		break; //We use break after every case statement so the next case statements are not automatically called as well.
	}
	case '2':
	{
		file.open("animalsLibrary.txt");
		break;
	}
	case '3':
	{
		file.open("fruitvegLibrary.txt");
		break;
	}
	case '4':
	{
		file.open("thingsLibrary.txt");
		break;
	}
	case '5':
	{
		file.open("citiesLibrary.txt");
		break;
	}
	default: //Invalid Input and a 2 second pause will be displayed if anything other than 1,2,3,4,5 is entered.
	{
		time_t InvalidInputBuffer = time(NULL);
		cout << "\nInvalid Input!";
		while (time(NULL) - InvalidInputBuffer < 2) {}
		system("CLS");
		withHintsLocal();
	}
	}
	while (getline(file, word)) //We used getline to read the file till the end.
	{
		wordList[count] = word; //We store each word within the file into an array at the appropriate index.
		count++;
	}
	wordListLength = count;
	file.close();
}

void addNewWord() 
{
	string newWord;
	char option;
	system("CLS");
	faceDisplay();
	std::cout << "Select a category: " << endl;
	cout << "1. Countries." << endl;
	cout << "2. Animals" << endl;
	cout << "3. Fruits/Vegetables." << endl;
	cout << "4. Things." << endl;
	cout << "5. Cities." << endl;
	cout << "6. No category." << endl << endl;
	cout << "Select an option: ";
	cin >> option;
	if (option > '6' || option < '1')
	{
		cout << "\nInvalid Input!";
		system("CLS");
		addNewWord();
	}
	std::cout << "\nPlease enter the word: ";
	cin >> newWord;
	addWordToFile(newWord, option);
}

void addWordToFile(string newWord, char option)
{
	if (option <= '5' && option >= '1') 
	{
		loadWordsFromFile(option);
		wordList[wordListLength] = newWord;
		wordListLength++;
		saveWordsToFile(option);
	} 
	loadWordsFromMainLibrary(); //All words inputted are also stored in the main library.
	wordList[wordListLength] = newWord;
	wordListLength++;
	saveWordsToFile('6');
	cout << "Word Added!\n\n";
	returnToMainMenu();
	system("CLS");
	mainScreen();
}

void saveWordsToFile(char option)
{
	ofstream file; //Declaring variable for a file so we can start file handling operations on it.
	switch (option)
	{
	case '1':
	{
		file.open("countriesLibrary.txt");
		break;
	}
	case '2':
	{
		file.open("animalsLibrary.txt");
		break;
	}
	case '3':
	{
		file.open("fruitvegLibrary.txt");
		break;
	}
	case '4':
	{
		file.open("thingsLibrary.txt");
		break;
	}
	case '5':
	{
		file.open("citiesLibrary.txt");
		break;
	}
	case '6':
	{
		file.open("wordLibrary.txt");
		break;
	}
	}
	for (int i = 0; i < wordListLength; i++) //Here, all the words within the wordList array are copied into the appropriate file opened from the above case statement.
	{
		file << wordList[i] << endl;
	}
}

string getRandomWordFromList()
{
	return wordList[rand() % wordListLength]; //Grabs a random word from the wordList array based on a random index from the array.
}

void faceDisplay()
{
	std::cout << "  _    _                                         " << endl;
	std::cout << " | |  | |                                        " << endl;
	std::cout << " | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __  " << endl;
	std::cout << " |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ " << endl;
	std::cout << " | |  | | (_| | | | | (_| | | | | | | (_| | | | |" << endl;
	std::cout << " |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|" << endl;
	std::cout << "                      __/ |                      " << endl;
	std::cout << "                     |___/                       " << endl << endl;
}
// Options that appear on the first screen of our game.
void mainScreen()
{
	char option;
	string randomWord;

	faceDisplay();
	std::cout << "1. Play Local" << endl;
	std::cout << "2. Play Multiplayer" << endl;
	std::cout << "3. Settings" << endl;
	std::cout << "4. About" << endl;
	std::cout << "5. Quit" << endl << endl;
	std::cout << "Select your option: ";
	cin >> option;

	switch (option)
	{
	case '1':   
		playLocal();
		break;
	case '2':
		playMultiplayer();
		break;
	case '3':
		settings();
		break;
	case '4':
		about();
		break;
	case '5':
		break;
	default: 
		time_t InvalidInputBuffer = time(NULL);
		cout << "\nInvalid Input!";
		while (time(NULL) - InvalidInputBuffer < 2) {} //Gives a 2 second pause.
		system("CLS");
		mainScreen();
	}
}

void playLocal()
{
	char role;
	system("CLS");
	faceDisplay();

	std::cout << "What role would you like to play?\n";
	std::cout << "1. Word Czar\n";
	std::cout << "2. Guesser\n\n";
	std::cout << "Select an option: ";
	cin >> role;

	switch (role)
	{
	case '1':
		wordCzarLocal();
		break;
	case '2':
		guesserLocal();
		break;
	default:
	{
		time_t InvalidInputBuffer = time(NULL);
		cout << "\nInvalid Input!";
		while (time(NULL) - InvalidInputBuffer < 2) {}
		system("CLS");
		playLocal();
	}
	}

}

void wordCzarLocal()
{
	string word;
	int j = 1;
	int number = 3;
	time_t loadingTime = time(NULL);
	system("CLS");
	faceDisplay();
	std::cout << "Word Czar enter a word: ";
	cin.ignore();
	getline(cin, word);
	std::cout << "\nThe screen will clear in ";
	for (int i = 0; i <= 2; i++)
	{
		while (time(NULL) - loadingTime < j) {}
		std::cout << number;
		number--;
		loadingTime = time(NULL);
		while (time(NULL) - loadingTime < j) {}
		system("CLS");
		faceDisplay();
		std::cout << "Word Czar enter a word: " << word << endl;
		std::cout << "\nThe screen will clear in ";
		if (number == 0)
		{
			system("CLS");
			guessWordLocal(word);
		}
	}
}

void guessWordLocal(string word)
{
	time_t loadingTime = time(NULL);
	char dot = 46;
	int j = 1;
	char ch;
	const int wordLength = word.length();
	int wrongCount = 0;
	string guess;
	string guessChar;
	bool guessed = false;
	string correctLettersArray;
	string wrongLettersArray;
	int wrongIndex = 0;
	int correctIndex = 0;
	string caseSensWord;
	int tempWordLength;
	string blankSpace = " ";
	int spaceCount = 0;
	string tempWord;
	int count = 0;
	
	tempWord = word; //We are assining a tempWord string so we can remove spaces in the original string if needed and save it here.
	tempWordLength = wordLength; //If there are spaces in the string, we can change the word length accordingly.

	for (int i = 0; i < wordLength; i++) //Checks for any spaces.
	{
		if (word[i] == blankSpace[0])
		{
			spaceCount++;
		}
	}

	tempWordLength = tempWordLength - spaceCount;

	tempWord.erase(remove(tempWord.begin(), tempWord.end(), ' '), tempWord.end()); //Removes the spaces.

	faceDisplay();
	for (int i = 0; i < wordLength; i++)
	{
		if (word[i] == blankSpace[0]) //If there is a space, a space will be shown.
		{
			std::cout << "  ";
		}
		else
			std::cout << "_ "; //Shows an underscore for any non-space character.
	}

	bool guessWrong = 1;

	while (wrongCount != 7) //Since the number of tries in hangman are 7, the game will only be played until seven tries.
	{
		string guess;
		guessWrong = 1;
		std::cout << endl << "CPU's guess: ";

		for (int i = 0; i < 3; i++) //Somewhat pointless, but it shows three dots one by one before the computer "guesses" a letter.
		{
			while (time(NULL) - loadingTime < j) {}
			std::cout << dot;;
			j++;
			if (j == 4)
			{
				system("CLS");
				j = 1;
				loadingTime = time(NULL);
				faceDisplay();
				drawHangman(wrongCount);
				for (int i = 0; i < wordLength; i++)
				{
					bool isWordGuessed = false;
					for (int j = 0; j < guessChar.length(); j++)
					{
						if (word[i] == guessChar[j])
						{
							isWordGuessed = true;
						}
					}
					if (isWordGuessed == false && word[i] == blankSpace[0])
					{
						std::cout << "  ";
					}
					else if (isWordGuessed == false)
					{
						std::cout << "_ ";
					}
					else
					{
						std::cout << word[i] << " ";
					}
				}
				std::cout << "\n";
				displayGuessedLetters(correctLettersArray, wrongLettersArray);

				std::cout << "\nCPU's guess: ";
			}
			else
				continue;
		}

		ch = rand() % 26 + 97; //Getting a random letter from the 26 alphabets.
		guess += ch; //Adding the random alphabet generated to a guess string.

		cout << guess << endl;

		for (int i = 0; i < tempWordLength; i++)
		{
			if ((guess[0] - 32) == tempWord[i] || (guess[0] + 32) == tempWord[i] || tempWord[i] == guess[0]) //This is done to accept the letter whether its uppercase or lowercase.
			{
				caseSensWord = tempWord[i]; //If the letter is present in the tempWord string, we store that letter in caseSensWord.
				bool check = 0;
				guessChar.append(caseSensWord); //Here we are storing that letter in another string known as guessChar.
				guessWrong = 0;
				for (int k = 0; k < correctLettersArray.length(); k++)
				{
					if (correctLettersArray[k] == tempWord[i])
					{
						check = 1;
					}
				}
				if (check == 0)
				{
					correctLettersArray.append(caseSensWord);
				}
			}
		}
		if (guessWrong == 1)
		{
			bool check = 0;
			for (int k = 0; k < wrongLettersArray.length(); k++)
			{
				if (wrongLettersArray[k] == guess[0])
				{
					check = 1;
				}
			}
			if (check == 0)
			{
				wrongLettersArray.append(guess);
				wrongCount++;
				std::cout << "No letter matched! Try again. You have " << 7 - wrongCount << "/" << 7 << " chances left." << endl;
			}
			if (check == 1)
			{
				std::cout << "You've already guessed this letter!" << endl;
			}
			time_t buffer = time(NULL);
			while (time(NULL) - buffer < 2) {}
			system("CLS");
			faceDisplay();
			if (wrongCount <= 7)
			{
				drawHangman(wrongCount);
			}
			for (int i = 0; i < wordLength; i++)
			{
				bool isWordGuessed = false;
				for (int j = 0; j < guessChar.length(); j++)
				{
					if (word[i] == guessChar[j])
					{
						isWordGuessed = true;
					}
				}
				if (isWordGuessed == false && word[i] == blankSpace[0])
				{
					std::cout << "  ";
				}
				else if (isWordGuessed == false)
				{
					std::cout << "_ ";
				}
				else
				{
					std::cout << word[i] << " ";
				}
			}
			std::cout << endl;
			displayGuessedLetters(correctLettersArray, wrongLettersArray);
		}
		else
		{
			system("CLS");
			faceDisplay();
			drawHangman(wrongCount);
			int correctGuessed = 0;

			for (int i = 0; i < wordLength; i++)
			{
				bool isWordGuessed = false;
				for (int j = 0; j < guessChar.length(); j++)
				{
					if (word[i] == guessChar[j])
					{
						isWordGuessed = true;
					}
				}
				if (isWordGuessed == false && word[i] == blankSpace[0])
				{
					std::cout << "  ";
				}
				else if (isWordGuessed == false)
				{
					std::cout << "_ ";
				}
				else
				{
					std::cout << word[i] << " ";
					correctGuessed++;
				}
			}
			std::cout << endl;
			displayGuessedLetters(correctLettersArray, wrongLettersArray);
			if (correctGuessed == tempWordLength)
			{
				guessed = true;
				break;
			}
		}
	}

	if (guessed == true)
	{
		std::cout << "\nYou guessed the word!" << endl;
	}
	else
	{
		std::cout << "\nThe computer ran out of the guessing chances!\n";
		std::cout << "The word was: " << word << endl;
	}

	returnToMainMenu();

	system("CLS");
	mainScreen();

	return;
}

void guesserLocal()
{
	char option;
	system("CLS");
	faceDisplay();
	std::cout << "Choose a playstyle: " << endl;
	std::cout << "1. Play with hints." << endl;
	std::cout << "2. Play without hints. " << endl << endl;
	std::cout << "Select an option: ";
	cin >> option;

	switch (option)
	{
	case '1':
	{
		withHintsLocal();
		break;
	}
	case '2':
	{
		noHintsLocal();
		break;
	}
	default:
		time_t InvalidInputBuffer = time(NULL);
		cout << "\nInvalid Input!";
		while (time(NULL) - InvalidInputBuffer < 2) {}
		guesserLocal();
	}
}
// Play Local part of the game.
void withHintsLocal()
{
	char option;
	string word;
	system("CLS");
	faceDisplay();
	std::cout << "Select a category: " << endl;
	std::cout << "1. Countries" << endl;
	std::cout << "2. Animals" << endl;
	std::cout << "3. Fruits/Vegetables" << endl;
	std::cout << "4. Things" << endl;
	std::cout << "5. Cities" << endl << endl;
	std::cout << "Select an option: ";
	cin >> option;

	loadWordsFromFile(option);
	word = getRandomWordFromList();
	guessWord(word);

}
// If user selects to play without hints 
void noHintsLocal()
{
	string word;
	system("CLS");
	faceDisplay();
	loadWordsFromMainLibrary();
	word = getRandomWordFromList();
	guessWord(word);
}

void loadWordsFromMainLibrary()
{
	int count = 0;
	string word;
	ifstream file;
	file.open("wordLibrary.txt");// Filing is used 
	while (getline(file, word))
	{
		wordList[count] = word;
		count++;
	}
	wordListLength = count;
	file.close();
}

void playMultiplayer()
{
	string word;
	int j = 1;
	int number = 3;
	time_t loadingTime = time(NULL);
	system("CLS");
	faceDisplay();
	std::cout << "Word Czar enter a word: ";
	cin.ignore();
	getline(cin, word);
	std::cout << "\nThe screen will clear in ";
	for (int i = 0; i <= 2; i++)
	{
		while (time(NULL) - loadingTime < j) {}
		std::cout << number;
		number--;
		loadingTime = time(NULL);
		while (time(NULL) - loadingTime < j) {}
		system("CLS");
		faceDisplay();
		std::cout << "Word Czar enter a word: " << word << endl;
		std::cout << "\nThe screen will clear in ";
		if (number == 0)
		{
			system("CLS");
			guessWord(word);
		}
	}
}

void settings()
{
	char option;

	system("CLS");
	faceDisplay();
	std::cout << "1. Add word to library" << endl;
	std::cout << "2. Change theme" << endl;
	std::cout << "\nSelect option: ";
	cin >> option;

	switch (option)
	{
	case '1':
	{
		addNewWord();
		break;
	}
	case '2':
	{
		changeBackground();
		break;
	}
	default:
	{
		time_t InvalidInputBuffer = time(NULL);
		cout << "\nInvalid Input!";
		while (time(NULL) - InvalidInputBuffer < 2) {}
		system("CLS");
		settings();
	}
	}
}
// This is included in settings For changing the background color
void changeBackground()
{
	char option;
	system("CLS");
	faceDisplay();
	cout << "Select a color: " << endl;
	cout << "1. Red background // Black text." << endl;
	cout << "2. Green background // Black text." << endl;
	cout << "3. Yellow background // Black text." << endl;
	cout << "4. White background // Black text." << endl;
	cout << "5. Blue background // White text." << endl << endl;
	cout << "Option: ";
	cin >> option;

	switch (option)
	{
	case '1':
	{
		system("color 40");//Here the number 4 represents the red background and 0 represents black text
		break;
	}
	case '2':
	{
		system("color 20");
		break;
	}
	case '3':
	{
		system("color 60");
		break;
	}
	case '4':
	{
		system("color 70");
		break;
	}
	case '5':
	{
		system("color 17");
		break;
	}
	default:
	{
		time_t InvalidInputBuffer = time(NULL);
		cout << "\nInvalid Input!";
		while (time(NULL) - InvalidInputBuffer < 2) {}
		system("CLS");
		changeBackground();
	}
	}
	cout << "\n\nChanges applied!" << endl;
	returnToMainMenu();
	system("CLS");
	mainScreen();
}
// *About* that you saw in  the first page of our game 
void about()
{
	char check;
	system("CLS");
	faceDisplay();
	std::cout << "Hangman Instructions: " << endl;
	std::cout << "1. Word Czar chooses a word.\n";
	std::cout << "2. The Guesser is tasked to guess the word letter by letter.\n";
	std::cout << "3. For every wrong guess of a letter, a part of body on the hangman is drawn.\n";
	std::cout << "4. The Guesser has to guess all the letters within the word before the hangman is fully drawn.\n\n";
	std::cout << "\nCredits:\n1. Muhammad Shaheer Ahmad\n2. Muhammad Ezaan Ali\n3. Muhammad Zain Amjad\n\n";
	std::cout << "Return to Main Menu (Press Y): ";
	cin >> check;
	if (check == 'Y' || check == 'y')
	{
		system("CLS");
		mainScreen();
	}
	else
	{
		about();
	}
}
// As we provided 7 chances to guess a word so here a 7 cases that basically display the hand man when the uses enters a wrong alphabet.
void drawHangman(int wrongCount)
{
	switch (wrongCount)
	{
	case 1:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;

	case 2:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "  O   |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;

	case 3:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "  O   |" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;

	case 4:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "  O   |" << endl;
		std::cout << " /|   |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;

	case 5:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "  O   |" << endl;
		std::cout << " /|\\  |" << endl;
		std::cout << "      |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;

	case 6:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "  O   |" << endl;
		std::cout << " /|\\  |" << endl;
		std::cout << " /    |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;

	case 7:
		std::cout << "  +---+" << endl;
		std::cout << "  |   |" << endl;
		std::cout << "  O   |" << endl;
		std::cout << " /|\\  |" << endl;
		std::cout << " / \\  |" << endl;
		std::cout << "      |" << endl;
		std::cout << "=========" << endl;
		break;
	}
}


void guessWord(string word)
{
	system("CLS");
	const int wordLength = word.length();
	int wrongCount = 0;
	string guess;
	string guessChar;
	bool guessed = false;
	string correctLettersArray;
	string wrongLettersArray;
	int wrongIndex = 0;
	int correctIndex = 0;
	string caseSensWord;
	int tempWordLength;
	string blankSpace = " ";
	int spaceCount = 0;
	string tempWord;
	int count = 0;

	tempWord = word;
	tempWordLength = wordLength;

	for (int i = 0; i < wordLength; i++)
	{
		if (word[i] == blankSpace[0])
		{
			spaceCount++;
		}
	}

	tempWordLength = tempWordLength - spaceCount;

	tempWord.erase(remove(tempWord.begin(), tempWord.end(), ' '), tempWord.end());

	faceDisplay();
	for (int i = 0; i < wordLength; i++)
	{
		if (word[i] == blankSpace[0])
		{
			std::cout << "  ";
		}
		else
			std::cout << "_ ";
	}

	bool guessWrong = 1;

	while (wrongCount != 7)
	{
		guessWrong = 1;
		std::cout << endl << "Your guess: ";

		cin >> guess;

		if (guess.length() != 1)
		{
			Beep(100, 500);// A beep will be heard 
			std::cout << "One letter at a time!" << endl;
			continue;
		}

		for (int i = 0; i < tempWordLength; i++)
		{
			if ((guess[0] - 32) == tempWord[i] || (guess[0] + 32) == tempWord[i] || tempWord[i] == guess[0])
			{
				caseSensWord = tempWord[i];
				bool check = 0;
				guessChar.append(caseSensWord);
				guessWrong = 0;
				for (int k = 0; k < correctLettersArray.length(); k++)
				{
					if (correctLettersArray[k] == tempWord[i])
					{
						check = 1;
					}
				}
				if (check == 0)
				{
					Beep(500, 500);
					correctLettersArray.append(caseSensWord);
				}
			}
		}
		if (guessWrong == 1)
		{
			bool check = 0;
			for (int k = 0; k < wrongLettersArray.length(); k++)
			{
				if (wrongLettersArray[k] == guess[0])
				{
					check = 1;
				}
			}
			if (check == 0)
			{
				wrongLettersArray.append(guess);
				wrongCount++;
				Beep(100, 500);
				std::cout << "No letter matched! Try again. You have " << 7 - wrongCount << "/" << 7 << " chances left." << endl;
			}
			if (check == 1)
			{
				Beep(100, 500);
				std::cout << "You've already guessed this letter!" << endl;
			}
			time_t buffer = time(NULL);
			while (time(NULL) - buffer < 2) {}
			system("CLS");
			faceDisplay();
			if (wrongCount <= 7)
			{
				drawHangman(wrongCount);
			}
			for (int i = 0; i < wordLength; i++)
			{
				bool isWordGuessed = false;
				for (int j = 0; j < guessChar.length(); j++)
				{
					if (word[i] == guessChar[j])
					{
						isWordGuessed = true;
					}
				}
				if (isWordGuessed == false && word[i] == blankSpace[0])
				{
					std::cout << "  ";
				}
				else if (isWordGuessed == false)
				{
					std::cout << "_ ";
				}
				else
				{
					std::cout << word[i] << " ";
				}
			}
			std::cout << endl;
			displayGuessedLetters(correctLettersArray, wrongLettersArray);
		}
		else
		{
			system("CLS");
			faceDisplay();
			drawHangman(wrongCount);
			int correctGuessed = 0;

			for (int i = 0; i < wordLength; i++)
			{
				bool isWordGuessed = false;
				for (int j = 0; j < guessChar.length(); j++)
				{
					if (word[i] == guessChar[j])
					{
						isWordGuessed = true;
					}
				}
				if (isWordGuessed == false && word[i] == blankSpace[0])
				{
					std::cout << "  ";
				}
				else if (isWordGuessed == false)
				{
					std::cout << "_ ";
				}
				else
				{
					std::cout << word[i] << " ";
					correctGuessed++;
				}
			}
			std::cout << endl;
			displayGuessedLetters(correctLettersArray, wrongLettersArray);
			if (correctGuessed == tempWordLength)
			{
				guessed = true;
				break;
			}
		}
	}

	if (guessed == true)
	{
		Beep(500, 500);
		Beep(500, 500);
		std::cout << "\nYou guessed the word!" << endl;
	}
	else
	{
		Beep(100, 500);
		Beep(100, 500);
		std::cout << "\nYou ran out of your guessing chances!\n";
		std::cout << "The word was: " << word << endl;
	}

	returnToMainMenu();

	system("CLS");
	mainScreen();

	return;
}

void displayGuessedLetters(string correctLettersArray, string wrongLettersArray)
{
	std::cout << "\nCorrect Letters Tried: ";
	for (int i = 0; i < correctLettersArray.length(); i++)
	{
		std::cout << correctLettersArray[i] << ", ";
	}
	std::cout << endl;
	std::cout << "Wrong Letters Tried: ";
	for (int i = 0; i < wrongLettersArray.length(); i++)
	{
		std::cout << wrongLettersArray[i] << ", ";
	}
	std::cout << endl;

	return;
}

void returnToMainMenu()
{
	time_t returnToMenu = time(NULL);
	std::cout << "You will be returned to the main menu in 3";
	returnToMenu = time(NULL);

	while (time(NULL) - returnToMenu < 1) {}
	std::cout << "\rYou will be returned to the main menu in 2";
	returnToMenu = time(NULL);

	while (time(NULL) - returnToMenu < 1) {}
	std::cout << "\rYou will be returned to the main menu in 1";
	returnToMenu = time(NULL);
	while (time(NULL) - returnToMenu < 1) {}
}