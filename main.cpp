// flashcards project

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;



// υλοποίηση για τις κάρτες
class Card{
public:
    Card(){
        cout << "New card created!" << endl;
    }

    Card(string question, string answer){
        Question = question;
        Answer = answer;
    }

    // getters and setters for private
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


    // show question and answer 
    void Show(){
        if(Question.empty()){
            cerr << "This field must not be empty" << endl;
            return;
        }   
        else
            cout << "Question: " <<  Question << endl;

        if(!Answer.empty())
            cout << "Answer: " <<  Answer << endl;
        else
            cout << " " << endl;
    }




    // save a card to a database SQLite implementation
    void Save(){

    }

private:
    string Question;
    string Answer;
};



// υλοποίηση για τις συλλογές καρτών (decks)
// διαχείριση καρτών
class Deck{
public:
    Deck(){}
    vector<Card> vec; // temp saving the cards 


    void add2vec(Card card){
        vec.push_back(card);
    }


    void print_vec(){
        if (vec.empty()) {
        cout << "The deck is empty!" << endl;
    } else {
        cout << "Cards in the deck:" << endl;
        for (auto& card : vec) {
            card.Show();
        }
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
    void delete_vec(){
        vec.clear();
        cout << "Deck is deleted!" << endl;
    }
};



// μελέτη με χρονική επανάληψη 
class Study{
public:
    Study(){}

};


// με timeit θα αποθηκεύω πόσο χρόνο κάνει στην κάθε κάρτα
// και θα εμφανίζω τα συνολικά στατιστικά και της κάθε κάρτας
class Statistics{
public:
    Statistics(){}


};


// Main συνάρτηση
int main() {
    // creating the objects 
    Card c1;
    Deck d1;
    Card c2;

    // setting the questions and answers of the cards
    c1.setQuestion("Hey there?");
    c1.setAnswer("there?");
    c2.setQuestion("c2 q");
    c2.setAnswer("c2 a");


    // printing the contents of the card
    c1.Show();
    c2.Show();

    // adding to a deck
    d1.add2vec(c1);
    // printing the deck
    d1.add2vec(c2);
    d1.print_vec();
    d1.delete_vec();
    d1.print_vec();

    return 0;
}


