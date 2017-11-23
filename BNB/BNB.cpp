#include "BNB.h"

using namespace std;

// Flag de interrupcao por tempo
volatile int pare = 0; // Indica se foi recebido o sinal de interrupcao

void interrompe(int signum) {
    pare = 1;
    /*if (escrevendo == 0) {
        // Se nao estava escrevendo a solucao, pode imprimir e terminar
        imprime_saida();
        exit(0);
		}*/
}

void atualiza_solucao(const vector<int> &solucao, int custo) {
    //escrevendo = 1;
    melhor_solucao = solucao;
    melhor_custo = custo;
    //escrevendo = 0;
    if (pare == 1) {
        // Se estava escrevendo a solucao quando recebeu o sinal,
        // espera terminar a escrita e apenas agora imprime a saida e
        // termina
        imprime_saida();
        exit(0);
    }
}
