#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

class Noh {
 public:
	int cena;
	int dia;
	int limite;
	std::vector<int> dias_anteriores;

	Noh();
	Noh(int cena_noh, int dia_noh, int limite_noh,
		std::vector<int> dias_anteriores_noh);
}; // fim classe Noh

class Fila_Prioridade_Noh {
 private:
	std::vector<Noh> gerados;
	std::vector<int> fila;
	int capacidade, fim_fila, fim_gerados;

	void minHeapify(int index);
	int pai (int index);
	
 public:
	Fila_Prioridade_Noh(int size);
	void insere(Noh noh_novo);
	Noh obtem_menor(void);
	void imprime(void);
}; // fim class Fila_Prioridade_Noh
	
