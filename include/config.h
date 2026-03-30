#pragma once
#include <string>
using namespace std;

/**
 * @brief Classe que armazena as configuracoes e parametros do sistema.
 * Guarda as regras globais definidas no ficheiro de input, como limites
 * de revisoes e diretrizes de execucao (controlos).
 */
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

    /**
     * @brief Construtor padrao da classe Config.
     * Inicializa todos os parametros numericos a 0 e o ficheiro de output para "output.csv".
     */
    // Contrutor: Inicializa tudo com valores seguros por defeito
    Config()
            : minReviewsPerSubmission(0), maxReviewsPerReviewer(0), primaryReviewerExpertise(0), secondaryReviewerExpertise(0), primarySubmissionDomain(0), secondarySubmissionDomain(0), generateAssignments(0), riskAnalysis(0), outputFilename("output.csv") {}

    // Os Setters

    /** @brief Define o minimo de revisoes necessarias por submissao. */
    void setMinReviewsPerSubmission(int val) {minReviewsPerSubmission = val;}

    /** @brief Define o maximo de revisoes permitidas por revisor. */
    void setMaxReviewsPerSubmission(int val) {maxReviewsPerReviewer = val;}

    /** @brief Define o peso/regra para a especialidade principal do revisor. */
    void setPrimaryReviewerExpertise(int val) {primaryReviewerExpertise = val;}

    /** @brief Define o peso/regra para a especialidade secundaria do revisor. */
    void setSecondaryReviewerExpertise(int val) {secondaryReviewerExpertise = val;}

    /** @brief Define o peso/regra para o dominio principal da submissao. */
    void setPrimarySubmissionDomain(int val) {primarySubmissionDomain = val;}

    /** @brief Define o peso/regra para o dominio secundario da submissao. */
    void setSecondarySubmissionDomain(int val) {secondarySubmissionDomain = val;}

    /** @brief Ativa ou desativa a geracao de atribuicoes. */
    void setGenerateAssignments(int val) {generateAssignments = val;}

    /** @brief Ativa ou desativa a execucao da analise de risco. */
    void setRiskAnalysis(int val) {riskAnalysis = val;}

    /** @brief Define o nome do ficheiro CSV onde os resultados serao guardados. */
    void setOutputFileName(const std::string& name) {outputFilename = name;}

    // Os Getters

    /** @brief Obtem o minimo de revisoes por submissao. */
    int getMinReviewsPerSubmission() const {
        return minReviewsPerSubmission;
    }

    /** @brief Obtem o maximo de revisoes por revisor. */
    int getMaxReviewsPerReviewer() const {
        return maxReviewsPerReviewer;
    }

    /** @brief Obtem a regra da especialidade principal do revisor. */
    int getPrimaryReviewerExpertise() const {
        return primaryReviewerExpertise;
    }

    /** @brief Obtem a regra da especialidade secundaria do revisor. */
    int getSecondaryReviewerExpertise() const {
        return secondaryReviewerExpertise;
    }

    /** @brief Obtem a regra do dominio principal da submissao. */
    int getPrimarySubmissionDomain() const {
        return primarySubmissionDomain;
    }

    /** @brief Obtem a regra do dominio secundario da submissao. */
    int getSecondarySubmissionDomain() const {
        return secondarySubmissionDomain;
    }

    /** @brief Verifica se a geracao de atribuicoes esta ativa. */
    int getGenerateAssignments() const {
        return generateAssignments;
    }

    /** @brief Verifica se a analise de risco esta ativa. */
    int getRiskAnalysis() const {
        return riskAnalysis;
    }

    /** @brief Obtem o nome atual do ficheiro de output configurado. */
    std::string getOutputFileName() const {
        return outputFilename;
    }
};