/* declaracoes de conjuntos e parametros */

param n, integer, >=1;  /* quantidade de cenas */
param m, integer, >= 1; /* quantidade de atores */

/* matriz T */
set ATORES := {1..m}; /* conjunto de indices de atores */
set CENAS := {1..n};  /* conjunto de indices de dias de gravacao */
set GRAVACOES, within CENAS cross CENAS;
param T{i in ATORES, j in CENAS};

/* custo diário de espera */
param c{i in ATORES};

/* numero de cenas nas quais cada ator participa */
param s{i in ATORES}:=sum{j in CENAS} T[i,j];

/* ===> variaveis: */
var e{i in ATORES} >= 0, integer;
var l{i in ATORES} >= 0, integer;
var g{(i,j) in GRAVACOES} >=0, binary;
var d{j in CENAS} >= 0, integer;

/* ===> funcao objetivo */
minimize custo: 
     sum{i in ATORES} (l[i]-e[i]+1)*c[i]);

/* ===> restricoes */



/* resolve problema */
solve;

/* ===> imprime solucao (n valores inteiros separados por espaco, onde
o j-esimo valor corresponde ao dia em que foi gravada a cena j) */


/* ===> imprime custo da solucao encontrada */


end;
