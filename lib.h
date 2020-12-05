#define MAX_DESCR 50

/* Armazena um horário de chegada */
typedef struct{
    int hh;
    int mm;
    int ss;
} horario;
/* Armazena informaçoes de um processo */
typedef struct{
    int prior;
    horario chegada;
    char descricao[MAX_DESCR + 1];
} celula;

/* Armazena informações da lista */
typedef struct objeto{
    celula cel;
    struct objeto *nextPrioridade;
    struct objeto *nextTime;
} objeto;

/* PROTOTIPO DAS FUNÇÕES */
void cadastraProcesso(celula componente, objeto *lista);
objeto* alocaNovoObjeto(celula componente);
void imprimeLista(objeto *lista, char *opcao);
void imprimeNext(objeto *lista, char *opcao);
int converteHmsEmSegundos(int hr, int mn, int sg);
void removePrioridade(objeto *lista, char *opcao);
void removeTempo(objeto *lista, char *opcao);
void modificaProcessoPrioridade(celula componente, celula componenteNovo, objeto *lista);
void modificaProcessoTempo(celula componente, celula componenteNovo, objeto *lista);
void inserePrioridade(objeto *componente, objeto *lista);
void insereTempo(objeto *componente, objeto *lista);
void menu(char *comando, objeto *lista);
