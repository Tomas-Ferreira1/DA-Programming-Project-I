#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream> // Permite Partir a String
#include <algorithm>
#include "Parser.h"

void Parser::parse(const std::string& filename){
    // Abrir o Ficheiro
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cerr << "Erro: Não foi possivel abrir o ficheiro" << filename << std::endl;
        return;
    }

    std::string line;
    std::string currentSection = ""; // Indica em que parte do ficheiro estamos

    // Ler o Ficheiro Linha a linha até ao fim
    while(std::getline(file,line)){

        // --- LIMPEZA DE COMENTÁRIOS E MUDANÇA DE SECÇÃO ---

        // Procurar se existe algum '#' na linha 
        size_t hashPos = line.find('#');

        if(hashPos != std::string::npos) {

            // Vereficamos se é um titulo de uma Secção
            if(line.find("#Submissions") == 0) {currentSection = "Submissions"; continue;}
            if(line.find("#Reviewers") == 0) {currentSection = "Reviewers"; continue;}
            if(line.find("#Parameters") == 0) {currentSection = "Parameters"; continue;}
            if(line.find("#Control") == 0) {currentSection = "Control"; continue;}
            
            line = line.substr(0,hashPos);
        }
            
        if(line.empty()) {
            continue;
        }

        // --- PARTIR A LINHA PELAS VÍRGULAS ---

        // Transformamos a nossa string num Stream para podermos extrair pedaços
        std::stringstream ss(line); 
   
        // Submissions
        if(currentSection == "Submissions") {

            std::string idStr, title, authors, email, primaryStr, secondaryStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, title, ',');
            std::getline(ss, authors, ',');
            std::getline(ss, email, ',');
            std::getline(ss, primaryStr, ',');
            std::getline(ss, secondaryStr);

            int id = std::stoi(idStr);
            int primary = std::stoi(primaryStr);

            // SecondaryStr pode estar vazio
            int secondary = 0;
            if(!secondaryStr.empty() && secondaryStr.find_first_not_of(" \r\n") != std::string::npos){
                secondary = std::stoi(secondaryStr);
            }

            // Criar o objeto usando o construtor
            Submission novaSubmissao(id, title, authors, email, primary, secondary);

            // Guardar a submissão dentro do vetor de submissões
            submissions.push_back(novaSubmissao);  
        }

        // Reviewers
        else if(currentSection == "Reviewers"){

            std::string idStr, name, email, primaryStr, secondaryStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, email, ',');
            std::getline(ss, primaryStr, ',');
            std::getline(ss, secondaryStr);

            int id = std::stoi(idStr);
            int primary = std::stoi(primaryStr);

            int secondary = 0;
            if (!secondaryStr.empty() && secondaryStr.find_first_not_of(" \r\n") != std::string::npos) {
                secondary = std::stoi(secondaryStr);
            }

            Reviewer novoRevisor(id,name,email,primary,secondary);

            reviewers.push_back(novoRevisor);
        }
        
        else if(currentSection == "Parameters" || currentSection == "Control"){

            std::string paramName, paramvalueStr;

            // Lemos a primeira parte até à virgula (o nome) e o que sobra (o valor)
            if(std::getline(ss, paramName, ',') && std::getline(ss, paramvalueStr)){
                size_t start = paramvalueStr.find_first_not_of(" \t\r\n");
                if(start != std::string::npos) {
                    paramvalueStr = paramvalueStr.substr(start);
                }

                start = paramName.find_first_not_of(" \t\r\n");
                if (start != std::string::npos) {
                    paramName = paramName.substr(start);
                }

                // Agora comparamos o nome que lemos com os nomes que conhecemos.
                if (paramName == "MinReviewsPerSubmission") {
                    config.setMinReviewsPerSubmission(std::stoi(paramvalueStr));
                } 
                else if (paramName == "MaxReviewsPerReviewer") {
                    config.setMaxReviewsPerSubmission(std::stoi(paramvalueStr));
                } 
                else if (paramName == "PrimaryReviewerExpertise") {
                    config.setPrimaryReviewerExpertise(std::stoi(paramvalueStr));
                } 
                else if (paramName == "SecondaryReviewerExpertise") {
                    config.setSecondaryReviewerExpertise(std::stoi(paramvalueStr));
                } 
                else if (paramName == "PrimarySubmissionDomain") {
                    config.setPrimarySubmissionDomain(std::stoi(paramvalueStr));
                } 
                else if (paramName == "SecondarySubmissionDomain") {
                    config.setSecondarySubmissionDomain(std::stoi(paramvalueStr));
                } 
                else if (paramName == "GenerateAssignments") {
                    config.setGenerateAssignments(std::stoi(paramvalueStr));
                } 
                else if (paramName == "RiskAnalysis") {
                    config.setRiskAnalysis(std::stoi(paramvalueStr));
                }
                else if (paramName == "OutputFileName") {
                    // O nome do ficheiro de output vem rodeado de aspas no guião Vamos retirar essas aspas antes de guardar
                    if (paramvalueStr.front() == '"' && paramvalueStr.back() == '"') {
                        paramvalueStr = paramvalueStr.substr(1, paramvalueStr.size() - 2);
                    }
                    config.setOutputFileName(paramvalueStr);
                }
            } 
        }
    }
    file.close();
}