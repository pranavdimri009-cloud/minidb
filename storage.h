#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>

#include <vector>
#include "record.h"

class Storage {
private:
    std::vector<Record> records;
    std::unordered_map<int, int> indexMap; 
    // id → position in vector

    std::string filename;

public:
    Storage(const char* file);

    void load();
    void save();

    bool insertRecord(int id, const char* name, int age);
    void selectAll();

    void saveAll();
    bool deleteRecord(int id);

    bool selectById(int id);
    bool updateRecord(int id, const char* name, int age);

};

#endif