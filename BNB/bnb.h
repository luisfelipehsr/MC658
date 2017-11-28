#include "es.h"

class Noh {
	int cena;
	int dia;
	std::vector<int> dias_anteriores;

 public:
	Noh(int cena_noh, int dia_noh, std::vector<int> &dias_anteriores_noh);
};

class BNB {
	std::vector<int> melhor_solucao;
	int melhor_custo;
	int cenas;
	int atores;
	int num_nos_exp;
	int lim_inf;
	std::vector<std::vector<int> > T;
	std::vector<Noh> noh_ativos;
	
	int escolhe_noh();
	void explora_noh(int noh_escolhido);
	int calcula_limitante(int cena, int dia,
						   std::vector<int> &dias_anteriores);
	void obtemSolucao();
	void atualiza_solucao(std::vector<int> &solucao, int &custo);
	
 public:
	BNB(int &m, int &n, std::vector<std::vector<int> > &matriz);


	void run();
};



void interrompe(int signum);
