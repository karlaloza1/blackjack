/**********************************************************************************
 ** BLACKJACK GAME
 ** Name: Karla Lozada
 ** Date: 04/28/2017
 ** CISP 400
 ***********************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

/************************************************************************************
 **
 ** This is the card class where we hold the information of each card, this class is
 ** going to show the card number and suit. Also, is going to help getting the cards
 ** in order to play the BLACKJACK
 **
 *************************************************************************************/

class Num_Card
{
public: // all public entry
    enum number_rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING};
    enum suit_number {CLUBS, DIAMONDS, HEARTS, SPADES};
    
    friend ostream& operator<<(ostream& os, const Num_Card& aCard);// This is the overloading
    
    Num_Card(number_rank r = ACE, suit_number s = SPADES, bool ifUp = true);
    int Value_Card() const; // give the cards from 1 to 11
    void Show_face(); //this function is going to flip the card in order to show the number they have.
    
private: // private entry to the functions
    number_rank card_Rank;
    suit_number card_Suit;
    bool card_show;
};

// here we have the constructor of the class
Num_Card::Num_Card(number_rank r, suit_number s, bool ifUp): card_Rank(r), card_Suit(s), card_show(ifUp)
{}

/*********************************************************************************
 ** Here we have the inheretance of the class Cards and the value, this means
 ** that it would show if the card is faced up or down.
 **********************************************************************************/

int Num_Card::Value_Card() const
{
    //the value is 0, this means the card is not showing the number or suit
    
    float number_value = 0;
    if (card_show)
    {
        number_value = card_Rank; //showing the number of the card
        if (number_value > 10) number_value = 10;
    }
    return number_value;
}

/*********************************************************************************
 ** Here we have the inheretance of the class Card, this inheritsnce is going to
 ** flip the card in order to show the number ans suit
 **********************************************************************************/

void Num_Card::Show_face()
{
    card_show = !(card_show);
}

/*********************************************************************************
 ** Here we have the Class Hand, which is going to give us the amount of card for
 ** each game in order to be able to start the game
 **********************************************************************************/

class Player_Hand_Game
{
public:
    Player_Hand_Game();
    
    virtual ~Player_Hand_Game();
    void Add(Num_Card* pCard); //adds cards to the hand
    void Delete_clear(); // delete the hand
    int Total_hand() const; // this function is going to help us getting the total of the hand
    
protected:
    vector <Num_Card*> nu_Cards;
};


Player_Hand_Game::Player_Hand_Game() // here we have the inheretance of the class Hand
{
    nu_Cards.reserve(7);
}

Player_Hand_Game::~Player_Hand_Game()
{
    Delete_clear();
}

void Player_Hand_Game::Add(Num_Card* pCard)  // here we have other inhere=itance of the class Hand
{
    nu_Cards.push_back(pCard);
}

void Player_Hand_Game::Delete_clear() //these inheritance is going to clear the memory of the heap
{
    //it is going to free the memory of the heap
    vector <Num_Card*>::iterator index = nu_Cards.begin();
    for (index = nu_Cards.begin(); index != nu_Cards.end(); ++index)
    {
        delete *index;
        *index = 0; //to set the nullptr
    }
    nu_Cards.clear();
}

/*********************************************************************************
 ** This inheritance is going to make the total of the cards in the Hand the
 ** player have in each play.
 ** This function is going to return the total of the cards in the hand in order to
 ** know who won.
 **********************************************************************************/

int Player_Hand_Game::Total_hand() const
{
    if (nu_Cards.empty()) // no cards in the hand then the value is 0
        return 0;
    
    if (nu_Cards[0]->Value_Card() == 0) // the card is not showing if the value of the card is 0
        return 0;
    
    float total_of_hand = 0; // each ace as 1
    vector<Num_Card*>::const_iterator index;
    for (index = nu_Cards.begin(); index != nu_Cards.end(); ++index)
        total_of_hand += (*index)->Value_Card();
    
    //show if the hand of the player have an ace
    bool have_Ace = false;
    for (index = nu_Cards.begin(); index != nu_Cards.end(); ++index)
        if ((*index)->Value_Card() == Num_Card::ACE)
            have_Ace = true;
    
    if (have_Ace && total_of_hand <= 11) // ace is 11, when the total is low enough
    {
        total_of_hand += 10;
    }
    
    return total_of_hand;
}

/*********************************************************************************
 ** This is an abstract class that is going to be used as a base for the
 ** two classes Player (is the useer playing) and House ( the computer plays)
 **********************************************************************************/


class Generated_Player : public Player_Hand_Game
{
    friend ostream& operator<<(ostream& os, const Generated_Player& aGenerated_Player);//overloading
    
public:
    Generated_Player(const string& name = "");
    
    virtual ~Generated_Player();
    virtual bool Add_Hitt() const = 0; //shows if the class generic play keep hitting or stop
    bool is_Lost() const; //come back to the class if it lose (grater than 21)
    void Lost() const; //show if the player won or lost
    
protected:
    string player_Name;
};

Generated_Player::Generated_Player(const string& name): player_Name(name) {}
Generated_Player::~Generated_Player() {}

/*********************************************************************************
 ** Here we have the inheretance of the class Cards and the value, this means
 ** that it would show if the card is faced up or down.
 **********************************************************************************/
bool Generated_Player::is_Lost() const
{
    return (Total_hand() > 21);
}

/*********************************************************************************
 ** Here we have the function that is going to Bust or make it losee in each game
 ** this means that the one that have more than 21 in their hand
 **********************************************************************************/
void Generated_Player::Lost() const
{
    cout << player_Name << " Sorry!! You lost!! (✖╭╮✖) .\n\n";
}

/********************************************************************************************
 ** This class is going to return the player decision of HIT or Stay in the Blackjack game
 ** Also, is going to determinate if the player won, lost or if there is a tie between 
 ** the players and the dealer
 ********************************************************************************************/

class Game_Player : public Generated_Player
{
public:
    Game_Player(const string& name = "");
    
    virtual ~Game_Player();
    
    
    virtual bool Add_Hitt() const; // return if the player wants to STAY or HIT AGAIN
    
    
    void win_player() const; // anounces if the player wonn
    
    
    void Lose() const; // anounces if the player lost
    
   
    void Player_push() const; // announces if the player push
};


/*********************************************************************************************
 ** Here we show the Player class which is going to ask the player the decision of 
 ** Sray or Hit which is going to connect with the last class and return the value 
 ** in order to get the result
 ************************************************************************************************/


Game_Player::Game_Player(const string& name): Generated_Player(name) {}
Game_Player::~Game_Player() {}

bool Game_Player::Add_Hitt() const
{
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
    
    cout << player_Name << ", Would you want a HIT or STAY? (H/S): ";
    char choice_player;
    cin >> choice_player;
    cout << endl;
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
    return (choice_player == 'h' || choice_player == 'H');
}
/************************************************************************************************
 ** Here we have the inheritance with the  function that will be called when the player 
 ** get 21 or he neares  result to 21. It is going to display the following message of
 ** their win
 *************************************************************************************************/

void Game_Player::win_player() const
{
    cout << endl;
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl;
    cout << endl;
    cout << player_Name << " CONGRATS!! YOU WONN (◕‿◕) .\n\n";
}

/****************************************************************************************************
 ** Here we have the inheritance between the Player class and the Lose function, which is going to be
 ** called if the player have more than 21 in their hand, if this happen the following message would 
 ** be display
 *****************************************************************************************************/

void Game_Player::Lose() const
{
    cout << endl << endl;
    cout << player_Name << " Sorry!! You LOST (✖╭╮✖) .\n\n";
}

//// THIS INHERITANCE IS GOING TO PUSH THE VALUE OF THE PLAYER

void Game_Player::Player_push() const
{
    cout << player_Name << " pushes.\n";
}

/****************************************************************************************************
 ** Here we have a new class called House wich is the Dealer (computer) this is going to generate a 
 ** a new player. The new player would have one card hidden and the other would be shown.
 *****************************************************************************************************/


class Dealer_Game : public Generated_Player
{
public:
    Dealer_Game(const string& name = "Dealer");
    virtual ~Dealer_Game();
    
    
    virtual bool Add_Hitt() const;  // would give the card which will be 10 or less
    
    
    void ShowFirstCar();  //will not show the first card
};

Dealer_Game::Dealer_Game(const string& name): Generated_Player(name) {}  // the name of each player should be called in order to mantain the order
Dealer_Game::~Dealer_Game() {}

/****************************************************************************************************
 ** Here we have the same class House but with an inheritance which is going to be called at the end
 ** this function will make the card to flip or show the value to the player when the game is over if
 ** if all cards all played in the deck then no more posible moves
 *****************************************************************************************************/

bool Dealer_Game::Add_Hitt() const
{
    return (Total_hand() <= 16);
}

void Dealer_Game::ShowFirstCar()
{
    if (!(nu_Cards.empty()))
        nu_Cards[0]->Show_face();
    
    else
        cout << "There are no more cards to flip!! SORRY!  ";
}

/****************************************************************************************************
 ** This is a new class Deck, this class is going to have an inheretance with different functions
 ** which will make the hand to exist. This means the deck function is here, also shuffle or hit and
 ** deal function will give the cards if the player ask for more cards into the deck
 *****************************************************************************************************/

class Cards_Deck : public Player_Hand_Game
{
public:
    Cards_Deck();
    virtual ~Cards_Deck(); //this is the deck funct
    
    
    void Cards_populate(); //is going to create the deck functiom
    
    
    void Cards_Shuffle(); //shuffle cards
    
    
    void Deal(Player_Hand_Game& aCards_Deck); //give a card when hit
   
    void AdditionalCards(Generated_Player& aGenerated_Player); //call this function each time the player ask for more cards
};

/****************************************************************************************************
 ** This is the Deck class is going to create the deck, with almost all characteristics, this means that 
 **the suit and number of each card that the player have in their hand or deck
 *****************************************************************************************************/

Cards_Deck::Cards_Deck()
{
    nu_Cards.reserve(52);
    Cards_populate();
}
Cards_Deck::~Cards_Deck() {}

void Cards_Deck::Cards_populate()
{
    Delete_clear();
    
    
    for (int s = Num_Card::CLUBS; s <= Num_Card::SPADES; ++s) //this is going to create the deck for the hand
    {
        for (int r = Num_Card::ACE; r <= Num_Card::KING; ++r) // create the suits fort the deck for the hand
        {
            Add(new Num_Card(static_cast <Num_Card::number_rank>(r),static_cast <Num_Card::suit_number>(s)));
        }
    }
}

/****************************************************************************************************
 ** This is a new class Deck in an inheritance with the suffle function which is going to give 
 ** new cards to each player in the Deck
 *****************************************************************************************************/


void Cards_Deck::Cards_Shuffle()
{
    random_shuffle(nu_Cards.begin(), nu_Cards.end());
}

void Cards_Deck::Deal(Player_Hand_Game& aHand)
{
    if (!nu_Cards.empty())
    {
        aHand.Add(nu_Cards.back());
        nu_Cards.pop_back();
    }
    
    else
    
    {
        cout << "There are not more cards in order to play, Sorry."<< endl;
    }
}

/****************************************************************************************************
 ** this is the Deck class with an inheritance with the AdditionalCards function which is going to 
 ** help with the adding for cards each time the player asks for more
 *****************************************************************************************************/

void Cards_Deck::AdditionalCards(Generated_Player& aGenericPlayer)
{
    cout << endl;
    
    while (!(aGenericPlayer.is_Lost()) && aGenericPlayer.Add_Hitt())
    {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;
        
        if (aGenericPlayer.is_Lost())
            aGenericPlayer.Lost();
    }
}
/****************************************************************************************************
 ** This is a new class Game, this class is going to play the game actually and start the game from the
 ** begining, so its going to hold the variables of deck and also the players
 *****************************************************************************************************/
class Starting_Game
{
public:
    Starting_Game(const vector<string>& names);
    
    ~Starting_Game();
    
    //plays the game of blackjack
    void Game_Begin();
    friend void Instructions();
    
private:
    Cards_Deck turn_Deck;
    Dealer_Game turn_House;
    vector<Game_Player>  turn_Players;
};

Starting_Game::Starting_Game(const vector<string>& names)
{
 
    vector<string>::const_iterator playerName;
    for (playerName = names.begin(); playerName != names.end(); ++playerName)
        turn_Players.push_back(Game_Player(*playerName));
    
    srand(static_cast<unsigned int >(time(NULL)));  //create the random number into the distribution of the cards
    turn_Deck.Cards_populate();
    turn_Deck.Cards_Shuffle();
}

Starting_Game::~Starting_Game() {}

/****************************************************************************************************
 ** This function is only going to show the instructions of the game, so its just going to output
 ** the way the player should play the game
 *****************************************************************************************************/

void Game_Instruc_Game()
{
    cout << " In case you dont know how to play poker DONT WORRY!! " << endl;
    cout << " Here is some explication that will HELP YOU!!"<< endl<< endl;
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
    
    cout << "★★★★★★★★ In order to WIN the game you need 21 cards ★★★★★★★★" << endl<< endl;;
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
    cout << "★ The DEALER is the computer playing against YOU! ★" << endl;
    cout << "★ In case the DEALER have more card than 21 the PLAYER WIN! ★"<< endl;
    cout << "★ In case the DEALER have less card than 21 then the DEALER WIN!! ★" << endl;
    cout << "★ In case that the DEALER and the PLAYER have 21 then is a TIE!! ★" << endl;
    cout << "~~ c = ♧ Clubs ♣ ~~" << endl;
    cout << "~~ d = ♢ Diamonds ♦ ~~" << endl;
    cout << "~~ h = ♡ Hearts ♥ ~~" << endl;
    cout << "~~ s = ♤ Spades ♠ ~~" << endl<< endl;
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
    cout << "                    LETS BEGIN THE GAME!!! GOOD LUCK !!!" << endl<< endl;
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
}

/****************************************************************************************************
 ** This is a new class Game inheretance with the play function whhich is going to start the game
 ** give the cards to the player and also the house. We see the loop that will keeping asking of you 
 ** want to hit or stay and display hand of the players
 *****************************************************************************************************/

void Starting_Game::Game_Begin()
{
    
    vector<Game_Player>::iterator time_Player;
    for (int i = 0; i < 2; ++i) //give the two cards for player -- thats why the loop is 2
    {
        for (time_Player = turn_Players.begin(); time_Player != turn_Players.end(); ++time_Player)
            turn_Deck.Deal(*time_Player);
        
        turn_Deck.Deal(turn_House);
    }
    
    
    turn_House.ShowFirstCar(); //call the function to dont show the card of the dealer
    
    
    for (time_Player = turn_Players.begin(); time_Player != turn_Players.end(); ++time_Player)
        cout << *time_Player << endl; // loop that would print the hand of each player include the dealer
    
    cout << turn_House << endl;
    
    
    for (time_Player = turn_Players.begin(); time_Player != turn_Players.end(); ++time_Player)
        turn_Deck.AdditionalCards(*time_Player);  //loop that would keep asking if HIT or STAY
    
  
    turn_House.ShowFirstCar();
    cout << endl << turn_House;
    
   
    turn_Deck.AdditionalCards(turn_House); //add new card to the dealer
    
    if (turn_House.is_Lost()) //everyone is losing
    {
        for (time_Player = turn_Players.begin(); time_Player != turn_Players.end(); ++time_Player)
            if (!(time_Player->is_Lost()))
                time_Player->win_player();
    }
    else
    {
        //compare each player in order to know who win ans lost
        for (time_Player = turn_Players.begin(); time_Player != turn_Players.end();
             ++time_Player)
            if (!(time_Player->is_Lost()))
            {
                if (time_Player->Total_hand() > turn_House.Total_hand())
                    time_Player->win_player();
                
                else if (time_Player->Total_hand() < turn_House.Total_hand())
                    time_Player->Lose();
                
                else
                    time_Player->Player_push();
            }
    }
   //no one wonnnn
    for (time_Player = turn_Players.begin(); time_Player != turn_Players.end(); ++time_Player)
        time_Player->Delete_clear();
    
    turn_House.Delete_clear();
}


ostream& operator<<(ostream& os, const Num_Card& aCard); //OVERLOAD OPERATORSS
ostream& operator<<(ostream& os, const Generated_Player& aGenericPlayer);

/****************************************************************************************************
** This is main function where we will call all the functions and classes in order to make the game 
** work. Also, its going to give the first introduction for the game or WELCOMING
*****************************************************************************************************/

int main()
{
    cout<< "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠  " << endl<< endl;    //welcoming to program
    cout << "\t\t\t♠ ♥ ♣ ♦ Welcome to Karla's Casino !!!! ♠ ♥ ♣ ♦\n\n";
    cout << " \t\t\t♠ ♥ ♣ ♦ Todays game is BLACKJACK ♣ ♦♠ ♥ ♣ ♦ ♠\n\n";
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠  " << endl << endl;
   
    Game_Instruc_Game(); //call the first part with the instrutios to have an ideo of how to play
    
    int players_amount = 0;  // know the information of amount of players
    while (players_amount < 1 || players_amount > 7)
    {
        cout << "Choose the quantity of players " << endl;
        cout << "The max amount of player is from (1 - 7): ";
        cin  >> players_amount;  // insert quantity of players into the blackjack
    }
    vector <string> names;  // insert the name of each players that is in the game
    string player_name;
    for (int i = 0; i < players_amount; ++i)
    {
        cout << endl;
        cout << "Please enter the name of player " << (i+1) << ": ";
        cin  >> player_name;
        names.push_back(player_name);
    }
    cout << endl;
    
    cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;
    cout << "★★★★★★★★ PLAYERS HANDS!! ★★★★★★★★ "<< endl<< endl; //show each hands
    
    //game loopp to hit again
    Starting_Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.Game_Begin();
        cout << "♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦ ♠ ♥ ♣ ♦♠ ♥ ♣ ♦♠ " << endl << endl;        cout << "\n WOULD YOU LIKE TO KEEP PLAYING !! (Y/N) ";
        cin  >> again;
        cout << endl;
    }
    
    return 0;
}

//overloads << operator so Card object can be sent to cout
ostream& operator<<(ostream& os, const Num_Card& anum_card)
{
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9",
        "10", "J", "Q", "K"};
    const string SUITS[] = {"♧", "♢", "♢", "♤"};
    
    if (anum_card.card_show)
        os << RANKS[anum_card.card_Rank] << SUITS[anum_card.card_Suit]<< "\t";
    else
        os << "hidden";
    
    return os;
}


//overloads << operator so a GenericPlayer object can be sent to cout
ostream& operator <<(ostream& os, const Generated_Player& aGenerated_Player)
{
    os << aGenerated_Player.player_Name << ":\t";
    
    vector <Num_Card*>::const_iterator posi_Card;
    if (!aGenerated_Player.nu_Cards.empty())
    {
        for (posi_Card = aGenerated_Player.nu_Cards.begin();
             posi_Card != aGenerated_Player.nu_Cards.end(); ++posi_Card)
            os << *(*posi_Card) << "\t";
        
        if (aGenerated_Player.Total_hand() != 0)
            cout << "(" << aGenerated_Player.Total_hand() << ")";
    }
    else
        os << "<empty>";
    
    return os;
}
