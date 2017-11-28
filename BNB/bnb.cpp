#include "bnb.h"

using namespace std;

// Flag de interrupcao por tempo
volatile int pare = 0; // Indica se foi recebido o sinal de interrupcao

void interrompe(int signum) {
    pare = 1;
}

/*** Classe Noh ***/
// Construtor
Noh::Noh(int cena_noh, int dia_noh, vector<int> &dias_anteriores_noh) {
	cena = cena_noh;
	dia = dia_noh;
	dias_anteriores = dias_anteriores_noh;
}


/*** Classe Branch and bound ***/
// Construtor
BNB::BNB(int &m, int &n, vector<vector< int> > &matriz) {
	cenas = m;
	atores = n;
	T = matriz;
}

// Atualiza solucao
void BNB::atualiza_solucao(vector<int> &solucao, int &custo) {

	/************************* ATENCAO *******************************/
	/* O programa deve parar o mais rapido possivel ao receber o sinal,
	 * portanto eh preciso uma politica de que em certos momentos ele
	 * deve checar se deve parar atraves da variavel PARE.            */

	// Codigo tosco de teste
    melhor_solucao = solucao;
    melhor_custo = custo;
	pare = 1;
	
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

int escolhe_noh() {
	return 0;
}

void explora_noh(int noh_escolhido) {
	if (noh_ativos.size() == 0) {
		printf("ERRO: tentativa de explorar noh sem noh ativos");
		exit(0);
	}

	

// Executa branch and bound
void BNB::run() {
	vector<int> solucao;
	int i;

	// Codigo tosco de teste
	solucao.resize(cenas);
	for (i = 0; i < cenas; i++)
		solucao[i] = i + 1;

	i = 666;
	atualiza_solucao(solucao, i);
}
