package engine;


/**
 * Classe que representa uma tag.
 * 
 * @Diogo Rocha, Gabriela Martins, Ricardo Frreira, Ricardo Veloso 
 * @12/06/2018
 */
public class Tag
{
    //variaveis de instância
    private long id_tag;
    private String tag;
    private long count;
    
    /**
    * Construtor por omissão de Tag.
    */
    public Tag(){
        this.id_tag=0;
        this.tag=null;
        this.count=0;
    }

    /**
    * Construtor parametrizado de Tag.
    * Recebe como parâmetros o ID da tag, a tag, o número de vezes que a tag foi utilizada em posts.
    */
    public Tag(long id_tag,String tag,long count){
        this.id_tag=id_tag;
        this.tag=tag;
        this.count=count;
    }

    /**
    * Devolve o ID da Tag em id_tag.
    * @return valor do ID da Tag.
    */
    public long getID_tag(){
        return id_tag;
    }

    /**
    * Devolve o nome da Tag em tag.
    * @return nome da Tag.
    */
    public String getTag(){
        return tag;
    }

    /**
    * Devolve o número de vezes que a Tag foi utilizada em posts em count.
    * @return somatório do número de vezes que a Tag foi utilizada.
    */
    public long getCount(){
        return count;
    }
    
    /**
    * Atualiza o ID da Tag em id_tag.
    * @param id_tag Novo ID da Tag.
    */
    public void setID_tag(long id_tag){
        this.id_tag=id_tag;
    }
    
    /**
    * Atualiza o nome da Tag em tag.
    * @param tag Novo nome da Tag.
    */
    public void setTag(String tag){
        this.tag=tag;
    }

    /**
    * Atualiza o número total de vezes que a Tag foi utilizada em posts em count.
    * @param count Novo número resultante do somatório do número de vezes que a Tag foi utilizada.
    */
    public void setCount(long count){
        this.count=count;
    }

}
