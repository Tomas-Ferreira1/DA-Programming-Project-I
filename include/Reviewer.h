#pragma once
#include <string>

/**
 * @brief Classe que representa um Revisor (avaliador) na conferencia.
 * Armazena os dados pessoais do revisor e as suas areas de especialidade
 * (dominios primario e secundario) para cruzamento com os artigos.
 */
class Reviewer {
private:
    int id;
    std::string name;
    std::string email;
    int primaryDomain;
    int secondaryDomain;

public:

    /**
     * @brief Construtor da classe Reviewer.
     * @param id Identificador unico do revisor.
     * @param name Nome completo do revisor.
     * @param email Endereco de email do revisor.
     * @param primaryDomain Area de especialidade principal (onde tem de avaliar).
     * @param secondaryDomain Area de especialidade secundaria (para desempates ou risco).
     */
    Reviewer(int id, std::string name, std::string email, int primaryDomain, int secondaryDomain)
            : id(id), name(name), email(email), primaryDomain(primaryDomain), secondaryDomain(secondaryDomain) {}

    /**
     * @brief Obtem o ID unico do revisor.
     * @return int O identificador do revisor.
     */
    int getId() const {
        return id;
    }

    /**
     * @brief Obtem o nome do revisor.
     * @return std::string O nome do revisor.
     */
    std::string getName() const {
        return name;
    }

    /**
     * @brief Obtem o email do revisor.
     * @return std::string O email do revisor.
     */
    std::string getEmail() const {
        return email;
    }

    /**
     * @brief Obtem o dominio de especialidade principal do revisor.
     * @return int O codigo do dominio principal.
     */
    int getPrimaryDomain() const {
        return primaryDomain;
    }

    /**
     * @brief Obtem o dominio de especialidade secundario do revisor.
     * @return int O codigo do dominio secundario.
     */
    int getSecondaryDomain() const {
        return secondaryDomain;
    }
};