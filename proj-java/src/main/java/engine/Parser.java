package engine;

import java.*;
import java.lang.String;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;

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

public class Parser {

    /**
    *parseXMLUsers. Lê o ficheiro Users.xml e adiciona á hashtable id_utilizador os varios utilizadores que encontra.
    *@param h1 HashMap dos utilizadores (id_utilizador).
    *@param filename Nome do ficheiro .xml que vai ler (ficheiro Users.xml.
    */
       public static void parseXMLUsers(HashMap<Long,Utilizador> h1, String fileName) {

        String name = "", shortb = "";
        long reputacao=-1L,id_u = -1L;
        int up_votes =0 ,down_votes=0,totalposts = 0, votes =0;


        // System.out.println("Comecei o parse.\n");

        try {
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLStreamReader xmlStreamReader = factory.createXMLStreamReader(new FileInputStream(fileName));
            while(xmlStreamReader.hasNext()) {

                int event = xmlStreamReader.getEventType();

                if (event == XMLStreamConstants.START_ELEMENT) {
                            name = "";
                            shortb = "";
                            reputacao=0;
                            id_u = 0;
                            up_votes =0 ;
                            down_votes=0;
                            totalposts = 0;
                            votes =0;
                    if ( xmlStreamReader.getName().getLocalPart().equalsIgnoreCase("row")) {


                            for (int iterador = 0; iterador<xmlStreamReader.getAttributeCount(); iterador++) {
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Id")){ 
                                    id_u = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("DisplayName")){ 
                                    name = xmlStreamReader.getAttributeValue(iterador);
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("AboutMe")){ 
                                    shortb = xmlStreamReader.getAttributeValue(iterador);
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Reputation")){ 
                                    reputacao= Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("UpVotes")){ 
                                    up_votes = Integer.parseInt(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("DownVotes")){ 
                                    down_votes = Integer.parseInt(xmlStreamReader.getAttributeValue(iterador));
                                }
                            }
                                votes= (up_votes)-(down_votes);


                    }

                    Utilizador newU = new Utilizador(id_u,name,shortb,totalposts,reputacao,votes);
        
                    h1.put(id_u,newU);

                }


                event = xmlStreamReader.next();
            
    }
        } catch (FileNotFoundException e) {

            e.printStackTrace();

        } catch (XMLStreamException e) {

            e.printStackTrace();

        }  

}
    

    /**
    *parseXMLTags. Lê o ficheiro Tags.xml e adiciona á hashtable id_tags as varias tags que encontra.
    *@param h2 HashMap das tags (id_tags).
    *@param filename Nome do ficheiro .xml que vai ler (ficheiro Tags.xml).
    */


        public static void parseXMLTags(HashMap<Long,Tag> h2,String fileName) {
            String tag = "";
            long idTag=-3;
            int count = 0;



        // System.out.println("Comecei o parse.\n");

        try {
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLStreamReader xmlStreamReader = factory.createXMLStreamReader(new FileInputStream(fileName));

            while(xmlStreamReader.hasNext()) {

                int event = xmlStreamReader.getEventType();

                if (event == XMLStreamConstants.START_ELEMENT) {
                                 tag = "";
                                 idTag=-3;
                                 count = 0;
                    if ( xmlStreamReader.getName().getLocalPart().equalsIgnoreCase("row")) {


                            for (int iterador = 0; iterador<xmlStreamReader.getAttributeCount(); iterador++) {
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Id")){ 
                                    idTag = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("TagName")){ 
                                    tag = xmlStreamReader.getAttributeValue(iterador);
                                }

                    }
                } 

                     
                     Tag newT = new Tag(idTag,tag,count);
    
    
                     h2.put(idTag,newT);


                    }
                
                event = xmlStreamReader.next();

            }

        } catch (FileNotFoundException e) {

            e.printStackTrace();

        } catch (XMLStreamException e) {

            e.printStackTrace();

        
    }
}


    /**
    *parseXMLPosts. Lê o ficheiro Posts.xml e adiciona á hashtable id_perguntas se o type_id = 1 os e á hashtable id_respostas se o type_id = 2 .
    *@param h3 HashMap das perguntas (id_perguntas).
    *@param h4 HashMap das respostas (id_respostas).
    *@param h5 HashMap dos utilizadores (id_utilizador).
    *@param filename Nome do ficheiro .xml que vai ler (ficheiro Posts.xml).
    */

        public static void parseXMLPosts(HashMap<Long,Pergunta> h3,HashMap<Long,Resposta> h4,HashMap<Long,Utilizador> h5, String fileName){

        String tags = "", title = "",data = "";
        long post_id = 0, author_id = 0, total_score= 0;

        long postTypeId=0, parent_id=0;

        long coment = 0; 
        long respo = 0;



        try {
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLStreamReader xmlStreamReader = factory.createXMLStreamReader(new FileInputStream(fileName));

            while(xmlStreamReader.hasNext()) {

                int event = xmlStreamReader.getEventType();

                if (event == XMLStreamConstants.START_ELEMENT) {
                        tags = "";
                        title = "";
                        data = "";
                        post_id = 0;
                        author_id = 0;
                        total_score= 0;
                        postTypeId=0;
                        parent_id=0;
                        coment = 0; 
                        respo = 0;                    

                    if ( xmlStreamReader.getName().getLocalPart().equalsIgnoreCase("row")) {

                            for (int iterador = 0; iterador<xmlStreamReader.getAttributeCount(); iterador++) {
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Id")){ 
                                    post_id = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Tags")){ 
                                    tags = xmlStreamReader.getAttributeValue(iterador);
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("CreationDate")){ 
                                    data = xmlStreamReader.getAttributeValue(iterador);
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Title")){ 
                                    title= xmlStreamReader.getAttributeValue(iterador);
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("OwnerUserId")){ 
                                    author_id = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("Score")){ 
                                    total_score = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("PostTypeId")){ 
                                    postTypeId = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("ParentId")){ 
                                    parent_id = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("CommentCount")){ 
                                    coment = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }
                                if (xmlStreamReader.getAttributeLocalName(iterador).equals("AnswerCount")){ 
                                    respo = Long.parseLong(xmlStreamReader.getAttributeValue(iterador));
                                }


                    }
                    } 

                    if (postTypeId == 1){
                        Pergunta newP = new Pergunta(post_id,author_id,title,tags,total_score,respo,data);

                        Utilizador u = h5.get(author_id);

                        u.setTotalposts(u.getTotalposts() + 1);
    
                        h3.put(post_id,newP);
                    }
                    else {
                        Resposta newR = new Resposta(post_id,parent_id,author_id,total_score,respo,data);
    
                        Utilizador u = h5.get(author_id);

                        u.setTotalposts(u.getTotalposts() + 1);

                        h4.put(post_id,newR);
                    
                    }
                
                                    
                                }
                event = xmlStreamReader.next();
}

        } catch (FileNotFoundException e) {

            e.printStackTrace();

        } catch (XMLStreamException e) {

            e.printStackTrace();

        }
    }
}