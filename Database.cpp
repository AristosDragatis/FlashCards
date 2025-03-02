/* This file is the implementation of the Database logic
 *
 * */ 
#include "Database.h"
#include <iostream>


class Deck {
public:
    Deck() { deck_id = -1; }
    Deck(string Name) { this->name = Name; this->deck_id = -1; }

    void setDeckID(int id) { this->deck_id = id; }
    int getDeckID() { return this->deck_id; }

    string getName() { return name; }
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



bool Database::tableExists(sqlite3* db, const string& tableName) {
    string sql = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name=?;";
    sqlite3_stmt* stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, tableName.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return count > 0;
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

    struct TableInfo {
        string name;
        string query;
    };

    TableInfo tables[] = {
        {"DECKS", "CREATE TABLE IF NOT EXISTS DECKS ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "NAME TEXT UNIQUE NOT NULL );"},
        {"CARDS", "CREATE TABLE IF NOT EXISTS CARDS ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "DECK_ID INTEGER, "
                  "QUESTION TEXT NOT NULL, "
                  "ANSWER TEXT NOT NULL, "
                  "FOREIGN KEY (DECK_ID) REFERENCES DECKS(ID) ON DELETE CASCADE, "
                  "UNIQUE (QUESTION) );"},
        {"STUDY", "CREATE TABLE IF NOT EXISTS STUDY ("
                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "CARD_ID INTEGER, "
                  "TOTAL_TIME REAL, "
                  "TIME_PER_CARD REAL, "
                  "CARDS_VIEWED INTEGER DEFAULT 0, "
                  "FOREIGN KEY (CARD_ID) REFERENCES CARDS(ID) ON DELETE CASCADE );"}
    };

    for (const auto& table : tables) {
        if (!tableExists(DB, table.name)) {
            exit = sqlite3_exec(DB, table.query.c_str(), 0, 0, &messageError);
            if (exit != SQLITE_OK) {
                cerr << "SQL Error: " << messageError << endl;
                sqlite3_free(messageError);
            } else {
                cout << "Table '" << table.name << "' created successfully" << endl;
            }
        } else {
            cout << "Table '" << table.name << "' already exists" << endl;
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


int Database::selectDeck(sqlite3* DB){
    string sql = "SELECT * FROM DECKS"; 

    sqlite3_stmt* stmt;
    int exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if(exit != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }


    while((exit = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string deckName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        cout << "ID: " << id << "| Name: " << deckName << endl;
    }

    if(exit != SQLITE_DONE)
    {
        cerr << "Error selecting data: " << sqlite3_errmsg(DB) << endl;
    }

    sqlite3_finalize(stmt);
    return exit == SQLITE_DONE ? SQLITE_OK : exit;
}



int Database::selectCard(sqlite3* DB, Deck &deck)
{
    string sql = "SELECT * FROM CARDS WHERE  deck_id = ?";
    sqlite3_stmt* stmt;
    int exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    

    if(exit != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        return exit;
    }

    int deckID = deck.getDeckID();
    cout << "DECK id: " << deckID << endl;
    sqlite3_bind_int(stmt, 1, deckID);


    bool found = false;
    while((exit = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        found = true;
        int id = sqlite3_column_int(stmt, 0);
        string question = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string answer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));


        cout << "Card id: " << id << " |  Q: " << question << " |  A: " << answer << endl;

    }


    if (!found) {
    cout << "No cards found for deck_id: " << deck.getDeckID() << endl;
    }


    if(exit != SQLITE_DONE)
    {
        cerr << "Error selecting data: " << sqlite3_errmsg(DB) << endl;
    }

    sqlite3_finalize(stmt);
    return (exit == SQLITE_DONE || exit == SQLITE_ROW) ? SQLITE_OK : exit;
}



void Database::deleteDeck(sqlite3* db, int deckID) {
    string sql1 = "DELETE FROM CARDS WHERE deck_id = ?;";
    string sql2 = "DELETE FROM DECKS WHERE ID = ?;";
    string resetSql = "DELETE FROM sqlite_sequence WHERE name='DECKS';";

    sqlite3_stmt* stmt;

    // Διαγραφή καρτών του Deck
    if (sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, deckID);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error deleting cards: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Διαγραφή του Deck
    if (sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, deckID);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        cout << "Deck with ID " << deckID << " deleted!" << endl;
    } else {
        cerr << "Error deleting deck: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Έλεγχος αν υπάρχουν άλλα decks, αν όχι μηδενίζει τον μετρητή
    string checkSql = "SELECT COUNT(*) FROM DECKS;";
    int count = 0;
    if (sqlite3_prepare_v2(db, checkSql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    if (count == 0) {
        sqlite3_exec(db, resetSql.c_str(), nullptr, nullptr, nullptr);
        cout << "Deck counter reset to 0!" << endl;
    }
}


void Database::deleteCard(sqlite3* db, int deckID, const string& question) {
    string sql = "DELETE FROM CARDS WHERE deck_id = ? AND question = ?;";
    string checkSql = "SELECT COUNT(*) FROM CARDS;";
    string resetSql = "DELETE FROM sqlite_sequence WHERE name='CARDS';";

    sqlite3_stmt* stmt;

    // Διαγραφή κάρτας
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, deckID);
        sqlite3_bind_text(stmt, 2, question.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        cout << "Card deleted successfully!" << endl;
    } else {
        cerr << "Error deleting card: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Έλεγχος αν υπάρχουν άλλες κάρτες
    int count = 0;
    if (sqlite3_prepare_v2(db, checkSql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    // Αν δεν υπάρχουν άλλες κάρτες, μηδενίζει το AUTOINCREMENT
    if (count == 0) {
        sqlite3_exec(db, resetSql.c_str(), nullptr, nullptr, nullptr);
        cout << "Card ID counter reset to 0!" << endl;
    } else {
        cout << "Card deleted, but ID counter not reset (still cards exist)." << endl;
    }
}

