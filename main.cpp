#include <iostream>
#include <string>
#include "storage.h"
#include "parser.h"

using namespace std;

int main() {
    Storage db("data.bin");
    db.load();

    string input;

    while (true) {
        cout << "db> ";
        getline(cin, input);

        Command cmd = parseCommand(input);

        if (cmd.type == CMD_INSERT) {
            db.insertRecord(cmd.id, cmd.name.c_str(), cmd.age);
        }

        else if (cmd.type == CMD_SELECT_ALL) {
            db.selectAll();
        }

        else if (cmd.type == CMD_SELECT_ONE) {
            if (!db.selectById(cmd.id))
                cout << "Record not found.\n";
        }

        else if (cmd.type == CMD_DELETE) {
            if (db.deleteRecord(cmd.id))
                cout << "Deleted.\n";
            else
                cout << "Record not found.\n";
        }

        else if (cmd.type == CMD_UPDATE) {
            if (db.updateRecord(cmd.id, cmd.name.c_str(), cmd.age))
                cout << "Updated.\n";
            else
                cout << "Record not found.\n";
        }

        else if (cmd.type == CMD_EXIT) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}
