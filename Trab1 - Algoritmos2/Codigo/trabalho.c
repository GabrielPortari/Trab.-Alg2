//Gabriel Portari de Moraes
//RGA: 2019.0743.034-2
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define max 100
typedef struct{ // registro dos caminhos que acharam uma saida
	int segundos;
	char saida;
	int caminho[100];
} reg_saida;

void print_saida(int nvitorias, reg_saida reg[], int saida, FILE *arq){
	int i, j, achou=0;
	char v[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //vetor de caractere onde cada posição do vetor (int) representa o mesmo numero em char, para facilitar a procura das saidas.
	
	for(i=0; i<nvitorias; i++){
		if (reg[i].saida == v[saida]){
			achou = 1;
			fprintf(arq, "Saida %c, %i segundos: ", reg[i].saida, reg[i].segundos);
			for(j=0; j<reg[i].segundos; j++){
				switch(reg[i].caminho[j]){
					case 1:
						fprintf(arq, "c");
					break;
					case 2:
						fprintf(arq, "b");
					break;
					case 3:
						fprintf(arq, "d");
					break;
					case 4:
						fprintf(arq, "e");
					break;
				}
			}
			fprintf(arq, "\n");
		}
	}
	if(achou == 0){
		fprintf(arq, "Saida %i: Nao alcancada!\n", saida);
	}
}
void escreve_matriz(int linha, int coluna, char **matriz){
	int i, j;
	for(i=0; i<linha; i++){
		for(j=0; j<coluna; j++){
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	//declaração de váriaveis
	int lin, col, passos, i, j, k, l, posx, xini, posy, yini, ganhou=0, nwins=0, nsaidas, fechado=0, caminho[20], tentativas, contapasso=0, contador=0, igual=0, menor;
	char **arena, **pt, nomearena[30], lx[15];
	reg_saida regexit[100];
	FILE *entrada, *saida;

	//abertura do arquivo de entrada
	entrada = fopen(argv[1], "r");
	if (entrada == NULL){
    	printf("Falha na abertura do arquivo\n");
     	return 0;
  	}
  	//leitura dados do arquivo
  	fscanf(entrada,"%s %s\n", lx, nomearena);
	fscanf(entrada,"%s %i\n", lx, &passos);
	fscanf(entrada,"%s %i\n", lx, &nsaidas);
	fscanf(entrada,"%s %ix%i", lx, &lin, &col);

	//alocação dinamica para a matriz	
	arena = (char **) malloc(lin * sizeof(char *));
		if (arena == NULL){
			return 0;
		}
	for (pt = arena, i = 0; i < lin; i++, pt++) {
		*pt = (char *) malloc(col*sizeof(char));
		if (*pt == NULL){
			printf("Falha na alocacao de memoria.");
			return 0;
		}
	}
	printf("Instancia: %s\nOrcamento disponivel: %i segundos\nQuantidade de saidas: %i\n", nomearena, passos, nsaidas);
	
	//leitura arena
	for(i=0; i<lin; i++){
		for(j=0; j<col; j++){
			fscanf(entrada, "%c", &arena[i][j]);
			if(arena[i][j] == '\n'){ // se houver um \n, substitui por um \0, e le novamente para não haver erros
				arena[i][j] = '\0'; // na contagem do tamanho da matriz
				j--;
			}
			if(arena[i][j] == ' '){ // como no arquivo o caractere é um espaço
				arena[i][j] = '\0'; // converte ele para um \0
			}
        }
	}
	
	//fechamento do arquivo entrada
	int fclose(FILE argv[1]);
	
	printf("\n");
	escreve_matriz(lin, col, &arena[0]);
	printf("\n");
	
	//percorre a matriz procurando a posição inicial do robo
	for(i=0; i<lin; i++){
		for(j=0; j<col; j++){
			if(arena[i][j] == '*'){
				posx = j;
				posy = i;
			}
		}
	}
	xini = posx; // variaveis de backup
	yini = posy;
	
	/*
	1 cima = y - 1
	2 baixo = y + 1
	3 direita = x + 1
	4 esquerda = x - 1
	*/
	
	tentativas = 4*passos; // como o algoritmo usado testa todas as possibilidades, quando o contador chegar em 444444 é porque todos os caminhos possiveis foram testados.
	while (contador != tentativas){ // loop para testar todas as possibilidades possiveis que o robo pode testar com n passos.
		contador = 0;
		for(i=0; i<passos; i++){
				switch(caminho[i]){
					/*
					Caso a posição escolhida (c, b, e, d) esteja fechada, sai do for
					Caso a posição seja diferente de # e de \0, logo é uma saida, registra a saida, e o tempo no vetor regexit.
					Caso não seja nenhuma das opçoes acima, move o * de lugar.
					*/
					case 1: // cima = y-1
						if(arena[posy-1][posx] == '#'){
							fechado = 1;
						}else
						if(arena[posy-1][posx] != '#' && arena[posy-1][posx] != '\0'){
							ganhou = 1;
							contapasso++;
							regexit[nwins].segundos = contapasso;
							regexit[nwins].saida = arena[posy-1][posx];
						}else{
							arena[posy-1][posx] = '*';
							arena[posy][posx] = '\0';
							contapasso++;
							posy--;
						}
					break;
				case 2: // baixo = y+1
					if(arena[posy+1][posx] == '#'){
						fechado = 1;
					}else
					if(arena[posy+1][posx] != '#' && arena[posy+1][posx] != '\0'){
						ganhou = 1;
						contapasso++;
						regexit[nwins].segundos = contapasso;
						regexit[nwins].saida = arena[posy+1][posx];
					}else{
						arena[posy+1][posx] = '*';
						arena[posy][posx] = '\0';
						contapasso++;
						posy++;
					}
					break;
				case 3:  //direita = x+1
					if(arena[posy][posx+1] == '#'){
						fechado = 1;
					}else
					if(arena[posy][posx+1] != '#' && arena[posy][posx+1] != '\0'){
						ganhou = 1;
						contapasso++;
						regexit[nwins].segundos = contapasso;
						regexit[nwins].saida = arena[posy][posx+1];
					}else{
						arena[posy][posx+1] = '*';
						arena[posy][posx] = '\0';
						posx++;
						contapasso++;
					}
				break;
				case 4: // esquerda = x-1
					if(arena[posy][posx-1] == '#'){
						fechado = 1;
					}else
					if(arena[posy][posx-1] != '#' && arena[posy][posx-1] != '\0'){
						ganhou = 1;
						contapasso++;
						regexit[nwins].segundos = contapasso;
						regexit[nwins].saida = arena[posy][posx-1];
					}else{
						arena[posy][posx-1] = '*';
						arena[posy][posx] = '\0';
						posx--;
						contapasso++;
					}
				break;
			}
			if(ganhou == 1){ //caso ache saida, adiciona o caminho ao registro
				for(j=0; j<contapasso; j++){
					regexit[nwins].caminho[j] = caminho[j];
				}
				nwins++; //incrementa o registro
				i = passos+1; //sai do loop forçadamente
			}else
			if(fechado == 1){ // se caminho tiver fechado, sai do for pois não precisa testar o resto
				i = passos+1;
			}
		}
		// incrementa o vetor com todas as possibilidades
		caminho[0]++;
		for(j=0; j<passos; j++){
			if(caminho[j] > 4){
				caminho[j] = 1;
				caminho[j+1]++;
			}
		}
		
		// calcula o contador
		for (j=0; j<passos; j++){ 
			contador = contador + caminho[j];
		}
		/*
		for(j=0; j<passos; j++){
			printf("%i ", caminho[j]);
		}
		printf("\n");
		*/
		if(ganhou == 1){ // registra o caminho que achou a saida no vetor de registro
			for(i=0; i<nwins; i++){
				for(j=i+1; j<nwins; j++){ // substitui saidas repetidas com mais passos que as anteriores
					if(regexit[i].saida == regexit[j].saida && regexit[i].segundos >= regexit[j].segundos){
						regexit[i] = regexit[j];
					}
				}
			}
			for(j=0; j<nwins; j++){
				for(k=nwins; k>j; k--){ // procura por caminhos repetidos no algoritmo, por ex cccc achou, porém as vezes conta ccccdd ccccee cccccd, esse for remove esses casos
					if(regexit[j].saida == regexit[k].saida && regexit[j].segundos == regexit[k].segundos){
						for(l=0; l<regexit[j].segundos; l++){
							igual = 1;
							if(regexit[j].caminho[l] != regexit[k].caminho[l]){ //procura diferenças no caminho
								igual = 0;
							}
						}
						if(igual == 1){ // caso um registro seja igual o anterior, ele é removido e o vetor anda para tras
							for(l=k; l<nwins; l++){
								regexit[l] = regexit[l+1];
							}
							nwins--; // diminui o tamanho total do registro que foram salvos as saidas				
						}
					}
				}
			}
		}
		// reset das variaveis do loop
		ganhou = 0;
		fechado = 0;
		contapasso = 0;
		arena[posy][posx] = '\0';
		arena[yini][xini] = '*';
		posy = yini;
		posx = xini;
	}

	//abertura do arquivo de entrada
	saida = fopen("saida.txt", "w");
	if (entrada == NULL){ 
    	printf("Falha na abertura do arquivo\n");
     	return 0;
  	}
  	
	fprintf(saida, "Posicao inicial [x, y]: [%i, %i]\n", posx, posy);
	fprintf(saida, "Orcamento disponivel: %i segundos\n", passos);
	if(nwins == 0){ // caso nao ache nenhuma saida
		printf("Arena sem saída!\n");
	}else{
		menor = regexit[0].segundos; // saida com menos passos = 1 posição do registro
		for(i=0; i<nwins; i++){
			if(regexit[i].segundos < menor){
				menor = regexit[i].segundos; // for para procura um menor
			}
		}
		printf("Saida mais proxima: %i segundos\n", menor);
		for(i=0; i<nwins; i++){
			if(regexit[i].segundos == menor){ // caso reg tenha mesmo tempo da menor saida
				printf("\nSaida %c: ", regexit[i].saida); 
				for(j=0; j<menor; j++){
					switch(regexit[i].caminho[j]){ // print do caminho
						case 1:
							printf("c");
						break;
						case 2:
							printf("b");
						break;
						case 3:
							printf("d");
						break;
						case 4:
							printf("e");
						break;
					}
				}
			}
		}
		for(i=0; i<nsaidas; i++){ // print das saidas encontradas no arquivo
			print_saida(nwins, regexit, i, saida);
		}
		printf("\n\nArquivo saida.txt gerado com sucesso!");
	}
	int fclose(FILE *saida); //fecha arquivo saida.txt
	for(i = 0; i < lin; i++){ //libera o espaço alocado na memoria
		free(arena[i]);
	}
	free(arena);
}
