#include "bnb.h"

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

// Construtor
BNB::BNB(int &m, int &n, vector<vector< int> > &matriz) {
	cenas = m;
	atores = n;
	T = matriz;
}

// Atualiza solucao
void BNB::atualiza_solucao(vector<int> &solucao, int &custo) {
	
    //escrevendo = 1;
    melhor_solucao = solucao;
    melhor_custo = custo;
    //escrevendo = 0;
	
    if (pare == 1) {
        // Se estava escrevendo a solucao quando recebeu o sinal,
        // espera terminar a escrita e apenas agora imprime a saida e
        // termina
		 lim_inf = 1111;
		 num_nos_exp = 2222;
		imprime_saida_bnb(melhor_solucao, melhor_custo, lim_inf, num_nos_exp);
        exit(0);
    }
}

// Executa branch and bound
void BNB::run() {
	vector<int> solucao;
	int i;

	solucao.resize(cenas);
	for (i = 0; i < cenas; i++)
		solucao[i] = i + 1;

	i = 666;
	atualiza_solucao(solucao, i);
}
