// flashcards project

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sqlite3.h>
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

    Deck (string Name) {
        name = Name;
    }
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


    string getName(){
        cout << name << endl;
        return name;
    }

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


    void startTime(){
        startTimer = clock();
    }


    void stopTime(){
        clock_t endTime = clock();
        double total = (double)(endTime - startTimer)/ CLOCKS_PER_SEC;
        timePerCard.push_back(total); // προσθέτουμε στο vector το χρόνο ανα κάρτα
        totalTime += total;
        cardCounter++;
    }


    // εμφάνιση στατιστικών
    void showStatistics(){
        cout << "Total study time: " << totalTime << " seconds" << endl;
        cout << "Total cards read: " << cardCounter << endl;
        if(cardCounter > 0) {
            cout << "Time per card: " << (totalTime / cardCounter) << " seconds" << endl;
        }
    }


private:
    clock_t startTimer; // ξεκίνημα χρόνου
    int cardCounter=0; // μετράει πόσες κάρτες διαβάστηκαν μέχρι στιγμής
    double totalTime = 0.0;
    vector<double> timePerCard; // χρόνος ανά κάρτα
};



// Main συνάρτηση
int main() {
    // Κάποιες δοκιμές 
    Study s1;
    Study s2;
    Card c1;
    Card c2;
    Deck d1;
    Deck d2;

    // κάρτα 1
    s1.startTime();  // Ξεκινάει το χρονόμετρο για την πρώτη κάρτα
    c1.setQuestion("This is a question");
    cout << "Press Enter to see the answer ..." << endl;
    cin.get();  
    c1.setAnswer("This is an answer");
    d1.add2deck(c1);  // Προσθέτει την κάρτα στο deck
    d1.print_deck();  
    s1.stopTime();  // Σταματά το χρονόμετρο
    s1.showStatistics();  // Εμφανίζει τα στατιστικά 

    // καρτα 2
    s1.startTime();  // Ξεκινάει το χρονόμετρο για την δεύτερη κάρτα
    c2.setQuestion("This is a question two");
    cout << "Press Enter to see the answer ..." << endl;
    cin.get();  
    c2.setAnswer("This is an answer two");
    d1.add2deck(c2);  // Προσθέτει την δεύτερη κάρτα στο deck
    d1.print_deck();  
    s1.stopTime();  // Σταματά το χρονόμετρο
    s1.showStatistics();  // Εμφανίζει τα στατιστικά


    // δοκιμή για ορισμό ονόματος σε κάθε deck
    d1.setName("mydeck");
    d1.getName();

    d2.setName("mydeck2");
    d2.getName();

    return 0;
}


