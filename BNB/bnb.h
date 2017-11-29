#ifndef _BNB_H_
#define _BNB_H_

#include "filaPrioridade.h"

class BNB {
	int cenas;
	int dias;
    int atores;
	std::vector<int> salario;
	std::vector<int> diasTrabalhando;
    std::vector<std::vector<int> > T;
    Fila_Prioridade_Noh ativos;

	// Metodos do BNB
	int escolhe_noh();
	void explora_noh(Noh escolhido);
	int calcula_limitante(int cena, int dia, std::vector<int> &anteriores,
						  std::vector<int> &posteriores);
	void obtemSolucao();
	void atualiza_solucao(std::vector<int> &solucao, int &custo);
	
 public:
    static std::vector<int> melhor_solucao;
    static int melhor_custo;
    static int num_nos_exp;
    static int lim_sup;

	
	// Construtor
	BNB(int m, int n, int lb, std::vector<std::vector<int> > &matriz,
		std::vector<int> salario);

	static void interrompe(int signum); /* sinal */
	void run();
};

#endif
