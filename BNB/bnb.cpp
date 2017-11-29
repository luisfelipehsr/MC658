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

/* Funcao de interrupcao */
void BNB::interrompe(int signum) {
    pare = 1;
	melhor_custo = 6969;
	if (escrevendo != 1) 
		imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, num_nos_exp);
}

/*** Classe Branch and bound ***/
// Construtor
BNB::BNB(int m, int n, int ls, vector<vector< int> > &matriz,
		 vector<int> salario_entrada) {
	int i, j;
	
	cenas = m;
	dias = cenas;
	atores = n;
	if (ls != -1)
		lim_sup = ls;
	else
		lim_sup = INT_MAX;
	T = matriz;
	salario = salario_entrada;
	ativos = Fila_Prioridade_Noh(1024);

	diasTrabalhando = vector<int> (n, 0);
	for (j = 0; j < n; j++) {
		for (i = 0; i < m; i++) {
			if (T[i][j] == 1)
				diasTrabalhando[i]++;
		}
	}
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
	//pare = 1; // DEBUG forca um pare
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

Noh BNB::escolhe_noh() {
	return ativos.obtem_menor();
}

void BNB::explora_noh(Noh escolhido) {

	// faz algo explorando o noh
}

void BNB::operaSolucao(Noh &noh_solucao) {
	vector<int> sol;
	int i, j, primeiro, ultimo, flag;
	int fim, custo, diasContratados, diasExtra;
	
	sol.resize(dias);
	fim = noh_solucao.anteriores.size();
	for (i = 0; i < fim; i++)
		sol[i] = noh_solucao.anteriores[i];
	sol[fim] = noh_solucao.cena;
    fim = fim + 1;
	for (i = fim; i < noh_solucao.posteriores.size(); i++)
		sol[i] = noh_solucao.posteriores[i];

	custo = 0;
   
	/* Calcula custo */
	for (j = 0; j < n; j++) {
		primeiro = -1;
		// Acha primeiro dia do ator j
		i = 0;
		flag = 0;
		while(i < m && !flag) {
			if (T[sol[i]][j] == 1) {
				primeiro = i;
				flag = 1;
			} else {
				i++;
			}
		}
		// Acha ultimo dia do ator j
		i = m-1;
		flag = 0;
		while(i >= 0 && !flag) {
			if (T[sol[i]][j] == 1) {
				ultimo = i;
				flag = 1;
			} else {
				i--;
			}
		}
		// Adiciona custo extra do ator j
		if (primeiro != -1) {
			diasContratados = ultimo - primeiro + 1;
		    custo += diasContratados * salario[j];
		}
	} // fim for ator j
		
}

int calcula_limitante(int cena, int dia, std::vector<int> &anteriores,
					  std::vector<int> &posteriores) {
	return 666;
}
	
	

// Executa branch and bound
void BNB::run() {
	int i;
	Noh explorado;
	vector<int> vectorVazio;
	vector<int> ant = vector<int>(1);
	vector<int> post = vector<int>(2,2);
	int custo;
	int cena;

	vectorVazio.clear();
	cena = 0;
	dia = 0;
	
	ativos.insere(Noh(cena,dia,0,vectorVazio,vectorVazio));
	while(!ativos.vazio()) {
		explorado = escolhe_noh();

		// gera proximos noh
		if (dia == dias - 1) {
			atualiza_solucao
		dia += 1;
		cena += 1;
		
		ant = explorado.anteriores;
		post = explorado.posteriores;

		ant.push_back(explorado.cena);

		ativos.insere(Noh(cena,dia,0,ant,post));
	}
	
	atualiza_solucao(melhor_solucao, melhor_custo);
	imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, num_nos_exp);
}
