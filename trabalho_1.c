#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/////////////////////////////////////////////////////////////lista e pilha para char
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
/////////////////////////////////////////////////////////////lista e pilha para float
typedef struct elementof{ 
	float dado;
	struct elementof * proximo;
}t_elementof;
typedef struct listaf{
	t_elementof * primeiro;
	t_elementof * ultimo;
}t_listaf;
typedef struct pilhaf{
	t_listaf * l;
}t_pilhaf;
////////////////////////////////////////////////////////////funcoes de lista e pilha para char
t_lista * criaLista(){
    t_lista * l = (t_lista *)malloc(sizeof(t_lista));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}
void insereInicio(char valor, t_lista *l){
    t_elemento * novoprimeiro = (t_elemento *)malloc(sizeof(t_elemento));
    novoprimeiro->dado = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}
void insereFinal(char valor, t_lista *l){
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
int estaVazia(t_lista *l){
    if(l->primeiro == NULL)
       return 1;
    return 0;
}
int removeInicio(t_lista *l){
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
void empilhar(char valor,t_pilha *p){
    insereInicio(valor, p->l);
}
char desempilhar(t_pilha *p){
    return removeInicio(p->l);
}
int estaVaziaPilha(t_pilha *p){
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
////////////////////////////////////////////////////////////funcoes de lista e pilha para float
t_listaf * criaListaf(){
    t_listaf * l = (t_listaf *)malloc(sizeof(t_listaf));
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}
void insereIniciof(float valor, t_listaf *l){
    t_elementof * novoprimeiro = (t_elementof *)malloc(sizeof(t_elementof));
    novoprimeiro->dado = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}
int estaVaziaf(t_listaf *l){
    if(l->primeiro == NULL)
       return 1;
    return 0;
}
float removeIniciof(t_listaf * l){
    if(estaVaziaf(l))
        return -1;
    float tmp = l->primeiro->dado;
    t_elementof * removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL) //nao precisava disso aqui (linha 98)
       l->ultimo = NULL;
    return tmp;
}
t_pilhaf * criaPilhaf(){
    t_pilhaf * p =  (t_pilhaf *)malloc(sizeof(t_pilhaf));
    p->l = criaListaf();
    return p;
}
void empilharf(float valor, t_pilhaf *p){
    insereIniciof(valor, p->l);
}
float desempilharf(t_pilhaf * p){
    return removeIniciof(p->l);
}
int estaVaziaPilhaf(t_pilhaf * p){
    return estaVaziaf(p->l);
}
void printPilhaf(t_pilhaf *p){
	if (p->l->primeiro == NULL){
		printf("Pilha vazia.\n");
	} else{
		t_elementof *temp = p->l->primeiro;
		int i = 0;

		while(temp != NULL){
			printf("Pos: %d\tDado: %.1f\n", i, temp->dado);
			temp = temp->proximo;
			i++;
		}
		printf("\n");
	}
}
////////////////////////////////////////////////////////////funcoes de comparacao
int ehNumero(char ch){
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
		return 1;
	return 0;
}
int ehOperador(char ch){
	if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
		return 1;
	return 0;
}
int ehEscopo(char ch){
	if (ch == '(')
		return 1;
	else if (ch == ')')
		return -1;
	return 0;
}
int prioridade(char ch){
	if (ch == '*' || ch == '/')
		return 2;
	else if (ch == '+' || ch == '-')
		return 1;
	return 0;
}
////////////////////////////////////////////////////////////main
int main(int argc, char *argv[]) {
    int i;
    char infixa[50] = "\0", posfixa[50] = "\0", temp[2], t;
    float a, b, c;
    t_pilha *p = criaPilha();
    t_pilhaf *pf = criaPilhaf();

    while (1) { //checa se todos os parenteses fecham
        printf("Digite a expressao na forma infixa:");
        scanf("%s", infixa);

        for (i = 0; i < strlen(infixa); i++) {
            if (ehEscopo(infixa[i] == 1)) //fazer funcoes pra substituir esse if e deixar a main mais limpa
                empilhar(infixa[i], p);
            else if (ehEscopo(infixa[i] == -1)){
                if (estaVaziaPilha(p)){
                    printf("Formato invalido. Tente novamente.\n");
                    break;
                }
                if (p->l->primeiro->dado == '(' && infixa[i] == ')')
                    desempilhar(p);
                else
                    printf("Formato invalido. Tente novamente.\n");
            }
        }
        if (estaVaziaPilha(p))
            break;
		while(!estaVaziaPilha(p))
			desempilhar(p);
    }
    printf("\nPOSFIXA --> %s\n", posfixa); //debug
    puts(posfixa); //debug
    printf("\n"); //debug
	for (i = 0; i < strlen(infixa); i++) {
		temp[0] = ' ';
		temp[1] = ' ';
		if (ehNumero(infixa[i])){
			if (ehNumero(infixa[i+1])){
				temp[0] = infixa[i];
				temp[1] = '\0'; 
				strcat(posfixa, temp);
			}
			else{
				temp[0] = infixa[i];
				strcat(posfixa, temp);
			}
		} else if (ehOperador(infixa[i])){
			if (!estaVaziaPilha(p) && prioridade(p->l->primeiro->dado) >= prioridade(infixa[i])){
				printf("%c\t%c\n", p->l->primeiro->dado, infixa[i]); //debug
				printf("%i\t%i\n", prioridade(p->l->primeiro->dado), prioridade(infixa[i])); //debug
				while(prioridade(p->l->primeiro->dado) >= prioridade(infixa[i])){
					temp[0] = desempilhar(p);
					if (!ehEscopo(temp[0]))
						strcat(posfixa, temp);
					printf("ESSE PRINT FUNCIONA\n");
				}
				printf("ESSE PRINT NAO FUNCIONA	\n");
			}
			empilhar(infixa[i], p);
		} else if (infixa[i] == '('){
			empilhar(infixa[i], p);
		} else if (infixa[i] == ')'){
			do{
				t = desempilhar(p);
				if (t != '('){	
					temp[0] = t;
					strcat(posfixa, temp);
				}
			} while (t != '(');
		}
		printf("ch: %c\ttot: %s\n", infixa[i], posfixa); //debug
		printPilha(p); //debug
	}
	while(!estaVaziaPilha(p)){
		temp[0] = desempilhar(p);
		temp[1] = ' ';
		strcat(posfixa, temp);
	}
	printf("\nEXPRESSAO POSFIXA --> %s\n", posfixa); //debug
	for (i = 0; i < strlen(posfixa); i++){
		if(ehNumero(posfixa[i])){
			empilharf((float)posfixa[i]-48, pf);
		} else if(ehOperador(posfixa[i])){
			a = desempilharf(pf);
			b = desempilharf(pf);
			switch (posfixa[i]){
				case '+':
					c = b + a;
					break;
				case '-':
					c = b - a;
					break;
				case '*':
					c = b * a;
					break;
				case '/':
					c = b / a;
					break;
			}
			empilharf(c, pf);
			printPilhaf(pf); //debug
		}
	}
	printf("\nResultado: %.1f\n", desempilharf(pf));	
    return 0;
}
