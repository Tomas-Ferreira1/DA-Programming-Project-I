#pragma once
#include <string>

class Submission {
    private:
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primaryDomain;
    int secondaryDomain;

    public:

    Submission(int id, std::string title, std::string authors, std::string email, int primaryDomain, int secondaryDomain)
    : id(id), title(title), authors(authors), email(email), primaryDomain(primaryDomain), secondaryDomain(secondaryDomain){}

    int getId() const {
        return id;
    }

    std::string getTitle() const {
        return title;
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