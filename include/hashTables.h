#include <glib.h>
#include "interface.h"
#include "date.h"
#include "common.h"

struct TCD_community
{
	GHashTable *h_IDUtilizador;
	GHashTable *h_IDPerguntas;
	GHashTable *h_IDRespostas;
	GHashTable *h_IDTags;

	long* top_NPosts;
	long* top_NClassificacoes;
};

struct h_IDUtilizador
{//users
	long id_u;//id
	char* name;//dispçayname
	char* shortb;//aboutme
	//long* ultimos10;
	int totalposts;
	long reputacao;//reputation
	int votes;
};

struct h_IDPerguntas
{//posts
	long id_post;//id
	long id_autor;//owneruserid
	char* title;//title
	char* tags;//tags
	long score;//score
	long n_resp;
	char* d;
};

struct h_IDRespostas
{//posts
	long id_post;// id em posts.xml
	long id_perg;// parent id em posts.xml
	long id_autor; // owneruserid
	long score; //score
	long n_coments;
	char* d;
};

struct h_IDTags
{
	long id_tag;
	char* tag;
	long count;
};

TAD_community initHashTables(TAD_community t);
TAD_community add_Utilizador(TAD_community t, long id, char * nome,char* shortbio, long , int votes);
TAD_community add_Perguntas(TAD_community t, long id, char* titulo, long id_autor2, char* tag, long scr, long respo, char* d2);
TAD_community add_Respostas(TAD_community t, long id_post2, long id_perg2, long id_autor,  long scr, long coment, char* d2);
TAD_community add_Tags(TAD_community t, long id_tag2, char* t1);
TAD_community clear(TAD_community t);
void * getHashIterator(GHashTable *t);
int getNextIterator(void *iterator, void *key, void *value);
void freeIterator(void *iterator);
int encontrado(TAD_community com, long author_id, long id_pai);