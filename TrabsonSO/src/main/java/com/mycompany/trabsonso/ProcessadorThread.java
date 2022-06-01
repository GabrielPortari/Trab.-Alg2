package com.mycompany.trabsonso;
import java.util.Random;
import java.util.concurrent.Semaphore;

/**
 *
 * @author Gabriel Portari
 */
public class ProcessadorThread extends Thread {
    private int idThread;
    private Semaphore semaforo;
    
    public ProcessadorThread(int id, Semaphore semaphore) {
        this.idThread = id;
        this.semaforo = semaphore;
    }
    private void npcResponder(String nomeNpc) {
        try {
            System.out.println(nomeNpc + " apertou o botão");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private void jogadorResponder(String nomeJogador) {
        try {
            System.out.println(nomeJogador + " apertou o botão");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void npcApertar(String nomeNpc) {
        try {
            Random rand = new Random();
            Thread.sleep(rand.nextInt(2500, 3000));
            semaforo.acquire();
            npcResponder(nomeNpc);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            semaforo.release();
        }
    }
     public void jogadorApertar(String nomeJogador) {
        try {
            semaforo.acquire();
            jogadorResponder(nomeJogador);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            semaforo.release();
        }
    }
}