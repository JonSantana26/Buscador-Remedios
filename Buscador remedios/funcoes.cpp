// funcoes.cpp
#include "funcoes.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

// Implementações
//Função para calcular distância entre o usuário e farmácia
float calcularDistancia(float x1, float y1, float x2, float y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}
//Função para obter coordenadas do usuário
Coordenada obterLocalizacaoUsuario() {
    Coordenada loc;
    while (true) {
        std::cout << "\nInforme sua localização em km (valores entre 0.0 e 10.0): \n";
        std::cout << "Coordenada X: ";
        std::cin >> loc.x;

        if (std::cin.fail() || loc.x < 0.0 || loc.x > 10.0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valor inválido para X. Tente novamente.\n";
        } else {
            break;
        }
    }
    while (true) {
        std::cout << "Coordenada Y: ";
        std::cin >> loc.y;

        if (std::cin.fail() || loc.y < 0.0 || loc.y > 10.0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valor inválido para Y. Tente novamente.\n";
        } else {
            break;
        }
    }
    return loc;
}

//Função que o sistema utiliza para validar respostas de perguntas e direcionar ações
int perguntarOpcao(const std::string& pergunta, const std::vector<int>& opcoesValidas) {
    int opcao;
    bool valido = false;

    do {
        std::cout << pergunta;
        std::cout << "Digite sua opção: ";
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nOpção inválida.  Tente novamente. \n\n";
            continue;
        }
        valido = std::find(opcoesValidas.begin(), opcoesValidas.end(), opcao) != opcoesValidas.end();
        if (!valido) {
            std::cout << "\nOpção inválida. Tente novamente. \n\n";
        }
    } while (!valido);

    return opcao;
}
//Caso o usuário digite por exemplo, catafran ou CaTafrAN, o sistema compreende o remédio da lista por conta desta função
std::string paraMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(), [](unsigned char c) {
        return std::tolower(c);
    }); //Tanto a lista quanto a resposta do usuário ficam em minúsculas para o sistema validar a entrada do usuário.
    return resultado;
}

//Ordena lista inicial cadastrada de remédios no sistema para o usuário visualizar os remédios disponíveis
void exibirListaRemediosOrdenada(const std::unordered_map<std::string, Remedio>& remedios) {
    std::vector<std::string> nomesRemedios;

    // Extrai as chaves do mapa
    for (const auto& par : remedios) {
        nomesRemedios.push_back(par.first);
    }

    // Ordena alfabeticamente
    std::sort(nomesRemedios.begin(), nomesRemedios.end());

    // Exibe a lista
     std::cout << "\n===========================================================\n\n";
    std::cout << "\n=== Lista de remédios disponíveis em nosso sistema ===\n";
    for (const auto& nome : nomesRemedios) {
        std::cout << "• " << nome << "\n";
    }
    std::cout << "\n===========================================================\n";
}

//Função para captar uma entrada válida do usuário sobre a escolha do remédio
std::string pedirNomeRemedioValido(const std::unordered_map<std::string, std::string>& indiceRemedios) {
    std::string nomeDigitado;
    std::string nomePadronizado;

    do {
        std::cout << "\nDigite o nome do remédio que você deseja buscar: ";
        std::getline(std::cin, nomeDigitado);
        std::string nomeMinusculo = paraMinusculas(nomeDigitado);

        auto it = indiceRemedios.find(nomeMinusculo);
        if (it != indiceRemedios.end()) {
            nomePadronizado = it->second;
            break;
        } else {
            std::cout << "Remédio não encontrado na nossa lista. Confira a lista acima novamente e digite um remédio existente em nosso sistema.\n";
        }
    } while (true);

    return nomePadronizado;
}
//Função para ordenar os resultados conforme escolha do cliente
void ordenarResultados(std::vector<ResultadoBusca>& resultados, int criterio) {
    if (criterio == 1) {
        std::sort(resultados.begin(), resultados.end(),
                  [](const ResultadoBusca& a, const ResultadoBusca& b) {
                      return a.preco < b.preco;
                  });
    } else {
        std::sort(resultados.begin(), resultados.end(),
                  [](const ResultadoBusca& a, const ResultadoBusca& b) {
                      return a.distancia < b.distancia;
                  });
    }
}
// Função para exibir resultados em formato de tabela
void exibirResultados(const std::vector<ResultadoBusca>& resultados, const std::string& nomeRemedio) {
    std::cout << "\nResultados encontrados para o remédio " << nomeRemedio << ":\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------\n";

    std::cout << std::left
              << "| " << std::setw(25) << "Farmácia"
              << "| " << std::setw(14) << "Telefone"
              << "| " << std::setw(45) << "Endereço"
              << "| " << std::setw(8) << "Preço"
              << " | " << std::setw(10) << "Distância"
              << "\n";

    std::cout << "-----------------------------------------------------------------------------------------------------------\n";

    for (const auto& r : resultados) {
        std::cout << std::left
                  << "| " << std::setw(25) << r.nomeFarmacia
                  << "| " << std::setw(14) << r.telefone
                  << "| " << std::setw(45) << r.endereco
                  << "| R$ " << std::setw(5) << std::fixed << std::setprecision(2) << r.preco
                  << "| " << std::setw(7) << std::fixed << std::setprecision(2) << r.distancia << "km"
                  << "\n";
        std::cout << "-----------------------------------------------------------------------------------------------------------\n";
    }
}

void menuReutilizacao(const std::unordered_map<std::string, Remedio>& remedios,
                      const std::unordered_map<std::string, std::string>& indiceRemedios,
                      std::string nomeRemedio,
                      Coordenada localUsuario) { //Passando todos os dados necessários já inseridos pelo usuário para o menu de reutilização
    while (true) {
        std::cout << "\n===Deseja realizar uma nova pesquisa?===\n";
        int opcao = perguntarOpcao(   //Função para validar a opção inserida pelo usuário
            "1 - Pesquisar outro remédio com mesma localização\n"
            "2 - Pesquisar o mesmo remédio com nova localização\n"
            "3 - Pesquisar novo remédio com nova localização\n"
            "4 - Encerrar sistema\n\n",
            {1, 2, 3, 4}
        );

        if (opcao == 4) {
            std::cout << "\n=== Sistema encerrado. Obrigado por utilizar o nosso sistema! ===\n";
            break;
        }

        if (opcao == 1 || opcao == 3) {   //Usando If para chamar as funções corretas conforme escolha do usuário
            exibirListaRemediosOrdenada(remedios);
            nomeRemedio = pedirNomeRemedioValido(indiceRemedios);
        }

        if (opcao == 2 || opcao == 3) {
            localUsuario = obterLocalizacaoUsuario();
        }

        Remedio remedioEscolhido = remedios.at(nomeRemedio);

        std::vector<ResultadoBusca> resultados;
        for (const auto& info : remedioEscolhido.disponivelEm) {
            ResultadoBusca r;
            r.nomeFarmacia = info.farmacia.nome;
            r.telefone = info.farmacia.telefone;
            r.endereco = info.farmacia.endereco;
            r.preco = info.preco;
            r.distancia = calcularDistancia(localUsuario.x, localUsuario.y, info.farmacia.x, info.farmacia.y);
            resultados.push_back(r);
        }

        int criterio = perguntarOpcao(
            "\n===Deseja ordenar os resultados por:===\n  1 - Preço\n  2 - Distância\n\n", {1, 2}
        );
        ordenarResultados(resultados, criterio); //Chamando função para ordenar os resultados conforme escolha do cliente
        exibirResultados(resultados, nomeRemedio); //Exibição dos resultados
    }
}
