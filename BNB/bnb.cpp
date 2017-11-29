#include <csignal>
#include <cstdlib>
#include <vector>
#include <climits>

#include "filaPrioridade.h"
#include "es.h"
#include "bnb.h"

using namespace std;

// Flag de interrupcao por tempo
volatile int pare = 0; // Indica se foi recebido o sinal de interrupcao
volatile int escrevendo = 0;

// Inicializa variaveis static
vector<int> BNB::melhor_solucao;
int BNB::melhor_custo = 0;
int BNB::num_nos_exp = 0;
int BNB::lim_sup = 0;


void BNB::interrompe(int signum) {
    pare = 1;
	imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, num_nos_exp);
}

/*** Classe Branch and bound ***/
// Construtor
BNB::BNB(int m, int n, int ls, vector<vector< int> > &matriz) {
	cenas = m;
	atores = n;
	if (ls != -1)
		lim_sup = ls;
	else
		lim_sup = INT_MAX;
	T = matriz;
	ativos = Fila_Prioridade_Noh(1024);
}

// Atualiza solucao
void BNB::atualiza_solucao(vector<int> &solucao, int &custo) {

	/************************* ATENCAO *******************************/
	/* O programa deve parar o mais rapido possivel ao receber o sinal,
	 * portanto eh preciso uma politica de que em certos momentos ele
	 * deve checar se deve parar atraves da variavel PARE.            */
	escrevendo = 1;

	// Codigo tosco de teste
    melhor_solucao = solucao;
    melhor_custo = custo;
	pare = 1; // DEBUG forca um pare
	escrevendo = 0;
	
    if (pare == 1) {
        // Se estava escrevendo a solucao quando recebeu o sinal,
        // espera terminar a escrita e apenas agora imprime a saida e
        // termina
		 lim_sup = 1111;
		 num_nos_exp = 2222;
		imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, num_nos_exp);
        exit(0);
    }
}

int BNB::escolhe_noh() {
	return 0;
}

void BNB::explora_noh(Noh escolhido) {

	// faz algo explorando o noh
}

void BNB::obtemSolucao() {
}

int calcula_limitante(int cena, int dia, std::vector<int> &anteriores,
					  std::vector<int> &posteriores) {
	return 666;
}
	
	

// Executa branch and bound
void BNB::run() {
	int i;
	Noh explorado;
	vector<int> exemplo1 = vector<int>(1);
	vector<int> exemplo2 = vector<int>(2,2);
	
	
	for (i = 0; i < 4; i++)
	    ativos.insere(Noh(6,i,3-i,exemplo1, exemplo2));
	for (i = 0; i < 4; i++)
	    ativos.insere(Noh(6,i,i,exemplo1, exemplo2));
	
	for (i = 0; i < 8; i++) {
		explorado = ativos.obtem_menor();
		melhor_solucao.push_back(explorado.limite);
		melhor_custo += 1;
	}
			
	atualiza_solucao(melhor_solucao, melhor_custo);
}
