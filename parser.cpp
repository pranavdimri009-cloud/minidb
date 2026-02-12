#include <sstream>
#include "parser.h"

ParsedCommand parseCommand(const std::string& input) {
    ParsedCommand cmd;
    cmd.type = CMD_UNKNOWN;

    std::stringstream ss(input);
    std::string keyword;
    ss >> keyword;

    if (keyword == "insert") {
        cmd.type = CMD_INSERT;
        ss >> cmd.id >> cmd.name >> cmd.age;
    }
    else if (keyword == "select") {
        cmd.type = CMD_SELECT;
    }
    else if (keyword == "exit") {
        cmd.type = CMD_EXIT;
    }

    return cmd;
}