// funcoes.hpp
#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <string>
#include <vector>
#include <unordered_map>

// Structs
struct Coordenada {
    float x;
    float y;
};

struct ResultadoBusca {
    std::string nomeFarmacia;
    std::string telefone;
    std::string endereco;
    float preco;
    float distancia;
};

struct Farmacia {
    std::string nome;
    std::string telefone;
    std::string endereco;
    float x, y;
};

struct RemedioInfo {
    float preco;
    Farmacia farmacia;
};

struct Remedio {
    std::string nome;
    std::vector<RemedioInfo> disponivelEm;
};

// Funções utilitárias
float calcularDistancia(float x1, float y1, float x2, float y2);
Coordenada obterLocalizacaoUsuario();
int perguntarOpcao(const std::string& pergunta, const std::vector<int>& opcoesValidas);
std::string paraMinusculas(const std::string& texto);
void exibirListaRemediosOrdenada(const std::unordered_map<std::string, Remedio>& remedios);
std::string pedirNomeRemedioValido(const std::unordered_map<std::string, std::string>& indiceRemedios);
void ordenarResultados(std::vector<ResultadoBusca>& resultados, int criterio);
void exibirResultados(const std::vector<ResultadoBusca>& resultados, const std::string& nomeRemedio);
void menuReutilizacao(const std::unordered_map<std::string, Remedio>& remedios,
                      const std::unordered_map<std::string, std::string>& indiceRemedios,
                      std::string nomeRemedio,
                      Coordenada localUsuario);


#endif
