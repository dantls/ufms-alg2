#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

/* FUNÇÃO UTILIZADA PARA CADASTRAR ORDENADAMENTE */
void cadastraProcesso(celula componente, objeto *lista){
    objeto *novoObjeto, *aux;

    int tempoObjeto;

    novoObjeto = alocaNovoObjeto(componente);
    /* PRIORIDADE */
    if (lista->nextPrioridade == NULL){
        lista->nextPrioridade = novoObjeto;
    }
    else{
        /* CABEÇA */
        aux = lista;
        /* ITERANDO ATÉ QUE ENCONTRE O OBJETO RESPECTIVO E INSERA NA ORDEM CORRETO */
        while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior > novoObjeto->cel.prior){
            aux = aux->nextPrioridade;
        }
        /* INSERÇÃO NA ORDEM CORRETA */
        novoObjeto->nextPrioridade = aux->nextPrioridade;
        aux->nextPrioridade = novoObjeto;
    }
    /* TEMPO */
    if (lista->nextTime == NULL){
        lista->nextTime = novoObjeto;
    }
    else{
        /* CABEÇA */
        aux = lista;
        /* CHAMANDO A FUNÇÃO DE TEMPO PARA REALIZAR A COMPARAÇÃO NO WHILE */
        tempoObjeto = converteHmsEmSegundos(novoObjeto->cel.chegada.hh, novoObjeto->cel.chegada.mm, novoObjeto->cel.chegada.ss);
        /* ITERANDO ATÉ QUE ENCONTRE O OBJETO RESPECTIVO E INSERA NA ORDEM CORRETO */
        while (aux->nextTime != NULL && converteHmsEmSegundos(aux->nextTime->cel.chegada.hh, aux->nextTime->cel.chegada.mm, aux->nextTime->cel.chegada.ss) < tempoObjeto){
            aux = aux->nextTime;
        }
        /* INSERÇÃO NA ORDEM CORRETA */
        novoObjeto->nextTime = aux->nextTime;
        aux->nextTime = novoObjeto;
    }
}
/* FUNÇÃO QUE REALIZA A ALOCAÇÃO DE MEMÓRIA PARA O NOVO OBJETO */
objeto *alocaNovoObjeto(celula componente){
    objeto *novoObjeto;

    novoObjeto = (objeto *)malloc(sizeof(objeto));
    if (novoObjeto != NULL)
    {
        novoObjeto->cel = componente;
        novoObjeto->nextPrioridade = NULL;
        novoObjeto->nextTime = NULL;
    }
    else
    {
        printf("ERRO AO ALOCAR MEMORIA\n");
    }
    return novoObjeto;
}

/* FUNÇÃO QUE REALIZA A IMPRESSÃO DA LISTA INTEIRA */
void imprimeLista(objeto *lista, char *opcao){
    objeto *aux = NULL;

    if(lista->nextTime != NULL){
        if (strcmp(opcao, "-p") == 0)
        {
            for (aux = lista->nextPrioridade; aux != NULL; aux = aux->nextPrioridade){
                printf("%02d", aux->cel.prior);
                printf(" %02d", aux->cel.chegada.hh);
                printf(":%02d", aux->cel.chegada.mm);
                printf(":%02d", aux->cel.chegada.ss);
                printf(" %s\n", aux->cel.descricao);
            }
        }else{
            for (aux = lista->nextTime; aux != NULL; aux = aux->nextTime){
                printf("%02d", aux->cel.prior);
                printf(" %02d", aux->cel.chegada.hh);
                printf(":%02d", aux->cel.chegada.mm);
                printf(":%02d", aux->cel.chegada.ss);
                printf(" %s\n", aux->cel.descricao);
            }
        }
    }else{
        printf("LISTA VAZIA!\n");
    }
}

/* FUNÇÃO QUE REALIZA A IMPRESSÃO ATRÁVES DO COMANDO NEXT */
/* LISTANDO APENAS O PRIMEIRO ELEMENTO DA LISTA(O MAIS PRIORITARIO) */
void imprimeNext(objeto *lista, char *opcao){
    objeto *aux = NULL;
    if(lista->nextPrioridade != NULL){
        if (strcmp(opcao, "-p") == 0){
            aux = lista->nextPrioridade;
            printf("%02d", aux->cel.prior);
            printf(" %02d", aux->cel.chegada.hh);
            printf(":%02d", aux->cel.chegada.mm);
            printf(":%02d", aux->cel.chegada.ss);
            printf(" %s\n", aux->cel.descricao);
        }else{
            aux = lista->nextTime;
            printf("%02d", aux->cel.prior);
            printf(" %02d", aux->cel.chegada.hh);
            printf(":%02d", aux->cel.chegada.mm);
            printf(":%02d", aux->cel.chegada.ss);
            printf(" %s\n", aux->cel.descricao);
        }
    }else{
        printf("LISTA VAZIA\n");
    }
}

/* FUNÇÃO UTILIZADA PARA DEIXA A BASE DE HORARIOS IGUALITARIA. AJUDANDO A REALIZAR AS DIVERSAS COMPARAÇÕES */
/* UTILIZAMOS A CONVERSÃO PARA SEGUNDOS */
int converteHmsEmSegundos(int hr, int mn, int sg){
    /* CONVERTE HORAS, MINUTOS E SEGUNDO EM SEGUNDOS */
	return (hr*3600) + (mn*60) + sg;
}
/* FUNÇÃO QUE REALIZA A REMOÇÃO DO OBJETO NA LISTA ATRAVES DO CHANGE -T */
void removeTempo(objeto *lista, char *opcao){
    objeto *lixo, *aux;

    if(lista->nextTime != NULL){
        /* CABEÇA */
        aux = lista;
        /* LIXO RECEBE O MAIS PRIORITARIO, QUE É FEITO ATRÁVES DA FUNÇÃO CHANGE */
        lixo = lista->nextTime;
        /* LISTA RECEBE O PROXIMO DO QUAL SERÁ O LIXO */
        lista->nextTime = lixo->nextTime;
        /* REALIZO A ITERAÇÃO NA PRIORIDADE PARA REMOVE-LO TAMBÉM */
        while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior != lixo->cel.prior){
            aux = aux->nextPrioridade;
        }
        /* FAÇO O QUE QUERO REMOVER RECEBER O PROXIMO DELE, COM ISSO ELE DEIXA DE EXISTIR */
        aux->nextPrioridade = aux->nextPrioridade->nextPrioridade;
        free(lixo);
    }else{
        printf("NAO HA PROCESSOS PARA EXECUTAR!\n");
    }
}
/* FUNÇÃO QUE REALIZA A REMOÇÃO DO OBJETO NA LISTA ATRAVES DO CHANGE -P */
void removePrioridade(objeto *lista, char *opcao){
    objeto *lixo, *aux;

    if(lista->nextPrioridade != NULL){
        /* CABEÇA */
        aux = lista;
        /* LIXO RECEBE O MAIS PRIORITARIO, QUE É FEITO ATRÁVES DA FUNÇÃO CHANGE */
        lixo = lista->nextPrioridade;
        /* LISTA RECEBE O PROXIMO DO QUAL SERÁ O LIXO */
        lista->nextPrioridade = lixo->nextPrioridade;
        /* REALIZO A ITERAÇÃO NA PRIORIDADE TEMPO PARA REMOVE-LO TAMBÉM */
        while (aux->nextTime != NULL && aux->nextTime->cel.prior != lixo->cel.prior){
            aux = aux->nextTime;
        }
        /* FAÇO O QUE QUERO REMOVER RECEBER O PROXIMO DELE, COM ISSO ELE DEIXA DE EXISTIR */
        aux->nextTime = aux->nextTime->nextTime;
        free(lixo);
    }else{
        printf("NAO HA PROCESSOS PARA EXECUTAR!\n");
    }
}
/* FUNÇÃO QUE REALIZA A MODIFICAÇÃO DO OBJETO NA LISTA CONFORME A PRIORIDADE */
void modificaProcessoPrioridade(celula componente, celula componenteNovo, objeto *lista){
    objeto *aux, *objetoAntigo;
    /* CABEÇA */
    aux = lista;
    /* ITERA ATÉ ENCONTRAR O ELEMENTO QUE QUERO */
    while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior > componente.prior){
        aux = aux->nextPrioridade;
    }
    /* AO ENCONTRAR O ELEMENTO, FAÇO A ATRIBUIÇÃO DA PRIORIDADE NOVA */
    objetoAntigo = aux->nextPrioridade;
    objetoAntigo->cel.prior = componenteNovo.prior;
    /* FAÇO COM QUE ELE RECEBA O PROXIMO ELEMENTO DELE */
    aux->nextPrioridade = aux->nextPrioridade->nextPrioridade;
    /* APÓS ATRIBUIR A NOVA PRIORIDADE CHAMO PARA REINSERIR NA LISTA */
    inserePrioridade(objetoAntigo, lista);
}
/* FUNÇÃO QUE REALIZA A MODIFICAÇÃO DO OBJETO NA LISTA CONFORME A PRIORIDADE DE TEMPO */
void modificaProcessoTempo(celula componente, celula componenteNovo, objeto *lista){
    objeto *aux, *objetoAntigo;
    int tempoProcesso2;
    /* CABEÇA */
    aux = lista;
    /* CHAMO A FUNÇÃO PARA REALIZAR A COMPARAÇÃO ATRAVÉS DO TEMPO EM SEGUNDOS */
    tempoProcesso2 = converteHmsEmSegundos(componente.chegada.hh, componente.chegada.mm, componente.chegada.ss);
    /* ITERA ATÉ ENCONTRAR O ELEMENTO QUE QUERO */
    while (aux->nextTime != NULL && converteHmsEmSegundos(aux->nextTime->cel.chegada.hh, aux->nextTime->cel.chegada.mm, aux->nextTime->cel.chegada.ss) != tempoProcesso2){
        aux = aux->nextTime;
    }
    /* AO ENCONTRAR O ELEMENTO, FAÇO A ATRIBUIÇÃO DA PRIORIDADE DE TEMPO NOVA */
    objetoAntigo = aux->nextTime;
    objetoAntigo->cel.chegada.hh = componenteNovo.chegada.hh;
    objetoAntigo->cel.chegada.mm = componenteNovo.chegada.mm;
    objetoAntigo->cel.chegada.ss = componenteNovo.chegada.ss;
    /* FAÇO COM QUE ELE RECEBA O PROXIMO ELEMENTO DELE */
    aux->nextTime = aux->nextTime->nextTime;
    /* APÓS ATRIBUIR A NOVA PRIORIDADE DE TEMPO CHAMO PARA REINSERIR NA LISTA */
    insereTempo(objetoAntigo, lista);
}

/* FUNÇÃO QUE REALIZA A INSERÇÃO DO OBJETO NA LISTA CONFORME A PRIORIDADE */
void inserePrioridade(objeto *novoObjeto, objeto *lista){

    objeto *aux;

    if (lista->nextPrioridade == NULL){
        lista->nextPrioridade = novoObjeto;
    }
    else{
        /* CABEÇA */
        aux = lista;
        /* ITERANDO ATÉ QUE ENCONTRE O OBJETO RESPECTIVO E INSERA NA ORDEM CORRETO */
        while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior > novoObjeto->cel.prior){
            aux = aux->nextPrioridade;
        }
        /* INSERÇÃO NA ORDEM CORRETA */
        novoObjeto->nextPrioridade = aux->nextPrioridade;
        aux->nextPrioridade = novoObjeto;
    }
}
/* FUNÇÃO QUE REALIZA A INSERÇÃO DO OBJETO NA LISTA CONFORME A PRIORIDADE DE TEMPO */
void insereTempo(objeto *novoObjeto, objeto *lista){

    objeto *aux;

    int tempo;

    if (lista->nextTime == NULL){
        lista->nextTime = novoObjeto;
    }
    else{
        /* CABEÇA */
        aux = lista;
        tempo = converteHmsEmSegundos(novoObjeto->cel.chegada.hh, novoObjeto->cel.chegada.mm, novoObjeto->cel.chegada.ss);
        /* ITERANDO ATÉ QUE ENCONTRE O OBJETO RESPECTIVO E INSERA NA ORDEM CORRETO */
        while (aux->nextTime != NULL && converteHmsEmSegundos(aux->nextTime->cel.chegada.hh, aux->nextTime->cel.chegada.mm, aux->nextTime->cel.chegada.ss) < tempo){
            aux = aux->nextTime;
        }
        /* INSERÇÃO NA ORDEM CORRETA */
        novoObjeto->nextTime = aux->nextTime;
        aux->nextTime = novoObjeto;
    }
}

/* FUNÇÃO QUE TEM COMO TAREFA A EXIBIÇÃO E REQUISIÇÃO DAS ENTRADAS DO PROGRAMA */
void menu(char *comando, objeto *lista){

    char opcao[2];
    celula componente, componenteNovo;

    if(strcmp(comando, "next") == 0){
        scanf("%s", opcao);
        imprimeNext(lista, opcao);
        printf("\n");
        scanf("%s", comando);
    }else if(strcmp(comando, "add") == 0){
        scanf("%d", &(componente.prior));
        scanf("%d:%d:%d", &(componente.chegada.hh), &(componente.chegada.mm), &(componente.chegada.ss));
        scanf("%s", componente.descricao);
        cadastraProcesso(componente, lista);
        scanf("%s", comando);
    }else if(strcmp(comando, "print") == 0){
        scanf("%s", opcao);
        imprimeLista(lista, opcao);
        printf("\n");
        scanf("%s", comando);
    }else if(strcmp(comando, "exec") == 0){
        scanf("%s", opcao);
        if(strcmp(opcao, "-p") == 0){
            removePrioridade(lista, opcao);
        }else{
            removeTempo(lista, opcao);
        }
        scanf("%s", comando);
    }else if(strcmp(comando, "change") == 0){
        scanf("%s", opcao);
        if(strcmp(opcao, "-t") == 0){
            scanf("%d:%d:%d|%d:%d:%d", &(componente.chegada.hh), &(componente.chegada.mm), &(componente.chegada.ss), &(componenteNovo.chegada.hh), &(componenteNovo.chegada.mm), &(componenteNovo.chegada.ss));
            modificaProcessoTempo(componente, componenteNovo, lista);
        }else{
            scanf("%d|%d", &(componente.prior), &(componenteNovo.prior));
            modificaProcessoPrioridade(componente, componenteNovo, lista);
        }
        scanf("%s", comando);
    }
}