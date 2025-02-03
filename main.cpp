// flashcards project
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sqlite3.h>

// choices on how difficult a card was
#define again 1
#define hard 2
#define good 3
#define easy 4
using namespace std;


// initializing database logic
static int createDB(const char* s);
static int createTable(const char* s);



// υλοποίηση για τις κάρτες
class Card{
public:
    Card(){}
    Card(string question, string answer){
        Question = question;
        Answer = answer;
    }


    // getters and setters for question and answer
    string getQuestion(){
        return Question;
    }

    void setQuestion(string question){
        Question = question;
    }

    string getAnswer(){
        return Answer;
    }

    void setAnswer(string answer){
        Answer = answer;
    }

    // deleting a card
    void deleteCard(){
        setQuestion("");
        setAnswer("");
    }


    // show question
    void ShowQuestion(){
        if(Question.empty()){
            cerr << "This field must not be empty" << endl;
            return;
        }   
        else
            cout << "Question: " <<  Question << endl;
    }

    // show answer
    void ShowAnswer(){
        if(!Answer.empty())
            cout << "Answer: " <<  Answer << endl;
        else
            cout << " " << endl;
    }


    // based on the difficulty input of the user . A score (in seconds) is given to the card.
    // it is based on the repeat strategy 
    // if a card is considered easy will take 4 days (in seconds) to re-appear.
    void setScore(double score){
        Score = score; 
    }


    double getScore(){
        return Score;
    }



private:
    string Question;
    string Answer;
    double Score = 0.0;
};


// υλοποίηση για τις συλλογές καρτών (decks)
// διαχείριση καρτών
class Deck{
public:
    Deck(){}

    Deck (string Name) {
        name = Name;
    }
    vector<Card> vec; // temp saving the cards 
    
    // adding a card to deck
    void add2deck(Card card){
        vec.push_back(card);
    }

    // print the contents of the deck
    void print_deck(){
        if (vec.empty()) {
        cout << "The deck is empty!" << endl;
    } else {
        cout << "Cards in the deck:" << endl;
        for (auto& card : vec) {
            card.ShowQuestion();
            card.ShowAnswer();
        }
        cout << "---------------------------------" << endl;
    }
    }


    // delete a card from the deck
    void delete_element(Card card){
        // delete the position of the card

        for(auto it = vec.begin(); it != vec.end();){
            if(it ->getQuestion() == card.getQuestion() && it->getAnswer() == card.getAnswer()){
                it = vec.erase(it); 
                cout << "Card deleted!" << endl;
                return;
            } else {
                ++it;
        }
    }
        cout << "card not found" << endl;
    }


    // Deleting the deck
    void delete_deck(){
        vec.clear();
        cout << "Deck is deleted!" << endl;
    }


    // updating the cards in the vector (question or answer)
    void update_deck(Card& card, const string& newQuestion, const string& newAnswer){
    for(auto it = vec.begin(); it != vec.end(); ++it){
            
            if (!newQuestion.empty() && newQuestion != it->getQuestion()) {
                it->setQuestion(newQuestion);
            }

            if (!newAnswer.empty() && newAnswer != it->getAnswer()) {
                it->setAnswer(newAnswer);
            }

            cout << "Card updated!" << endl;
            return;
        }
        cout << "Card not found!" << endl;  
    }

    
    // get the name of the deck
    string getName(){
        cout << name << endl;
        return name;
    }

    // set the name of the deck
    void setName(string Name){
        name = Name;
    }


private:
    string name;
};


// μελέτη με χρονική επανάληψη και στατιστικά  
class Study{
public:
    Study(){}
    double score = 0.0; // repeat score

    // start the timer
    void startTime(){
        startTimer = clock();
    }


    // stop the timer
    void stopTime(){
        clock_t endTime = clock();
        double total = (double)(endTime - startTimer)/ CLOCKS_PER_SEC;
        timePerCard.push_back(total); 
        totalTime += total;
        cardCounter++;
    }


    // εμφάνιση στατιστικών
    void showStatistics(){
        cout << "Total study time: " << totalTime << " seconds" << endl;
        cout << "Total cards read: " << cardCounter << endl;
        if(cardCounter > 0) {
            double time_per_card = (totalTime / cardCounter);
            cout << "Time per card: " << time_per_card << " seconds" << endl;
        }
    }

    
    // repeat - strategy
    // αρχική υλοποίηση με switch 
    // λειτουργεί οκ
    void repeat(Card card, int input){
        switch(input){
            case 1:
                card.setScore(60);
                score = card.getScore();
                break;
            case 2:
                card.setScore(360);
                score = card.getScore();
                break;
            case 3:
                card.setScore(600);
                score = card.getScore();
                break;
            case 4:
                card.setScore(345600);
                score = card.getScore();
                break;
        } 
    }


private:
    clock_t startTimer; // ξεκίνημα χρόνου
    int cardCounter=0; // μετράει πόσες κάρτες διαβάστηκαν μέχρι στιγμής
    double totalTime = 0.0;
    vector<double> timePerCard; 
};


// Main συνάρτηση
int main() {

    const char* dir = "c:/MyDatabase/FLASHCARDS.db";
    sqlite3* DB;
    createDB(dir);
    createTable(dir);
    

    return 0;
}


// implementation of the sqlite logic
// function to create/open the database 
static int createDB(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);

    if (exit) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    } else {
        cout << "Database created/opened successfully!" << endl;
    }

    sqlite3_close(DB);
    return 0;
}


// function to create table in the database 
static int createTable(const char* s) {
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);
    if (exit) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    // table DECKS
    string sql_decks = "CREATE TABLE IF NOT EXISTS DECKS ("
                       "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "NAME TEXT UNIQUE NOT NULL );";

    // table CARDS
    string sql_cards = "CREATE TABLE IF NOT EXISTS CARDS ("
                       "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "DECK_ID INTEGER, "
                       "QUESTION TEXT NOT NULL, "
                       "ANSWER TEXT NOT NULL, "
                       "FOREIGN KEY (DECK_ID) REFERENCES DECKS(ID) ON DELETE CASCADE );";

    // table STUDY
    string sql_study = "CREATE TABLE IF NOT EXISTS STUDY("
                       "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "CARD_ID INTEGER, "
                       "TOTAL_TIME REAL, "
                       "TIME_PER_CARD REAL, "
                       "CARDS_VIEWED   INTEGER DEFAULT 0, "
                       "FOREIGN KEY (CARD_ID) REFERENCES CARDS(ID) ON DELETE CASCADE );";

    // execute one by one 
    string queries[] = {sql_decks, sql_cards, sql_study};

    for (const string& query : queries) {
        exit = sqlite3_exec(DB, query.c_str(), 0, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "SQL Error: " << messageError << endl;
            sqlite3_free(messageError);
        } else {
            cout << "Table created successfully: " << query << endl;
        }
    }

    sqlite3_close(DB);
    return 0;
}



