#include <csignal>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "es.h"

class BNB {
	vector<int> melhor_solucao;
	int melhor_custo;

 public:
	BNB();
	vector<int> get_solucao;
	int get_custo;
	void atualiza_solucao(const vector<int> &solucao, int custo);
};

void interrompe(int signum);
