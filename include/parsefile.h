#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "hashTables.h"


long turn_long (xmlChar *key);
int turn_int (xmlChar *key);

void printUserHT(gpointer key, gpointer value, gpointer user_data);
TAD_community get_PerguntasHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t);
TAD_community get_UsersHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t);
TAD_community get_RespostasHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t);
TAD_community get_TagsHashInfo(xmlNodePtr curp, xmlDocPtr doc,TAD_community t);
//TAD_istruct get_Votes(xmlNodePtr curp, xmlDocPtr doc,TAD_istruct t);
TAD_community loadHashUsers(TAD_community t,const char *filename);
TAD_community loadHashPerguntas(TAD_community t,const char *filename);
TAD_community loadHashRespostas(TAD_community t,const char *filename);
TAD_community loadHashTags(TAD_community t,const char *filename);