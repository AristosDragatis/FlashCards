// flashcards project

#include <iostream>
#include <string>
using namespace std;


// υλοποίηση για τις κάρτες
class Card{
public:
    Card(){
        cout << "New card created" << endl;
    }
    Card(string user, string question, string answer){
        Question = question;
        Answer = answer;
    }

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

    // show q and a 
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
        cout << "Saved! " << endl;
    }


private:
    string Question;
    string Answer;
};


// υλοποίηση για τις συλλογές καρτών
class Decks:Card {
    Decks(){}
};


// μελέτη με χρονική επανάληψη 
class Time:Card{
    Time(){}
};


// Main συνάρτηση
int main() {
    
    Card card1;
    Card card2;
    
    card1.setQuestion("blabla");
    card1.Show();
    


    return 0;
}
