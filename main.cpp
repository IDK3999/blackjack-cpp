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
    cout << "a - toggle odds assist on/off" << endl;
    cout << "The odds give suggestions on whether to hit or not, but gives you only 3/4 of the normal payout if you win." << endl;
}

int main(){
    srand(static_cast<unsigned>(time(nullptr)));

    ifstream input("stats.txt");
    long long balance, highscore;
    int gamesPlayed;
    input >> balance >> highscore >> gamesPlayed;
    input.close();

    ifstream settings(".hide_splash.txt");
    int hide_splash = 0;
    settings >> hide_splash >> assistEnabled;
    settings.close();

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
        }        if(choice == 'a') {
            toggleAssist();
            continue;
        }        if(choice == 's') {
            cout << "Balance: " << balance << endl;
            cout << "Highscore: " << highscore << endl;
            cout << "Games Played: " << gamesPlayed << endl;
            cout << "Assist: " << (assistEnabled ? "on" : "off") << endl;
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
    }
    return 0;
}