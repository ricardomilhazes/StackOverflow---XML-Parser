#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

#include "parsefile.h"
#include "interface.h"

/** \brief Inicializa todas as estruturas.
@return Estrutura inicializada
*/
TAD_community init(){
	TAD_community t = malloc(sizeof(struct TCD_community));

	t->h_IDUtilizador=NULL;
	t->h_IDPerguntas=NULL;
	t->h_IDRespostas=NULL;

	t->top_NPosts='\0';
	t->top_NClassificacoes='\0';


	t=initHashTables(t);

	return t;
}

/** \brief Carrega para a estrutura toda a informaçao necessária.
@param com Estrutura inicializada
@param dump_path Localizaçao dos ficheiros do dump
@return Estrutura carregada
*/
TAD_community load(TAD_community com, char* dump_path){

	//char *files="/home/gabriela/Desktop/ubuntu/Users.xml";
	//char *files2="/home/gabriela/Desktop/ubuntu/Posts.xml";	

	//char *files="/mnt/c/Users/rjsf3/Desktop/LI3/ubuntu/Users.xml";
	//char *files2="/mnt/c/Users/rjsf3/Desktop/LI3/ubuntu/Posts.xml";

	char *files="/home/milhazes/Desktop/LI3/Grupo20/src/LI3/ubuntu/Users.xml";
	char *files2="/home/milhazes/Desktop/LI3/Grupo20/src/LI3/ubuntu/Posts.xml";
	char *files3="/home/milhazes/Desktop/LI3/Grupo20/src/LI3/ubuntu/Tags.xml";


	com=loadHashUsers(com,(const char*)files);
	com=loadHashPerguntas(com,(const char*)files2);
	com=loadHashTags(com,(const char*)files3);

	//int i=0;
	//g_hash_table_foreach(com->h_IDRespostas, printUserHT, &i);


	return com;
}

/** \brief funçao que verifica se uma string ocorre na outra.
@param s1 Primeira string
@param s2 Segunda string
@return 1 caso uma ocorra na outra, 0 caso contrário
*/
int mystrstr (char* s1, char* s2) {
    int i,j;
    for(i=0;s1[i]!='\0';i++) {
        
        for(j=0;s2[j]!='\0'&&s2[j]==s1[i];j++,i++);
        if (s2[j]=='\0') return 1;
        
    }
    if(s1[0]=='\0'&&s2[0]=='\0') return 1;
    return 0;
}

/** \brief Funcao que ordena um array em funcao das datas.
@param datas Array de datas
@param ids Array de IDs
@param N Tamanho do array
*/
void ordena_array (char* datas[],long ids[], int N ){
	char* temp;
	long temp2;
	for (int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if ((strcmp((datas[j]),(datas[i])))<=0){
				temp = datas[i];
				temp2 = ids[i];

				datas[i]=datas[j];
				datas[j]=temp;

				ids[i]=ids[j];
				ids[j]=temp2;
			}
		}
	}
}

void aumenta_tags(TAD_community com, char* tags){
	void *iterator = getHashIterator(com->h_IDTags);

	void *key =NULL;

	struct h_IDTags *current = malloc(sizeof(struct h_IDTags));

	while(getNextIterator(iterator,&key,&current)){
		if(mystrstr(tags,current->tag)==1)
			current->count++;
		}
}

/** \brief Interrogaçao 1. Dado o identificador de um post, retorna o título do post e o nome de utilizador do autor.
@param com Estrutura inicializada
@param id Identificador do post
@return Se o post for uma pergunta, retorna o título e utilizador. Caso seja uma resposta, retorna o título e utilizador da pergunta correspondente
*/
STR_pair info_from_post(TAD_community com, long id){

	char* title_perg;
	char* user_name;
	long id_user;
	long id_temp=id;

	STR_pair info;

	struct h_IDPerguntas *currentP = malloc(sizeof(struct h_IDPerguntas));
	struct h_IDRespostas *currentR = malloc(sizeof(struct h_IDRespostas));
	struct h_IDUtilizador *current = malloc(sizeof(struct h_IDUtilizador));
	
	if(g_hash_table_lookup(com->h_IDRespostas,&id)!=NULL){
		currentR = g_hash_table_lookup(com->h_IDRespostas,&id);
		id_temp = (currentR->id_perg);
	}

	currentP=g_hash_table_lookup(com->h_IDPerguntas,&id_temp);
	title_perg = (currentP->title) ;
	id_user = (currentP->id_autor) ; 

	current = g_hash_table_lookup(com->h_IDUtilizador,&id_user);
	user_name = (current ->name) ;

	info = create_str_pair(title_perg , user_name);

return info;
}

/** \brief Interrogaçao 2. Funcao que obtém o top N utilizadores com maior número de  posts  de  sempre, considerando tanto perguntas quanto respostas dadas pelo respectivo utilizador.
@param Estrutura inicializada
@param N número de elementos do top
@return O top N de utiizadores com mais posts
*/
LONG_list top_most_active(TAD_community com, int N){
	void *iterator = getHashIterator(com->h_IDUtilizador);

	int i, fixo = (N-1),pos;

	LONG_list topN;

	topN = create_list(N);

	struct h_IDUtilizador *verificador[N];

	struct h_IDUtilizador tmp = {(long) 0, "", "",/*falta,*/ 0, (long) 0, (long) 0}; 

	for(i=0;i<N;i++){
		verificador[i]=&tmp;
	}

	void *key=NULL;
	
	struct h_IDUtilizador *current = malloc(sizeof(struct h_IDUtilizador));

	while(getNextIterator(iterator,&key,&current)){
		pos = (N-1);
		if(current->totalposts>(verificador[fixo]->totalposts)){
			while((pos>=1)&&(current->totalposts>(verificador[pos-1]->totalposts))){
				pos--;
			}
			for(i=N-1;i>pos;i--){
				verificador[i]=verificador[i-1];
			}
			verificador[pos] = current;
		}
	}
	for(i=0;i<N;i++){
		set_list(topN,i,(verificador[i]->id_u));
	}
	return topN;


}

/** \brief Interrogaçao 3. Obtém o número total de posts (perguntas e respostas separadamente), num determinado intervalo de tempo.
@param com Estrutura inicializada
@param begin Data inicial do intervalo de tempo
@param end Data final do intervalo de tempo
@return Par com o número total de perguntas e respostas nesse intervalo de tempo
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){

	long perg = 0;
	long resp = 0;


	GDateTime* data_begin = g_date_time_new_local(get_year(begin),get_month(begin),get_day(begin),0,0,0.0);
	GDateTime* data_end = g_date_time_new_local(get_year(end),get_month(end),get_day(end),0,0,0.0);



	char* data_begin_string = g_date_time_format(data_begin,"%F");
	char* data_end_string = g_date_time_format(data_end,"%F");

	void *iterator1 = getHashIterator(com->h_IDPerguntas);
	void *iterator2 = getHashIterator(com->h_IDRespostas);

	void *key=NULL;
	
	struct h_IDPerguntas *currentP = malloc(sizeof(struct h_IDPerguntas));

	struct h_IDRespostas *currentR = malloc(sizeof(struct h_IDRespostas));

	while (getNextIterator(iterator1, &key, &currentP)){
		if(((strcmp((currentP->d),data_begin_string))>=0) && ((strcmp((currentP->d),data_end_string))<=0)){
		perg++;
	}
}

	void* key2 = NULL;	

	while(getNextIterator(iterator2, &key2, &currentR)) {
		if(((strcmp((currentR->d),data_begin_string))>=0) && ((strcmp((currentR->d),data_end_string))<=0)){
			resp++;
	}
}

	LONG_pair total;
	total = create_long_pair(perg, resp);

	return total;
}

/** \brief Interrogaçao 4. Funcao que retorna todas as perguntas contendo uma determinada tag.
@param com Estrutura inicializada
@param tag Tag a procurar
@param begin Data inicial do intervalo de tempo
@param end Data final do intervalo de tempo
@return Lista com os IDs das perguntas ordenadas em cronologia inversa
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	int soma_tags=0,pos,i;
	void *iterator1 = getHashIterator(com->h_IDPerguntas);
	void *iterator2 = getHashIterator(com->h_IDPerguntas);

	LONG_list idTags;

	GDateTime* data_begin = g_date_time_new_local(get_year(begin),get_month(begin),get_day(begin),0,0,0.0);
	GDateTime* data_end = g_date_time_new_local(get_year(end),get_month(end),get_day(end),0,0,0.0);
	GDateTime* data = g_date_time_new_local(1000,1,1,0,0,0.0);

	char* string_Data = g_date_time_format(data,"%F");
	char* data_begin_string = g_date_time_format(data_begin,"%F");
	char* data_end_string = g_date_time_format(data_end,"%F");

	struct h_IDPerguntas *currentP1 = malloc(sizeof(struct h_IDPerguntas));

	void *key=NULL;

	while(getNextIterator(iterator1,&key,&currentP1)){
		if(mystrstr(currentP1->tags,tag)==1){
			if((strcmp((currentP1->d),data_begin_string))>=0 && (strcmp((currentP1->d),data_end_string))<=0){
				soma_tags++;
				}
			}
		}

	struct h_IDPerguntas *verificador[soma_tags];

	struct h_IDPerguntas tmp = {(long) 0, (long) 0,"","",(long) 0,(long) 0, string_Data}; 
 	
 	for(i=0;i<soma_tags;i++){
		verificador[i]=&tmp;
	}

	struct h_IDPerguntas *currentP2 = malloc(sizeof(struct h_IDPerguntas));

	key=NULL;

	while(getNextIterator(iterator2,&key,&currentP2)){
		if(mystrstr(currentP2->tags,tag)==1){
			if((strcmp((currentP2->d),data_begin_string))>=0 && (strcmp((currentP2->d),data_end_string))<=0){
				pos=soma_tags-1;
				if(strcmp((currentP2->d),(verificador[soma_tags-1]->d))>=0){
					while(pos>=1 && strcmp((currentP2->d),(verificador[pos-1]->d))>=0)
						pos--;
				}
				for(i=soma_tags-1;i>pos;i--){
				verificador[i]=verificador[i-1];
				}
				verificador[pos] = currentP2;
				}	
			}
		}
	idTags=create_list(soma_tags);

	for(i=0;i<soma_tags;i++){
		set_list(idTags,i,(verificador[i]->id_post));
	}

	return idTags;

}

/** \brief Interrogaçao 5. Funcao que, dado o ID de um utilizador devolve a informaçao do seu perfil.
@param com Estrutura inicializada
@param id ID do respetivo utilizador
@return Informaçao do utilizador, nomeadamente short bio e os IDs dos seus 10 últimos posts (perguntas ou respostas), ordenados por cronologia inversa
*/
USER get_user_info(TAD_community com, long id){
	char* short_bio;
	long ultimos10[20];
	char* datas[20];

	int pos,i,j;

	USER userinfo;
	
 	struct h_IDUtilizador *lugar_utilizador = (struct h_IDUtilizador*) g_hash_table_lookup(com->h_IDUtilizador, &id);
	short_bio = (lugar_utilizador->shortb);

	void *iterator1 = getHashIterator(com->h_IDPerguntas);
	void *iterator2 = getHashIterator(com->h_IDRespostas);


	struct h_IDPerguntas *verificador1[9];
	struct h_IDRespostas *verificador2[9];

	struct h_IDPerguntas tmp1 = {(long) 0, (long) 0,"","",(long) 0,(long) 0, ""};
	struct h_IDRespostas tmp2 = {(long) 0, (long) 0,(long) 0,(long) 0,(long) 0, ""};

	for(i=0;i<10;i++){
		verificador1[i]=&tmp1;
	}

	for(i=0;i<10;i++){
		verificador2[i]=&tmp2;
	}



	struct h_IDPerguntas *currentP = malloc(sizeof(struct h_IDPerguntas));
	struct h_IDRespostas *currentR = malloc(sizeof(struct h_IDRespostas));

	void *key=NULL;

	while(getNextIterator(iterator1,&key,&currentP)){
		pos = 9;
		if(currentP->id_autor==id){
			if(strcmp((currentP->d),(verificador1[9]->d))>=0){
				while((pos>=1)&&(strcmp((currentP->d),(verificador1[pos-1]->d))>=0)){
					pos--;
				}
				for(i=9;i>pos;i--){
					verificador1[i]=verificador1[i-1];
				}
				verificador1[pos] = currentP;
			}
		}
	}
	while(getNextIterator(iterator2,&key,&currentR)){
		pos = 9;
		if(currentR->id_autor==id){
			if(strcmp((currentR->d),(verificador2[9]->d))>=0){
				while((pos>=1)&&(strcmp((currentR->d),(verificador2[pos-1]->d))>=0)){
					pos--;
				}
				for(i=9;i>pos;i--){
					verificador2[i]=verificador2[i-1];
				}
				verificador2[pos] = currentR;
			}
		}
	}

	for(i=0;i<10;i++){
		ultimos10[i]=verificador1[i]->id_post;
	}

	for(i=10,j=0;i<20;i++,j++){
		ultimos10[i]=verificador2[j]->id_post;

	}

	for (i=0;i<10;i++){
		datas[i]=verificador1[i]->d;

	}
	for (i=10,j=0;i<20;i++,j++){
		datas[i]=verificador2[j]->d;
	}
	ordena_array(datas,ultimos10,20);

	userinfo=create_user(short_bio,ultimos10);
	
	return userinfo;
}

/** \brief Interrogaçao 6. Devolve os IDs das N respostas com mais votos.
@param com Estrutura inicializada
@param N Número de respostas a apresentar
@param begin Data inicial do intervalo de tempo
@param end Data final do intervalo de tempo
@return IDs das N resposta com mais votos por ordem decrescente, (número de votos é obtido pela diferenca entre Up Votes e Down Votes, equivalente ao score)
*/
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){

	int i, fixo = (N-1),pos;

	LONG_list mais_votos;

	mais_votos = create_list(N);

	GDateTime* data_begin = g_date_time_new_local(get_year(begin),get_month(begin),get_day(begin),0,0,0.0);
	GDateTime* data_end = g_date_time_new_local(get_year(end),get_month(end),get_day(end),0,0,0.0);

	char* data_begin_string = g_date_time_format(data_begin,"%F");
	char* data_end_string = g_date_time_format(data_end,"%F");

	void *iterator2 = getHashIterator(com->h_IDRespostas);

	struct h_IDRespostas *verificador[N];

	struct h_IDRespostas tmp = {(long) 0, (long) 0, (long) 0, (long) 0, (long) 0, ""}; 
 	
 	for(i=0;i<N;i++){
		verificador[i]=&tmp;
	}

	struct h_IDRespostas *currentR = malloc(sizeof(struct h_IDRespostas));

	void *key = NULL;

	while (getNextIterator(iterator2,&key,&currentR)){
		pos=N-1;
		if(((strcmp((currentR->d),data_begin_string))>=0) && ((strcmp((currentR->d),data_end_string))<=0)){
			if((currentR->score)>(verificador[fixo]->score)){
				while((pos>=1)&&(currentR->score>(verificador[pos-1]->score))){
				pos--;
				}
			for(i=N-1;i>pos;i--){
				verificador[i]=verificador[i-1];
			}
			verificador[pos] = currentR;
			}
		}
	}
	for(i=0;i<N;i++){
		set_list(mais_votos,i,(verificador[i]->id_post));
	}
	
	return mais_votos;
}


/** \brief Interrogaçao 7. Dado um intervalo de tempo, devolve os IDs das N perguntas com mais respostas.
@param com Estrutura inicializada
@param N número de respostas a apresentar
@param begin Data inicial do intervalo de tempo
@param end Data final do intervalo de tempo
@return N perguntas com mais respostas (em ordem decrescente)
*/
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){

	LONG_list top_N_Perg;

	top_N_Perg = create_list(N);
	int i;
	void *iterator = getHashIterator(com->h_IDPerguntas);
	void *key=NULL;
	int fixo=N-1;
	int pos;

	GDateTime* data_begin = g_date_time_new_local(get_year(begin),get_month(begin),get_day(begin),0,0,0.0);
	GDateTime* data_end = g_date_time_new_local(get_year(end),get_month(end),get_day(end),0,0,0.0);

	char* data_begin_string = g_date_time_format(data_begin,"%F");
	char* data_end_string = g_date_time_format(data_end,"%F");

	struct h_IDPerguntas *currentP = malloc(sizeof(struct h_IDPerguntas));

	struct h_IDPerguntas *verificador[N];

	struct h_IDPerguntas tmp = {(long) 0, (long) 0, "" , "", (long) 0, (long) 0,""}; 

	for(i=0;i<N;i++){
		verificador[i]=&tmp;
	}
	while (getNextIterator(iterator,&key,&currentP)){
		if(((strcmp((currentP->d),data_begin_string))>=0) && ((strcmp((currentP->d),data_end_string))<=0)){
			pos = (N-1);
			if((currentP->n_resp)>(verificador[fixo]->n_resp)){
				while((pos>=1)&&((currentP->n_resp)>(verificador[pos-1]->n_resp))){
				pos--;
			}
			for(i=N-1;i>pos;i--){
				verificador[i]=verificador[i-1];
			}
			verificador[pos] = currentP;
		}
	}
	}


	for(i=0;i<N;i++){
		set_list(top_N_Perg,i,(verificador[i]->id_post));
	}

	return top_N_Perg;

}

/** \brief Interrogaçao 8. Dado uma palavra, devolve uma lista com os IDs de N perguntas cujos tıtulos a contenham.
@param com Estrutura inicilizada
@param word Palavra a procurar
@param N número de elementos da lista a apresentar dos IDs
@return Lista com os IDs das N perguntas que contém a palavra (ordenados por cronologia inversa)
*/
LONG_list contains_word(TAD_community com, char* word, int N){
	
	int i, fixo = (N-1),pos;

	LONG_list container;

	container = create_list(N);

	struct h_IDPerguntas *verificador[N];

	struct h_IDPerguntas tmp = {(long) 0, (long) 0,"","",(long) 0,(long) 0, ""}; 

	for(i=0;i<N;i++){
		verificador[i]=&tmp;
	}

	void *iterator1 = getHashIterator(com->h_IDPerguntas);

	void *key=NULL;
	
	struct h_IDPerguntas *currentP = malloc(sizeof(struct h_IDPerguntas));

	while(getNextIterator(iterator1,&key,&currentP)){
		pos=N-1;
		if(mystrstr(currentP->title,word)==1){
			if(strcmp((currentP->d),(verificador[fixo]->d))>=0){
				while(pos>=1 && strcmp((currentP->d),(verificador[pos-1]->d))>=0)
					pos--;
			for(i=N-1;i>pos;i--){
				verificador[i]=verificador[i-1];
			}
			verificador[pos] = currentP;
			}
		}

		}

	for(i=0;i<N;i++){
		set_list(container,i,(verificador[i]->id_post));
	}

	return container;
}

/** \brief Interrogaçao 9. Dados os IDs de dois utilizadores, devolve as últimas N perguntas em que ambos participaram (via pergunta ou respostas).
@param com Estrutura inicializada
@param id1 ID do primeiro utilizador
@param id2 ID do segundo utilizador
@return Lista com as últimas N perguntas em que ambos participaram (cronologia inversa)
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N){

	void *iterator2 = getHashIterator(com->h_IDRespostas);

	LONG_list ultimasN;

	int i, j, fixo = N-1, pos, contador=0;

	GDateTime* data = g_date_time_new_local(1000,1,1,0,0,0.0);

	char* string_Data = g_date_time_format(data,"%F");

	ultimasN = create_list(N);

	struct h_IDPerguntas *verificador[N];

	struct h_IDPerguntas tmp = {(long) 0, (long) 0,"","",(long) 0,(long) 0, string_Data}; 

 	for(i=0;i<N;i++){
		verificador[i]=&tmp;
	}

	void *key=NULL;
	
	struct h_IDPerguntas *currentP;
	struct h_IDRespostas *currentR = malloc(sizeof(struct h_IDRespostas));

	while(getNextIterator(iterator2,&key,&currentR)){
		pos=(N-1);
		if(currentR->id_autor==id1){
			currentP =(struct h_IDPerguntas*) g_hash_table_lookup(com->h_IDPerguntas,&(currentR->id_perg));
			if(currentP!=NULL){
			if(currentP->id_autor==id2){
				if(strcmp((currentP->d),(verificador[fixo]->d))>=0){
					while(pos>=1 && strcmp((currentP->d),(verificador[pos-1]->d))>=0)
						pos--;
				}
			}
		  	if(encontrado(com,id2,currentR->id_perg)==1){
		  		if(strcmp((currentP->d),(verificador[fixo]->d))>=0){
					while(pos>=1 && strcmp((currentP->d),(verificador[pos-1]->d))>=0){
						pos--;
				}}
			}
			for(i=N-1;i>pos;i--){
				verificador[i]=verificador[i-1];
			}
			verificador[pos] = currentP;
			}
		}
		if(currentR->id_autor==id2){
			currentP =(struct h_IDPerguntas*) g_hash_table_lookup(com->h_IDPerguntas,&(currentR->id_perg));
			if(currentP!=NULL) {
			if(currentP->id_autor==id1){
				if(strcmp((currentP->d),(verificador[fixo]->d))>=0){
					while(pos>=1 && strcmp((currentP->d),(verificador[pos-1]->d))>=0)
						pos--;
				}
			}
			if(encontrado(com,id1,currentR->id_perg)==1){
		  		if(strcmp((currentP->d),(verificador[fixo]->d))>=0){
					while(pos>=1 && strcmp((currentP->d),(verificador[pos-1]->d))>=0)
						pos--;
				}
			}
			for(i=N-1;i>pos;i--){
				verificador[i]=verificador[i-1];
			}
			verificador[pos] = currentP;
			}
		}
	}
	for(i=0;verificador[i]->id_post!=0;i++){
		set_list(ultimasN,i,(verificador[i]->id_post));
		contador++;
	}
	for(i=contador;i<N;i++){
		set_list(ultimasN,i,-2);
	}

	for(i=0;i<N;i++){
		for(j=i+1;j<N;j++){
			if(get_list(ultimasN,i)==get_list(ultimasN,j)) set_list(ultimasN,j,-2);
		}
	}
	return ultimasN;
}

/** \brief Interrogaçao 10. Dado o ID de uma pergunta, obter a melhor resposta, segundo a funçao (Scr × 0.45) + (Rep × 0.25) + (Vot × 0.2) + ( Comt × 0.1).
@param com Estrutura inicializada
@param id1 ID da pergunta
@return A melhor resposta
*/
long better_answer(TAD_community com, long id){

	long best=-1;
	long try;
	long id_melhor;
	long reput; 
	long scr;
	long come; 
	
	void *iterator2 = getHashIterator(com->h_IDRespostas);

	void *key = NULL;

	struct h_IDRespostas *currentR = malloc(sizeof(struct h_IDRespostas));
	struct h_IDUtilizador *currentU;
	
	while(getNextIterator(iterator2, &key,&currentR)) {
		if ((currentR->id_perg) == id ){

			scr = currentR->score;
			come = currentR->n_coments;
			
			currentU = (struct h_IDUtilizador*) g_hash_table_lookup(com->h_IDUtilizador,&(currentR->id_autor));
			
			reput = currentU->reputacao;
			
			try = (0.65 * scr) + (0.25 * reput) + (0.1 * come);

			if (try>=best){
				id_melhor = currentR->id_post;
				best=try;
			}


		}

	}	return id_melhor;
}

/** \brief Interrogaçao 11. Dado um intervalo arbitr ́ario de tempo, devolver os identificadores das N tags mais usadas pelos N utilizadores com melhor reputacao. 
Em ordem decrescente do n ́umero de vezes em que atag foi usada.
@param com Estrutura inicializada
@param N número de respostas a apresentar
@param begin Data inicial do intervalo de tempo
@param end Data final do intervalo de tempo
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	int i, fixo = (N-1),pos;
	int contador=0;

	LONG_list user_best_rep=create_list(N);

	void *iterator = getHashIterator(com->h_IDUtilizador);
	void *iterator2 = getHashIterator(com->h_IDPerguntas);
	void *iterator4 = getHashIterator(com->h_IDTags);

	GDateTime* data_begin = g_date_time_new_local(get_year(begin),get_month(begin),get_day(begin),0,0,0.0);
	GDateTime* data_end = g_date_time_new_local(get_year(end),get_month(end),get_day(end),0,0,0.0);

	char* data_begin_string = g_date_time_format(data_begin,"%F");
	char* data_end_string = g_date_time_format(data_end,"%F");

	struct h_IDUtilizador *currentU = malloc(sizeof(struct h_IDUtilizador));
	struct h_IDUtilizador *verificador1[N];
	struct h_IDTags *verificador2[N];

	struct h_IDUtilizador tmp = {(long) 0, "", "", 0, (long) 0, (long) 0};
	struct h_IDTags tmp2 = {(long) 0, "", (long) 0};

	for(i=0;i<N;i++){
		verificador1[i]=&tmp;
	}

	for(i=0;i<N;i++){
		verificador2[i]=&tmp2;
	}

	void *key=NULL;

	while(getNextIterator(iterator,&key,&currentU)){
		pos = (N-1);
		if(currentU->reputacao>(verificador1[fixo]->reputacao)){
			while((pos>=1)&&(currentU->reputacao>(verificador1[pos-1]->reputacao))){
				pos--;
			}
			for(i=N-1;i>pos;i--){
				verificador1[i]=verificador1[i-1];
			}
			verificador1[pos] = currentU;
		}
	}

	struct h_IDPerguntas *currentP= malloc(sizeof(struct h_IDPerguntas));
	key=NULL;
	while(getNextIterator(iterator2,&key,&currentP)){
		for(contador=0;contador<N;contador++){
			if(verificador1[contador]->id_u == currentP->id_autor){
				if(((strcmp((currentP->d),data_begin_string))>=0) && ((strcmp((currentP->d),data_end_string))<=0)){
					aumenta_tags(com,currentP->tags);
					}
				}
			}
		}

	struct h_IDTags *currentT1 = malloc(sizeof(struct h_IDTags));
	void *key2=NULL;

	while(getNextIterator(iterator4,&key2,&currentT1)){
		pos = (N-1);
		if(currentT1->count>(verificador2[fixo]->count)){
			while((pos>=1)&&(currentT1->count>(verificador2[pos-1]->count))){
				pos--;
			}
			for(i=N-1;i>pos;i--){
				verificador2[i]=verificador2[i-1];
			}
			verificador2[pos] = currentT1;
			}
	}

	for(i=0;i<N;i++){
		set_list(user_best_rep,i,(verificador2[i]->id_tag));
	}

	return user_best_rep;
}


TAD_community clean(TAD_community com){
	clear(com);
	return com;
}
