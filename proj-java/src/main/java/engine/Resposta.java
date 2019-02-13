package engine;


/**
 * Classe que representa um post do tipo resposta .
 * 
 * @Diogo Rocha, Gabriela Martins, Ricardo Frreira, Ricardo Veloso 
 * @12/06/2018
 */
public class Resposta
{
    //variaveis de instância
    private long id_post;
    private long id_perg;
    private long id_autor;
    private long score;
    private long n_coments;
    private String d;
    
    /**
    * Construtor por omissão de Resposta.
    */
    public Resposta(){
        this.id_post=0;
        this.id_perg=0;
        this.id_autor=0;
        this.score=0;
        this.n_coments=0;
        this.d="";
    }

    /**
    * Construtor parametrizado de Resposta.
    * Recebe como parâmetros o ID da Resposta (post),o ID da pergunta à qual a Resposta corresponde, o ID do autor da Resposta,
    * o score da Resposta, o número de comentários à Resposta e a data da Resposta.
    */
    public Resposta(long id_post,long id_perg,long id_autor,long score,long n_coments , String d ){
        this.id_post=id_post;
        this.id_perg=id_perg;
        this.id_autor=id_autor;
        this.score=score;
        this.n_coments=n_coments;
        this.d=d;
    }
    
    /**
    * Devolve o ID da Resposta em id_post.
    * @return valor do ID da Resposta.
    */
    public long getId_post() {
        return id_post;
    }
    
    /**
    * Atualiza o ID da Resposta (post) em id_post.
    * @param id_post Novo ID da Resposta.
    */
    public void setId_post(long id_post) {
        this.id_post = id_post;
    }
    
    /**
    * Devolve o ID da pergunta à qual a Resposta corresponde em id_perg.
    * @return valor do ID da pergunta correspondente.
    */
    public long getId_perg() {
        return id_perg;
    }
    
    /**
    * Atualiza o ID da pergunta à qual a Resposta corresponde em id_perg.
    * @param id_perg Novo ID da pergunta correspondente.
    */
    public void setId_perg(long id_perg) {
        this.id_perg = id_perg;
    }
    
    /**
    * Devolve o ID do autor da Resposta em id_autor.
    * @return valor do ID do autor da Resposta.
    */
    public long getId_autor() {
        return id_autor;
    }
    
    /**
    * Atualiza o ID do autor da Resposta em id_autor.
    * @param id_autor Novo ID do autor da Resposta.
    */
    public void setId_autor(long id_autor) {
        this.id_autor = id_autor;
    }
    
    /**
    * Devolve o score da Resposta em score.
    * @return valor do score da Resposta.
    */
    public long getScore() {
        return score;
    }
    
    /**
    * Atualiza o score da Resposta em score.
    * @param score Novo score da Resposta.
    */
    public void setScore(long score) {
        this.score = score;
    }
    
    /**
    * Devolve o número de comentários à Resposta em n_coments.
    * @return valor do número de comentários à Resposta.
    */
    public long getN_coments() {
        return n_coments;
    }
    
    /**
    * Atualiza o número de comentários à Resposta em n_coments.
    * @param n_coments Novo número de comentários à Resposta.
    */
    public void setN_coments(long n_coments) {
        this.n_coments = n_coments;
    }
    
    /**
    * Devolve a data da Resposta em d.
    * @return data da Resposta.
    */
    public String getD() {
        return d;
    }
    
    /**
    * Atualiza a data da Resposta em d.
    * @param d Nova data da Resposta.
    */
    public void setD(String d) {
        this.d = d;
    }
    
}

