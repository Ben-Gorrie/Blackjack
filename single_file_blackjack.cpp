#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>

using namespace std;

class Deck {

	vector<string> deck = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	vector<string> play_deck;

public: 

	void make_play_deck(int deck_num) {

		for (int i = 0; i < deck_num; i++) {

			for (int j = 0; j < deck.size(); j++) {

				play_deck.push_back(deck[j]);

			}

		}

	}

	vector<string> &get_play_deck() {

		return play_deck;

	}

	void print_play_deck() {

		for (int i = 0; i < play_deck.size(); i++) {

			cout << play_deck[i] << " ";

		}
		cout << endl;

	}

	void remove_top_card() {

		play_deck.erase(play_deck.begin());

	}


};

class Player {

	vector<string> hand;
	double balance;
	double bet_amount;
	int score = 0;

public:

	void set_hand(vector<string> new_hand) {

		hand = new_hand;

	}

	vector<string> &get_hand() {

		return hand;

	}

	void print_hand() {

		for (int i = 0; i < hand.size(); i++) {

			cout << hand[i] << " "; 

		}
		cout << endl;

	}

	void draw_card(Deck &aDeck) {

		hand.push_back(aDeck.get_play_deck()[0]);
		aDeck.remove_top_card();

	}

	void set_balance(double new_balance) {

		balance = new_balance;

	}

	double &get_balance() {

		return balance;

	}

	void set_bet_amount(double new_bet_amount) {

		bet_amount = new_bet_amount;

	}

	double &get_bet_amount() {

		return bet_amount;

	}

	void make_bet(double amount) {

		if (amount > balance) {

			cout << "Sorry, you do not have enough funds! Please try again\n";
			double new_amount;
			cin >> new_amount;
			(*this).make_bet(new_amount);

		} else if (amount < 2){

			cout << "The minimum bet amount is 2" << endl;
			double new_amount;
			cin >> new_amount;
			(*this).make_bet(new_amount);

		} else {

			bet_amount = amount;
			balance -= amount;

		}

	}

	int &get_score() {

		return score;

	}


	void calculate_score() {

		int total = 0;
		int ace_as_eleven = 0;
		score = total;
		for (int i = 0; i  < hand.size(); i++) {

			if (hand[i] != "A" && hand[i] != "J" && hand[i] != "Q" && hand[i] != "K") {

				total += stoi(hand[i]);

			} else if (hand[i] != "A") {

				total += 10;

			} else {

				total += 11;
				ace_as_eleven += 1;

			}

		}
		while (total > 21 && ace_as_eleven != 0) {

			total -= 10;
			ace_as_eleven--;

		}
		score = total;

	}


};

class Dealer {

	vector<string> hand;
	double balance;
	int score;

public:

	void mix_play_deck(Deck &aDeck) {

		srand(time(NULL));
		for (int i = 0; i < aDeck.get_play_deck().size(); i++) {

			int j = i + rand() % (aDeck.get_play_deck().size() - i);
			swap(aDeck.get_play_deck()[i], aDeck.get_play_deck()[j]);

		}

	}

	void draw_card(Deck &aDeck) {

		hand.push_back(aDeck.get_play_deck()[0]);
		aDeck.remove_top_card();

	}

	void set_hand(vector<string> new_hand) {

		hand = new_hand;

	}

	vector<string> &get_hand() {

		return hand;

	}

	void print_hand() {

		for (int i = 0; i < hand.size(); i++) {

			cout << hand[i] << " "; 

		}
		cout << endl;

	}

	void print_censored_hand() {

		cout << hand[0] << " * \n";

	}

	void give_card_to_player(Player &aPlayer, Deck &aDeck) {

		aPlayer.get_hand().push_back(aDeck.get_play_deck()[0]);
		aDeck.remove_top_card();

	}

	void set_balance(double new_balance) {

		balance = new_balance;

	}

	double &get_balance() {

		return balance;

	}

	void calculate_score() {

		int total = 0;
		int ace_as_eleven = 0;
		score = total;
		for (int i = 0; i  < hand.size(); i++) {

			if (hand[i] != "A" && hand[i] != "J" && hand[i] != "Q" && hand[i] != "K") {

				total += stoi(hand[i]);

			} else if (hand[i] != "A") {

				total += 10;

			} else {

				total += 11;
				ace_as_eleven += 1;

			}

		}
		while (total > 21 && ace_as_eleven != 0) {

			total -= 10;
			ace_as_eleven--;

		}
		score = total;


	}

	int &get_score() {

		return score;

	}

	void hit_or_stick(Player &aPlayer, Deck &aDeck) {

		bool has_stuck = false;
		bool has_hit = false;

		while (aPlayer.get_score() < 21 && !has_stuck) {

			cout << "'hit' or 'stick'?\n";
			string hos;
			cin >> hos;
		
			if (hos == "hit") {
				cout << "Here is another card\n";
				(*this).give_card_to_player(aPlayer, aDeck);
				aPlayer.calculate_score();
				aPlayer.print_hand();
				has_hit = true;

			} else if (hos == "stick") {

				cout << "Good luck\n";
				aPlayer.calculate_score();
				has_stuck = true;


			} else {

				cout << "This is not a valid option, please try again\n";
				(*this).hit_or_stick(aPlayer, aDeck);

			}

		}
		if (aPlayer.get_score() == 21 && has_hit == true) {

			cout << "Blackjack!" << endl;

		} else if (aPlayer.get_score() == 21 && has_hit== false) {

			cout << "Natural Blackjack!" << endl;

		}

	}

	void self_hit_or_stick(Deck &aDeck) {

		(*this).calculate_score();
		if ((*this).get_score() <= 16) {

			cout << "Dealer draws\n";
			(*this).draw_card(aDeck);
			cout << "Dealer's hand: \n";
			(*this).print_hand();
			(*this).self_hit_or_stick(aDeck);

		} else {

			cout << "Dealer sticks\n";

		}

	}

	void next_round(Player &aPlayer, Deck &aDeck) {

		string ans;
		cin.ignore();
		while (ans != "play again") {

			cout << "What would you like to do now?\n";
			cout << "'view balance' or 'add funds' or 'play again' or 'stop'\n";
			getline(cin, ans);
			if (ans == "view balance") {

				cout << "Balance : " << aPlayer.get_balance() << endl;

			} else if (ans == "add funds") {

				cout << "How much would you like to add?\n";
				double fund_added;
				cin >> fund_added;
				aPlayer.set_balance(aPlayer.get_balance() + fund_added);
				cout << "Done!\n";

			} else if (ans == "stop") {

				cout << "We hope you enjoyed yourself!\n";

			} else if (ans != "play again") {

				cout << "Invalid input! Please try again\n";

			}

		}
		(*this).start_round(aPlayer, aDeck);


	}


	void start_round(Player &aPlayer, Deck &aDeck) {

		cout << "Round starting\n";
		cout << "Current balance is " << aPlayer.get_balance() << endl;
		cout << "How much would you like to bet?\n";
		double temp_bet;
		cin >> temp_bet;
		aPlayer.make_bet(temp_bet);
		(*this).give_card_to_player(aPlayer, aDeck);
		(*this).draw_card(aDeck);
		cout << "Your hand: ";
		aPlayer.print_hand();
		cout << "Dealer's hand: ";
		(*this).print_hand();
		(*this).give_card_to_player(aPlayer, aDeck);
		(*this).draw_card(aDeck);
		cout << "Your hand: ";
		aPlayer.print_hand();
		cout << "Dealer's hand: ";
		(*this).print_censored_hand();
		aPlayer.calculate_score();
		(*this).hit_or_stick(aPlayer, aDeck);
		aPlayer.calculate_score();
		if (aPlayer.get_score() <= 21) {

			cout << "Here is the dealer's hand: \n";
			(*this).print_hand();
			(*this).self_hit_or_stick(aDeck);
			if ((*this).get_score() > 21) {

				cout << "Dealer has gone bust! You win!\n";
				aPlayer.set_balance(aPlayer.get_balance() + aPlayer.get_bet_amount() * 2);
				(*this).set_balance((*this).get_balance() - aPlayer.get_bet_amount());
				aPlayer.set_bet_amount(0);

			} else {

				if (aPlayer.get_score() < (*this).get_score()) {

					cout << "Dealer wins.\n";
					(*this).set_balance((*this).get_balance() + aPlayer.get_bet_amount());
					aPlayer.set_bet_amount(0);

				} else if (aPlayer.get_score() > (*this).get_score()) {

					cout << "Player wins!\n";
					aPlayer.set_balance(aPlayer.get_balance() + aPlayer.get_bet_amount() * 2);
					(*this).set_balance((*this).get_balance() - aPlayer.get_bet_amount());
					aPlayer.set_bet_amount(0);

				} else {

					cout << "Draw!\n";
					aPlayer.set_balance(aPlayer.get_balance() + aPlayer.get_bet_amount());
					aPlayer.set_bet_amount(0);

				}

			}

		} else {

			cout << "You have gone bust\n"; 
			(*this).set_balance((*this).get_balance() + aPlayer.get_bet_amount());
			aPlayer.set_bet_amount(0);

		}
		
		//return the cards, clear hands and mix deck
		aDeck.get_play_deck().insert(aDeck.get_play_deck().end(), aPlayer.get_hand().begin(), aPlayer.get_hand().end());
		aPlayer.get_hand().clear();
		aDeck.get_play_deck().insert(aDeck.get_play_deck().end(), (*this).get_hand().begin(), (*this).get_hand().end());
		(*this).get_hand().clear();
		(*this).mix_play_deck(aDeck);

		//ask user what to do next
		(*this).next_round(aPlayer, aDeck);

	}

};


//Figure out self equivalent (like in python)  DONE (*this)
//Figure out how to do this in multiple files
//Print out cards as nice big ASCII art pieces	
//Use inheritence


int main() {

	Deck myDeck;
	Dealer myDealer;
	Player myPlayer;
	myDeck.make_play_deck(5);
	myPlayer.set_balance(1000);
	myDealer.set_balance(10000);
	myDealer.mix_play_deck(myDeck);
	myDealer.start_round(myPlayer, myDeck);	


	return 0;

}



