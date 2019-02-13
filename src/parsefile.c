#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parsefile.h"


/** \brief Recebe xmlChar e tranforma num char
 @param key xmlChar
 @return string Char
 */
char* get_string (xmlChar* key) {
    
    char *string='\0';

    string=mystrdup((const char *) key);
    
    xmlFree(key);
    return string;
}
/** \brief Recebe xmlChar e tranforma numa string do formato de uma data
 @param key xmlChar
 @return string Char
 */
char* get_string_data (xmlChar* key){
    int i;
    char *string='\0';

    for(i=0;key[i]!='T';i++);
    key[i]='\0';

    string=mystrdup((const char *) key);

    xmlFree(key);
    return string;
}
/** \brief Recebe xmlChar e tranforma num long 
 @param key xmlChar
 @return n long
 */
long turn_long (xmlChar *key){
	long n;
	n=(long) atoi ((const char*)key);
	return n;
}
/** \brief Recebe xmlChar e tranforma num int
 @param key xmlChar
 @return n int
 */
int turn_int (xmlChar *key){
	int n;
	n=(int) atoi((const char*)key);
	return n;
}

/** \brief Procura elementos no nodo/documento e adiciona á hashtable das perguntas/respostas
 @param curp xmlNodePtr nodo de um documento 
 @param doc xmlDocPtr documento 
 @param t Estrutura TAD_community
 @return Estrutura TAD_community
 */
TAD_community get_PerguntasouRespostasHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t) {
    TAD_community tmp = t ;
    
    xmlNodePtr cur = curp;

    long post_id = 0, author_id = 0, total_score= 0;

    long postTypeId=0, parent_id=0;

    char *tags= (char *) calloc (1001,sizeof (char));
    tags[1000] = '\0';

    char *title = (char *) calloc (1001,sizeof (char));
    title[1000] = '\0';

    long coment = 0; 
    long respo = 0;

    char *data= (char *) calloc (50,sizeof (char));
    data[49] = '\0';

    cur = cur -> xmlChildrenNode;
    
   while (cur != NULL) {
       if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {//acho que nao é necessario;
            postTypeId= turn_long(xmlGetProp(cur,(const xmlChar *)"PostTypeId"));
            post_id = turn_long(xmlGetProp(cur,(const xmlChar *)"Id"));
            if((xmlGetProp(cur,(const xmlChar *)"Title"))!=NULL) title = get_string(xmlGetProp(cur,(const xmlChar *)"Title"));
            if((xmlGetProp(cur,(const xmlChar *)"ParentId"))!=NULL) parent_id = turn_long(xmlGetProp(cur,(const xmlChar *)"ParentId"));
            if((xmlGetProp(cur,(const xmlChar *)"OwnerUserId"))!=NULL) author_id= turn_long(xmlGetProp(cur,(const xmlChar *)"OwnerUserId"));
            if((xmlGetProp(cur,(const xmlChar *)"AnswerCount"))!=NULL) respo = turn_long(xmlGetProp(cur,(const xmlChar *)"AnswerCount"));
            if((xmlGetProp(cur,(const xmlChar *)"CommentCount"))!=NULL) coment = turn_long(xmlGetProp(cur,(const xmlChar *)"CommentCount"));
            total_score = turn_long(xmlGetProp(cur,(const xmlChar *)"Score"));
            if((xmlGetProp(cur,(const xmlChar *)"Tags"))!=NULL) tags = get_string(xmlGetProp(cur,(const xmlChar *)"Tags"));
            data = get_string_data(xmlGetProp(cur,(const xmlChar *)"CreationDate"));
    }
        if(postTypeId==1){ tmp=add_Perguntas(tmp,post_id,title,author_id,tags,total_score,respo,data);
                        }
        if(postTypeId==2){ tmp=add_Respostas(tmp,post_id,parent_id,author_id,total_score,coment,data);
            }
        cur = cur->next;
    }
    free(tags);
    free(title);
    free(data);
	t = tmp;
    return t;
}    

    

/** \brief Procura elementos no nodo/documento e adiciona á hashtable dos Users
 @param curp xmlNodePtr nodo de um documento 
 @param doc xmlDocPtr documento 
 @param t Estrutura TAD_community
 @return Estrutura TAD_community
 */
TAD_community get_UsersHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t){
        TAD_community tmp = t ;
    	xmlNodePtr cur = curp;
    
    long user_id=0, rep=0;
    int upvotes=0,downvotes=0,total_votes=0;
    
    
    char *author_name=(char *) calloc (100,sizeof (char));
    author_name [99]= '\0';
    
    
    char *short_bio= (char *) calloc (200,sizeof (char));
    short_bio [199] ='\0';
    
    cur = cur -> xmlChildrenNode;
    while(cur != NULL){
    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
            user_id=turn_long(xmlGetProp(cur,(const xmlChar *)"Id"));
            author_name = get_string(xmlGetProp(cur,(const xmlChar *)"DisplayName"));
            short_bio = get_string(xmlGetProp(cur,(const xmlChar *)"AboutMe"));
            rep = turn_long(xmlGetProp(cur,(const xmlChar *)"Reputation"));
            upvotes = turn_int(xmlGetProp(cur,(const xmlChar *)"UpVotes"));
            downvotes = turn_int(xmlGetProp(cur,(const xmlChar *)"DownVotes"));
            total_votes = upvotes + downvotes;
    		}
            tmp = add_Utilizador(tmp, user_id, author_name,short_bio, rep, total_votes);
            cur=cur->next;
    	}
        free(author_name);
        free(short_bio);    
        t = tmp;
    return t;
}
/** \brief Procura elementos no nodo/documento e adiciona á hashtable das Tags
 @param curp xmlNodePtr nodo de um documento 
 @param doc xmlDocPtr documento 
 @param t Estrutura TAD_community
 @return Estrutura TAD_community
 */
TAD_community get_TagsHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t){
    TAD_community tmp =t;
    xmlNodePtr cur = curp;

    int contador=0;

    long id=0;

    char *tags= (char *) calloc (1001,sizeof (char));
    tags[1000] = '\0';

    cur = cur->xmlChildrenNode;
     while(cur != NULL){
        contador++;
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
            id=turn_long(xmlGetProp(cur,(const xmlChar *)"Id"));
            tags=get_string(xmlGetProp(cur,(const xmlChar *)"TagName"));
        }
        tmp = add_Tags(tmp,id,tags);
        cur=cur->next;
    }
    printf("%d\n", contador);
    free(tags);
    t=tmp;
    return t;
}


/** \brief Lê o documento Users.xml e adiciona á estrutura
 @param t Estrutura TAD_community
 @param char filename nome do documento 
 @return Estrutura TAD_community
 */
TAD_community loadHashUsers(TAD_community t,const char *filename){
    xmlDocPtr doc1;
    xmlNodePtr cur1;

    doc1 = xmlReadFile(filename,NULL,0);
    if (doc1 == NULL) {

        fprintf(stderr, "Failed to parse %s\n", filename);
        return NULL;

    }

    cur1 = xmlDocGetRootElement(doc1);

    if (cur1 == NULL) {

        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc1);
        return NULL;

	}

    t=get_UsersHashInfo(cur1,doc1,t);

    xmlFreeDoc(doc1);
    return t;
}
/** \brief Lê o documento Posts.xml e adiciona á estrutura
 @param t Estrutura TAD_community
 @param char filename nome do documento 
 @return Estrutura TAD_community
 */
TAD_community loadHashPerguntas(TAD_community t,const char *filename){
    xmlDocPtr doc1;
    xmlNodePtr cur1;

    doc1 = xmlReadFile(filename,NULL,0);
    if (doc1 == NULL) {

        fprintf(stderr, "Failed to parse %s\n", filename);
        return NULL;

    }

    cur1 = xmlDocGetRootElement(doc1);

    if (cur1 == NULL) {

        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc1);
        return NULL;

    }

    t=get_PerguntasouRespostasHashInfo(cur1,doc1,t);

    xmlFreeDoc(doc1);
    return t;
}

/** \brief Lê o documento Tags.xml e adiciona á estrutura
 @param t Estrutura TAD_community
 @param char filename nome do documento 
 @return Estrutura TAD_community
 */
TAD_community loadHashTags(TAD_community t,const char *filename){
    xmlDocPtr doc1;
    xmlNodePtr cur1;

    doc1 = xmlReadFile(filename,NULL,0);
    if (doc1 == NULL) {

        fprintf(stderr, "Failed to parse %s\n", filename);
        return NULL;

    }

    cur1 = xmlDocGetRootElement(doc1);

    if (cur1 == NULL) {

        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc1);
        return NULL;

    }

    t=get_TagsHashInfo(cur1,doc1,t);

    xmlFreeDoc(doc1);
    return t;
}
