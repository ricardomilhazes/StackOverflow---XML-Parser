#include <glib.h>
#include <stdio.h>
#include "interface.h"
#include "hashTables.h"
/** \brief Inicializa as Hash tables e executa todas as querys
 @param argc
 @param argv[]
 @return 0 se correr tudo bem
 */

int main(int argc, char *argv[]){
  
  TAD_community t = init();

  char *files="mellonz";

  load(t,files);

  //Query 1
  STR_pair query1 = info_from_post (t, 796430);

  char* prim;
  char* seg;

  prim = get_fst_str(query1);
  seg = get_snd_str(query1);

  printf("Query 1 -> \n");

  printf("%s , %s \n",prim,seg);

  printf("\n");

  //Query 2

  LONG_list topN = top_most_active(t,11);

  printf("Query 2 -> TOPN mais ativos\n");

  int i;
  for (i = 0; i < 10; i++) {
    printf("%ld;",get_list(topN,i));
  }

  printf("\n");
  printf("\n");
  //Query 3
   
   Date d1 = createDate(1,1,2014);
   Date d2 = createDate(31,12,2014);


   LONG_pair query3 =total_posts(t,d1 ,d2 );

   printf("Query 3 -> Numero de perguntas e respostas totais num certo intervalo de tempo\n");


   printf("%ld , %ld \n", get_fst_long (query3), get_snd_long (query3));

   printf("\n");

  //Query 4

  d1 = createDate(1,1,2014);
  d2 = createDate(31,1,2014);

  LONG_list idTags = questions_with_tag(t,"nautilus",d1,d2);

  printf("Query 4 -> Tag contida numa pergunta num certo intervalo de tempo\n");

  for (i = 0; i < 27; i++) {
      printf("%ld;",get_list(idTags,i));
  }

  printf("\n");
  printf("\n");

  printf("Query 5 -> User Info\n");

  USER info_utilizador = get_user_info(t, 15811);

  printf("%s\n", get_bio(info_utilizador));

  long* ultimos = get_10_latest_posts(info_utilizador);

  for (i = 0; i < 10; i++) {
      printf("%ld;",ultimos[i]);
  }

  printf("\n");
  printf("\n");


  //Query 6

  d1 = createDate(1,5,2013);
  d2 = createDate(6,5,2013);

  LONG_list mais_votos = most_voted_answers (t, 50, d1, d2);

  printf("Query 6 -> Melhores respostas com mais votos.\n");

  for (i = 0; i < 50; i++) {
    printf("%ld;",get_list(mais_votos,i));
  }

  printf("\n");
  printf("\n");

  //Query 7

  printf("Query 7 -> Mais respostas\n");
  
  d1 = createDate(1,1,2012);
  d2 = createDate(31,12,2012);

  LONG_list mais_resp = most_answered_questions(t, 100, d1,d2);
  for (i = 0; i < 100; i++) {
    printf("%ld;", get_list(mais_resp,i));
  }

  printf("\n");
  printf("\n");

  //Query 8

  printf("Query 8 -> Perguntas que contêm palavra no título\n");

  LONG_list container = contains_word(t,"glib",10);

  for (i = 0; i < 10; i++) {
      printf("%ld;",get_list(container,i));
  }

  printf("\n");
  printf("\n");

  //Query 9

  printf("Query 9 -> Ambos participaram\n");

  LONG_list ultimosN = both_participated(t,87,5691,10);

  for (i = 0; i < 10; i++) {
    printf("%ld;", get_list(ultimosN,i));
  }

  printf("\n");
  printf("\n");

  //Query 10

  printf("Query 10 -> Dado o id de uma pergunta, obter a melhor resposta\n");

  long id_melhor = better_answer(t, 30334);

  printf("%ld \n", id_melhor);

  printf("\n");
 //Query 11
  printf("Query 11 -> N Tags mais utilizadas pelos N utilizadores com melhor reputação\n");

  d1 = createDate(1,11,2013);
  d2 = createDate(30,11,2013);

  LONG_list user_best_rep = most_used_best_rep(t,5,d1,d2);

  for (i = 0; i < 5; i++) {
    printf("%ld;", get_list(user_best_rep,i));
  }
  
  return 0;
} 
