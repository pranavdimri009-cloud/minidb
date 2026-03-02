#include <iostream>
#include <fstream>
#include "storage.h"
#include "parser.h"

using namespace std;

int main() {

    Storage db;
    string currentTable = "";
    string input;

    cout << "MiniDB v1.0\n";

    while(true) {

        cout << "db> ";
        getline(cin, input);

        Command cmd = parseCommand(input);

        if(cmd.type == CMD_CREATE) {

    // Create table file
    ofstream file(cmd.tableName + ".tbl");
    file.close();

    ofstream meta("schema.meta", ios::app);   
    meta << cmd.tableName << " id:int name:string age:int\n";
    meta.close();

    cout << "Table created.\n";
}

        else if(cmd.type == CMD_USE) {

            currentTable = cmd.tableName;
            db.setTable(currentTable);
            db.load();

            cout << "Using table: " << currentTable << endl;
        }

        else if(currentTable == "") {
            cout << "No table selected. Use 'create table' or 'use table'.\n";
        }

        else if(cmd.type == CMD_INSERT) {

            if(db.insertRecord(cmd.id, cmd.name.c_str(), cmd.age))
                cout << "Inserted.\n";
            else
                cout << "Duplicate ID.\n";
        }

        else if(cmd.type == CMD_SELECT_ALL)
            db.selectAll();

        else if(cmd.type == CMD_SELECT_ONE) {

            if(!db.selectById(cmd.id))
                cout << "Record not found.\n";
        }

        else if(cmd.type == CMD_DELETE) {

            if(db.deleteRecord(cmd.id))
                cout << "Deleted.\n";
            else
                cout << "Record not found.\n";
        }
        else if(cmd.type == CMD_SHOW_TABLES) {
        db.showTables();}
                  
        else if(cmd.type == CMD_UPDATE) {

            if(db.updateRecord(cmd.id, cmd.name.c_str(), cmd.age))
                cout << "Updated.\n";
            else
                cout << "Record not found.\n";
        }

        else if(cmd.type == CMD_EXIT) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}