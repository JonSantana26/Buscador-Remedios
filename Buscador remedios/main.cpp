// main.cpp
#include <iostream>
#include <unordered_map>
#include "funcoes.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

// RECOMENDAÇÕES PARA USAR O SISTEMA:
// A Simulação da cidade é de uma área de 10 km x 10 km (100km²).
// As farmácias estão posicionadas com coordenadas (x, y) dentro dessa área.
// Ao usar o sistema, informe sua posição atual com valores de 0.0 a 10.0 para x e y.
// Isso permitirá que o sistema calcule a distância em linha reta até cada farmácia, também sendo mais realista.
// Exemplo realista: (x = 5.0, y = 5.0) representa uma posição central da cidade.


int main() {
    //  Dicionário de remédios (normalizados para busca)
    std::unordered_map<std::string, Remedio> remedios;
    std::unordered_map<std::string, std::string> indiceRemedios; // nome em minúsculas → nome original

    //  Cadastro de remédios e farmácias manualmente
    remedios["Catafran"] = {
        "Catafran", {
            {6.50, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
            {7.70, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0}},
            {6.80, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0}}   
        }
    };

    remedios["Dipirona"] = {
        "Dipirona", {
            {7.80, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
            {5.60, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0} },
            {7.00, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0}}
        }
    };

    remedios["Dorflex"] = {
        "Dorflex", {
          {7.40, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
          {8.10, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0} },
          {6.90, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0} },
        }
    };

    remedios["Ibuprofeno"] = {
        "Ibuprofeno", {
            {8.25, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
            {7.85, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0} },
            {7.15, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0} },
        }
    };

    remedios["Loprazol"] = {
        "Loprazol", {
            {9.00, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
        }
    };

    remedios["Metamizol"] = {
        "Metamizol", {
            {9.80, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0} },
        }
    };

    remedios["Minoxidil"] = {
        "Minoxidil", {
            {8.00, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
            {6.75, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0} },
            {8.30, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0} },
        }
    };

    remedios["Neocopan"] = {
        "Neocopan", {
            {11.35, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0} },
        }
    };

    remedios["Paracetamol"] = {
        "Paracetamol", {
            {5.50, {"Farmácia Safari", "4554-3223", "Rua numero 05, Nº35, Cidade Criativa", 2.0, 3.5} },
            {6.30, {"Farmácia Rubi", "8998-7667", "Rua das rosas, Nº80, Cidade Criativa", 7.5, 2.0} },
            {6.50, {"Farmácia Esmeralda", "1221-2112", "Rua das joias, Nº300, Cidade Criativa", 4.0, 8.0} },
        }
    };

    // Preenche o índice de busca com nomes normalizados em minúsculas
    for (const auto& par : remedios) {
        std::string nomeOriginal = par.first;
        std::string nomeNormalizado = paraMinusculas(nomeOriginal);
        indiceRemedios[nomeNormalizado] = nomeOriginal;
    }

    //  Início da interação com o usuário
    std::cout << "\n=== Bem-vindo ao Sistema de Busca de Remédios ===\n";
    std::cout << "\n=== Por enquanto só estamos disponíveis na cidade criativa! ===\n";
    exibirListaRemediosOrdenada(remedios);
    std::cout << "\n=== Caso não tenha o remédio disponível em nosso sistema que você esteja procurando, você pode encerrar o sistema escolhendo a opção 2 ===\n";

    int escolha = perguntarOpcao("1 - Prosseguir para pesquisa de remédio.\n2 - Fechar sistema.\n", {1, 2});
        if(escolha == 2){
        std::cout << "\n===Sistema encerrado. Obrigado por utilizar o nosso sistema!===\n";
       return 0; 
    }
    

    // Solicita nome válido do remédio
    std::string nomeRemedio = pedirNomeRemedioValido(indiceRemedios);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Remedio remedioEscolhido = remedios[nomeRemedio];

    // Solicita localização do usuário
    Coordenada localUsuario = obterLocalizacaoUsuario();

    // Monta resultados e calcula distância
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

    // Pergunta critério de ordenação
    int criterio = perguntarOpcao(
        "\nDeseja ordenar os resultados por:\n  1 - Preço\n  2 - Distância\n\n", {1, 2}
    );

    // Ordena resultados e exibe
    ordenarResultados(resultados, criterio);
    exibirResultados(resultados, nomeRemedio); //Chamando função para exibir os resultados

    // Chamada do menu de reutilização
    menuReutilizacao(remedios, indiceRemedios, nomeRemedio, localUsuario);
   
    return 0;

}    