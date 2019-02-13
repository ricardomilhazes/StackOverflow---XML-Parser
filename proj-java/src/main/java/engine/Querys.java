package engine;

import common.MyLog;
import common.Pair;
import li3.TADCommunity;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.stream.XMLStreamReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import org.w3c.dom.*;
import javax.xml.parsers.*;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.function.*;
import java.util.stream.*;
import java.util.stream.Collectors;
import java.util.Collections;
import java.util.Comparator;
import java.time.*;
import java.time.LocalDate;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.HashMap;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

public class Querys {

    /**
     * Verifica se existe alguma resposta que tenha um respetivo post (id_pai) e um respetivo autor (author_id).
     * @param id_respostas HashMap das respostas.
     * @param author_id respetivo autor.
     * @param id_pai pergunta a que a resposta corresponde.
     * @return true se existir, falso caso não exista.
     */
    public static boolean encontrado(HashMap<Long,Resposta> id_respostas, long author_id, long id_pai){
        ArrayList<Resposta> resps = new ArrayList<Resposta>();
        for(Resposta x : id_respostas.values()) {
            resps.add(x);
        }

        for(int i = 0; i<resps.size(); i++) {
            if(Long.compare(resps.get(i).getId_autor(),author_id)==0 && Long.compare(resps.get(i).getId_perg(),id_pai)==0){
                return true;
            }
        }

        return false;

       }

    /**
    *Interrogaçao 1. Dado o identificador de um post, retorna o título do post e o nome de utilizador do autor.
    *@param id_utilizador HashMap dos utilizadores
    *@param id_respostas HashMap das respostas
    *@param id_perguntas HashMap das perguntas
    *@param id Identificador do post
    *@return Se o post for uma pergunta, retorna o título e utilizador. Caso seja uma resposta, retorna o título e utilizador da pergunta correspondente.
    */
    public static Pair<String,String> infoFromPostH(HashMap<Long,Utilizador> id_utilizador,HashMap<Long,Resposta> id_respostas,HashMap<Long,Pergunta> id_perguntas,long id) {
        if (id_perguntas.containsKey(id)){
             Pergunta pergunta = id_perguntas.get(id);
             String titulo = pergunta.getTitle();
             Long autor = pergunta.getId_autor();
             Utilizador util = id_utilizador.get(autor);
             String nome = util.getName();
             Pair<String,String> p = new Pair(titulo,nome);
             String teste = p.toString();
             System.out.println(teste);
             return p;
        }
         else if (id_respostas.containsKey(id)){
            Resposta resposta = id_respostas.get(id);
            Long perg = resposta.getId_perg();
            Pergunta pergunta = id_perguntas.get(perg);
            String titulo = pergunta.getTitle();
            Long autor = pergunta.getId_autor();
            Utilizador util = id_utilizador.get(autor);
            String nome = util.getName();
            Pair<String,String> p = new Pair(titulo,nome);
            String teste = p.toString();
            System.out.println(teste);
            return p;
            }

            else return null;
    }
    
    /**
    *Interrogaçao 2. Funcao que obtém o top N utilizadores com maior número de  posts  de  sempre, considerando tanto perguntas quanto respostas dadas pelo respectivo utilizador.
    *@param id_utilizador HashMap dos utilizadores.
    *@param N número de elementos do top.
    *@return O top N de utiizadores com mais posts.
    */
    public static List<Long> topMostActiveH(HashMap<Long,Utilizador> id_utilizador, int N){
            ArrayList<Utilizador> infoPost = new ArrayList<Utilizador>();
                for(Utilizador u: id_utilizador.values()){
                    infoPost.add(u);
                }
            Collections.sort(infoPost, new Comparator<Utilizador>(){
                    public int compare(Utilizador u1, Utilizador u2){
                        return Double.compare(u2.getTotalposts(),u1.getTotalposts());
                    }
            });
            List<Long> resultado = new ArrayList<>();
            
            for(int i=0;i<N;i++){
                resultado.add(infoPost.get(i).getId_u());
            }

            String teste = resultado.toString();
            System.out.println(teste);
            return resultado;
            }

    /**
    *Interrogaçao 3. Obtém o número total de posts (perguntas e respostas separadamente), num determinado intervalo de tempo.
    *@param id_respostas HashMap das respostas.
    *@param id_perguntas HashMap das perguntas.
    *@param begin Data inicial do intervalo de tempo.
    *@param end Data final do intervalo de tempo.
    *@return Par com o número total de perguntas e respostas nesse intervalo de tempo.
    */
    public static Pair<Long,Long> totalPostsH(HashMap<Long,Resposta> id_respostas,HashMap<Long,Pergunta> id_perguntas,LocalDate begin, LocalDate end){

         long perg=0;
         long resp=0;
         String b = begin.toString();
         String e = end.toString();
            
            for (Pergunta p: id_perguntas.values()){
                
                if (p.getD().compareTo(b)>=0 && p.getD().compareTo(e)<=0) perg++;
            } 

            for (Resposta r: id_respostas.values()){
                if (r.getD().compareTo(b)>=0 && r.getD().compareTo(e)<=0) resp++;
            }

            Pair<Long,Long> p = new Pair(perg,resp);

            String teste = p.toString();
            System.out.println(teste);

            return p;

    }

    /**
    *Interrogaçao 4. Função que retorna todas as perguntas contendo uma determinada tag.
    *@param id_perguntas HashTables das perguntas.
    *@param tag Tag a procurar.
    *@param begin Data inicial do intervalo de tempo.
    *@param end Data final do intervalo de tempo.
    *@return Lista com os IDs das perguntas ordenadas em cronologia inversa.
    */
    public static List<Long> questionsWithTagH(HashMap<Long,Pergunta> id_perguntas,String tag, LocalDate begin, LocalDate end){
        ArrayList<Pergunta> TagsData = new ArrayList<Pergunta>();
        String b = begin.toString();
        String e = end.toString();
        for(Pergunta p : id_perguntas.values()){
            if(p.getD().compareTo(b)>0 && p.getD().compareTo(e)<0 && p.getTags().contains(tag)){
                TagsData.add(p);
            }
        }

        Collections.sort(TagsData, new Comparator<Pergunta>(){
                public int compare(Pergunta p1, Pergunta p2){
                    return p2.getD().compareTo(p1.getD());
                }
        });

        List<Long> res = new ArrayList<>();

        for(int i=0; i<TagsData.size(); i++) {
           res.add(TagsData.get(i).getId_post());
        }

        String teste = res.toString();
        System.out.println(teste);

        return res;
    }

    /**
     * Interrogaçao 5. Funcao que, dado o ID de um utilizador devolve a informaçao do seu perfil.
     * @param id_utilizador HashMap dos utilizadores.
     * @param id_respostas HashMap das respostas.
     * @param id_perguntas HashMap das perguntas.
     * @param id ID do respetivo utilizador.
     * @return Informaçao do utilizador, nomeadamente short bio e os IDs dos seus 10 últimos posts (perguntas ou respostas), ordenados por cronologia inversa.
     */
    public static Pair<String, List<Long>> getUserInfoH(HashMap<Long,Utilizador> id_utilizador,HashMap<Long,Resposta> id_respostas,HashMap<Long,Pergunta> id_perguntas,long id){
        Utilizador u = id_utilizador.get(id);
        String shortbio= u.getShortb();
        ArrayList<Pergunta> ultimasPerg = new ArrayList<Pergunta>();
        ArrayList<Resposta> ultimasResp = new ArrayList<Resposta>();
        for(Pergunta p : id_perguntas.values()){
            if(Long.compare(p.getId_autor(),id)==0){
                ultimasPerg.add(p);
            }
        }
        for(Resposta r : id_respostas.values()){
            if(Long.compare(r.getId_autor(),id)==0){
                ultimasResp.add(r);
            }
        }

        LinkedHashMap<Long,String> result = new LinkedHashMap<Long,String>();

        for(int i=0;i<ultimasPerg.size();i++) {
            result.put(ultimasPerg.get(i).getId_post(),ultimasPerg.get(i).getD());
        }

        for(int j=0;j<ultimasResp.size();j++) {
            result.put(ultimasResp.get(j).getId_post(),ultimasResp.get(j).getD());
        }

        result.entrySet().stream().sorted(Map.Entry.comparingByValue()).collect(Collectors.toMap(Entry::getKey, Entry::getValue));

        List<Long> res = new ArrayList<>(result.keySet());
        List<Long> f = new ArrayList<>();

        for(int k=0; k<10; k++){
            f.add(res.get(k));
        }

        Pair<String,List<Long>> p = new Pair(shortbio,f);

        String teste = p.toString();

        System.out.println(teste);

        return p;
    }

    /**
     *Interrogaçao 6. Devolve os IDs das N respostas com mais votos.
     *@param id_respostas HashMap das respostas.
     *@param N Número de respostas a apresentar.
     *@param begin Data inicial do intervalo de tempo.
     *@param end Data final do intervalo de tempo.
     *@return IDs das N resposta com mais votos por ordem decrescente, (número de votos é obtido pela diferenca entre Up Votes e Down Votes, equivalente ao score).
     */
    public static List<Long> mostVotedAnswersH(HashMap<Long,Resposta> id_respostas, int N, LocalDate begin, LocalDate end){
        ArrayList<Resposta> resp_Data = new ArrayList<Resposta>();
        String b = begin.toString();
        String e = end.toString();
        for(Resposta p : id_respostas.values()){
            if(p.getD().compareTo(b)>0 && p.getD().compareTo(e)<0){
                resp_Data.add(p);
            }
        }

        Collections.sort(resp_Data, new Comparator<Resposta>(){
                    public int compare(Resposta p1, Resposta p2){
                        return Double.compare(p2.getScore(),p1.getScore());
                    }
        });

        List<Long> res = new ArrayList<>();

        for(int i=0; i<resp_Data.size() && i<N; i++) {
            res.add(resp_Data.get(i).getId_post());
        }

        String teste = res.toString();
        System.out.println(teste);

        return res;
    }
    
    /**
     *Interrogaçao 7. Dado um intervalo de tempo, devolve os IDs das N perguntas com mais respostas.
     *@param id_perguntas HashMap das perguntas.
     *@param N número de perguntas a apresentar.
     *@param begin Data inicial do intervalo de tempo.
     *@param end Data final do intervalo de tempo.
     *@return IDs das N perguntas com mais respostas (em ordem decrescente).
     */
    public static List<Long> mostAnsweredQuestionsH(HashMap<Long,Pergunta> id_perguntas, int N, LocalDate begin, LocalDate end){
        ArrayList<Pergunta> pergsData = new ArrayList<Pergunta>();
        String b = begin.toString();
        String e = end.toString();
        for(Pergunta p : id_perguntas.values()){
            if(p.getD().compareTo(b)>0 && p.getD().compareTo(e)<0){
                    pergsData.add(p);
                }
            }

        Collections.sort(pergsData, new Comparator<Pergunta>(){
                public int compare(Pergunta p1, Pergunta p2){
                    return Double.compare(p2.getN_resp(),p1.getN_resp());
                }
        });

        List<Long> res = new ArrayList<>();

        for(int i=0; i<pergsData.size() && i<N; i++) {
            res.add(pergsData.get(i).getId_post());
        }

        String teste = res.toString();
        System.out.println(teste);

        return res;
    }

    /**
    *Interrogaçao 8. Dado uma palavra, devolve uma lista com os IDs de N perguntas cujos tıtulos a contenham.
    *@param id_perguntas HashMap das perguntas.
    *@param N número de elementos da lista a apresentar dos IDs
    *@param word Palavra a procurar
    *@return Lista com os IDs das N perguntas que contém a palavra (ordenados por cronologia inversa).
    */
    public static List<Long> containsWordH(HashMap<Long,Pergunta> id_perguntas, int N, String word) {
        ArrayList<Pergunta> perg = new ArrayList<Pergunta>();
        
        for(Pergunta p : id_perguntas.values()){
            if(p.getTitle().contains(word)){
                    perg.add(p);
            }
        }
        
        Collections.sort(perg, new Comparator<Pergunta>(){
                public int compare(Pergunta p1, Pergunta p2){
                    return p2.getD().compareTo(p1.getD());
                }
        });
        
        List<Long> res = new ArrayList<>();
        
        for(int i=0; i<perg.size() && i<N; i++) {
            res.add(perg.get(i).getId_post());
        }
        
        String teste = res.toString();
        System.out.println(teste);

        return res;
    }
    
    /**
    *Interrogaçao 9. Dados os IDs de dois utilizadores, devolve as últimas N perguntas em que ambos participaram (via pergunta ou respostas).
    *@param id_respostas HashMap das respostas.
    *@param id_perguntas HashMap das perguntas.
    *@param N número de perguntas a apresentar.
    *@param id1 ID do primeiro utilizador.
    *@param id2 ID do segundo utilizador.
    *@return Lista com as últimas N perguntas em que ambos participaram (cronologia inversa).
    */
    public static List<Long> bothParticipatedH(HashMap<Long,Resposta> id_respostas,HashMap<Long,Pergunta> id_perguntas, int N, long id1, long id2){
        ArrayList<Resposta> resps = new ArrayList<Resposta>();
        ArrayList<Pergunta> pergsFinal = new ArrayList<Pergunta>();

        for(Resposta r : id_respostas.values()) {
            resps.add(r);
        }

        for(int i=0; i<resps.size();i++) {
            if(Long.compare(resps.get(i).getId_autor(),id1)==0){
                Pergunta p1 = id_perguntas.get(resps.get(i).getId_perg());
                if(Long.compare(p1.getId_autor(),id2)==0) {
                    pergsFinal.add(p1);
                }
                if(encontrado(id_respostas, id2, resps.get(i).getId_perg())) {
                    pergsFinal.add(p1);
                }
            }
            if(Long.compare(resps.get(i).getId_autor(),id2)==0){
                Pergunta p2 = id_perguntas.get(resps.get(i).getId_perg());
                if(p2!=null) {
                    if(Long.compare(p2.getId_autor(),id1)==0) {
                        pergsFinal.add(p2);
                    }
                    if(encontrado(id_respostas, id2, resps.get(i).getId_perg())) {
                        pergsFinal.add(p2);
                    }
                }
            }
        }

        Collections.sort(pergsFinal, new Comparator<Pergunta>(){
            public int compare(Pergunta p1, Pergunta p2){
                return p1.getD().compareTo(p2.getD());
            }
        });

        List<Long> res = new ArrayList<>();

        for(int i=0; i<pergsFinal.size() && i<N; i++) {
            res.add(pergsFinal.get(i).getId_post());
        }

        String teste = res.toString();
        System.out.println(teste);

        return res;

    }

    /**
    *Interrogaçao 10. Dado o ID de uma pergunta, obter a melhor resposta, segundo a funçao (Scr × 0.45) + (Rep × 0.25) + (Vot × 0.2) + ( Comt × 0.1).
    *@param id_utilizador HashMap dos utilizadores.
    *@param id_respostas HashMap das respostas.
    *@param id ID da pergunta.
    *@return A melhor resposta da respetiva pergunta.
    */
    public static long betterAnswerH(HashMap<Long,Utilizador> id_utilizador,HashMap<Long,Resposta> id_respostas,long id) {
        long res=0;
        long temp=0;
        long f=0;
        ArrayList<Resposta> respDaPerg = new ArrayList<Resposta>();

        for(Resposta r : id_respostas.values()) {
            if(Long.compare(r.getId_perg(),id)==0) {
                respDaPerg.add(r);
            }
        }

        for(int i=0; i<respDaPerg.size(); i++){

            Utilizador u = id_utilizador.get(respDaPerg.get(i).getId_autor());

            temp =(long) ((respDaPerg.get(i).getScore() * 0.65) + (respDaPerg.get(i).getN_coments() * 0.1) + (u.getReputacao() * 0.25));

            if(Long.compare(temp,res)>0){ 
                res = temp;
                f = respDaPerg.get(i).getId_post();
            }

            temp = 0;
        }
        return f;
    }

}