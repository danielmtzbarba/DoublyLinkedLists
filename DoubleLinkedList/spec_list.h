#pragma once

#include "utils.h"


class SpecNode {
public:
	std::string id;
	std::string name;
    std::string userid;

	SpecNode* next;
	SpecNode* prev;

    SpecNode(const std::string& id,
        const std::string name,
        const std::string userid)
		: id(id), name(name), userid(userid),
		next(nullptr), prev(nullptr) {
	}
};

class SpecList {
public:
    SpecNode* head;
    SpecNode* tail;

    SpecList() : head(nullptr), tail(nullptr) {}

    void append(SpecNode* newNode) {
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
        SpecNode* current = head;
        while (current) {
            SpecNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addSpec(const std::string& id,
        const std::string& name,
        const std::string userid){
        SpecNode* newNode = new SpecNode(id, name, userid);
        append(newNode);
    }

    bool removeSpecById(const std::string& id) {
        SpecNode* current = head;
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
        const std::string& filename = "specialties.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        SpecNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->name);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "specialties.bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }
        clear(); // make sure list is empty

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string name = readString(inFile);
            std::string userid = readString(inFile);

            SpecNode* newNode = new SpecNode(id, name, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<SpecNode*> extractToVector() {
        std::vector<SpecNode*> nodes;
        SpecNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }
};

extern SpecList spec_list;
