#include "Database.h"
#include <iostream>


class Deck {
public:
    Deck() { deck_id = -1; }
    Deck(string Name) { name = Name; deck_id = -1; }

    void setDeckID(int id) { deck_id = id; }
    int getDeckID() const { return deck_id; }

    string getName() const { return name; }
    void setName(string Name) { name = Name; }

private:
    string name;
    int deck_id;
};


// implementation of the sqlite logic
// function to create/open the database 
int Database::createDB(const char* s) {
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
int Database::createTable(const char* s) {
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

    for (string& query : queries) {
        exit = sqlite3_exec(DB, query.c_str(), 0, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "SQL Error: " << messageError << endl;
            sqlite3_free(messageError);
        } else {
            cout << "Table created successfully" << endl;
        }
    }

    sqlite3_close(DB);
    return 0;
}


int Database::insertDeck(sqlite3* DB, Deck &deck) {
    string sql = "INSERT INTO DECKS (NAME) VALUES (?);";
    sqlite3_stmt* stmt;

    int exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    sqlite3_bind_text(stmt, 1, deck.getName().c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        cerr << "Error inserting data: " << sqlite3_errmsg(DB) << endl;
    } else {
        cout << "Deck inserted successfully!" << endl;

        int new_id = sqlite3_last_insert_rowid(DB);
        deck.setDeckID(new_id);
    }

    sqlite3_finalize(stmt);
    return exit;
}


int Database::insertCard(sqlite3* DB,int deck_id, const string& question, const string& answer)
{
    string sql = "INSERT INTO CARDS(DECK_ID, QUESTION, ANSWER) VALUES(?, ?, ?);";

    sqlite3_stmt* stmt; // use prepared statement

    int exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if(exit != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    
    // allocate 
    sqlite3_bind_int(stmt, 1, deck_id);
    sqlite3_bind_text(stmt, 2, question.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, answer.c_str(), -1, SQLITE_STATIC);

    exit = sqlite3_step(stmt);
    if(exit != SQLITE_DONE)
    {
        cerr << "Error inserting data: " << sqlite3_errmsg(DB) << endl;

    }else
    {
        cout << "Card inserted successfully!" << endl;
    }

    sqlite3_finalize(stmt);
    return exit;
}

