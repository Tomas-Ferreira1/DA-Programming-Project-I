#pragma once
#include <string>

class Reviewer {
    private:
    int id;
    std::string name;
    std::string email;
    int primaryDomain;
    int secondaryDomain;

    public:

    Reviewer(int id, std::string name, std::string email, int primaryDomain, int secondaryDomain)
    : id(id), name(name), email(email), primaryDomain(primaryDomain), secondaryDomain(secondaryDomain) {}

    int getId() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    std::string getEmail() const {
        return email;
    }

    int getPrimaryDomain() const {
        return primaryDomain;
    }

    int getSecondaryDomain() const {
        return secondaryDomain;
    }
};