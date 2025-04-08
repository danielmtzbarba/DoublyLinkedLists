#pragma once

#include "utils.h"


class AppointmentNode {
public:
    std::string id;
    std::string spec;
    std::string consid;
    std::string medicid;
    std::string day;
    std::string hour;
    std::string patientid;
    std::string status;
    std::string diag;
    std::string userid;

    AppointmentNode* next;
    AppointmentNode* prev;

    AppointmentNode(const std::string& id,
        const std::string& spec, const std::string& consid,
        const std::string& medicid, const std::string& day,
        const std::string& hour, const std::string& patientid,
        const std::string& status, const std::string& diag,
        const std::string& userid) : id(id), spec(spec), consid(consid),
        medicid(medicid), day(day), hour(hour), patientid(patientid),
        status(status), diag(diag), userid(userid),
        next(nullptr), prev(nullptr) {
    }
};

class AppointmentList {
public:
    AppointmentNode* head;
    AppointmentNode* tail;

    AppointmentList() : head(nullptr), tail(nullptr) {}

    void append(AppointmentNode* newNode) {
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
        AppointmentNode* current = head;
        while (current) {
            AppointmentNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

    void addAppointment(const std::string& id,
        const std::string& name,
        const std::string& spec,
        const std::string& consid,
        const std::string& medicid,
        const std::string& day,
        const std::string& hour,
        const std::string& patientid,
        const std::string& status,
        const std::string& diag,
        const std::string& userid) {
        AppointmentNode* newNode = new AppointmentNode(id, spec, consid, medicid, day, hour, patientid, status, diag, userid);
        append(newNode);
    }

    bool removeAppointmentById(const std::string& id) {
        AppointmentNode* current = head;
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
        const std::string& filename = "appointments.bin";
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }

        AppointmentNode* current = head;
        while (current) {
            writeString(outFile, current->id);
            writeString(outFile, current->spec);
            writeString(outFile, current->consid);
            writeString(outFile, current->medicid);
            writeString(outFile, current->day);
            writeString(outFile, current->hour);
            writeString(outFile, current->patientid);
            writeString(outFile, current->status);
            writeString(outFile, current->diag);
            writeString(outFile, current->userid);
            current = current->next;
        }

        outFile.close();
    }

    void loadFromFile() {
        const std::string& filename = "appointments.bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        clear(); // make sure list is empty

        while (inFile.peek() != EOF) {
            std::string id = readString(inFile);
            std::string spec= readString(inFile);
            std::string consid = readString(inFile);
            std::string medicid = readString(inFile);
            std::string day = readString(inFile);
            std::string hour = readString(inFile);
            std::string patientid = readString(inFile);
            std::string status = readString(inFile);
            std::string diag = readString(inFile);
            std::string userid = readString(inFile);

            AppointmentNode* newNode = new AppointmentNode(id, spec, consid, medicid, day, hour, patientid, status, diag, userid);
            append(newNode);
        }

        inFile.close();
    }

    std::vector<AppointmentNode*> extractToVector() {
        std::vector<AppointmentNode*> nodes;
        AppointmentNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        return nodes;
    }
};

extern AppointmentList appointment_list;
