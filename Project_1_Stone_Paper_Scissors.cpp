
#include <iostream>
using namespace std;

enum enGameChoice{ Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo{

    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
   short GameRounds = 0, Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
   enWinner GameWinner;
   string WinnerName;
};

int RandomNumber(int From, int To) {
    int random = rand() % (To - From + 1) + From;
    return random;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

string Tabs(short NumberOfTabs) {
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++) {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen() {
    cout << endl;
        cout << Tabs(2) << "-----------------------------------------------------------------------\n";
        cout << Tabs(3) << "+++ G a m e O v e r +++\n";
        cout << Tabs(2) << "-----------------------------------------------------------------------\n";
}

short ReadHowManyRounds() {
    short Rounds = 1;
    do {
        cout << "How Many Rounds 1 To 10 ? \n";
        cin >> Rounds;
    } while (Rounds <=0 || Rounds > 10);

    return Rounds;
}

enGameChoice ReadPlayer1Choice() {
    short Choice;
    do {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone: {
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
           return enWinner::Computer;
        break;
    };
    case enGameChoice::Paper: {
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enWinner::Computer;
        break;
    };
    case enGameChoice::Scissors: {
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }
    }
    //if you reached here then player1 is the winner
    return enWinner::Player1;
}

string WinnerName(enWinner Winner) {
    string arrWinnerName[3] = { "Player1", "Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes) {
    if (Player1WonTimes > ComputerWonTimes)
        return enWinner::Player1;
    else if (ComputerWonTimes > Player1WonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short HowManyRounds, short Player1WonTimes, short ComputerWonTimes, short DrawTimes) {
    stGameResults GameResults;
    GameResults.GameRounds = HowManyRounds;
    GameResults.Player1WonTimes = Player1WonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WonTimes,ComputerWonTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

string ChoiceName(enGameChoice Choice) {
    string arrChoiceName[3] = { "Stone","Paper","Scissors" };
    return arrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner) {
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;

    case enWinner::Computer: {
        system("color 4F");
        cout << "\a";
        break;
    }
    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo) {
       cout << "\n___________ Round [" << RoundInfo.RoundNumber << "] ____________________________\n\n";
       cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
       cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
       cout << "Round Winner: [" << RoundInfo.WinnerName << "]" << endl;
       cout << "__________________________________________________\n" << endl;

       SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++) {
        cout << "\nRound [" << GameRounds << "] begins: \n";
        RoundInfo.RoundNumber = GameRounds;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        //Increese win/draw Counters
        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "--------------------------- [ Game Results ] --------------------------\n";
    cout << Tabs(2) << "Game Rounds         : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times   : " << GameResults.Player1WonTimes << endl;
    cout << Tabs(2) << "Computer won times  : " << GameResults.ComputerWonTimes << endl;
    cout << Tabs(2) << "Draw times          : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner        : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "-----------------------------------------------------------------------\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << endl << Tabs(3) << "Do you wnat to play again ? Y/N ?";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
}


//My Code
//enum enGameData { Stone = 1, Paper = 2, Scissors = 3 };
//
//struct stGameResults
//{
//    short GameRounds = 0, Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
//    string FinalWinner;
//};
//
//int RandomNumber(int From, int To) {
//    int random = rand() % (To - From + 1) + From;
//    return random;
//}
//
//short ReadNumberOfRounds() {
//    short rounds;
//    cout << "How Many Rounds 1 To 10 ?\n";
//    cin >> rounds;
//
//    return rounds;
//}
//
//string CheckChoice(short choice) {
//    if (choice == enGameData::Stone)
//        return "Stone";
//    else if (choice == enGameData::Paper)
//        return "Paper";
//    else if (choice == enGameData::Scissors)
//        return "Scissors";
//}
//
//string CheckWinner(short Player1, short Computer, stGameResults& GameResults) {
//    switch (Player1)
//    {
//    case enGameData::Stone: {
//        if (Computer == enGameData::Stone) {
//            //Yellow
//            system("Color 67");
//            GameResults.DrawTimes++;
//            return "No Winner";
//        }
//        else if (Computer == enGameData::Paper) {
//            //Red
//            cout << "\a";
//            system("Color 47");
//            GameResults.ComputerWonTimes++;
//            return "Computer";
//        }
//        else if (Computer == enGameData::Scissors) {
//            //Green
//            system("Color 27");
//            GameResults.Player1WonTimes++;
//            return "Player 1";
//        }
//    }
//    case enGameData::Paper: {
//        if (Computer == enGameData::Stone) {
//            //Green
//            system("Color 27");
//            GameResults.Player1WonTimes++;
//            return "Player 1";
//        }
//        else if (Computer == enGameData::Paper) {
//            //Yellow
//            system("Color 67");
//            GameResults.DrawTimes++;
//            return "No Winner";
//        }
//        else if (Computer == enGameData::Scissors) {
//            //Red
//            cout << "\a";
//            system("Color 47");
//            GameResults.ComputerWonTimes++;
//            return "Computer";
//        }
//    }
//    case enGameData::Scissors: {
//        if (Computer == enGameData::Stone) {
//            //Red
//            cout << "\a";
//            system("Color 47");
//            GameResults.ComputerWonTimes++;
//            return "Computer";
//        }
//        else if (Computer == enGameData::Paper) {
//            //Green
//            system("Color 27");
//            GameResults.Player1WonTimes++;
//            return "Player 1";
//        }
//        else if (Computer == enGameData::Scissors) {
//            //Yellow
//            system("Color 67");
//            GameResults.DrawTimes++;
//            return "No Winner";
//        }
//    }
//    default:
//        break;
//    }
//}
//
//string GetFinalWinner(stGameResults GameResults) {
//    if (GameResults.Player1WonTimes > GameResults.ComputerWonTimes) {
//        if (GameResults.Player1WonTimes >= GameResults.DrawTimes)
//            return "Player1";
//        else
//            return "No Winner";
//    }
//    else if (GameResults.ComputerWonTimes >= GameResults.DrawTimes)
//        return "Computer";
//    else
//        return "No Winner";
//}
//
//void PrintHeader(stGameResults GameResults) {
//    cout << endl;
//    cout << "\t\t\t" << "-----------------------------------------------------------------------\n";
//    cout << "\t\t\t\t\t\t" << "+++ G a m e O v e r +++\n";
//    cout << "\t\t\t" << "-----------------------------------------------------------------------\n";
//    cout << "\t\t\t" << "--------------------------- [ Game Results ] --------------------------\n";
//    cout << "\t\t\t" << "Game Rounds \t\t : " << GameResults.GameRounds << endl;
//    cout << "\t\t\t" << "Player1 won times \t : " << GameResults.Player1WonTimes << endl;
//    cout << "\t\t\t" << "Computer won times \t : " << GameResults.ComputerWonTimes << endl;
//    cout << "\t\t\t" << "Draw times \t\t : " << GameResults.DrawTimes << endl;
//    cout << "\t\t\t" << "Final Winner \t\t : " << GetFinalWinner(GameResults) << endl;
//    cout << "\t\t\t" << "-----------------------------------------------------------------------\n";
//
//}
//
//void PrintRoundResult(short player1, short computer, short round, stGameResults& GameResults) {
//    cout << "\n\n";
//    cout << "___________ Round [" << round << "] ____________________________\n\n";
//    cout << "Player1 Choice: " << CheckChoice(player1) << endl;
//    cout << "Computer Choice: " << CheckChoice(computer) << endl;
//    cout << "Round Winner: [" << CheckWinner(player1, computer, GameResults) << "]" << endl;
//    cout << "\n__________________________________________________\n";
//}
//
//void Choice(short Rounds, stGameResults& GameResults) {
//
//    short Player1;
//    short computer;
//    for (int i = 1; i <= Rounds; i++) {
//        cout << "\nRound [" << i << "] begins: \n";
//        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
//        cin >> Player1;
//        computer = RandomNumber(1, 3);
//        GameResults.GameRounds++;
//        PrintRoundResult(Player1, computer, i, GameResults);
//    }
//
//    cout << endl;
//}
//
//void NewGame(stGameResults& GameResults) {
//    GameResults.ComputerWonTimes = 0;
//    GameResults.Player1WonTimes = 0;
//    GameResults.DrawTimes = 0;
//    GameResults.GameRounds = 0;
//    GameResults.FinalWinner = "";
//}
//
//void StartTheGame() {
//    char PlayAgain;
//    stGameResults GameResults;
//    do {
//        system("cls");
//        system("Color 07");
//        NewGame(GameResults);
//        Choice(ReadNumberOfRounds(), GameResults);
//        PrintHeader(GameResults);
//        cout << "\t\t\t" << "Do you wnat to play again ? Y/N ?";
//        cin >> PlayAgain;
//    } while (PlayAgain == 'Y' || PlayAgain == 'y');
//}
