// flashcards project

#include <iostream>
#include <string>
#include <time.h>
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
    
};

// μελέτη με χρονική επανάληψη 
class Study{
public:
    Study(){}

};


class Statistics{
public:
    Statistics(){}


};


// Main συνάρτηση
int main() {
    Card c1;
    c1.setQuestion("Hey there?");
    c1.setAnswer("there?");
    c1.Show();
    return 0;
}


