#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;

enum TypeOfChoice {
	Stone = 1,
	Paper = 2,
	Scissor = 3,
};
enum Result {
	ComputerWinner = 1,
	UserWinner = 2,
	Draw = 3,
};
struct counterOfResult {
	short computerWinner;
	short userWinner;
	short draw;
};

short readRoundFromUser(string message) {
	short round = 1;

	cout << message << endl;
	cin >> round;
	while (cin.fail() || round <= 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> round;
	}
	return round;
}
short randomNumber(short from, short to) {
	srand((unsigned)time(NULL));
	short randomNumber = rand() % (to - from + 1) + from;
	return randomNumber;
}
TypeOfChoice choiceFromUser(string message) {
	short typeOfGamesUser;
	TypeOfChoice enTypeOfGames;
	cout << message << endl;
	cin >> typeOfGamesUser;
	while (cin.fail() || (typeOfGamesUser <= 0 || typeOfGamesUser > 3)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> typeOfGamesUser;
	}
	enTypeOfGames = (TypeOfChoice)typeOfGamesUser;
	return enTypeOfGames;

}
TypeOfChoice ChoiceFromComputer() {
	short typeOfGamesFromComputer = randomNumber(1, 3);
	TypeOfChoice enTypeOfGames;
	enTypeOfGames = (TypeOfChoice)typeOfGamesFromComputer;
	return enTypeOfGames;
}


void printChoice(TypeOfChoice choice, string message) {
	cout << message;
	switch (choice)
	{
	case TypeOfChoice::Stone:
		cout << "Stone\n";
		break;
	case TypeOfChoice::Paper:
		cout << "Paper\n";
		break;
	case TypeOfChoice::Scissor:
		cout << "Scissor\n";
		break;
	default:
		cout << "Opps Error";
		break;
	}
}
Result WhoWinnerEachRound(TypeOfChoice fromUser, TypeOfChoice fromComputer) {
	if (fromUser == TypeOfChoice::Paper && fromComputer == TypeOfChoice::Scissor) {
		return Result::ComputerWinner;
	}
	else if (fromUser == TypeOfChoice::Paper && fromComputer == TypeOfChoice::Stone) {
		return Result::UserWinner;
	}
	else if (fromUser == TypeOfChoice::Paper && fromComputer == TypeOfChoice::Paper) {
		return Result::Draw;
	}
	else if (fromUser == TypeOfChoice::Scissor && fromComputer == TypeOfChoice::Scissor) {
		return Result::Draw;
	}
	else if (fromUser == TypeOfChoice::Scissor && fromComputer == TypeOfChoice::Paper) {
		return Result::UserWinner;
	}
	else if (fromUser == TypeOfChoice::Scissor && fromComputer == TypeOfChoice::Stone) {
		return Result::ComputerWinner;
	}
	else if (fromUser == TypeOfChoice::Stone && fromComputer == TypeOfChoice::Scissor) {
		return Result::UserWinner;
	}
	else if (fromUser == TypeOfChoice::Stone && fromComputer == TypeOfChoice::Stone) {
		return Result::Draw;
	}
	else if (fromUser == TypeOfChoice::Stone && fromComputer == TypeOfChoice::Paper) {
		return Result::ComputerWinner;
	}

}
string ResultAfterEachRound(Result whoIsWinner) {
	string winner = "";
	switch (whoIsWinner)
	{
	case Result::ComputerWinner:
		winner = "[Computer Winner]";
		system("color 4F");
		cout << '\a';
		return winner;

	case Result::UserWinner:
		winner = "[Player 1 Winner]";
		system("color 2F");
		return winner;

	default:
		winner = "[Draw]";
		system("color 6F");
		return winner;
	}
}

char restartGame() {

	char restart = 'y';

	cout << "\t\t\tDo you want to play again ? y/n ";
	cin >> restart;

	return restart;
}


void roundOfGames(short roundGames, counterOfResult& finalResult) {
	Result WhoIsWinner;
	TypeOfChoice choiceFromPlayer;
	TypeOfChoice choiceFromComputer;

	finalResult.computerWinner = 0;
	finalResult.userWinner = 0;
	finalResult.draw = 0;
	for (short round = 1; round <= roundGames; round++) {
		cout << "\nRounds {" << round << "}" << "begins :\n" << endl;
		choiceFromPlayer = choiceFromUser("Your Choice : {1} Stone,{2} Paper,{3}Scissors ? ");
		choiceFromComputer = ChoiceFromComputer();
		cout << "__________Round {" << round << "} __________\n\n";
		printChoice(choiceFromPlayer, "choice OF Player is :\t");
		printChoice(choiceFromComputer, "choice OF Computer is :\t");
		WhoIsWinner = WhoWinnerEachRound(choiceFromPlayer, choiceFromComputer);

		if (ResultAfterEachRound(WhoIsWinner) == "[Computer Winner]") {
			finalResult.computerWinner += 1;
		}
		else if (ResultAfterEachRound(WhoIsWinner) == "[Player 1 Winner]") {
			finalResult.userWinner += 1;
		}
		else if (ResultAfterEachRound(WhoIsWinner) == "[Draw]") {
			finalResult.draw += 1;
		}

		cout << "Round Winner is : ";
		cout << ResultAfterEachRound(WhoIsWinner);
		cout << "\n________________________________________________\n\n\n";
	}

}
string finalWinner(counterOfResult result) {

	if (result.computerWinner > result.userWinner) {
		return "Winner is Computer";
	}
	else if (result.computerWinner < result.userWinner) {
		return "Winner is Player";
	}
	else {
		return "Draw No Winner";
	}
}
void gameOverScreen(short roundOfGame, counterOfResult result) {
	cout << "\t\t\t__________________________________________________________________\n";
	cout << "\n\t\t\t\t\t\t+++ Game Over +++\t\t\t\t\t\t\t";
	cout << "\t\t\t\t__________________________________________________________________\n\n";
	cout << "\t\t\t_________________________ { Game Results } _______________________\n\n\n";
	cout << "\t\t\tGame Rounds         :" << roundOfGame << endl;
	cout << "\t\t\tPlayer 1 Won times  :" << result.userWinner << endl;
	cout << "\t\t\tComputer Won Times  :" << result.computerWinner << endl;
	cout << "\t\t\tDraw Times          :" << result.draw << endl;
	cout << "\t\t\tFinal Winner        :" << finalWinner(result) << endl;
	cout << "\t\t\t__________________________________________________________________\n" << endl;

}
void resetScreen() {
	system("color 0F");
	system("cls");
}

void startGame() {
	char resetGame;
	do {
		resetScreen();
		short roundFromUser = readRoundFromUser("How Many Rounds do you want?");
		counterOfResult counter;
		roundOfGames(roundFromUser, counter);
		gameOverScreen(roundFromUser, counter);
		resetGame = restartGame();
	} while (resetGame == 'y' || resetGame == 'Y');



}


int main() {

	startGame();

	return 0;

}/*

 How Many Rounds do you want?
ffs
Invalid Number, Enter a valid one
-99
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
3

Rounds {1}begins :

Your Choice : {1} Stone,{2} Paper,{3}Scissors ?
-99
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
;mm
Invalid Number, Enter a valid one
4
Invalid Number, Enter a valid one
1
__________Round {1} __________

choice OF Player is :   Stone
choice OF Computer is : Scissor
Round Winner is : [Player 1 Winner]
________________________________________________



Rounds {2}begins :

Your Choice : {1} Stone,{2} Paper,{3}Scissors ?
3
__________Round {2} __________

choice OF Player is :   Scissor
choice OF Computer is : Scissor
Round Winner is : [Draw]
________________________________________________



Rounds {3}begins :

Your Choice : {1} Stone,{2} Paper,{3}Scissors ?
ohuo
Invalid Number, Enter a valid one
-99
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
2
__________Round {3} __________

choice OF Player is :   Paper
choice OF Computer is : Paper
Round Winner is : [Draw]
________________________________________________


						__________________________________________________________________

												+++ Game Over +++
						__________________________________________________________________

						_________________________ { Game Results } _______________________


						Game Rounds         :3
						Player 1 Won times  :1
						Computer Won Times  :0
						Draw Times          :2
						Final Winner        :Winner is Player
						__________________________________________________________________

						Do you want to play again ? y/n
 
 */