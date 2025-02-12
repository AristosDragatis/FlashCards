#ifndef DATABASE_H
#define DATABASE_H


#include <sqlite3.h>
#include <string>
using namespace std;

class Deck; // forward declaration
class Card;

class Database{
public:
    // initializing database logic
    static int createDB(const char* s);
    static int createTable(const char* s);
    static int insertDeck(sqlite3* DB, Deck &deck);
    static int insertCard(sqlite3* DB, int deck_id, const string& question, const string& answer);
    static int selectDeck(sqlite3* DB);
    static int selectCard(sqlite3* DB, Deck &deck);
    static bool tableExists(sqlite3* db, const std::string& tableName);
    static void deleteDeck(sqlite3* db, int deckID);
    static void deleteCard(sqlite3* db, int deckID, const string& question);
};

#endif