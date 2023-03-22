#include <iomanip>
#include <vector>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include<string>
#include <map>
#define MAT_RNG_MUL            214013L
#define MAT_RNG_ADD            2531011L

// Random seed global
unsigned int gvMathRandSeed;

using namespace std;

struct account{ 
	int money; 
	int wins; 
	int total_played; 
	double win_percentage; 
	string username;

};

// Struttura della carta
struct Card {
    int value;
    char type;
    bool up;
};

// Struttura giocatore
struct player{ 
    vector<Card> hand; 
    int bet; 
    int insurance_bet; 
    account info; 
};

Card deal(vector<Card>);
int score(vector<Card>);
void split(vector<player> &players, vector<Card> &cards);
bool hasAce(vector<Card>);
void printFirstCard(Card);
void printFirstCardNum(Card);//print colonna
void printGiocatore(vector<player>&);//print riga
string getCardGiocatore(vector<player>&);
string getStrategyCardGiocatore(vector<player>&, int c);
void printCards(vector<Card>, int n);
//int  winner(vector<player>&);
int  winner(player dealer, player &user);
void play(vector<player>&, vector<Card> &, int, double, double, map<string,map<string,bool>> , map<string,map<string,int>>);
Card pickCard(vector<Card> &cards, int position);
string getFirstCard(Card);

FILE * pFile;
const char* RTP_FILE =  "Rtp.tsv";
vector<string> DEALER_HEADER = { "2", "3", "4" ,"5" ,"6" ,"7" ,"8" ,"9" ,"10", "A"};
vector<string> PLAYER_HEADER = { "2", "3", "4" ,"5" ,"6" ,"7" ,"8" ,"9" ,"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "BJ", "A-9", "A-8", "A-7", "A-6", "A-5", "A-4", "A-3", "A-2", "A-A"};
vector<string> PLAYER_HEADERSplit = { "2", "3", "4" ,"5" ,"6" ,"7" ,"8" ,"9" ,"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "BJ", "A-9", "A-8", "A-7", "A-6", "A-5", "A-4", "A-3", "A-2", "A-A", "10-10", "9-9", "8-8", "7-7", "6-6", "5-5", "4-4", "3-3", "2-2"};
