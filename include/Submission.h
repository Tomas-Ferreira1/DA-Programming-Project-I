#pragma once
#include <string>

/**
 * @brief Classe que representa uma submissao (artigo) na conferencia.
 * Armazena os detalhes do artigo, os autores e as areas de dominio
 * em que o trabalho se insere (primario e secundario).
 */
class Submission {
private:
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primaryDomain;
    int secondaryDomain;

public:

    /**
     * @brief Construtor da classe Submission.
     * @param id Identificador unico da submissao.
     * @param title Titulo do artigo cientifico.
     * @param authors Nome do(s) autor(es) do artigo.
     * @param email Endereco de email de contacto.
     * @param primaryDomain Area de dominio principal do artigo.
     * @param secondaryDomain Area de dominio secundaria do artigo.
     */
    Submission(int id, std::string title, std::string authors, std::string email, int primaryDomain, int secondaryDomain)
            : id(id), title(title), authors(authors), email(email), primaryDomain(primaryDomain), secondaryDomain(secondaryDomain){}

    /**
     * @brief Obtem o ID unico da submissao.
     * @return int O identificador do artigo.
     */
    int getId() const {
        return id;
    }

    /**
     * @brief Obtem o titulo do artigo.
     * @return std::string O titulo da submissao.
     */
    std::string getTitle() const {
        return title;
    }

    /**
     * @brief Obtem o email de contacto da submissao.
     * @return std::string O email do autor principal.
     */
    std::string getEmail() const {
        return email;
    }

    /**
     * @brief Obtem o dominio principal da submissao.
     * @return int O codigo do dominio principal.
     */
    int getPrimaryDomain() const {
        return primaryDomain;
    }

    /**
     * @brief Obtem o dominio secundario da submissao.
     * @return int O codigo do dominio secundario.
     */
    int getSecondaryDomain() const {
        return secondaryDomain;
    }
};