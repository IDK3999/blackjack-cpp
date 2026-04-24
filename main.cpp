#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "game.cpp"
using namespace std;

void displayHelp(){
    cout << "Commands:" << endl;
    cout << "m - Show this help message" << endl;
    cout << "q - Quit the program" << endl;
    cout << "n - new game" << endl;
    cout << "s - show stats" << endl;
    cout << "R - reset stats" << endl;
}

int main(){
    srand(static_cast<unsigned>(time(nullptr)));

    ifstream input("stats.txt");
    long long balance, highscore;
    int gamesPlayed;
    input >> balance >> highscore >> gamesPlayed;
    input.close();
    cout << "Balance: " << balance << endl;
    cout << "Highscore: " << highscore << endl;
    cout << "Games Played: " << gamesPlayed << endl;
    char choice = '\0';
    while (choice != 'q') {
        cout << "Enter command. (\"m\" for help, \"q\" to quit): ";
        cin >> choice;
        if (choice == 'm') {
            displayHelp();
            continue;
        }
        if(choice == 's') {
            cout << "Balance: " << balance << endl;
            cout << "Highscore: " << highscore << endl;
            cout << "Games Played: " << gamesPlayed << endl;
            continue;
        }
        if(choice == 'R'){
            cout << "Are you sure you want to reset your stats?";
            cout << "This action cannot be undone!!!" << endl;
            cout << "Type \"yes\" to confirm." << endl;
            string answer;
            cin >> answer;
            if(answer == "yes"){
                system("./reset.sh");
                balance = 100;
                highscore = 0;
                gamesPlayed = 0;
                cout << "Stats reset." << endl;
            }
            else{
                cout << "Stats not reset." << endl;
            }
            return 0;
        }
        if(choice == 'n') {
                initGame();
                gameplay(bet_period(balance), balance);
                if(balance > highscore) highscore = balance;
                gamesPlayed++;
                ofstream output("stats.txt");
                output << balance << endl;
                output << highscore << endl;
                output << gamesPlayed << endl;
                output.close();
            }
        if(balance <= 0){
            cout << "You have no more money to bet. Game over!" << endl;
            cout << "Do you want to save your stats to another file? (Type \"yes\" or \"no\")" << endl;
            string answer;
            cin >> answer;
            if(answer == "yes"){
                system("./save_stats.sh");
            }
            system("./reset.sh");
            return 0;
        }
    }
    return 0;
}