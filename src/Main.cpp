#include <iostream>
#include <string>
#include "Parser.h"

// ---(MENU) ---
void runInteractiveMenu() {
    int choice = -1;
    std::string filename;
    
    // ferramenta de extração de dados
    Parser parser; 

    while (choice != 0) {
        std::cout << "\n==================================================\n";
        std::cout << "   FERRAMENTA DE ORGANIZACAO DE CONFERENCIA\n";
        std::cout << "==================================================\n";
        std::cout << "1. Ler ficheiro de dados (Parser)\n";
        std::cout << "2. Gerar Atribuicoes (Max-Flow - A implementar)\n";
        std::cout << "0. Sair\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "Escolha uma opcao: ";
        
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Introduza o caminho do ficheiro (ex: data/input.csv): ";
            std::cin >> filename;
            
            parser.parse(filename);
            
            // Imprimir
            std::cout << "\n[SUCESSO] Ficheiro lido!\n";
            std::cout << " -> Submissoes carregadas: " << parser.getSubmissions().size() << "\n";
            std::cout << " -> Revisores carregados: " << parser.getReviewers().size() << "\n";
            std::cout << " -> Ficheiro de Output configurado para: " << parser.getConfig().getOutputFileName() << "\n";
            
        } else if (choice == 2) {
            std::cout << "\n[INFO] O algoritmo de Max-Flow ainda esta em desenvolvimento pelo meu colega...\n";
        } else if (choice != 0) {
            std::cout << "\n[ERRO] Opcao invalida. Tente novamente.\n";
        }
    }
    std::cout << "A encerrar o programa. Bom trabalho!\n";
}

// --- O MODO BATCH (SCRIPT) ---
void runBatchMode(const std::string& inputFile, const std::string& outputFile) {
    std::cout << "[BATCH MODE] A iniciar...\n";
    std::cout << "Input: " << inputFile << " | Output: " << outputFile << "\n";
    
    Parser parser;
    parser.parse(inputFile);
    
    std::cout << "[BATCH MODE] Leitura concluida. Ficheiro pronto para o Max-Flow.\n";
}

// --- FUNÇÃO PRINCIPAL ---
// argc: O número de palavras escritas no terminal para correr o programa
// argv: Um array com as palavras que o utilizador escreveu
int main(int argc, char* argv[]) {
    
    if (argc == 4 && std::string(argv[1]) == "-b") {
        // Se o utilizador escreveu a sintaxe certa do Batch Mode, chamamos a função:
        runBatchMode(argv[2], argv[3]);
    } else {
        // Se ele só deu duplo clique no programa ou não pôs os argumentos todos, 
        // abrimos o Menu Interativo amigável.
        runInteractiveMenu();
    }
    
    return 0;
}