package com.mycompany.trabsonso;
import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.ArrayList;
import java.util.Scanner;

public class TrabsonSO {

    public static void main(String[] args) {
        Operacoes operacao = new Operacoes();
        Scanner scan = new Scanner(System.in);
        ArrayList<String> nomes = new ArrayList<>();
        
        Semaphore semaphore = new Semaphore(1);
        
        ProcessadorThread NPC = new ProcessadorThread(1, semaphore); 
        ProcessadorThread Jogador = new ProcessadorThread(2, semaphore); 

        operacao.adicionarNomes(nomes); // Adiciona vários nomes aleatorios a nosso Array de nomes
        Random rand = new Random();
        int n1, n2, resultado, resposta, pontosNpc = 0, pontosUsuario = 0, nperg = 1;
        
        operacao.apresentadorFala1();
        
        /*Seleciona um nome aleatório para o nosso npc*/
        String nomeNpc = nomes.get(rand.nextInt(nomes.size()));
        
        operacao.npcFala1(nomeNpc);
        operacao.apresentadorFala2(nomeNpc);
        
        /*Lê o nome do usuário*/
        String nomeJogador = scan.nextLine();
        
        operacao.apresentadorFala3(nomeJogador);
        
        System.out.println("####### APERTE ENTER ASSIM QUE VER O AVISO DE VALENDO #######");
        
        NPC.start();
        Jogador.start();
        
        while(nperg < 2){
            n1 = rand.nextInt(1, 1000);
            n2 = rand.nextInt(1, 1000);
            resultado = n1 + n2;
            operacao.pergunta(n1, n2, nperg);
            nperg++;
            
            NPC.npcApertar(nomeNpc);
            
            scan.nextLine();
            Jogador.jogadorApertar(nomeJogador);
            
           //lançar a thread, delay 500 ~ 1000 ms
           //scan enter para apertar o botao
           
           
        }
    }
}
