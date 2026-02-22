#include <iostream>
#include <fstream>
#include <cstring>
#include "storage.h"

using namespace std;

Storage::Storage(const char* file) {
    filename = file;
}

void Storage::load() {
    records.clear();
    indexMap.clear();

    ifstream file(filename, ios::binary);

    Record r;
    int position = 0;

    while (file.read((char*)&r, sizeof(Record))) {
        records.push_back(r);
        indexMap[r.id] = position;
        position++;
    }

    file.close();
}

void Storage::save() {
    ofstream out(filename, ios::binary | ios::trunc);

    for (auto &r : records) {
        out.write((char*)&r, sizeof(Record));
    }

    out.close();
}

bool Storage::insertRecord(int id, const char* name, int age) {

    if(indexMap.find(id) != indexMap.end())
        return false;   // duplicate

    Record r;
    r.id = id;
    strcpy(r.name, name);
    r.age = age;

    records.push_back(r);
    indexMap[id] = records.size() - 1;

    ofstream file(filename, ios::binary | ios::app);
    file.write((char*)&r, sizeof(Record));
    file.close();

    return true;
}



void Storage::selectAll() {
    for (auto &r : records) {
        cout << r.id << " " << r.name << " " << r.age << endl;
    }
}

bool Storage::deleteRecord(int id) {

    if(indexMap.find(id) == indexMap.end())
        return false;

    int pos = indexMap[id];

    records.erase(records.begin() + pos);

    indexMap.erase(id);

    // rebuild index positions
    for(int i = 0; i < records.size(); i++)
        indexMap[records[i].id] = i;

    saveAll();
    return true;
}

void Storage::saveAll() {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);

    for (auto &r : records) {
        file.write((char*)&r, sizeof(Record));
    }

    file.close();
}

bool Storage::selectById(int id) {

    if(indexMap.find(id) == indexMap.end())
        return false;

    int pos = indexMap[id];
    Record &r = records[pos];

    cout << r.id << " " << r.name << " " << r.age << endl;
    return true;
}

bool Storage::updateRecord(int id, const char* name, int age) {
    for (auto &r : records) {
        if (r.id == id) {
            strcpy(r.name, name);
            r.age = age;
            saveAll();
            return true;
        }
    }
    return false;
}
