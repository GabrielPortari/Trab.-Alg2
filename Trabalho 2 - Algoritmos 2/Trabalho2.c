//Gabriel Portari de Moraes
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

typedef struct cel{
	char palavra[30], PoS[30];
	struct cel *prox;
}celula;

//função para alocar memoria e inserir variaveis
celula *aloca(char palavra[], char pos[], int tampalavra, int tampos){
	//declaração de váriaveis
	celula *nova;
	int i;
	//aloca memória para nova celula
	nova = (celula *) malloc(sizeof (celula));
	if(nova == NULL){
		printf("Falha ao alocar memoria.");
		exit(1);
	}
	//adiciona a palavra lida na struct
	for(i=0; i<tampalavra; i++){
		nova->palavra[i] = palavra[i];
	}//ultima posição = '\0' para não ler o lixo na memória
	nova->palavra[tampalavra] = '\0';
	
	//adiciona o PoS lido na struct
	for(i=0; i<tampos; i++){
		nova->PoS[i] = pos[i];
	}//ultima posição = '\0' novamente para nao ler lixo
	nova->PoS[tampos] = '\0';
	
	//nova->prox = NULL para não dar em uma posição aleatoria e dar erro
	nova->prox = NULL;
	
	return nova;
}
//função para inserir uma nova celula
void insere(celula **ini, char palavra[], char pos[], int tampalavra, int tampos){
	//declaração de variáveis
	celula *p;
	//se inicio = NULO então aloca na primeira posição
	if(*ini == NULL){
		*ini = aloca(palavra, pos, tampalavra, tampos);
	}else{ //caso inicio != NULO, incremento p->prox até achar a ultima posição para alocar
		p = *ini;
		while(p->prox != NULL){
			p = p->prox;
		}
		//ultima posição vazia encontrada, aloca espaço e váriaveis
		p->prox = aloca(palavra, pos, tampalavra, tampos);
	}
}
//função para ordenar PoS e escrever no arquivo
void escreve_arq(celula *ini, FILE *exit){
	//declaração de variaveis
	celula *p, *q;
  	int cmp, repete=1;
  	
	p = ini;
	q = p->prox;
	
	fprintf(exit,"\nPoS, FREQ\n");
	//Printf das PoS e vezes que repetem respectivamente
	while(q != NULL){
		cmp = strcmp(p->PoS, q->PoS); //compara p->PoS e q->PoS, se for igual incrementa repete e q = q->prox
		if(cmp != 0){ //caso PoS do ponteiro p seja diferente do ponteiro q, escreve no arquivo, reseta repete e atualiza ponteiro p
			fprintf(exit,"%s, %i\n", p->PoS, repete);
			repete = 1;
			p = q;
			if(q->prox == NULL){ //este if e o abaixo foi colocado para resolver um problema que tive, em que a ultima posição da fila nao saia no arquivo
				fprintf(exit,"%s, %i\n", q->PoS, repete);
			}	
			q = q->prox;
		}else{ //caso PoS seja igual, incrementa repete, e atualiza ponteiro q
			repete++;
			if(q->prox == NULL){ 
				fprintf(exit,"%s, %i\n", q->PoS, repete);
			}
			q = q->prox;
		}
	}
	
	//ponteiro p volta para posição inicial da fila
	p = ini;		
	repete = 1;
	q = p->prox;
	
	fprintf(exit,"\nPALAVRAS, FREQ\n");
	while(q != NULL){
		cmp = strcmp(p->palavra, q->palavra); //compara p->palavra e q->palavra, se for igual incrementa repete e q = q->prox
		if(cmp != 0){ //caso palavra do ponteiro p seja diferente do ponteiro q, escreve no arquivo, reseta repete e atualiza ponteiro p
			fprintf(exit,"%s, %i\n", p->palavra, repete);
			repete = 1;
			p = q;
			
			if(q->prox == NULL){ //este if e o abaixo foi colocado para resolver um problema que tive, em que a ultima posição da fila nao saia no arquivo
				fprintf(exit,"%s, %i\n", q->palavra, repete);
			}
			
			q = q->prox;
		}else{  //caso palavra seja igual, incrementa repete, e atualiza ponteiro q
			repete++;	
			if(q->prox == NULL){
				fprintf(exit,"%s, %i\n", q->palavra, repete);
			}	
			q = q->prox;
		}
	}
}
//função para ordenar palavras e escrever no arquivo
void ordem_alfabetica(celula *ini, FILE *exit){
	//declaração de variaveis
	celula *p, *q;
	int cmp, tamp, tamq, rep=1, palavras_distintas=1, totalpalavras=1;
	char aux[30];
  	
	p = ini;
	q = p->prox;
	
	//coloca as palavras ordem alfabetica
	while(p != NULL){
		while(q != NULL){
			cmp = strcmp(p->palavra, q->palavra); //compara p->palavra e q->palavra
			if(cmp >= 0){ // se cmp == 0, são iguais, se cmp > 0, p->palavra vem antes, se cmp < 0 p-> palavra vem depois
				tamp = strlen(p->palavra); // -----------------------------------------------------------
				tamq = strlen(q->palavra);
				strcpy(aux, p->palavra); //            essa parte apenas troca as palavras de lugar
				strcpy(p->palavra, q->palavra);
				strcpy(q->palavra, aux); // -----------------------------------------------------------
			}
			q = q->prox;
		}
		p = p->prox;
		q = p;
	}
	
	//volta para posição inicial da fila
	p = ini;
	q = p->prox;
	
	//coloca os PoS ordem alfabetica
	while(p != NULL){
		while(q != NULL){
			cmp = strcmp(p->PoS, q->PoS); //compara p->PoS e q->PoS
			if(cmp >= 0){ // se cmp == 0, são iguais, se cmp > 0, p->PoS vem antes, se cmp < 0 p->PoS vem depois
				tamp = strlen(p->PoS); // -----------------------------------------------------------
				tamq = strlen(q->PoS);
				strcpy(aux, p->PoS); //            essa parte apenas troca as PoS de lugar
				strcpy(p->PoS, q->PoS);
				strcpy(q->PoS, aux); // -----------------------------------------------------------
			}
			q = q->prox;
		}
		p = p->prox;
		q = p;
	}
	
	//ponteiro p volta para posição inicial da fila
	p = ini;
	
	//while(!isalpha(p->palavra[0])){ // ignorar pontos, virgulas e apostrofos
	//	p = p->prox;
	//}
	q = p->prox;
	
	//conta as palavras totais e palavras distintas
	while(q != NULL){
		cmp = strcmp(p->palavra, q->palavra); // compara p->palavra com q->palavra
			if(cmp == 0){
				rep++; //incrementa caso palavra seja repetida
				totalpalavras++; //incrementa total de palavras
			}else{
				rep = 1; //reset de palavras repetidas
				p = q;
				palavras_distintas++; //incrementa palavras distintas e total de palavras
				totalpalavras++;
			}
		q = q->prox;
	}
	fprintf(exit,"TOTAL DE PALAVRAS, %i\nTOTAL DE PALAVRAS DISTINTAS, %i\n", totalpalavras, palavras_distintas);	
}
//função para desalocar memória
void freelista(celula *ini){
	//declaração de váriaveis
	celula *p;
	//enquanto o inicio for != de NULL, libera a memória celula por celula
	while(ini != NULL){
		p = ini;
		ini = ini->prox;
		free(p);
	}
}

int main(int argc, char *argv[]){
	//declaração de váriaveis
	celula *ini;
	char palavra[30], pos[30], saida[30];
	int x=0, tampalavra, tampos, tamsaida, i, caracter=1;
	FILE *entrada, *exit;
	
	ini = NULL;
	
	if(argc != 2){
		fprintf(stderr, "Modo de usar %s nome_do_arquivo\n", argv[0]);
		return 0;
	}
	
	//abertura do arquivo de entrada
	entrada = fopen(argv[1], "r");
	if (entrada == NULL){
    	printf("Falha na abertura do arquivo\n");
     	return 0;
  	}
  	
  	//muda o nome do arquivo de saida de .pos para .csv
	strcpy(saida, argv[1]);
	tamsaida = strlen(saida);
	for(i=0; i<tamsaida; i++){
		if(saida[i] == '.'){
			saida[i+1] = 'c';
			saida[i+2] = 's';
			saida[i+3] = 'v';
			saida[i+4] = '\0';
		}
	}
	
	//leitura do arquivo
	while(!feof(entrada)){
		fscanf(entrada," %[^/] %s", palavra, pos);
		
		tampalavra = strlen(palavra);
		tampos = strlen(pos);
		
		//coloca as palavras lidas no diminutivo
		for(i=0; i<tampalavra; i++){
			palavra[i] = tolower(palavra[i]);
		}

		//puxa a string PoS 1 posição para trás para remover a barra '/'
		for(i=0; i<tampos; i++){
			pos[i] = pos[i+1];
		}
		tampos--;
		if(isalpha(pos[0])){
			//chama função para inserir uma nova celula na fila
			insere(&ini, palavra, pos, tampalavra, tampos);	
		}
	}
	
	//fechamento do arquivo de entrada
	int fclose(FILE argv[1]);
	
	//abertura do arquivo de saida
	exit = fopen(saida, "w");
	if (exit == NULL){ 
    	printf("Falha na abertura do arquivo\n");
     	return 0;
  	}
  	printf("Arquivo %s gerado com sucesso!", saida);
  	
  	//chama função para ordenar palavras / PoS em ordem alfabetica
	ordem_alfabetica(ini, exit);
	
	//chama função para escrever PoS e palavras no arquivo.
	escreve_arq(ini, exit);
	
	//fecha arquivo de saida
	int fclose(FILE *saida); 
	
	//chama função para liberar espaço alocado na memória.
	freelista(ini);
}

