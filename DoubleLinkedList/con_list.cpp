#pragma once

#include "utils.h"


class ConsultoryNode {
public:
    std::string id;
    std::string days;
    std::string hours;

    ConsultoryNode* next;
    ConsultoryNode* prev;

    ConsultoryNode(const std::string& id,
        const std::string& fname,
        const std::string& lname1,
        const std::string& lname2,
        const std::string& email,
        const std::string& phone,
        const std::string& spec,
        const std::string& userid)
        : id(id), fname(fname), lname1(lname1), lname2(lname2),
        email(email), phone(phone), spec(spec), userid(userid),
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

    void addMedic(const std::string& id,
        const std::string& fname,
        const std::string& lname1,
        const std::string& lname2,
        const std::string& email,
        const std::string& phone,
        const std::string& spec,
        const std::string& userid) {
        ConsultoryNode* newNode = new ConsultoryNode(id, fname, lname1, lname2, email, phone, spec, userid);
        append(newNode);
    }

    bool updateMedicById(const std::string& id,
        const std::string& newFname,
        const std::string& newLname1,
        const std::string& newLname2,
        const std::string& newEmail,
        const std::string& newPhone,
        const std::string& newSpec,
        const std::string& newUserid) {
        ConsultoryNode* current = head;
        while (current) {
            if (current->id == id) {
                current->fname = newFname;
                current->lname1 = newLname1;
                current->lname2 = newLname2;
                current->email = newEmail;
                current->phone = newPhone;
                current->spec = newSpec;
                current->userid = newUserid;
                return true;
            }
            current = current->next;
        }
        return false; // not found
    }

    bool removeMedicById(const std::string& id) {
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

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        ConsultoryNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->fname);
            writeString(outFile, current->lname1);
            writeString(outFile, current->lname2);
            writeString(outFile, current->email);
            writeString(outFile, current->phone);
            writeString(outFile, current->spec);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        clear(); // make sure list is empty

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string fname = readString(inFile);
            std::string lname1 = readString(inFile);
            std::string lname2 = readString(inFile);
            std::string email = readString(inFile);
            std::string phone = readString(inFile);
            std::string spec = readString(inFile);
            std::string userid = readString(inFile);

            ConsultoryNode* newNode = new ConsultoryNode(id, fname, lname1, lname2, email, phone, spec, userid);
            append(newNode);
        }

        inFile.close();
    }

    void printList() const {
        ConsultoryNode* current = head;
        while (current) {
            std::cout << "ID: " << current->id << ", Name: "
                << current->fname << " " << current->lname1 << " " << current->lname2
                << ", Email: " << current->email
                << ", Phone: " << current->phone
                << ", Specialty: " << current->spec << "\n";
            current = current->next;
        }
    }
};