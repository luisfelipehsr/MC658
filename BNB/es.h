// guarda
#ifndef __ES_H_INCLUDED__
#define __ES_H_INCLUDED__

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

void imprime_saida_bnb(std::vector<int> &melhor_solucao, int &custo,
					   int &lim_inf, int &num_nos_exp);

void imprime_saida_heur(std::vector<int> &melhor_solucao, int &custo);

void recebe_entrada(const std::string arquivo, int &m, int &n,
					std::vector<std::vector <int> > &T);

#endif
