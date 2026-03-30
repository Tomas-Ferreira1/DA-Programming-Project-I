#pragma once
#include <string>
#include <vector>
#include "Submission.h"
#include "Reviewer.h"
#include "Config.h"

/**
 * @brief Classe responsavel por ler e interpretar o ficheiro de dados (CSV).
 * Extrai as configuracoes, submissoes e revisores, guardando-os em memoria
 * para serem usados pelo algoritmo de Max-Flow.
 */
class Parser {
private:
    // Onde Guardamos os dados lidos
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;

    Config config;

public:

    /**
     * @brief Le o ficheiro de texto fornecido e popula as estruturas de dados.
     * @param filename O caminho para o ficheiro a ser lido (ex: data/input.csv).
     */
    void parse(const std::string& filename);

    /**
     * @brief Obtem a lista de submissoes lidas do ficheiro.
     * @return Um vetor contendo todos os objetos Submission carregados.
     */
    std::vector<Submission> getSubmissions() const {return submissions;}

    /**
     * @brief Obtem a lista de revisores lidos do ficheiro.
     * @return Um vetor contendo todos os objetos Reviewer carregados.
     */
    std::vector<Reviewer> getReviewers() const {return reviewers;}

    /**
     * @brief Obtem as configuracoes e parametros lidos do ficheiro.
     * @return Um objeto Config com as regras da conferencia (ex: min reviews).
     */
    Config getConfig() const {return config;}
};