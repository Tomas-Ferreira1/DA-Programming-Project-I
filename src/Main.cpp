#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Parser.h"
#include "Graph.h"

// ---(MENU) ---
Graph  buildNetwork(const Parser& parser){
    auto subs = parser.getSubmissions();
    auto revs = parser.getReviewers();
    auto config = parser.getConfig();

    int nSub = subs.size();
    int nRev = revs.size();

    int source = 0;
    int sink = nSub + nRev + 1;

    Graph g(sink + 1);

    for (int i = 0; i < nSub; ++i) {
        g.addEdge(source, i+1, config.getMinReviewsPerSubmission());
    }

    for (int j = 0; j < nRev; ++j) {
        g.addEdge(nSub + j+1, sink, config.getMaxReviewsPerReviewer());
    }

    for (int i = 0; i < nSub; ++i) {
        for (int j = 0; j < nRev; ++j) {
            if (subs[i].getPrimaryDomain() == revs[j].getPrimaryDomain()){
                g.addEdge(i+1, nSub + j+1, 1);
            }
        }
    }
    return g;
}

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
            if (parser.getSubmissions().empty()) {
                std::cout << "[ERRO] Primeiro precisa de ler um ficheiro (Opcao 1)!\n";
            } else {
                Graph g = buildNetwork(parser);
                int nSub = parser.getSubmissions().size();
                int nRev = parser.getReviewers().size();
                int source = 0;
                int sink = nSub + nRev + 1;

                int flow = g.maxFlow(source, sink);
                int totalNeeded = nSub * parser.getConfig().getMinReviewsPerSubmission();

                if (flow == totalNeeded) {
                    std::cout << "\n[SUCESSO] Todas as atribuicoes foram feitas!\n";
                } else {
                    std::cout << "\n[AVISSO] Nao foi possivel satisfazer todos os requesitos.\n";
                    std::cout << "Faltam " << (totalNeeded - flow) << " revisoes no total.\n";
                }

                std::string outName = parser.getConfig().getOutputFileName();
                std::ofstream outFile(outName);
                if (outFile.is_open()){
                    outFile << "#SubmissionID, ReviewerID\n";

                    auto subs = parser.getSubmissions();
                    auto revs = parser.getReviewers();

                    for (int i = 1; i <= nSub; ++i) {
                        for (const auto &edge: g.getAdj()[i]) {
                            if (edge.flow == 1 && edge.to > nSub && edge.to <= nSub + nRev) {
                                outFile << subs[i - 1].getId() << "," << revs[edge.to - nSub - 1].getId() << "\n";
                            }
                        }
                    }
                    outFile.close();
                    std::cout << " -> Ficheiro gerado: " << outName << "\n";
                } else {
                    std::cout << "[ERRO] Nao foi possivel criar o ficheiro " << outName << "\n";
                }
            }
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