// guarda
#ifndef _ES_H_INCLUDED_
#define _ES_H_INCLUDED_

#include <string>

void imprime_saida_bnb(std::vector<int> &melhor_solucao, int &custo,
					   int &lim_inf, int &num_nos_exp);

void imprime_saida_heur(std::vector<int> &melhor_solucao, int &custo);

void recebe_entrada(const std::string arquivo, int &m, int &n,
					std::vector<std::vector <int> > &T,
					std::vector<int> &salario);

#endif
