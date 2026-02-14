#include "parser.h"
#include <sstream>

using namespace std;

Command parseCommand(const string& input) {
    Command cmd;
    cmd.type = CMD_INVALID;
    cmd.id = -1;
    cmd.age = -1;

    stringstream ss(input);
    string keyword;
    ss >> keyword;

    if (keyword == "insert") {
        cmd.type = CMD_INSERT;
        ss >> cmd.id >> cmd.name >> cmd.age;
    }
    else if (keyword == "select") {
        if (ss >> cmd.id) {
            cmd.type = CMD_SELECT_ONE;
        } else {
            cmd.type = CMD_SELECT_ALL;
        }
    }
    else if (keyword == "delete") {
        cmd.type = CMD_DELETE;
        ss >> cmd.id;
    }
    else if (keyword == "update") {
        cmd.type = CMD_UPDATE;
        ss >> cmd.id >> cmd.name >> cmd.age;
    }
    else if (keyword == "exit") {
        cmd.type = CMD_EXIT;
    }

    return cmd;
}
