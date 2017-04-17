#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento{
	char dado;
	struct elemento * proximo;
}t_elemento;
typedef struct lista{
	t_elemento * primeiro;
	t_elemento * ultimo;
}t_lista;
typedef struct pilha{
	t_lista * l;
}t_pilha;

t_lista * criaLista(){
    t_lista * l = (t_lista *)malloc(sizeof(t_lista));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}
void insereInicio(char valor, t_lista * l){
    t_elemento * novoprimeiro = (t_elemento *)malloc(sizeof(t_elemento));
    novoprimeiro->dado = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}
void insereFinal(char valor, t_lista * l){
    t_elemento * novoultimo = (t_elemento *)malloc(sizeof(t_elemento));
    novoultimo->dado = valor;
    novoultimo->proximo = NULL;
    if(l->primeiro == NULL){
        l->primeiro = novoultimo;
    }else{
        l->ultimo->proximo = novoultimo;
    }
    l->ultimo = novoultimo;
}
int removeInicio(t_lista * l){
    if(estaVazia(l))
        return -1;
    int tmp = l->primeiro->dado;
    t_elemento * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL) //nao precisava disso aqui (linha 98)
       l->ultimo = NULL;
    return tmp;
}
int estaVazia(t_lista * l){
    if(l->primeiro == NULL)
       return 1;
    return 0;
}
t_pilha * criaPilha(){
    t_pilha * p =  (t_pilha *)malloc(sizeof(t_pilha));
    p->l = criaLista();
    return p;
}
void empilhar(char valor,t_pilha * p){
    insereInicio(valor, p->l);
}
char desempilhar(t_pilha * p){
    return removeInicio(p->l);
}
int estaVaziaPilha(t_pilha * p){
    return estaVazia(p->l);
}

int main() {
    int i;
    char infixa[50];
    t_pilha *p = criaPilha();

    while (1) { //checa se todos os parenteses fecham
        printf("Digite a expressao na forma infixa:");
        scanf("%s", infixa);

        for (i = 0; i < strlen(infixa); i++) {
            if (infixa[i] == '(')
            empilhar(infixa[i], p);
            else if (infixa[i] == ')')
            desempilhar(p);
        }
        if (estaVaziaPilha(p)){
            break;
        }
    }



    return 0;
}
