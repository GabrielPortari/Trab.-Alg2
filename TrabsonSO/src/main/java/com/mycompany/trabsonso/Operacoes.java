package com.mycompany.trabsonso;
import java.util.Random;
import java.util.ArrayList;


/**
 *
 * @author Gabriel Portari
 */
public class Operacoes {
    Random rand = new Random();
    public void apresentadorFala1(){
        try {
                System.out.println("Apresentador: Olá senhoras e senhores!! ");
                Thread.sleep(3000);
                System.out.println("Apresentador: Sejam todos bem vindos ao nosso adorado jogo de perguntas e respostas!! ");
                Thread.sleep(3000);
                System.out.println("\nPlatéia: <clap><clap><clap> ihuuuuu!!! <clap><clap>");
                Thread.sleep(1000);
                System.out.println("Platéia: êêêêêêê <clap><clap><clap> vamooo !!! <clap><clap>");
                Thread.sleep(1000);
                System.out.println("Platéia: VAMOOO <clap><clap> EEEEE <clap><clap><clap>\n");
                Thread.sleep(1000);
                System.out.println("Apresentador: Obrigado pela recepção calorosa pessoal, agora vamos conhecer nossos participantes!!");
                Thread.sleep(4000);
                System.out.println("Apresentador: Primeiramente o nosso jogador da casa, sempre conosco, se apresente!");
                Thread.sleep(4000);
            } catch (InterruptedException ex) {
            }
    }
    public void npcFala1(String nomeNpc){
        try {
                System.out.println(nomeNpc + ": Olá pessoal, obrigado por me receberem aqui novamente!!");
                Thread.sleep(3000);
                System.out.println(nomeNpc + ": Mais um dia aqui para ter aquela competição saudável!!");
                Thread.sleep(3000);
                
            } catch (InterruptedException ex) {
            }
    }
    public void apresentadorFala2(String nomeNpc){
        try {
                System.out.println("Apresentador: Obrigado por mais uma participação " + nomeNpc + " é sempre um prazer ter você aqui conosco.");
                Thread.sleep(3000);
                System.out.println("Apresentador: Agora é a vez do nosso desafiante se apresentar, por favor nos diga seu nome!");
                Thread.sleep(3000);
                System.out.print("\nDigite seu nome: "); 
            } catch (InterruptedException ex) {
            }
    }
    public void apresentadorFala3(String nomeUsuario){
        try {
                System.out.println("\nApresentador: Seja muito bem vindo " + nomeUsuario + " é sempre um prazer ter você aqui conosco.");
                Thread.sleep(2000);
                System.out.println("\nPlatéia: êêêêêêê <clap><clap><clap> vamooo !!! <clap><clap>");
                Thread.sleep(1000);
                System.out.println("Platéia: <clap><clap><clap> ihuuuuu!!! <clap><clap>\n");
                Thread.sleep(1000);
                System.out.println("Apresentador: Vou explicar as regras do nosso jogo!!");
                Thread.sleep(3000);
                System.out.println("Apresentador: Eu vou fazer uma pergunta, e contar até 3, o primeiro que apertar o botão tem direito a responder");
                Thread.sleep(5000);
                System.out.println("Apresentador: Lembrando que cada resposta correta é 1 ponto, e caso erre não ganha nada!");
                Thread.sleep(5000);
                System.out.println("Apresentador: Preparados?? Então vamos começar !!");
                Thread.sleep(5000);
            } catch (InterruptedException ex) {
            }
    }
    public void pergunta(int n1, int n2, int nperg){
        try {
                System.out.println("Pergunta número " + nperg);
                Thread.sleep(2000);
                System.out.println("Qual é o resultado da soma de " + n1 + " + " + n2 + " ??");
                Thread.sleep(3000);
                System.out.println("No 3 !!");
                Thread.sleep(rand.nextInt(1000, 4000));
                System.out.println("1...");
                Thread.sleep(rand.nextInt(1000, 4000));
                System.out.println("2...");
                Thread.sleep(rand.nextInt(1000, 4000));
                System.out.println("3...");
                System.out.println("VAALEENDOOOOO !!");
            } catch (InterruptedException ex) {
            }
    }
    public ArrayList<String> adicionarNomes(ArrayList<String> nomes){
        nomes.add("Junior");
        nomes.add("Pedro");
        nomes.add("Max");
        nomes.add("Bruno");
        nomes.add("Cleber");
        nomes.add("Gustavo");
        nomes.add("Valdemar");
        nomes.add("Yago");
        nomes.add("Giovana");
        nomes.add("Bianca");
        nomes.add("Isabela");
        nomes.add("Juliana");
        nomes.add("Fatima");
        nomes.add("Melissa");
        nomes.add("Mayara");
        nomes.add("Yanca");
        nomes.add("Milena");
        return nomes;
    }
}
