#include <iostream>
#include <string>
#include "storage.h"
#include "parser.h"

using namespace std;

int main() {
    Storage db("database.bin");
    db.load();

    string input;

    while (true) {
        cout << "db> ";
        getline(cin, input);

        ParsedCommand cmd = parseCommand(input);

        if (cmd.type == CMD_INSERT) {
            db.insertRecord(cmd.id, cmd.name.c_str(), cmd.age);
        }
        else if (cmd.type == CMD_SELECT) {
            db.selectAll();
        }
        else if (cmd.type == CMD_EXIT) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Unknown command.\n";
        }
    }

    return 0;
}