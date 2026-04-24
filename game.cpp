#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

bool deck[52] = {false}; // To keep track of which cards have been dealt

string human_readable_card(int card){
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    return ranks[card % 13] + string(" of ") + suits[card / 13];
}

void initGame(){

    cout << "Welcome to Blackjack!" << endl;
    ifstream input(".hide_splash.txt");
    int hide_splash;
    input >> hide_splash;
    input.close();
    if(hide_splash) return;
    cout << "Would you like to read the rules? (Type \"yes\" or \"no\")" << endl;
    string answer;
    cin >> answer;
    if(answer == "no"){
        ofstream input(".hide_splash.txt");
        input << 1;
        input.close();
        return;
    }
    cout << "The goal of the game is to get as close to 21 as possible without going over." << endl;
    cout << "You will be dealt two cards, and you can choose to hit (get another card) or stand (keep your current hand)." << endl;
    cout << "The dealer will also be dealt two cards, but only one of them will be visible to you." << endl;
    cout << "The dealer will hit until they have at least 17 points." << endl;
    cout << "If you go over 21, you lose. If the dealer goes over 21, you win. If you have a higher hand than the dealer without going over 21, you win. If you have the same hand as the dealer, it's a tie." << endl;
    cout << "Good luck!" << endl;
    cout << "Type \"hide\" to mute the messages." << endl;
    
}

int bet_period(long long &balance){
    cout << "You have " << balance << " dollars." << endl;
    cout << "How much would you like to bet? (Enter a number)" << endl;
    long long bet;
    cin >> bet;
    while(bet > balance || bet <= 0){
        cout << "Invalid bet. Please enter a number between 1 and " << balance << "." << endl;
        cin >> bet;
    }
    return bet;
}

int calculateHand(const vector<int> &hand){
    int total = 0;
    int aces = 0;
    for(int card : hand){
        int value = card % 13;
        if(value >= 10) value = 10; // Face cards are worth 10
        if(value == 0) value = 11; // Aces are worth 11 initially
        total += value;
        if(value == 11) aces++;
    }
    // Adjust for aces if total is over 21
    while(total > 21 && aces > 0){
        total -= 10; // Count ace as 1 instead of 11
        aces--;
    }
    return total;
}

void gameplay(long long bet, long long &balance){
    vector<int> playerHand;
    vector<int> dealerHand;
    for(int i = 0; i < 52; i++) deck[i] = false;
    // Deal initial cards
    for(int i = 0; i < 2; i++){
        int card;
        do {
            card = rand() % 52;
        } while(deck[card]);
        deck[card] = true;
        playerHand.push_back(card);
    }
    if(calculateHand(playerHand) == 21){
        cout << "Blackjack! You win!" << endl;
        balance += static_cast<int>(bet * 1.5);
        return;
    }
    int card;
    do {
        card = rand() % 52;
    } while(deck[card]);
    deck[card] = true;
    dealerHand.push_back(card);
    cout << "Your cards: " << human_readable_card(playerHand[0]) << " and " << human_readable_card(playerHand[1]) << endl;
    cout << "Your total: " << calculateHand(playerHand) << endl;
    cout << "Dealer's visible card: " << human_readable_card(dealerHand[0]) << endl;
    // Player's turn
    string action;
    while(true){
        cout << "Do you want to hit or stand? (Enter 'hit' or 'stand')" << endl;
        cin >> action;
        if(action == "hit"){
            int card;
            do {
                card = rand() % 52;
            } while(deck[card]);
            deck[card] = true;
            playerHand.push_back(card);
            cout << "You drew a " << human_readable_card(card) << endl;
            if(calculateHand(playerHand) > 21){
                cout << "You went over 21! You lose." << endl;
                balance -= bet;
                return;
            }
            cout << "Your total: " << calculateHand(playerHand) << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(action == "stand"){
            break;
        }
        else{
            cout << "Invalid action. Please enter 'hit' or 'stand'." << endl;
        }
    }
    // Dealer's turn
    while(calculateHand(dealerHand) < 17){
        int card;
        do {
            card = rand() % 52;
        } while(deck[card]);
        deck[card] = true;
        dealerHand.push_back(card);
        cout << "Dealer drew a " << human_readable_card(card) << endl;
        cout << "Dealer's total: " << calculateHand(dealerHand) << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(calculateHand(dealerHand) > 21){
            cout << "Dealer busted! You win." << endl;
            balance += bet;
            return;
        }
    }
    // Compare hands
    int playerTotal = calculateHand(playerHand);
    int dealerTotal = calculateHand(dealerHand);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Your total: " << playerTotal << endl;
    cout << "Dealer's total: " << dealerTotal << endl;
    if(playerTotal > dealerTotal){
        cout << "You win!" << endl;
        balance += bet;
    }
    else if(playerTotal < dealerTotal){
        cout << "You lose!" << endl;
        balance -= bet;
    }
    else{
        cout << "It's a tie!" << endl;
    }
}