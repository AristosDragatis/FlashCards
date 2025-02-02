// flashcards project

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;


// υλοποίηση για τις κάρτες
class Card{
public:
    Card(){}

    Card(string question, string answer){
        Question = question;
        Answer = answer;
    }


    // getters and setters
    string getQuestion() const{
        return Question;
    }

    void setQuestion(string question){
        Question = question;
    }

    string getAnswer() const{
        return Answer;
    }

    void setAnswer(string answer){
        Answer = answer;
    }


    // show question
    void ShowQuestion(){
        if(Question.empty()){
            cerr << "This field must not be empty" << endl;
            return;
        }   
        else
            cout << "Question: " <<  getQuestion() << endl;
    }

    // show answer
    void ShowAnswer(){
        if(!Answer.empty())
            cout << "Answer: " <<  getAnswer() << endl;
        else
            cout << " " << endl;
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
    

    void add2deck(Card card){
        vec.push_back(card);
    }


    void print_deck(){
        if (vec.empty()) {
        cout << "The deck is empty!" << endl;
    } else {
        cout << "Cards in the deck:" << endl;
        for (auto& card : vec) {
            card.ShowQuestion();
            card.ShowAnswer();
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
    void delete_deck(){
        vec.clear();
        cout << "Deck is deleted!" << endl;
    }


    // updating the cards in the vector
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



};



// μελέτη με χρονική επανάληψη 
class Study{
public:
    Study(){}
    // όσο υπάρχουν τα αντικείμενα της deck και της card τοσο θα μετράω το χρόνο τους

      
    
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

    c1.setQuestion("initial?");
    c1.setAnswer("sample");
    d1.add2deck(c1);
    d1.print_deck();


    c1.setQuestion("new question");
    c1.ShowQuestion();
    c1.ShowAnswer();
    d1.update_deck(c1, c1.getQuestion(), c1.getAnswer());
    d1.print_deck();
    d1.delete_deck();
    d1.print_deck();
    

    return 0;
}


