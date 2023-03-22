/******************************************************************************

                    Black Jack game simulator.
               			 C++ program.

*******************************************************************************/
#include "BJprova.h"

/**
 * Calcola il punteggio della mano del giocatore nel caso abbia da tre a 9 carte 
 * come parametri
 * 
 * @param  players
 * @param  c
 * 
 * @return una string con il valore delle carte della mano 
 */
string getStrategyCardGiocatore(vector<player> &players, int c) { 
    string value;


 if (players[0].hand[0].value <=13){
    	for(int i = 1;i< players.size(); i++) { 
	        int playerNumber = i%players.size();
	        int playerScore = score(players[playerNumber].hand);
            if(players[i].hand.size()>(c-1)) {
                int manoStrategia = 0;
                stringstream ss;
                for(int n = 0; n < c; n++) { // calcola strategia giocatore fino alla c-esima carta
                    bool hasAce = false;
                    if(players[i].hand[n].value==1) hasAce = true;
                    if(players[i].hand[n].value >= 10) {//se é 10, J, Q, or K
                        manoStrategia = manoStrategia + 10; 
                    }
                    else {
                        manoStrategia =  manoStrategia + players[i].hand[n].value;
                    }
                }
                if(manoStrategia <22) {
                    ss << manoStrategia;
                    value = ss.str();
                }
                if (hasAce && manoStrategia <= 11) { //se nella mano ho un asso peró non sforo
		            manoStrategia  +=10; //aggiungo  10 asso vale 11
	            }
            }
                   
        }
    }
    
    return value;
}

/**
 * Calcola il punteggio della mano del giocatore nel caso abbia solo due carte (strategia con due carte) 
 * come parametri
 * 
 * @param vettore players
 *  
 * @return una string con il valore delle carte della mano (uso string per i casi "A-")
 */
string getCardGiocatore(vector<player> &players) {
    string value;
    if (players[0].hand[0].value <=13){
    	for(int i = 1;i< players.size(); i++) { 
	        int playerNumber = i%players.size();
	        int playerScore = score(players[playerNumber].hand);
                if (score(players[i].hand) == 100){
                        value ="BJ";
                    }
                if(!(players[i].hand[0].value == 1) && !(players[i].hand[1].value == 1)) { // se non ho asso nella prima ne seconda carta
                    int manoStrategia = 0;
                    stringstream ss;
                    if((players[i].hand[0].value == players[i].hand[1].value || (players[i].hand[0].value >=10 && players[i].hand[1].value>=10))) {
                        if(players[i].hand[0].value >= 10) value = "10-10";
                        else {
                            ss << players[i].hand[0].value;
                            value = ss.str()+"-"+ss.str();

                        }
                    }
                    else {
                            for(int n = 0; n < 2; n++) {
                                if(players[i].hand[n].value >= 10) {//se é 10, J, Q, or K
                                    manoStrategia = manoStrategia + 10; //prime due carte del giocatore per tabella
                                }
                                else {
                                    manoStrategia =  manoStrategia + players[i].hand[n].value;

                                }
                            }
                            ss << manoStrategia;
                            value = ss.str();
                        }
                }
                if((players[i].hand[0].value == 1 && players[i].hand[1].value<=9 && players[i].hand[1].value>1) || ( players[i].hand[1].value == 1 && players[i].hand[0].value<=9 && players[i].hand[0].value>1)) { 
                     for(int n=0; n<2; n++) {
                        stringstream ss;
                        if(players[i].hand[n].value!=1) {
                            ss << players[i].hand[n].value;
                            value = "A-" +ss.str();

                        }
                    }
                }   

                else if(players[i].hand[1].value==1 &&  players[i].hand[0].value==1) value ="A-A";
        }
    }
    return value;
}

/**
 * Stampa  la prima carta del banco 
 * come parametri
 * 
 * @param card
 * 
 */
void printFirstCard(Card card){
        switch (card.value) {
		        case 11 : printf("J%c ", card.type);
		        break;	  
		        case 12 : printf("Q%c ", card.type);
		        break;	  
		        case 13 : printf("K%c ", card.type);
		        break;
		        default : printf("%d%c " , card.value, card.type);
    	    }
        printf("\t");
}

/**
 * Calcola il valore della prima carta del banco 
 * come parametri
 * 
 * @param card
 * 
 * @return string con valore carta (uso string per casi con asso "A")
 */
string getFirstCard(Card card){
    string value;
    stringstream ss;
    if(card.value < 11 && card.value>1) {
        ss << card.value;
        value = ss.str();
    }
    else if(card.value > 10) 
        value = "10";
    else if(card.value == 1) 
        value = "A";
    return value;
}

/**
 * Stampa valori carte della mano
 * Le figure valgono 10, divido per colonna valore e seme
 * come parametri
 * 
 * @param cards
 * @param n
 * 
 */
void printCards(vector<Card> cards, int n) {
    for(int i = 0; i < n; i++) {
        if ( i < cards.size() ) {
            Card card = cards[i];
	        switch (card.value) {
		        case 11 : printf("10\t%c ", card.type);
		        break;	  
		        case 12 : printf("10\t%c ", card.type);
		        break;	  
		        case 13 : printf("10\t%c ", card.type);
		        break;
		        default : printf("%d\t%c " , card.value, card.type);
    	    }
        }
        else { 
        printf("\t");
        }
        printf("\t");
    }
}

/**
 *  
 * Generatore del random seed
 * 
 * @return random seed
 * 
 */
unsigned int CMWC1Random(void) {
    gvMathRandSeed = gvMathRandSeed * MAT_RNG_MUL + MAT_RNG_ADD;
    return(gvMathRandSeed);
}

/**
 *  
 * Reset random seed
 * 
 */
void resetSeed() {
    gvMathRandSeed = 0;
}

/**
 * Mischia le carte usando il random seed 
 * come parametri
 * 
 * @param cards
 * 
 */
void swapCards(vector<Card>& cards) {
    for(int i = 0; i < cards.size()-1; i++) {
        Card* card = &(cards[i]);          
        int j = CMWC1Random()%(cards.size() - 1);
        Card* cardRandom = &(cards[j]);
        int value = card->value;
        char type = card->type;         
        card->value = cardRandom->value;
        card->type = cardRandom->type;
        cardRandom->value = value;
        cardRandom->type = type;
    }
}
                                      
/**
 * Crea le carte basandosi sul numero di mazzi, typo e valori passati 
 * come parametri
 * 
 * @param packs
 * @param values
 * @param types
 * 
 * @return un array con tutte le carte generate 
 */
vector<Card> createCards(int packs, int values, vector<char> types) {
    // Vettore di carte 
    vector<Card> cards;
    // Aggiungo carte ordinate
    for(int pack = 0; pack < packs; pack++) {
        for(int i = 0; i < types.size(); i++) {
            for(int j = 1; j <= values; j++) {
                Card card;
                card.type = types[i];
                card.value = j;
                cards.push_back(card);
            }
        }
    }
    return cards;
}

/**
 * Funzione di gioco in cui viene applicata la strategia relativa alla tabella intermedia 
 * come parametri
 * 
 * @param players
 * @param cards
 * @param n
 * @param in
 * @param out
 * @param strategiaIntermediaSlit
 * 
 */
void play(vector<player> &players, vector<Card> &cards, int n, double in, double out, map<string,map<string,bool>> strategyIntermedia, map<string,map<string,int>> strategyIntermediaSplit){
    //Calcolo strategia tabella intermedia, per vedere se il giocatore chiede o sta
    for(int i = 0;i< players.size()*n; i++) { 
	    int playerNumber = i%players.size();
	    if  (players[playerNumber].hand.size() == 0)  { // se é la prima mano
      	    //Aggiunge la carta alla mano del giocatore
    		players[playerNumber].hand.push_back(deal(cards));
    	}
	}

    string cardBanco;
    string cardPlayer;
    string cardPlayerSplit;
    bool hasSplit=false;
    cardBanco = getFirstCard(players[0].hand[0]); 
    for(int i = 0;i< players.size()*n; i++) { 
	    int playerNumber = i%players.size();
	    int playerScore = score(players[playerNumber].hand);
        if(players[playerNumber].hand.size() == 0 || playerScore > 0) {
	        if ( playerNumber > 0 ) { //players (al momento è 1)
                 if ( players[playerNumber].hand.size() > 1 ) {
                    if ( players[1].hand.size() == 2) {
                        if((players.size()<3)) {//chiede carta o split
                            //se players.size() che dopo lo split sará 3 e non 2 {e > del player counter che é rimasto a 2, non entra nel if
                            cardPlayer = getCardGiocatore(players);
                            cardBanco = getFirstCard(players[0].hand[0]); 
                            if (strategyIntermediaSplit[cardPlayer][cardBanco] == 1) {
                                players[playerNumber].hand.push_back(deal(cards));
                            }
                            if (strategyIntermediaSplit[cardPlayer][cardBanco] == 2) {
 

                                split(players, cards);
                            }
                        }
                        else { //players[1].hand.size() == 2 peró ho 3 giocatori dopo il split
                            if(!(players[1].hand[0].value==1)) {//se lo split non è avvenuto con assi, chiedo carta sennó mi fermo
                                vector<player> user;
                                user.push_back(players[0]);
                                user.push_back(players[1]);
                                cardPlayer = getCardGiocatore(user);
                                cardBanco = getFirstCard(players[0].hand[0]); 
                                if(strategyIntermedia[cardPlayer][cardBanco]){
                                    players[1].hand.push_back(deal(cards));//playerNumber
                                } 
                                vector<player> userSplit;
                                userSplit.push_back(players[0]);
                                userSplit.push_back(players[2]);
                                cardPlayerSplit = getCardGiocatore(userSplit);
                                if(strategyIntermedia[cardPlayerSplit][cardBanco]){
                                    players[2].hand.push_back(deal(cards));
                                } 
                            }
                        }
                    }
                    else if( players[playerNumber].hand.size() > 2 && players[playerNumber].hand.size()< 10 ) {
                            cardPlayer = getStrategyCardGiocatore(players, players[playerNumber].hand.size());
                            if(strategyIntermediaSplit[cardPlayer][cardBanco]==1) players[playerNumber].hand.push_back(deal(cards));
                    }
                }
                else players[playerNumber].hand.push_back(deal(cards)); //Chiedo carta se ho una carta o meno
            }
            else { //dealer é player 0
                if ( playerScore < 17 )  players[playerNumber].hand.push_back(deal(cards));
            }
        }
    }
   
	for(int i = 0;i < 2; i++) { //players.size() se voglio stampare il playerSplit
		const char* chr = (players[i].info.username).c_str();
		if(i == 0) printf("%s\t",  chr) ;
		else printf("   %s\t",  chr) ;
        printCards(players[i].hand, 9); //printCards(cards, n max carte);
            if (score(players[i].hand) == 100){
                printf("BJ\t");
                }
            else {
                printf("%i\t", score(players[i].hand));
            }
    }
    double favore  = 0;
    for(int i = 1; i<2;i++) {
        favore = score(players[0].hand) - score(players[1].hand);
        printf("%.f\t", favore);
    }
	

    if (score(players[0].hand) == 0) { 
        printf(" Dealer ha sforato! ");
    }

	for (int i = 1;i< players.size(); i++) { //stampo solo player reale, lascio player.size() se voglio stampare anche il player_split

        if (score(players[i].hand) == 0 ){ 
	        printf(" Player %d ha sforato! ", i);
	    }
        int win = winner(players[0], players[i]); //we figure out who wins
		if (win == 1) {
	       printf(" Player %d vince ", i );
	    }	
	    else if (win == 0) {
	       printf(" TIE " );
	    }	
	    else if (win == -1) {
            if(i==2) printf(" Dealer vince (D-Psplit)");
            else printf(" Dealer vince (D-P1) ");
	    } 

    }	    
			
}

/**
 * Stabilisce il vincitore della mano utilizzando la funzione score 
 * come parametri
 * 
 * @param players
 * 
 * @return intero 0, 1, -1 a seconda che sia tie, vinca il giocatore, vinca il banco
 */

int winner(player dealer, player &user){
	if((score(dealer.hand) == score(user.hand)) && (score(user.hand)!=0)){ //se giocatore sballa perde, anche nel caso sballino banco e giocatore
		return 0;
	}
	else if(score(dealer.hand) < score(user.hand)){ //giocatore vince
		return 1;
	}
	else{ //dealer vince
		return -1;
	}
}
/**
 * Controlla se nella mano sono presenti assi 
 * come parametri
 * 
 * @param hand
 * 
 * @return "1" o "0" se nella mano ho un asso o no
 */
bool hasAce(vector<Card> hand){
	bool has_ace = false; //per il momento non c'è nessun asso
	for(int i =0;i<hand.size();i++){
		if(hand[i].value == 1){ //ho un asso
			has_ace = true; //set a true
		}
	}

	return has_ace;
}

/**
 * Calcola il punteggio della della giocata 
 * come parametri
 * 
 * @param hand
 * 
 * @return 100 se BJ, 0 se si sfora, valore totale delle carte in mano
 */
int score(vector<Card> hand){
	int total = 0; 
	bool hasBJ;
	for(int i = 0; i<hand.size();i++){
		if(hand[i].value >= 10){ //se é 10, J, Q, or K
			total+=10; //aggiungo 10 al totale
		}
		else{
			total += hand[i].value; //aggiunge valori carte al totale 
		}
	}

	if(hasAce(hand) && total <= 11){ //se nella mano ho un asso peró non sforo
		total+=10; //aggiungo  10 asso vale 11
	}
        
    if (total == 21 && hand.size() == 2) {
        return 100; //Black jack
    }
    else if (total > 21) {
        return 0; // se sforo
    }
    // Return total valore carte se non succedono le condizioni precedenti 
    return total;
}

/**
 * Distrituisce una carta 
 * come parametri
 * 
 * @param cards
 * 
 * @return struttura della carta
 */
Card deal(vector<Card> cards) {
    int j = CMWC1Random()%(cards.size() - 1);
    Card card = cards[j];
    cards.erase(cards.begin()+j);
    return card; 
}

/**
 * Si splitta la mano 
 * come parametri
 * 
 * @param dealer
 * @param user
 * @param cards
 * 
 */
void split(vector<player> &players, vector<Card> &cards){
	player split;  //crea un nuovo player per lo split
	split.hand.push_back(players[1].hand[0]); //prende la prima carta del user e la da al split player
	split.hand.push_back(deal(cards)); //da a la persona "split" una nuova carta
    players[1].hand.pop_back(); //rimuove l'ultima carta
    players[1].hand.push_back(deal(cards)); //da al user una nuova carta
	//players[1].hand[1] = deal(cards); //da al user una nuova carta
	split.info.username = players[1].info.username+"_Split";
	players.push_back(split); //il giocatore del split viene messo nel vettore di players
}



int main() {
    int n;
    int counter = 0; 
    int totPlays = 10000;
    double rtp = 0;
    double ratio = 0;
    double in = 0;
    double out = 0;
    double win = 0;
    
    map<string, map<string,bool>> strategyIntermedia;
    map<string, map<string,int>> strategyIntermediaSplit;
    for(int i=0; i < PLAYER_HEADER.size(); i++) {
        for(int j=0; j < DEALER_HEADER.size(); j++) {
            //devo mettere solo i true perché per default sta giá in false
            strategyIntermedia[PLAYER_HEADER[i]][DEALER_HEADER[j]] = ((i < 10 || (i > 22 && i < 28)) || (i == 10 && (j < 2 || j > 4)) || ((i > 10 && i < 15 ) && j > 4) || (i == 22 && j > 6) ||(i == 28  && (j < 2 || j > 4))  );
        }
    }
    for(int i=0; i < PLAYER_HEADERSplit.size(); i++) {
        for(int j=0; j < DEALER_HEADER.size(); j++) {
            //devo mettere solo i true perché per default sta giá in false
            if((i < 10 || (i > 22 && i < 28)) || (i == 10 && (j < 2 || j > 4)) || ((i > 10 && i < 15 ) && j > 4) || (i == 22 && j > 6) || (i>31 && j>5) || i==34 || (i==35 && j<3) || ((i>32 && i<36) && j == 5))
            strategyIntermediaSplit[PLAYER_HEADERSplit[i]][DEALER_HEADER[j]] = 1;
            else if (i==28 || ((i>29 && i<34) && j<5) || i ==31 || (i==30 && (j>5 && j<8)) || (i==32 && j==5) || (i>35 && j<6) || (i==35 && (j>2 && j<5)) )
            strategyIntermediaSplit[PLAYER_HEADERSplit[i]][DEALER_HEADER[j]] = 2;
            else 
            strategyIntermediaSplit[PLAYER_HEADERSplit[i]][DEALER_HEADER[j]] = 0;
        }
    }

    pFile = fopen (RTP_FILE,"w");
    for (int i=0; i<totPlays; i++)  {     
        win = out;
        player user;
        player dealer;
        vector<player> players;
        dealer.info.username = "Dealer";
        players.push_back(dealer);
        user.info.username = "Player1";
        players.push_back(user);
        // 13 carte
        int values = 13;
        // C = Cuori, Q = Quadri, F = Fiori, P = Picche
        vector<char> types = {'C','Q','F','P'};
        // 8 mazzi
        int packs = 8;
        // Vettore di carte
        vector<Card> cards = createCards(packs,values,types);
        //mischio carte
        swapCards(cards);
        printf("\n%d\t", i+1 ); 
        play(players, cards, 9, in, out, strategyIntermedia, strategyIntermediaSplit); 
        in = in + 100; //giocatore punta 100
        const char* cardPlayer;
        const char* cardBanco;
        bool hasSplit = false;
        string stringCardPlayer;
        int w = winner(players[0], players[1]); 


        //se splitto
        if ( players.size()>2 ) {
            hasSplit = true;
            in = in + 100;
            for(int p=1; p<players.size(); p++) {  
                int w = winner(players[0], players[p]); 
                if (w==1) {  
                    if(score(players[p].hand)==100)  out = out + 200; //200 se BJ é fatto con lo split
                    else out = out + 200;
                    if(p==2) printf("\t%.f\t%.f\t",in, out );
                }
                if (w==0) {
                    out = out + 100;
                    if(p==2) printf("\t%.f\t%.f\t",in, out );
                }   
                if (w==-1) {
                    out = out + 0;
                    if(p==2) printf("\t%.f\t%.f\t",in, out );
                }
            }    
        }
        else{
            if (w==1) {
                counter++;
                if(score(players[1].hand)==100) 
                    out = out + 300; //300 se BJ
                else 
                    out = out + 200; 
                printf("\t%.f\t%.f\t",in, out );
            }
            if (w==0) {
                out = out + 100;
                printf("\t%.f\t%.f\t",in, out );
            }
            if (w==-1) {
                out = out + 0;
                printf("\t%.f\t%.f\t",in, out );
            }
            if(i==0) win = std::numeric_limits<double>::quiet_NaN();
        }

        if ( hasSplit ) {
            players.pop_back();
            stringCardPlayer = getFirstCard(players[1].hand[0]) +"-"+ getFirstCard(players[1].hand[0]);
            cardPlayer = stringCardPlayer.c_str();
        }
        else {
            cardPlayer = getCardGiocatore(players).c_str();
            stringCardPlayer = string(cardPlayer);

        }
        cardBanco = (getFirstCard(players[0].hand[0])).c_str();
        string stringCardBanco(cardBanco);

        
        win = abs(win - out);
        ratio = double(counter)/double(totPlays);
        rtp = abs(out)/in;
        if (!(i %1000)) fprintf(pFile, "%.d\t%.2f\n", i+1 ,  rtp);

        printf("%.f\t%.2f ",win,rtp);
        printf("\t%s\t", cardPlayer);
        printf("%s\t", cardBanco);
        if(strategyIntermediaSplit[stringCardPlayer][stringCardBanco]==1) {
            printf("CARTA\t");
        }

        else if ( hasSplit ) printf("SPLIT\t");

        else printf("STAI\t");

        if( hasSplit ) {
            if (!(players[1].hand[0].value==1)) {
                const char* cardPlayer2 = getCardGiocatore(players).c_str();
                printf("%s\t", cardPlayer2);
                printf("%s\t", cardBanco);
                string stringCardPlayer2(cardPlayer2);
                string stringCardBanco(cardBanco);
                if(strategyIntermediaSplit[stringCardPlayer2][stringCardBanco]==1) printf("CARTA\t");
                else printf("STAI\t");
            }
            else {
                const char* cardPlayer2 = getCardGiocatore(players).c_str();
                printf("%s\t", cardPlayer2);
                printf("%s\t", cardBanco);
                printf("STAI per Split A-A\t");
            }
        }
        
        for(int j=3; j<=9; j++) {
            const char* cardPlayer_j = getStrategyCardGiocatore(players, j).c_str();
            string stringCardPlayer_j(cardPlayer_j);
            printf("%s\t", cardPlayer_j);
            if(stringCardPlayer_j!="")printf("%s\t", cardBanco);
            if(strategyIntermedia[stringCardPlayer_j][stringCardBanco]) printf("CARTA\t");
            else if (stringCardPlayer_j!="" && !(strategyIntermedia[stringCardPlayer_j][stringCardBanco]))printf("STAI\t");
            else printf("\t");
        }
   }


   fclose (pFile);
   return 0;
}
