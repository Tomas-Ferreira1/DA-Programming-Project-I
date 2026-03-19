#pragma once
#include <string>
using namespace std;

class Config {
    private:
    // Secção #Parameters
    int minReviewsPerSubmission;
    int maxReviewsPerReviewer;
    int primaryReviewerExpertise;
    int secondaryReviewerExpertise;
    int primarySubmissionDomain;
    int secondarySubmissionDomain;
    
    // Secção #Control
    int generateAssignments;
    int riskAnalysis;
    std::string outputFilename;

    public:
    // Contrutor: Inicializa tudo com valores seguros por defeito

    Config()
    : minReviewsPerSubmission(0), maxReviewsPerReviewer(0), primaryReviewerExpertise(0), secondaryReviewerExpertise(0), primarySubmissionDomain(0), secondarySubmissionDomain(0), generateAssignments(0), riskAnalysis(0), outputFilename("output.csv") {}

    // Os Setters
    void setMinReviewsPerSubmission(int val) {minReviewsPerSubmission = val;}
    void setMaxReviewsPerSubmission(int val) {maxReviewsPerReviewer = val;}
    void setPrimaryReviewerExpertise(int val) {primaryReviewerExpertise = val;}
    void setSecondaryReviewerExpertise(int val) {secondaryReviewerExpertise = val;}
    void setPrimarySubmissionDomain(int val) {primarySubmissionDomain = val;}
    void setSecondarySubmissionDomain(int val) {secondarySubmissionDomain = val;}
    void setGenerateAssignments(int val) {generateAssignments = val;}
    void setRiskAnalysis(int val) {riskAnalysis = val;}
    void setOutputFileName(const std::string& name) {outputFilename = name;}

    int getMinReviewsPerSubmission() const {
        return minReviewsPerSubmission;
    }

    int getMaxReviewsPerReviewer() const { 
        return maxReviewsPerReviewer;
    }

    int getPrimaryReviewerExpertise() const { 
        return primaryReviewerExpertise; 
    }
    
    int getSecondaryReviewerExpertise() const { 
        return secondaryReviewerExpertise; 
    }

    int getPrimarySubmissionDomain() const { 
        return primarySubmissionDomain; 
    }

    int getSecondarySubmissionDomain() const { 
        return secondarySubmissionDomain; 
    }
    
    int getGenerateAssignments() const { 
        return generateAssignments; 
    }

    int getRiskAnalysis() const { 
        return riskAnalysis; 
    }
    
    std::string getOutputFileName() const { 
        return outputFilename; 
    }
};