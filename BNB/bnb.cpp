#include <csignal>
#include <cstdlib>
#include <vector>
#include <climits>
#include <iostream>

#include "filaPrioridade.h"
#include "es.h"
#include "bnb.h"

using namespace std;

// Flag de interrupcao por tempo
volatile int pare = 0; // Indica se foi recebido o sinal de interrupcao
volatile int escrevendo = 0;

// Inicializa variaveis static
vector<int> BNB::melhor_solucao;
int BNB::melhor_custo = INT_MAX;
int BNB::total_noh = 0;
int BNB::lim_sup = 0;

/* Funcao de interrupcao */
void BNB::interrompe(int signum) {
    pare = 1;
	melhor_custo = 6969;
	if (escrevendo != 1) 
		imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, total_noh);
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
	ativos = Fila_Prioridade_Noh(1024); /* Aloca a fila */
    melhor_solucao.resize(cenas, 0);
	/*
	diasTrabalhando = vector<int> (n, 0);
	
	for (j = 0; j < n; j++) {
		for (i = 0; i < m; i++) {
			if (T[i][j] == 1)
				diasTrabalhando[i]++;
		}
		}*/
}

// Atualiza solucao
void BNB::atualiza_solucao(vector<int> &sol, int &custo) {
	int i;
	
	escrevendo = 1;
	melhor_custo = custo;

	/* corrige notacao de solucao */
	for (i = 0; i < cenas; i++)
		melhor_solucao[sol[i]] = i;
	//pare = 1; // DEBUG forca um pare
	escrevendo = 0;
	
    if (pare == 1) {
        // Se estava escrevendo a solucao quando recebeu o sinal,
        // espera terminar a escrita e apenas agora imprime a saida e
        // termina
		imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, total_noh);
        exit(0);
    }
}

Noh BNB::escolhe_noh() {
	return ativos.obtem_menor();
}

void BNB::explora_noh(Noh escolhido) {

	// faz algo explorando o noh
}

/* Calcula custo */
int BNB::calculaCusto(vector<int> &sol) {
	int i, j, custo, primeiro, ultimo, flag, diasContratados;

	for(j = 0; j < atores; j++) {
		for (i = 0; i < cenas; i++) {
			cout << T[i][j] << " ";
		}
		cout << endl;
	}

	
	custo = 0;
	/* Atravessa a matriz resultante */
	for (j = 0; j < atores; j++) {
		primeiro = -1;
		// Acha primeiro dia do ator j
		i = 0;
		flag = 0;
		while(i < dias && !flag) {
			if (T[sol[i]][j] == 1) {
				primeiro = i;
				flag = 1;
			} else {
				i++;
			}
		}
		// Acha ultimo dia do ator j
		i = dias-1;
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

		cout << "Custo ator " << j << ": " << diasContratados*salario[j] << endl;
	} // fim for ator j

	return custo;
}

void BNB::operaSolucao(Noh &noh_solucao) {
	vector<int> sol;
	int i, j, primeiro, ultimo, flag;
	int fim, custo, diasContratados, diasExtra;

	/* Obtem solucao do noh */
	sol.resize(dias);
	fim = noh_solucao.anteriores.size();
	for (i = 0; i < fim; i++)
		sol[i] = noh_solucao.anteriores[i];
	sol[fim] = noh_solucao.cena;
    fim = fim + 1;
	for (i = fim; i < noh_solucao.posteriores.size(); i++)
		sol[i] = noh_solucao.posteriores[i];

	/*
	for (i = 0; i < sol.size(); i++)
		cout << sol[i] << " ";
	cout << endl; cout << noh_solucao.cena << endl;
	*/
	/* Avalia se eh melhor que a atual e a substitui se necessario */
	custo = calculaCusto(sol);
	if (custo < melhor_custo)
		atualiza_solucao(sol, custo);
}

int calcula_limitante(int cena, int dia, std::vector<int> &anteriores,
					  std::vector<int> &posteriores) {
	return 666;
}
	
	

// Executa branch and bound
void BNB::run() {
	int i, j, custo, cena, dia, novaCena, diaMedio, diaFinal;
	Noh explorado, filho;
	vector<int> vectorVazio;

	vectorVazio.clear(); /* utilizado para garantir vetor vazio */
 
	total_noh++;
	explorado = Noh(cena,dia,dia+1,vectorVazio,vectorVazio);
	ativos.insere(explorado);

	diaMedio = (dias / 2) - 1;
	diaFinal = diaMedio + (dias % 2);
	
	while(!ativos.vazio()) {
		/* Escolhe um noh ativo e o remove da fila */
		explorado = escolhe_noh();

		/*
		  cout << "Noh: " << explorado.dia << " " << explorado.cena << " " << explorado.anteriores.size() << endl;*/
		
		/* Gera filhos e os testa */
	    for (i = 0; i < cenas, i++) {
			novaCena = 1;
			if (i == explorado.cena)
				novaCena = 0;
			for (j = 0; j < explorado.anteriores.size(); j++) {
				if (explorado.anteriores[j] == i)
					novaCena = 0;
			}
			for (j = 0; j < explorado.posteriores.size(); j++) {
				if (explorado.posteriores[j] == i)
					novaCena = 0;
			}

			if (novaCena) {
				explorado.anteriores.push_back(i);
				
		
	    explorado.anteriores.push_back(int(explorado.cena));
		for (i = 0; i < explorado.anteriores.size(); i++)
			cout << explorado.anteriores.at(i);
		cout << endl;
		
		filho = Noh(cena,dia,dia+1,explorado.anteriores,explorado.posteriores);
	    total_noh++;

		/* Opera nos filhos solucao ou adiciona a ativos */
		if (filho.dia == dias - 1)
			operaSolucao(filho);
		else
			ativos.insere(filho);
	} // fim while ativos nao vazio
	
	atualiza_solucao(melhor_solucao, melhor_custo);
	imprime_saida_bnb(melhor_solucao, melhor_custo, lim_sup, total_noh);
}
