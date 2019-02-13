package engine;


/**
 * Classe que representa um utilizador.
 * 
 * @Diogo Rocha, Gabriela Martins, Ricardo Frreira, Ricardo Veloso 
 * @12/06/2018
 */
public class Utilizador
{
    //variaveis de instância
    private long id_u;
    private String name;
    private String shortb;
    private int totalposts;
    private long reputacao;
    private int votes;

    /**
    * Construtor por omissão de Utilizador.
    */
    public Utilizador(){
        this.id_u=0;
        this.name="";
        this.shortb="";
        this.totalposts=0;
        this.reputacao=0;
        this.votes=0;
    }
    
    /**
    * Construtor parametrizado de Utilizador.
    * Recebe como parâmetros o ID do Utilizador, o nome, a shortbio, o numero total de posts, a reputação e os votos.
    */
    public Utilizador(long id_u,String name,String shortb,int totalposts,long reputacao,int votes){
        this.id_u=id_u;
        this.name=name;
        this.shortb=shortb;
        this.totalposts=totalposts;
        this.reputacao=reputacao;
        this.votes=votes;
    }
    
    /**
    * Devolve o ID do Utilizador em id_u.
    * @return valor do ID do Utilizador.
    */
    public long getId_u() {
        return id_u;
    }
    
    /**
    * Atualiza o ID do Utilizador em id_u.
    * @param id_u Novo ID do Utilizador.
    */
    public void setId_u(long id_u) {
        this.id_u = id_u;
    }
    
    /**
    * Devolve o nome do Utilizador em name.
    * @return nome do Utilizador.
    */
    public String getName() {
        return name;
    }

    /**
    * Atualiza o nome do Utilizador em name.
    * @param name Novo nome do Utilizador.
    */
    public void setName(String name) {
        this.name = name;
    }
    
    /**
    * Devolve a shortbio do Utilizador em shortb.
    * @return shortbio do Utilizador.
    */
    public String getShortb() {
        return shortb;
    }

    /**
    * Atualiza a shortbio do Utilizador em shortb.
    * @param shotb Nova shortbio do Utilizador.
    */
    public void setShortb(String shortb) {
        this.shortb = shortb;
    }
    
    /**
    * Devolve o número total de posts do Utilizador em totalposts.
    * @return número total de posts.
    */
    public int getTotalposts() {
        return totalposts;
    }

    /**
    * Atualiza o número total de posts em totalposts.
    * @param totalposts Novo número de posts do Utilizador.
    */
    public void setTotalposts(int totalposts) {
        this.totalposts = totalposts;
    }
    
    /**
    * Devolve a reputação do Utilizador em reputacao.
    * @return reputação do Utilizador.
    */
    public long getReputacao() {
        return reputacao;
    }

    /**
    * Atualiza a reputação do Utilizador em reputacao.
    * @param reputacao Novo valor de reputação.
    */
    public void setReputacao(long reputacao) {
        this.reputacao = reputacao;
    }
    
    /**
    * Devolve os votos do Utilizador em votes.
    * @return votos do Utilizador.
    */
    public int getVotes() {
        return votes;
    }

    /**
    * Atualiza o valor dos votos em votes.
    * @param votes Novo valor dos votos.
    */
    public void setVotes(int votes) {
        this.votes = votes;
    }
}