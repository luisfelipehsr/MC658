#ifndef _BNB_H_
#define _BNB_H_

class BNB {
	std::vector<int> melhor_solucao;
	int melhor_custo;
	int cenas;
	int atores;
	int num_nos_exp;
	int lim_inf;
	std::vector<std::vector<int> > T;
	std::vector<Noh> noh_gerados;
	std::vector<int> noh_ativos;
	
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

#endif
