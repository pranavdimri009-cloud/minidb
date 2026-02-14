#include <iostream>
#include <fstream>
#include <cstring>
#include "storage.h"

using namespace std;

Storage::Storage(const char* file) {
    filename = file;
}

void Storage::load() {
    ifstream in(filename, ios::binary);
    if (!in.is_open()) {
        cout << "No database file found. Starting fresh.\n";
        return;
    }

    Record r;
    while (in.read((char*)&r, sizeof(Record))) {
        records.push_back(r);
    }

    in.close();
}

void Storage::save() {
    ofstream out(filename, ios::binary | ios::trunc);

    for (auto &r : records) {
        out.write((char*)&r, sizeof(Record));
    }

    out.close();
}

void Storage::insertRecord(int id, const char* name, int age) {
    Record r;
    r.id = id;
    strncpy(r.name, name, 49);
    r.name[49] = '\0';
    r.age = age;

    records.push_back(r);
    save();

    cout << "Inserted.\n";
}


void Storage::selectAll() {
    for (auto &r : records) {
        cout << r.id << " " << r.name << " " << r.age << endl;
    }
}

bool Storage::deleteRecord(int id) {
    for (int i = 0; i < records.size(); i++) {
        if (records[i].id == id) {
            records.erase(records.begin() + i);
            saveAll();
            return true;
        }
    }
    return false;
}

void Storage::saveAll() {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);

    for (auto &r : records) {
        file.write((char*)&r, sizeof(Record));
    }

    file.close();
}

bool Storage::selectById(int id) {
    for (auto &r : records) {
        if (r.id == id) {
            cout << r.id << " " << r.name << " " << r.age << endl;
            return true;
        }
    }
    return false;
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
