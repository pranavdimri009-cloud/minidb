#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "record.h"

class Storage {
private:
    std::vector<Record> records;
    const char* filename;

public:
    Storage(const char* file);

    void load();
    void save();

    void insertRecord(int id, const char* name, int age);
    void selectAll();

    void saveAll();
    bool deleteRecord(int id);

    bool selectById(int id);
    bool updateRecord(int id, const char* name, int age);

};

#endif