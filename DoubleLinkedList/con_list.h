#pragma once

#include "utils.h"


class ConsultoryNode {
public:
    std::string id;
    std::string name;
    std::string spec;
    std::string days;
    std::string hours;
    std::string userid;

    ConsultoryNode* next;
    ConsultoryNode* prev;

    ConsultoryNode(const std::string& id,
        const std::string&name, const std::string&spec, const std::string& days,
        const std::string& hours, const std::string& userid)
        : id(id), name(name), spec(spec), days(days), hours(hours), userid(userid),
        next(nullptr), prev(nullptr) {
    }
};

class ConsultoryList {
public:
    ConsultoryNode* head;
    ConsultoryNode* tail;

    ConsultoryList() : head(nullptr), tail(nullptr) {}

    void append(ConsultoryNode* newNode) {
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void clear() {
        ConsultoryNode* current = head;
        while (current) {
            ConsultoryNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addConsultory(const std::string& id,
        const std::string& name,
        const std::string& spec,
        const std::string& days,
        const std::string& hours,
        const std::string& userid) {
        ConsultoryNode* newNode = new ConsultoryNode(id, name, spec, days, hours, userid);
        append(newNode);
    }

    bool updateConsultoryById(const std::string& id,
        const std::string& newName,
        const std::string& newSpec,
        const std::string& newDays,
        const std::string& newHours,
        const std::string& newUserid) {
        ConsultoryNode* current = head;
        while (current) {
            if (current->id == id) {
                current->name = newName;
                current->spec = newSpec;
                current->days = newDays;
                current->hours = newHours;
                current->userid = newUserid;
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool removeConsultoryById(const std::string& id) {
        ConsultoryNode* current = head;
        while (current) {
            if (current->id == id) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;

                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;

                delete current;
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    void saveToFile() const {
        const std::string& filename = "consultory.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        ConsultoryNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->days);
            writeString(outFile, current->hours);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "consultory.bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        clear(); // make sure list is empty

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string name = readString(inFile);
            std::string spec = readString(inFile);
            std::string days= readString(inFile);
            std::string hours= readString(inFile);
            std::string userid = readString(inFile);

            ConsultoryNode* newNode = new ConsultoryNode(id, name, spec, days, hours, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<ConsultoryNode*> extractToVector() {
        std::vector<ConsultoryNode*> nodes;
        ConsultoryNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }
};

extern ConsultoryList consultory_list;
