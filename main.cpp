// flashcards project
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sqlite3.h>
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
    Deck(){
        int deck_id = -1;
    }

    Deck (string Name) {
        name = Name;
        int deck_id = -1;
    }
    vector<Card> vec; // temp saving the cards 
    

    void setDeckID(int id){
        deck_id = id;
    }


    int getDeckID(){
        return deck_id;
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
    Deck d1;
    Deck d2;
    Card c1;
    Card c2;

    c1.setQuestion("This is a question?");
    c1.setAnswer("This is an answer!");
    c2.setQuestion("Why do you love programming?");
    c2.setAnswer("Because it feels like a game!");
    d1.setName("mydeck4");
    d2.setName("d2deck");
    

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


    d1.setDeckID(1);
    d2.setDeckID(2);
    cout << "d1 deck id: " << d1.getDeckID() << endl;
    cout << "d2 deck id: " << d2.getDeckID() << endl;
    sqlite3_close(DB);
    return 0;
}

