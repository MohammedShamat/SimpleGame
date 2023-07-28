#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;

enum enGameChoice {
	Stone = 1, Paper = 2, Scissors = 3,
};

enum enWinner {
	Player = 1, Computer = 2, Draw = 3
};

short ReadHowManyRounds() {
	short gameRounds = 1;
	cout << "How Many Rounds From 1 To 10 ?\n";
	cin >> gameRounds;
	while (cin.fail() || (gameRounds < 1 || gameRounds>10)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid value, Enter a valid one\n";
		cin >> gameRounds;
	}
	return gameRounds;
}

short RandomNumber(short from, short to) {
	srand((unsigned)time(NULL));
	short randomNumber = rand() % (to - from + 1) + from;
	return randomNumber;
}

struct stRoundInfo {
	short roundNumber = 0;
	enGameChoice playerChoice;
	enGameChoice computerChoice;
	enWinner winner;
	string winnerName = "";
};

struct stGameResults {
	short gameRounds = 0;
	short playerWinTimes = 0;
	short computerWinTimes = 0;
	short drawTimes = 0;
	enWinner gameWinner;
	string winnerName = "";
};

enGameChoice ReadPlayerChoice() {
	short choice = 1;
	cout << "\nYour Choice: [1] Stone,[2] Paper,[3]Scissors ?";
	cin >> choice;
	while (cin.fail() || (choice < 1 || choice>3)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid value, Enter a valid one\n";
		cin >> choice;
	}
	return (enGameChoice)choice;
}

enGameChoice GetComputerChoice() {
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo roundInfo) {
	if (roundInfo.playerChoice == roundInfo.computerChoice) {
		return enWinner::Draw;
	}
	switch (roundInfo.playerChoice) {
	case  enGameChoice::Stone:
		if (roundInfo.computerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (roundInfo.computerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (roundInfo.computerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;

}

string WinnerName(enWinner winner) {
	string arrWinnerName[3] = { "Player","Computer","Draw" };
	return arrWinnerName[winner - 1];
}

string ChoiceName(enGameChoice choice) {
	string arrGameChoices[3] = { "Stone","Paper","Scissors" };
	return arrGameChoices[choice - 1];
}

void SetWinnerScreenColor(enWinner winner) {

	switch (winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}


}

void showRoundResults(stRoundInfo roundInfo) {
	cout << "\n__________Round [" << roundInfo.roundNumber << "]__________\n\n";
	cout << "Player Choice      : " << ChoiceName(roundInfo.playerChoice) << endl;
	cout << "Computer Choice    : " << ChoiceName(roundInfo.computerChoice) << endl;
	cout << "Round Winner       : [" << roundInfo.winnerName << "] \n";
	cout << "_____________________________\n" << endl;
	SetWinnerScreenColor(roundInfo.winner);
}

enWinner WhoWonTheGame(short playerWinTimes, short computerWinTimes) {
	if (playerWinTimes > computerWinTimes) {
		return enWinner::Player;
	}
	else if (playerWinTimes < computerWinTimes) {
		return enWinner::Computer;
	}
	else {
		return enWinner::Draw;
	}
}

stGameResults FillGameResults(int gameRounds, short playerWinTimes, short computerWinTimes, short drawTimes) {

	stGameResults gameResults;
	gameResults.gameRounds = gameRounds;
	gameResults.playerWinTimes = playerWinTimes;
	gameResults.computerWinTimes = computerWinTimes;
	gameResults.drawTimes = drawTimes;
	gameResults.gameWinner = WhoWonTheGame(playerWinTimes, computerWinTimes);
	gameResults.winnerName = WinnerName(gameResults.gameWinner);
	return gameResults;
}

stGameResults PlayGame(short howManyRounds) {
	stRoundInfo roundInfo;
	short playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;

	for (short gameRound = 1; gameRound <= howManyRounds; gameRound++) {
		cout << "\nRound [" << gameRound << "] begins:\n";
		roundInfo.roundNumber = gameRound;
		roundInfo.playerChoice = ReadPlayerChoice();
		roundInfo.computerChoice = GetComputerChoice();
		roundInfo.winner = WhoWonTheRound(roundInfo);
		roundInfo.winnerName = WinnerName(roundInfo.winner);

		if (roundInfo.winner == enWinner::Player) {
			playerWinTimes++;
		}
		else if (roundInfo.winner == enWinner::Computer) {
			computerWinTimes++;
		}
		else {
			drawTimes++;
		}
		showRoundResults(roundInfo);
	}
	return FillGameResults(howManyRounds, playerWinTimes, computerWinTimes, drawTimes);
}

string Tabs(short numbersOfTabs) {
	string tabs = "";
	for (short counter = 1; counter < numbersOfTabs; counter++) {
		tabs = tabs + "\t";
		cout << tabs;
	}
	return tabs;
}

void ShowGameOverScreen() {
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                    +++ Game Over +++                \n\n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults gameResults) {

	cout << Tabs(2) << "_____________________[Game Results]_______________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << gameResults.gameRounds << endl;
	cout << Tabs(2) << "Player Won Times   : " << gameResults.playerWinTimes << endl;
	cout << Tabs(2) << "Computer Won Times : " << gameResults.computerWinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << gameResults.drawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << gameResults.winnerName << endl;
	cout << Tabs(2) << "__________________________________________________________" << endl;
	SetWinnerScreenColor(gameResults.gameWinner);

}


void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame() {
	char playAgain = 'Y';
	do {
		ResetScreen();
		stGameResults gameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(gameResults);
		cout << endl << Tabs(3) << "Do You Want To Play Again ? Y/N ?";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');
}
int main() {

	StartGame();


	return 0;

}/*
 output...
How Many Rounds From 1 To 10 ?
asdf
Invalid value, Enter a valid one
-99
Invalid value, Enter a valid one
0
Invalid value, Enter a valid one
2

Round [1] begins:

Your Choice: [1] Stone,[2] Paper,[3]Scissors ?2

__________Round [1]__________

Player Choice      : Paper
Computer Choice    : Stone
Round Winner       : [Player]
_____________________________


Round [2] begins:

Your Choice: [1] Stone,[2] Paper,[3]Scissors ?3

__________Round [2]__________

Player Choice      : Scissors
Computer Choice    : Stone
Round Winner       : [Computer]
_____________________________

				__________________________________________________________

									+++ Game Over +++

				__________________________________________________________

				_____________________[Game Results]_______________________

				Game Rounds        : 2
				Player Won Times   : 1
				Computer Won Times : 1
				Draw Times         : 0
				Final Winner       : Draw
				__________________________________________________________

				Do You Want To Play Again ? Y/N ?
 */