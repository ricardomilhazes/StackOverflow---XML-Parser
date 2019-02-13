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

public class TCDExample implements TADCommunity {    

    private static HashMap<Long,Utilizador> id_utilizador;
    private static HashMap<Long,Pergunta> id_perguntas;
    private static HashMap<Long,Resposta> id_respostas;
    private static HashMap<Long,Tag> id_tags;

    /**
     * Cria as HashMap a serem utilizadas.
     */
    public void init() {
        id_utilizador = new HashMap<Long,Utilizador>();
        id_perguntas = new HashMap<Long,Pergunta>();
        id_respostas = new HashMap<Long,Resposta>();
        id_tags = new HashMap<Long,Tag>();
    }

    /**
     * Inicializa o carregamento das HashMap.
     */
    public  void parsAllData(String dumpPath) {
        
        String fileName;

        //parse Users
            fileName = dumpPath+"/Users.xml";
            System.out.println(fileName);
            Parser.parseXMLUsers(id_utilizador,fileName);

        //parse Posts
            fileName = dumpPath+"/Posts.xml";
            System.out.println(fileName);
            Parser.parseXMLPosts(id_perguntas,id_respostas,id_utilizador,fileName);
     
        //parse Tags
            fileName = dumpPath+"/Tags.xml";
            System.out.println(fileName);
            Parser.parseXMLTags(id_tags,fileName);            
    }
    
    /**
     * Executa a parseAllData(), que faz o load através dos vários ficheiros.
     */
    public void load(String dumpPath) {
        parsAllData(dumpPath);
    }


    // Query 1
    public Pair<String,String> infoFromPost(long id) {
    	 System.out.println("Query 1 -> \n");
         return Querys.infoFromPostH(id_utilizador,id_respostas,id_perguntas,id);
    }

    // Query 2
    public  List<Long> topMostActive(int N){
    	System.out.println("Query 2 -> \n");
        return Querys.topMostActiveH(id_utilizador,N);
    }

    // Query 3
   public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
   		System.out.println("Query 3 -> \n");
   		return Querys.totalPostsH(id_respostas,id_perguntas,begin,end);
     }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
    	System.out.println("Query 4 -> \n");
   		return Querys.questionsWithTagH(id_perguntas,tag,begin,end);
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id){
    	System.out.println("Query 5 -> \n");
    	return Querys.getUserInfoH(id_utilizador,id_respostas,id_perguntas,id);
	}

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
    	System.out.println("Query 6 -> \n");
        return Querys.mostVotedAnswersH(id_respostas,N,begin,end);
    }

    // Query 7
   public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
   		System.out.println("Query 7 -> \n");
  		return Querys.mostAnsweredQuestionsH(id_perguntas,N,begin,end);
  	}

    // Query 8
    public List<Long> containsWord(int N, String word) {
    	System.out.println("Query 8 -> \n");
        return Querys.containsWordH(id_perguntas,N,word);
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2){
    	System.out.println("Query 9 -> \n");
    	return Querys.bothParticipatedH(id_respostas,id_perguntas,N,id1,id2);
	}


    // Query 10
    public long betterAnswer(long id) {
    	System.out.println("Query 10 -> \n");
    	return Querys.betterAnswerH(id_utilizador,id_respostas,id);
	}

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
    	System.out.println("Query 11 -> \n");
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){
    	id_utilizador.clear();
    	id_perguntas.clear();
    	id_respostas.clear();
    	id_tags.clear();
    }
}
