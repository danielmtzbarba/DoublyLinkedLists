#pragma once

#include "utils.h"


class MedicNode {
public:
	std::string id;
	std::string fname;
	std::string lname1;
	std::string lname2;
	std::string email;
	std::string phone;
	std::string spec;
	std::string userid;

	MedicNode* next;
	MedicNode* prev;

	MedicNode(const std::string& id,
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

class MedicList {
public:
    MedicNode* head;
    MedicNode* tail;

    MedicList() : head(nullptr), tail(nullptr) {}

    void append(MedicNode* newNode) {
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
        MedicNode* current = head;
        while (current) {
            MedicNode* toDelete = current;
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
        MedicNode* newNode = new MedicNode(id, fname, lname1, lname2, email, phone, spec, userid);
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
        MedicNode* current = head;
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
        MedicNode* current = head;
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
        const std::string& filename = "medics.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        MedicNode* current = head;
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

    void loadFromFile() {
        const std::string& filename = "medics.bin";
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

            MedicNode* newNode = new MedicNode(id, fname, lname1, lname2, email, phone, spec, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<MedicNode*> extractToVector() {
        std::vector<MedicNode*> nodes;
        MedicNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }
    void swapNodeData(MedicNode* a, MedicNode* b) {
        std::swap(a->id, b->id);
        std::swap(a->fname, b->fname);
        std::swap(a->lname1, b->lname1);
        std::swap(a->lname2, b->lname2);
        std::swap(a->email, b->email);
        std::swap(a->phone, b->phone);
        std::swap(a->spec, b->spec);
        std::swap(a->userid, b->userid);
    }

    MedicNode* partition(MedicNode* low, MedicNode* high) {
        std::string pivot = high->lname1;
        MedicNode* i = low->prev;

        for (MedicNode* j = low; j != high; j = j->next) {
            if (j->lname1 < pivot) {
                i = (i == nullptr) ? low : i->next;
                swapNodeData(i, j);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swapNodeData(i, high);
        return i;
    }

    void quickSort(MedicNode* low, MedicNode* high) {
        if (low && high && low != high && low != high->next) {
            MedicNode* pivot = partition(low, high);
            quickSort(low, pivot->prev);
            quickSort(pivot->next, high);
        }
    }

    void printList() const {
        MedicNode* current = head;
        while (current) {
            std::ofstream log("log.txt", std::ios::app);
            log << "ID: " << current->id << ", Name: "
                << current->fname << " " << current->lname1 << " " << current->lname2
                << ", Email: " << current->email
                << ", Phone: " << current->phone
                << ", Specialty: " << current->spec << "\n";
            current = current->next;
        }
    }
};

extern MedicList medic_list;
