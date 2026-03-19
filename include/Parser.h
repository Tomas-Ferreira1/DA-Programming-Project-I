#pragma once
#include <string>
#include <vector>
#include "Submission.h"
#include "Reviewer.h"
#include "Config.h"

class Parser {
    private:
    // Onde Guardamos os dados lidos
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;

    Config config;

    public:
    
    void parse(const std::string& filename);
    std::vector<Submission> getSubmissions() const {return submissions;}
    std::vector<Reviewer> getReviewers() const {return reviewers;}
    Config getConfig() const {return config;}
};