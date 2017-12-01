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
int BNB::lim_inf = INT_MAX;

/* Funcao de interrupcao */
void BNB::interrompe(int signum) {
    pare = 1;
	melhor_custo = 6969;
	if (escrevendo != 1) {
		imprime_saida_bnb(melhor_solucao, melhor_custo, lim_inf, total_noh);
		exit(0);
	}
}

/*** Classe Branch and bound ***/
// Construtor
BNB::BNB(int m, int n, int ls, vector<vector< int> > &matriz,
		 vector<int> salario_entrada) {
	int i, j;
	vector<int> vazios;
	
	cenas = m;
	dias = cenas;
	atores = n;
	diaFinal = dias / 2; /* dia do ultimo nivel do bnb */

	/* Limitante superior que pode ser fornecido pelo calculo 
	 * feito anteriormente por uma heuristica */
	if (ls != -1)
		lim_sup = ls;
	else
		lim_sup = INT_MAX;

	/* Matriz T das cenas Trabalhadas pelos atores */
	T = matriz;
	salario = salario_entrada;
	ativos = Fila_Prioridade_Noh(1024); /* Aloca a fila */
    melhor_solucao.resize(cenas, 0);

	
	/* Pre processa calculando os dias atuados por um ator j */
	diasAtuados.resize(atores, 0);
	for (j = 0; j < atores; j++)
		for (i = 0; i < cenas; i++)
			if (T[i][j] == 1)
				diasAtuados[j]++;
}

// Atualiza solucao
void BNB::atualiza_solucao(vector<int> &sol, int &custo) {
	int i;
	
	escrevendo = 1;
	melhor_custo = custo;

	/* corrige notacao de solucao */
	for (i = 0; i < cenas; i++)
		melhor_solucao[sol[i]] = i;
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
		    custo += (diasContratados - diasAtuados[j]) * salario[j];
		}
		
	} // fim for ator j

	return custo;
}

void BNB::operaSolucao(Noh &noh_solucao) {
	vector<int> sol;
	int i, j, primeiro, ultimo, flag;
	int fim, custo, diasContratados, diasExtra, tam;

	if (noh_solucao.anteriores.size() + noh_solucao.posteriores.size() +
		1 != dias) {
		cout << "ERRO: fornecido solucao invalida. Tamanho: " <<
			noh_solucao.anteriores.size() + noh_solucao.posteriores.size() +
			1 << endl;
		exit(0);
	}

	/* Obtem solucao do noh na forma de um vetor */
	sol.resize(dias);
	fim = noh_solucao.anteriores.size();
	for (i = 0; i < fim; i++)
		sol[i] = noh_solucao.anteriores[i];
	sol[fim] = noh_solucao.cena;
	fim++;
	tam = noh_solucao.posteriores.size();
	for (i = 0; i < tam; i++)
		sol[fim+i] = noh_solucao.posteriores[tam-i-1];

	/* Avalia se eh melhor que a atual e a substitui se necessario */
	custo = calculaCusto(sol);
	if (custo < melhor_custo) {
		atualiza_solucao(sol, custo);
	}
}

/* Calcula limitante inferior de um certo noh explorando */
void BNB::calcula_limitante(Noh &explorando) {
	vector<int> ant(atores, -1);
	vector<int> ant_ultimo(atores, -1);
	vector<int> post(atores, -1);
	vector<int> post_primeiro(atores, -1);
	vector<int> ant_dias(atores, 0);
	vector<int> post_dias(atores, 0);
	int i, j, achou, dia, limite1, limite2, limite3, limite4;

	limite1 = 0;
	limite2 = 0;
	limite3 = 0;
	limite4 = 0;

	/* O noh possui si mesmo, um conjunto de dias anteriores B e de posteriores
	 * E. Calcula o primeiro dia que um ator j aparece em B e o ultimo dia em
	 * que aparece em E. */
	for (j = 0; j < atores; j++) {
		
		dia = 0;
		achou = 0;
		/* acha primeiro do lado esquerdo */
		while (dia < explorando.anteriores.size() && !achou) {
			if (T[explorando.anteriores[dia]][j] == 1) {
				ant[j] = dia;
				achou = 1;
			}
			dia++;
		}

		dia--;
		/* acha ultimo do lado esquerdo */
		while (achou && dia < explorando.anteriores.size()) {
			if (T[explorando.anteriores[dia]][j] == 1) {
				ant_ultimo[j] = dia;
				ant_dias[j]++;
			}
			dia++;
		}

		dia = 0;
		achou = 0;
		/* acha ultimo do lado direito */
		while (dia < explorando.posteriores.size() && !achou) {
			if (T[explorando.posteriores[dia]][j] == 1) {
				post[j] = dias - dia - 1;
				achou = 1;
			}
			dia++;
		}
		
		dia--;
		/* acha primeiro do lado direito */
		while (achou && dia < explorando.posteriores.size()) {
			if (T[explorando.posteriores[dia]][j] == 1) {
				post_primeiro[j] = dias - dia - 1;
				post_dias[j]++;
			}
			dia++;
		}
		
	    /* correcoes com o dia atual s */
		if (explorando.dia < diaFinal) {
			if (T[explorando.cena][j] == 1) {
	            ant_ultimo[j] = explorando.dia;
				ant_dias[j]++;
				if (ant_dias[j] == 1)
					ant[j] = explorando.dia;
			}
		} else {
			if (T[explorando.cena][j] == 1) {
				post_primeiro[j] = explorando.dia;
				post_dias[j]++;
				if (post_dias[j] == 1)
					post[j] = explorando.dia;
			}
		}
	} // fim for ator j
	
	/* Calcula o custo do noh atual em relacao a E e L */
	/* Calculo de K1, o custo dado por atores em B e E */
	for (j = 0; j < atores; j++)
		if (ant_dias[j] > 0 && post_dias[j] > 0) {
			limite1 += (salario[j] * (post[j] - ant[j] + 1 - diasAtuados[j]));
		}
   
	/* Calculo de K2 */
	for (j = 0; j < atores; j++) {
		if (ant_dias[j] > 0 && post_dias[j] == 0) {
			limite2 += salario[j] *
				(ant_ultimo[j] - ant[j] + 1 - ant_dias[j]);
		}
		else if (ant_dias[j] == 0 && post_dias[j] > 0) {
			limite2 += salario[j] *
				(post[j] - post_primeiro[j] + 1 - post_dias[j]);
		}
	}

	/* Calculo de K3 */
	/* Calculo de K4 */

	/* Soma os limitantes */
	explorando.limite = limite1 + limite2 + limite3 + limite4;
	if (explorando.limite < lim_inf)
		lim_inf = explorando.limite;
} // fim membro calcula_limitante
	

// Executa branch and bound
void BNB::run() {
	int i, j, custo, cena, dia, novaCena, diaMedio;
	Noh explorado, filho;
	vector<int> vectorVazio, ant, post;

	char debug;

	vectorVazio.clear(); /* utilizado para garantir vetor vazio */

	/* Adiciona primeiro nivel da arvore */
	for (i = 0; i < cenas; i++) {
		filho = Noh(i,0,0,vectorVazio,vectorVazio);
		calcula_limitante(filho);
		ativos.insere(filho);
	}
	total_noh += cenas;
	
	while(!ativos.vazio()) {
		/* Escolhe um noh ativo e o remove da fila */
		explorado = escolhe_noh();

		/* Verifica se o noh ativo realmente deveria ser realizado */
	    if (explorado.limite < lim_sup) {
		
			/* Gera filhos e os testa */
			for (i = 0; i < cenas; i++) {
				/* filtra os valores possiveis para os filhos */
				novaCena = 1;
				if (i == explorado.cena)
					novaCena = 0;
				for (j = 0; j < explorado.anteriores.size(); j++) {
					if (explorado.anteriores.at(j) == i)
						novaCena = 0;
				}
				for (j = 0; j < explorado.posteriores.size(); j++) {
					if (explorado.posteriores.at(j) == i)
						novaCena = 0;
				}

				/* caso seja um filho possivel */
				if (novaCena) {
					total_noh++;

					/* estabelece dia do filho e cria seus anteriores e pos-
					 * teriores. Os posteriores estao na ordem de adicao */
					if (explorado.dia < diaFinal) {
						dia = dias - explorado.dia - 1;
						explorado.anteriores.push_back(explorado.cena);
					} else {
						dia = dias - explorado.dia;
						explorado.posteriores.push_back(explorado.cena);
					}

					/* Cria um noh filho */
					filho = Noh(i, dia, 0, explorado.anteriores,
								explorado.posteriores);
				
					/* conserta noh anterior */
					if (explorado.dia < diaFinal) {
						explorado.anteriores.pop_back();
					} else {
						explorado.posteriores.pop_back();
					}

					/* Opera nos filhos solucao ou adiciona a ativos */
					if (filho.dia == diaFinal)
						operaSolucao(filho);
					else {
						/* Estabelece limitante do filho e se preciso ama-
						 * durece-o. */
						calcula_limitante(filho);
						if (filho.limite < melhor_custo)
							ativos.insere(filho);
					}
				} // fim if novaCena
			} // fim for filhos possiveis
		} // fim if lower bound < upper bound
	} // fim while ativos nao vazio

	imprime_saida_bnb(melhor_solucao, melhor_custo, lim_inf, total_noh);
}
