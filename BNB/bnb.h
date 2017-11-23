#include "es.h"

class BNB {
	std::vector<int> melhor_solucao;
	int melhor_custo;
	int cenas;
	int atores;
	int num_nos_exp;
	int lim_inf;
	std::vector<std::vector<int> > T;
	
    void atualiza_solucao(std::vector<int> &solucao, int &custo);
	
 public:
	BNB(int &m, int &n, std::vector<std::vector<int> > &matriz);
	
	void run();
};

void interrompe(int signum);
