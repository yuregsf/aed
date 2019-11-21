#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista4.h"

/* FUNCOES PRIVADAS */
char * private_char_copia (char * s) {
	char * aux = (char *) malloc (strlen(s)+1);
	strcpy(aux, s);
	return aux;
}
/* IMPLEMENTACAO POR ENCADEAMENTO DUPLO */
typedef struct no No;
struct no {
	struct no * anterior;
	char * elemento;
	struct no * proximo;
};
struct lista {
	No * cabeca;
	int tamanho;
};
Lista * lista_cria () {
	Lista * q = (Lista *) malloc(sizeof(Lista));
	if (q!=NULL) {
		q->cabeca = NULL;
		q->tamanho = 0;
	}
	return q;
}
Lista * lista_copia (Lista * p) {
	return NULL;
}
void lista_libera (Lista * p) {
	No * q = p->cabeca;
	int tamanho;
	for (tamanho = lista_obtem_tamanho(p); tamanho > 0; tamanho--) {
		No * aux = q->proximo;
		free(q);
		q = aux;
	}
	free(p);
}
int lista_insere_inicio (Lista * p, char * elemento) {
	No * no = (No *) malloc(sizeof(No));
	if (no==NULL)
		return 0; // insercao sem sucesso;
	no->elemento = (char *) malloc(strlen(elemento)+1);
	strcpy(no->elemento, elemento);
	if (!lista_obtem_tamanho(p)) {
		no->anterior = no;
		no->proximo  = no;
	} else {
		p->cabeca->anterior->proximo = no;
		no->anterior = p->cabeca->anterior;
		no->proximo  = p->cabeca;
		p->cabeca->anterior = no;
	}
	p->cabeca = no;
	p->tamanho = p->tamanho + 1;
	return 1; // insercao com sucesso
}
int lista_insere_final (Lista * p, char * elemento) {
	No * node = (No *)malloc(sizeof(No));
	if(p != NULL && node != NULL){
		node->elemento = (char *) malloc(strlen(elemento)+1);
		strcpy(node->elemento, elemento);
		if(!lista_obtem_tamanho(p)){
			node->proximo = node;
			node->anterior = node;
			p->cabeca = node;
		}else{
			node->proximo = p->cabeca;
			node->anterior = p->cabeca->anterior;
			p->cabeca->anterior->proximo = node;
			p->cabeca->anterior = node;
		}
		p->tamanho++;
		return 1;

	}
	return 0; // insercao sem sucesso
}
int lista_insere_posicao (Lista * p, char * elemento, int posicao) {
	if(posicao >= 0 && posicao <= p->tamanho){
		No * node = (No *)malloc(sizeof(No));
		if(p != NULL && node != NULL){
			if(posicao == 0){
				lista_insere_inicio(p, elemento);
			}else if(posicao == p->tamanho){
				lista_insere_final(p, elemento);
			}else{
				int i;
				No * aux = p->cabeca;
				node->elemento = (char *) malloc(strlen(elemento)+1);
				strcpy(node->elemento, elemento);
				for(i = 0; i<posicao; i++){
					aux = aux->proximo;
				}
				node->proximo = aux->proximo;
				aux->proximo->anterior = node;
				node->anterior = aux;
				aux->proximo = node;
			}
			p->tamanho++;
			return 1;
		}
	}
	return 0; // insercao sem sucesso
}
int lista_remove_inicio (Lista * p){
	if(p != NULL){
		No * aux = p->cabeca;
		if(p->tamanho == 0){
			p->cabeca = NULL;
			free(aux);
		}else{
			p->cabeca->proximo->anterior = p->cabeca->anterior;
			p->cabeca->anterior->proximo = p->cabeca->proximo;
			p->cabeca = p->cabeca->proximo;
			free(aux);

		}
		p->tamanho--;
		return 1;
	}
	return 0; // remocao sem sucesso
}
int lista_remove_final  (Lista * p){
	if(p != NULL){
		if(p->tamanho == 0){
			p->cabeca = NULL;
			free(p->cabeca);
		}else{
			No * aux = p->cabeca->anterior;
			aux->anterior->proximo = p->cabeca;
			p->cabeca->anterior = aux->anterior;
			free(aux);

		}
		p->tamanho--;
		return 1;
	}
	return 0; // remocao sem sucesso
}
int lista_remove_posicao (Lista * p, int posicao){
	if(posicao >= p->tamanho && posicao < p->tamanho){
		if(posicao == 0){
			lista_remove_inicio(p);
		}else if(posicao == p->tamanho-1){
			lista_remove_final(p);
		}else{
			No * aux = p->cabeca;
			int i;
			for(i = 0; i < p->tamanho; i++){
				aux = aux->proximo;
			}
			aux->anterior->proximo = aux->proximo;
			aux->proximo->anterior = aux->anterior;
			free(aux);
		}
		p->tamanho--;
		return 1;
	}
	return 0; // remocao sem sucesso
}
char * lista_obtem_elemento  (Lista * p, int posicao) {
	if ((posicao<1)||(posicao>lista_obtem_tamanho(p)))
		return NULL;
	No * q = p->cabeca;
	int i;
	for (i=0; i<posicao-1; i++)
		q = q->proximo;
	return private_char_copia(q->elemento);
}
int lista_se_presente  (Lista * p, char * elemento) {
	return 0; // elemento ausente
}
int lista_obtem_tamanho  (Lista * p) {
	return p->tamanho;
}
char * lista_imprime  (Lista * p) {
	char * retorno = (char *) malloc(lista_obtem_tamanho(p)*10+1);
	retorno[0] = '\0';
	No * q = p->cabeca;
	int i;
	for (i=0; i < lista_obtem_tamanho(p); i++) {
		char aux[50];
		sprintf(aux, "%s " , q->elemento);
		strcat(retorno, aux);
		q = q->proximo;
	}
	retorno = (char*) realloc (retorno, strlen(retorno)+1);
	return retorno;
}
void lista_ordena (Lista * p) {
	int i, j;
	for(i = 0; i<p->tamanho-1; i++){
		for(j = 0; j < p->tamanho-i-1; j++){
			char * p1 = (char *)malloc(strlen(lista_obtem_elemento(p, j))+1);
			strcpy(p1, lista_obtem_elemento(p, j));
			char * p2 = (char *)malloc(strlen(lista_obtem_elemento(p, j+1))+1);
			strcpy(p2, lista_obtem_elemento(p, j+1));
			if(strcmp(p1,p2) > 0){
				lista_remove_posicao(p, j);
				lista_insere_posicao(p, p1, j+1);
			}
			free(p1);
			free(p2);
		}
	}
}
int lista_se_consistente (Lista * p) {
	if ( ! lista_obtem_tamanho(p) )
		return 1; // lista consistente
	No * aux = p->cabeca;
	int tam;
	for (tam = lista_obtem_tamanho(p); tam > 0; tam--)
		aux = aux->proximo;
	if (aux != p->cabeca)
		return 0; // lista nao consistente
	for (tam = lista_obtem_tamanho(p); tam > 0; tam--)
		aux = aux->anterior;
	if (aux != p->cabeca)
		return 0; // lista nao consistente
	return 1; // lista consistente
}
