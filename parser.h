#ifndef PARSER_H
#define PARSER_H

#include <string>

enum CommandType {
    CMD_INSERT,
    CMD_SELECT_ALL,
    CMD_SELECT_ONE,
    CMD_DELETE,
    CMD_UPDATE,
    CMD_EXIT,
    CMD_INVALID
};

struct Command {
    CommandType type;
    int id;
    std::string name;
    int age;
};

Command parseCommand(const std::string& input);

#endif
