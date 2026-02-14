#ifndef PARSER_H
#define PARSER_H

#include <string>

enum CommandType {
    CMD_INSERT,
    CMD_SELECT,
    CMD_EXIT,
    CMD_UNKNOWN,
    CMD_DELETE
};

struct ParsedCommand {
    CommandType type;
    int id;
    std::string name;
    int age;
};

ParsedCommand parseCommand(const std::string& input);

#endif