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
int estaVazia(t_lista * l){
    if(l->primeiro == NULL)
       return 1;
    return 0;
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
void printPilha(t_pilha *p){
	if (p->l->primeiro == NULL){
		printf("Pilha vazia.\n");
	} else{
		t_elemento *temp = p->l->primeiro;
		int i = 0;

		while(temp != NULL){
			printf("Pos: %d\tDado: %c\n", i, temp->dado);
			temp = temp->proximo;
			i++;
		}
		printf("\n");
	}
}

int main() {
    int i;
    char infixa[50], aff;
    t_pilha *p = criaPilha();

    while (1) { //checa se todos os parenteses fecham
        printf("Digite a expressao na forma infixa:");
        scanf("%s", infixa);

        for (i = 0; i < strlen(infixa); i++) {
            //printf("%c\n", infixa[i]);
            if (infixa[i] == '(' || infixa[i] == '[' || infixa[i] == '{'){
                empilhar(infixa[i], p);
                //printf("empilhou %c\n", infixa[i]);
            }
            else if (infixa[i] == ')' || infixa[i] == ']' || infixa[i] == '}'){
                if (estaVaziaPilha(p)){
                    printf("Formato invalido. Tente novamente.11111\n");
                    break;
                }
                if ((p->l->primeiro->dado == '(' && infixa[i] == ')') || (p->l->primeiro->dado == '[' && infixa[i] == ']') || (p->l->primeiro->dado == '{' && infixa[i] == '}')){
                    //printf("desempilhou %c\n", desempilhar(p)); //
                    desempilhar(p);
                }
                else
                    printf("Formato invalido. Tente novamente.222222\n");
            }
        }
        printPilha(p);
        if (estaVaziaPilha(p)){
            break;
        }
    }
    return 0;
}
