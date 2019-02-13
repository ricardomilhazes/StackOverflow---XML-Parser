#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

#include "hashTables.h"


/** \brief Inicializa a estrutura TAD_community
 @param t Estrutura TAD_community
 @return Estrutura TAD_community
 */
TAD_community initHashTables(TAD_community t){

	GHashTable *id_autor=g_hash_table_new_full(g_int64_hash, g_int64_equal, free, free);
	GHashTable *id_p=g_hash_table_new_full(g_int64_hash, g_int64_equal, free, free);
	GHashTable *id_r=g_hash_table_new_full(g_int64_hash, g_int64_equal, free, free);
	GHashTable *id_tag=g_hash_table_new_full(g_int64_hash, g_int64_equal, free,free);

	t->h_IDUtilizador=id_autor;
	t->h_IDPerguntas=id_p;
	t->h_IDRespostas=id_r;
	t->h_IDTags=id_tag;

	return t;
}

/** \brief Adiciona um utilizador à TAD_community
 @param t Estrutura TAD_community
 @param id ID do utilizador
 @param nome Nome do utilizador
 @param shortbio Shortbio do utilizador
 @param reputation Reputação do utilizador
 @return Estrutura TAD_community
 */
TAD_community add_Utilizador(TAD_community t, long id, char* nome,char* shortbio, long reputation, int votos) {

	struct h_IDUtilizador *hAtualizada = malloc(sizeof(struct h_IDUtilizador));	

	long *idCopy=malloc(sizeof(long));
		*idCopy=id;

	hAtualizada->id_u=id;
	hAtualizada->name=mystrdup(nome);
	hAtualizada->shortb=mystrdup(shortbio);
	hAtualizada->totalposts=0;
	hAtualizada->reputacao=reputation;
	hAtualizada->votes=votos;

	g_hash_table_insert(t->h_IDUtilizador,idCopy,hAtualizada);
	
	return t;
}

/** \brief Adiciona uma pergunta à TAD_community
 @param t Estrutura TAD_community
 @param id ID da pergunta
 @param titulo Título da pergunta
 @param nome Nome do autor
 @param id_autor2 ID do autor da pergunta
 @param tag Tags utilizadas na pergunta
 @param scr Score da pergunta
 @param post_type_id Tipo de post(1 para pergunta, 2 para resposta)
 @return Estrutura TAD_community
 */

TAD_community add_Perguntas(TAD_community t, long id, char* titulo, long id_autor2, char* tag, long scr, long respo, char* d2){

		long *idCopy=malloc(sizeof(long));
		*idCopy=id;
		
		struct h_IDUtilizador *numeroposts = (struct h_IDUtilizador*) g_hash_table_lookup(t->h_IDUtilizador, &id_autor2);
		struct h_IDPerguntas *hAtualizada = malloc(sizeof(struct h_IDPerguntas));

		hAtualizada->id_post = id;
		hAtualizada->id_autor = id_autor2;
		hAtualizada->title = mystrdup(titulo);
		hAtualizada->tags = mystrdup(tag);
		hAtualizada->score=scr;
		hAtualizada->n_resp = respo;
		hAtualizada->d=mystrdup(d2);

		g_hash_table_insert(t->h_IDPerguntas,idCopy,hAtualizada);

		if(numeroposts!=NULL) numeroposts->totalposts=(numeroposts->totalposts)+1;

	return t;
}

/** \brief Adiciona uma resposta à TAD_community
 @param t Estrutura TAD_community
 @param id_post2 ID do post
 @param id_perg2 ID da pergunta a que corresponde a resposta
 @param id_autor2 ID do autor da resposta
 @param nome Nome do autor
 @param votes Votos da resposta
 @param scr Score da resposta
 @param post_type_id Tipo do post (1 para pergunta, 2 para resposta)
 @return Estrutura TAD_community
 */
TAD_community add_Respostas(TAD_community t, long id_post2, long id_perg2, long id_autor2, long scr, long coment, char* d2){

		struct h_IDUtilizador *numeroposts = (struct h_IDUtilizador*) g_hash_table_lookup(t->h_IDUtilizador, &id_autor2);
		struct h_IDRespostas *hAtualizada = malloc(sizeof(struct h_IDRespostas));	

		long *idCopy=malloc(sizeof(long));
		*idCopy=id_post2;

		hAtualizada->id_post = id_post2;
		hAtualizada->id_perg = id_perg2;
		hAtualizada->id_autor = id_autor2;
		// hAtualizada->name=strcpy(hAtualizada->name,nome); como tiramos o nome do autor acho que n é preciso
		//hAtualizada->votes=votes;
		hAtualizada->score=scr;
		hAtualizada->n_coments = coment;
		hAtualizada->d=mystrdup(d2);
		g_hash_table_insert(t->h_IDRespostas,idCopy,hAtualizada);

		numeroposts->totalposts=(numeroposts->totalposts)+1;
		
	return t;
}
/** \brief Adiciona uma tag à TAD_community
 @param t Estrutura TAD_community
 @param id_tag2 Id da Tag
 @param t1 Nome da Tag
 @return Estrutura TAD_community
 */

TAD_community add_Tags(TAD_community t, long id_tag2, char* t1){

	struct h_IDTags *hAtualizada = malloc(sizeof(struct h_IDTags));

	long *idCopy=malloc(sizeof(long));
		*idCopy=id_tag2;

	hAtualizada->id_tag = id_tag2;
	hAtualizada->tag = mystrdup(t1);
	hAtualizada->count=0;

	g_hash_table_insert(t->h_IDTags,idCopy,hAtualizada);

	return t;
}
/** \brief Liberta todos os recursos associados à estrutura TAD_community
 @param t Estrutura TAD_community
 @return Estrutura TAD_community
 */
TAD_community clear(TAD_community t){
	g_hash_table_destroy(t->h_IDPerguntas);
	g_hash_table_destroy(t->h_IDRespostas);
	g_hash_table_destroy(t->h_IDUtilizador);
	g_hash_table_destroy(t->h_IDTags);
	return t;
}
/** \brief É criado um iterador que percorre a tabela de hash
 @param t Estrutura TAD_community
 @return Estrutura TAD_community
 */
void * getHashIterator(GHashTable *t) {

	GHashTableIter *iterator = malloc(sizeof(GHashTableIter));

	g_hash_table_iter_init(iterator, t);

	return (void*) iterator;
}
/** \brief O iterador passa para o proximo elemento da tabela de hash
 @param iterator iterador pertendente a uma hash table
 @param key Representa o valor pela qual a tabela de hash é ordenada
 @param value Representa a tabela de hash em questao
 @return result Retorna valores se a hash table e a sua key nao for nula
 */
int getNextIterator(void *iterator, void *key, void *value) {

	int result = (int) g_hash_table_iter_next(iterator, (gpointer) key, (gpointer) value);

	return result;
}
/** \brief Deixa de percorrer a hash table do @param iterator
 @param iterator percorre a hash table atraves da key

 */
void freeIterator(void *iterator) {
	free(iterator);
}
/** \brief Verifica se existe alguma repsosta com um especifico parent_id
 @param com Estrutura TAD_community 
 @param author_id Representa o id do autor da resposta
 @param id_pai Representa o parent_id de uma resposta
 @return 1 se encontrar
 @return 0 se nao encontrar
 */
int encontrado(TAD_community com, long author_id, long id_pai){
	void* iterator = getHashIterator(com->h_IDRespostas);

	struct h_IDRespostas *t = malloc(sizeof(struct h_IDRespostas));

	void *key=NULL;

	while(getNextIterator(iterator,&key,&t)){
		if(t->id_autor==author_id&&t->id_perg==id_pai)
			return 1;
	}
	return 0;
}