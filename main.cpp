// flashcards project
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "Database.h"

// choices on how difficult a card was
#define again 1
#define hard 2
#define good 3
#define easy 4
using namespace std;


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
        return Question.c_str();
    }

    void setQuestion(string question){
        Question = question;
    }

    string getAnswer(){
        return Answer.c_str();
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
    static int deckCounter; 

    Deck(){
        deck_id = ++deckCounter;
    }


    Deck (string Name) {
        this->name = Name;
        this->deck_id = ++deckCounter;
    }

    ~Deck(){
        deckCounter--;
    }

    vector<Card> vec; // temp saving the cards 

    int getDeckID(){
        return this->deck_id;
    }

    
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
    int deck_id;
};


int Deck::deckCounter=0;


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


class User
{
public:
    static int counter;
    User(){
        this->userId = ++counter; 
    }


    ~User(){
        counter--;
    }


    string getName(){
        cout << name << endl;
        return this->name; 
    }

    void setName(string name){
        this->name = name;
    }

    int getUserId(){
        return this->userId;
    }

    // implement deleting a user
    // or implement it straight to the database

private:
    string name;
    int userId;
};


int User::counter = 0;


// Main συνάρτηση
int main() {
    // initializing the database
    const char* dir = "c:/MyDatabase/FLASHCARDS.db";
    sqlite3* DB;
    Database::createDB(dir);
    Database::createTable(dir);

    int exit = sqlite3_open(dir, &DB);
    if (exit) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }
    


    sqlite3_close(DB);
    return 0;
}

