#ifndef _FILAPRIORIDADE_H_
#define _FILAPRIORIDADE_H_

/* Classe de um noh do branch and bound. O nivel do noh eh dado pelo
 * dia dele. A escolha eh determinada pela cena. O limite eh o melhor
 * limitante encontrado para o noh. Anteriores sao as escolhas de cena feitas
 * para os dias anteriores ao noh. Posteriores o oposto. Sao ordenados de acordo
 * com a ordem correta dos dias.
 */
class Noh {
 public:
	int cena;
	int dia;
	int limite;
	std::vector<int> anteriores;
	std::vector<int> posteriores;

	Noh();
	Noh(int cena_noh, int dia_noh, int limite_noh,
		std::vector<int> &dias_anteriores, std::vector<int> &dias_posteriores);
}; // fim classe Noh

class Fila_Prioridade_Noh {
 private:
	std::vector<Noh> gerados;
	std::vector<int> fila;
	int capacidade, fim_fila, fim_gerados;

	void minHeapify(int index); /* Transforma eh heap o vector fila */
	int pai (int index); /* Obtem indice do pai da posicao do heap */
	
 public:
	//Construtores
	Fila_Prioridade_Noh();
	Fila_Prioridade_Noh(int size);
	
	void insere(Noh noh_novo); /* Insere novo noh ativo na fila */
	Noh obtem_menor(void); /* Obtem melhor noh da fila */
	void imprime(void); /* Imprime o limitante de cada elemento da fila */
	int vazio();
}; // fim class Fila_Prioridade_Noh

#endif
