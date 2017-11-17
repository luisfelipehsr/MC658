/* declaracoes de conjuntos e parametros */

param n, integer, >=1;  /* quantidade de cenas */
param m, integer, >= 1; /* quantidade de atores */

/* matriz T */
set ATORES := {1..m}; /* conjunto de indices de atores */
set CENAS := {1..n};  /* conjunto de indices de dias de gravacao */
set GRAVACOES, within CENAS cross CENAS := setof{j in CENAS, k in CENAS} (j,k);
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
    sum{i in ATORES} ((l[i] - e[i] + 1 - s[i])*c[i]);

/* ===> restricoes */
s.t. gravacaoUnicaCena{j in CENAS}:       
       sum{k in CENAS} g[j,k] = 1;  
    
s.t. gravacaoUnicaDia{k in CENAS}:
       sum{j in CENAS} g[j,k] = 1;

s.t. diaGravacao{j in CENAS}:
       d[j] = sum{k in CENAS} g[j,k]*k;

s.t. primeiroDia{i in ATORES, j in CENAS: T[i,j] == 1}:
       e[i] <= d[j];

s.t. ultimoDia{i in ATORES, j in CENAS: T[i,j] == 1}:
       d[j] <= l[i];

/* resolve problema */
solve;

/* ===> imprime solucao (n valores inteiros separados por espaco, onde
o j-esimo valor corresponde ao dia em que foi gravada a cena j) */
for {j in CENAS} printf "%d ", d[j];
printf '\n';

/* ===> imprime custo da solucao encontrada */
printf: "%d\n", (sum{i in ATORES}((l[i] - e[i] + 1 - s[i])*c[i]));

end;
