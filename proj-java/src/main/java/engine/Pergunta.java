package engine;


/**
 * Classe que representa um post do tipo pergunta.
 * 
 * @Diogo Rocha, Gabriela Martins, Ricardo Frreira, Ricardo Veloso 
 * @12/06/2018
 */
public class Pergunta
{
    //variaveis de instância
    private long id_post;
    private long id_autor;
    private String title;
    private String tags;
    private long score;
    private long n_resp;
    private String d;
    
   /**
    * Construtor por omissão de Pergunta.
    */
   public Pergunta(){
        this.id_post=0;
        this.id_autor=0;
        this.title="";
        this.tags="";
        this.score=0;
        this.n_resp=0;
        this.d="";
   }

   /**
    * Construtor parametrizado de Pergunta.
    * Recebe como parâmetros o ID da Pergunta (post), o ID do autor da Pergunta, o título da Pergunta, as tags utilizadas na Pergunta,
    * o score da Pergunta, o número de repostas à Pergunta e a data da Pergunta.
    */
   public Pergunta(long id_post,long id_autor, String title, String tags, long score,long n_resp,String d ){
        this.id_post=id_post;
        this.id_autor=id_autor;
        this.title=title;
        this.tags=tags;
        this.score=score;
        this.n_resp=n_resp;
        this.d=d;
   }
    
    /**
    * Devolve o ID da Pergunta em id_post.
    * @return valor do ID da Pergunta.
    */
   public long getId_post() {
       return id_post;
   }
   
   /**
    * Atualiza o ID da Pergunta em id_post.
    * @param id_post Novo ID da Pergunta.
    */
   public void setId_post(long id_post) {
       this.id_post = id_post;
    }

    /**
    * Devolve o ID do autor da Pergunta em id_autor.
    * @return valor do ID do autor da Pergunta.
    */
   public long getId_autor() {
        return id_autor;
   }

   /**
    * Atualiza o ID do autor da Pergunta em id_autor.
    * @param id_autor Novo ID do autor da Pergunta.
    */
   public void setId_autor(long id_autor) {
       this.id_autor = id_autor;
    }

    /**
    * Devolve o título da Pergunta em title.
    * @return título da Pergunta.
    */
   public String getTitle() {
       return title;
   }

   /**
    * Atualiza o título da Pergunta em title.
    * @param title Novo título da Pergunta.
    */
   public void setTitle(String title) {
       this.title = title;
    }

    /**
    * Devolve as tags utilizadas na Pergunta em tags.
    * @return tags utilizadas na Pergunta.
    */
   public String getTags() {
       return tags;
   }

   /**
    * Atualiza as tags utilizadas na Pergunta em tags.
    * @param tags Novas tags utilizadas.
    */
   public void setTags(String tags) {
       this.tags = tags;
   }

   /**
    * Devolve o score da Pergunta em score.
    * @return score da Pergunta.
    */
   public long getScore() {
       return score;
   }

   /**
    * Atualiza o score da Pergunta em score.
    * @param score Novo score da Pergunta.
    */
   public void setScore(long score) {
       this.score = score;
    }

   /**
    * Devolve o número de respostas à Pergunta em n_resp.
    * @return número de respostas à Pergunta.
    */
   public long getN_resp() {
       return n_resp;
   }

   /**
    * Atualiza o número de respostas à Pergunta em n_resp.
    * @param n_resp Novo número de respostas à Pergunta.
    */
   public void setN_resp(long n_resp) {
       this.n_resp = n_resp;
   }

   /**
    * Devolve a data da Pergunta em d.
    * @return data da Pergunta.
    */
   public String getD() {
       return d;
   }

   /**
    * Atualiza a data da Pergunta em d.
    * @param d Nova data da Pergunta.
    */
   public void setD(String d) {
       this.d = d;
    }
 
}
