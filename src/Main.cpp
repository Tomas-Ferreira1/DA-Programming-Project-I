/**
 * @file Main.cpp
 * @brief Ponto de entrada da aplicacao e funcoes do menu interativo.
 * Contem a logica principal de atribuicao (Max-Flow) e a analise de risco.
 */

/**
 * @mainpage Sistema de Atribuicao de Revisores (Max-Flow)
 * * @section intro_sec Introducao
 * Bem-vindo a documentacao do projeto de Desenho de Algoritmos!
 * * Este programa foi desenvolvido para automatizar a gestao de uma conferencia cientifica.
 * Ele le dados de artigos e revisores, e constroi uma rede de fluxo (Grafos).
 * * @section features_sec Funcionalidades Principais
 * - Leitura e parseamento de ficheiros CSV.
 * - Atribuicao inteligente de revisores usando o algoritmo de **Edmonds-Karp** (Max-Flow).
 * - Analise de risco: simulacao de falhas de revisores para detetar gargalos na conferencia.
 * * @section run_sec Como Executar
 * Compile usando: `g++ src/Main.cpp src/Parser.cpp src/Graph.cpp -I include -o myProg`
 * Execute usando: `./myProg`
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Parser.h"
#include "Graph.h"


/**
 * @brief Constroi o grafo bipartido e executa a atribuição de revisões (Max-Flow).
 * Utiliza as Submissões e Revisores carregados no Parser para criar uma rede de fluxo.
 * Em seguida, gera um ficheiro CSV com as atribuicões ou o relatorio de falhas.
 * * @param parser O objeto Parser contendo os dados extraidos do input.csv.
 * @param customOutput (Opcional) Nome do ficheiro de saida. Se vazio, usa a configuracao.
 */
void runMaxFlowAssignment(Parser& parser, const std::string& customOutput = "") {
    auto subs = parser.getSubmissions();
    auto revs = parser.getReviewers();
    auto config = parser.getConfig();

    if (subs.empty() || revs.empty()) {
        std::cerr << "[ERRO] Faltam dados (Submissoes ou Revisores) para correr o Max-Flow.\n";
        return;
    }

    int N = subs.size();
    int M = revs.size();
    int source = 0;
    int sink = N + M + 1;
    int totalNodes = N + M + 2;

    Graph g(totalNodes);

    int minReviews = config.getMinReviewsPerSubmission();
    int maxReviews = config.getMaxReviewsPerReviewer();

    // 1. Ligar Source -> Submissions
    for (int i = 0; i < N; ++i) {
        g.addEdge(source, i + 1, minReviews);
    }

    // 2. Ligar Submissions -> Reviewers (Apenas Domínios Principais)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (subs[i].getPrimaryDomain() == revs[j].getPrimaryDomain()) {
                // Aresta da Submissão (i+1) para o Revisor (N+1+j)
                g.addEdge(i + 1, N + 1 + j, 1);
            }
        }
    }

    // 3. Ligar Reviewers -> Sink
    for (int j = 0; j < M; ++j) {
        g.addEdge(N + 1 + j, sink, maxReviews);
    }

    // 4. Executar o Algoritmo Edmonds-Karp
    int maxFlow = g.edmondsKarp(source, sink);
    int requiredFlow = N * minReviews;

    // 5. Gerar o ficheiro de Output
    std::string outFilename = customOutput.empty() ? config.getOutputFileName() : customOutput;
    std::ofstream outFile(outFilename);
    if (!outFile.is_open()) {
        std::cerr << "[ERRO] Nao foi possivel criar o ficheiro: " << outFilename << "\n";
        return;
    }

    const auto& adj = g.getAdj();

    if (maxFlow == requiredFlow) {
        std::cout << "[SUCESSO] Todas as revisoes foram atribuidas! (Max-Flow: " << maxFlow << ")\n";

        // Formato 1: Submissions -> Reviewers
        outFile << "#SubmissionId,ReviewerId,Match\n";
        for (int i = 0; i < N; ++i) {
            for (const auto& edge : adj[i + 1]) {
                if (edge.to >= N + 1 && edge.to <= N + M && edge.flow == 1) {
                    int revIdx = edge.to - (N + 1);
                    outFile << subs[i].getId() << ", " << revs[revIdx].getId() << ", " << subs[i].getPrimaryDomain() << "\n";
                }
            }
        }

        // Formato 2: Reviewers -> Submissions
        outFile << "#ReviewerId,SubmissionId,Match\n";
        for (int j = 0; j < M; ++j) {
            for (int i = 0; i < N; ++i) {
                for (const auto& edge : adj[i + 1]) {
                    if (edge.to == N + 1 + j && edge.flow == 1) {
                        outFile << revs[j].getId() << ", " << subs[i].getId() << ", " << subs[i].getPrimaryDomain() << "\n";
                    }
                }
            }
        }
        outFile << "#Total: " << maxFlow << "\n";

    } else {
        std::cout << "[FALHA] Nao existem revisores suficientes! Gerando relatorio de falhas...\n";
        outFile << "#SubmissionId, Domain, MissingReviews\n";

        // Procurar submissões que não receberam fluxo suficiente
        for (int i = 0; i < N; ++i) {
            int flowReceived = 0;
            // Para ver a água que chegou à submissão, olhamos para a aresta inversa do source
            for (const auto& edge : adj[i + 1]) {
                if (edge.to == source) {
                    flowReceived = -edge.flow; // Aresta residual tem fluxo negativo
                    break;
                }
            }
            int missing = minReviews - flowReceived;
            if (missing > 0) {
                outFile << subs[i].getId() << ", " << subs[i].getPrimaryDomain() << ", " << missing << "\n";
            }
        }
    }

    // 6. Adicionar Análise de Risco ao ficheiro (se configurado como 1 ou 2)
    if (config.getRiskAnalysis() >= 1) {
        outFile << "#Risk Analysis: 1\n";
        bool first = true;

        // Itera sobre todos os revisores para identificar os críticos
        for (const auto& rev : revs) {
            Graph tempG(totalNodes);

            // Reconstroi o grafo base
            for (int i = 0; i < N; ++i) tempG.addEdge(source, i + 1, minReviews);

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    // Pula o revisor que estamos a testar (simula a sua ausência)
                    if (revs[j].getId() == rev.getId()) continue;

                    if (subs[i].getPrimaryDomain() == revs[j].getPrimaryDomain()) {
                        tempG.addEdge(i + 1, N + 1 + j, 1);
                    }
                }
            }

            for (int j = 0; j < M; ++j) {
                if (revs[j].getId() != rev.getId()) {
                    tempG.addEdge(N + 1 + j, sink, maxReviews);
                }
            }

            // Se sem este revisor não atingimos o fluxo necessário, ele é crítico
            if (tempG.edmondsKarp(source, sink) < requiredFlow) {
                if (!first) outFile << ", ";
                outFile << rev.getId();
                first = false;
            }
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "[INFO] Ficheiro " << outFilename << " gerado com sucesso!\n";
}

/**
 * @brief Simula a falta de um Revisor para analisar os riscos da conferencia.
 * Reconstrói a rede de fluxo ignorando completamente as ligacoes para um
 * revisor especifico escolhido pelo utilizador para avaliar se o fluxo maximo diminui.
 * * @param parser O objeto Parser contendo os dados originais.
 */
// --- ANALISE DE RISCO ---
void runRiskAnalysis(Parser& parser) {
    auto subs = parser.getSubmissions();
    auto revs = parser.getReviewers();
    auto config = parser.getConfig();

    if (subs.empty() || revs.empty()) {
        std::cerr << "[ERRO] Primeiro tem de ler o ficheiro de dados (Opcao 1)!\n";
        return;
    }

    int missingReviewerId;
    std::cout << "Introduza o ID do Revisor que vai faltar (ex: 1 ou 2): ";
    std::cin >> missingReviewerId;

    int N = subs.size();
    int M = revs.size();
    int source = 0;
    int sink = N + M + 1;
    int totalNodes = N + M + 2;

    Graph g(totalNodes);

    int minReviews = config.getMinReviewsPerSubmission();
    int maxReviews = config.getMaxReviewsPerReviewer();

    // 1. Ligar Source -> Submissions
    for (int i = 0; i < N; ++i) {
        g.addEdge(source, i + 1, minReviews);
    }

    // 2. Ligar Submissions -> Reviewers
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // Se for o revisor que faltou, ignoramos
            if (revs[j].getId() == missingReviewerId) {
                continue; // Salta este revisor, ele nao recebe ligacoes
            }

            if (subs[i].getPrimaryDomain() == revs[j].getPrimaryDomain()) {
                g.addEdge(i + 1, N + 1 + j, 1);
            }
        }
    }

    // 3. Ligar Reviewers -> Sink
    for (int j = 0; j < M; ++j) {
        if (revs[j].getId() != missingReviewerId) {
            g.addEdge(N + 1 + j, sink, maxReviews);
        }
    }

    // 4. Executar o Algoritmo Edmonds-Karp
    int maxFlow = g.edmondsKarp(source, sink);
    int requiredFlow = N * minReviews;

    // 5. Avaliar e Imprimir o Risco
    std::cout << "\n=== RESULTADO DA ANALISE DE RISCO ===\n";
    if (maxFlow == requiredFlow) {
        std::cout << "[BAIXO RISCO] A conferencia sobrevive sem o Revisor " << missingReviewerId << "!\n";
        std::cout << " -> Ainda conseguimos atingir as " << requiredFlow << " revisoes necessarias.\n";
    } else {
        std::cout << "[ALTO RISCO] A conferencia falha sem o Revisor " << missingReviewerId << "!\n";
        std::cout << " -> So conseguimos " << maxFlow << " revisoes das " << requiredFlow << " necessarias.\n";
        std::cout << " -> O Revisor " << missingReviewerId << " e CRITICO para o sucesso do evento!\n";
    }
    std::cout << "=====================================\n";
}

/**
 * @brief Executa o menu interativo da aplicacao.
 * Permite ao utilizador ler ficheiros, gerar atribuicoes e fazer analise de risco.
 */
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
        std::cout << "3. Analise de Risco (Falta de um Revisor)\n";
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
            std::cout << "\n[A PROCESSAR] A calcular atribuicoes perfeitas...\n";
            runMaxFlowAssignment(parser);
        } else if (choice == 3) {
            runRiskAnalysis(parser);
        } else if (choice != 0) {
            std::cout << "\n[ERRO] Opcao invalida. Tente novamente.\n";
        }
    }
    std::cout << "A encerrar o programa. Bom trabalho!\n";
}

/**
 * @brief Corre o programa em Modo Batch (silencioso).
 * Utilitario para automacao: le o ficheiro de entrada e gera o output sem interacao.
 * * @param inputFile O caminho do ficheiro CSV de entrada.
 * @param outputFile O caminho do ficheiro CSV de saida a ser gerado.
 */
// --- O MODO BATCH (SCRIPT) ---
void runBatchMode(const std::string& inputFile, const std::string& outputFile) {
    std::cout << "[BATCH MODE] A iniciar...\n";
    Parser parser;
    parser.parse(inputFile);
    runMaxFlowAssignment(parser, outputFile);
    
    std::cout << "[BATCH MODE] Leitura concluida. Ficheiro pronto para o Max-Flow.\n";
}

/**
 * @brief Funcao principal do programa.
 * Faz a gestao entre iniciar o modo interativo ou o modo batch.
 * * @param argc O numero de argumentos passados na linha de comandos.
 * @param argv O array contendo os argumentos da linha de comandos.
 * @return int 0 em caso de sucesso.
 */
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