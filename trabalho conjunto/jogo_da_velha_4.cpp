#include	<stdio.h>
#include	<locale.h>
#include	<stdlib.h>
#include	<string.h>

struct DADOS_RANKING {
	char jogadores[2][30];
	int resultado;
	int rodada;
};

void	limpaTela(void);
void 	inicia_tabuleiro(char *tabuleiro);
void 	exibe_tabuleiro(char *tabuleiro);
void	carregaDados(struct DADOS_RANKING *dados);
void	lerDados(void);
int		checarJogo(char *tabuleiro, char *reset_tabuleiro, int turno);
void 	jogo(struct DADOS_RANKING ranking);
void 	menu_principal(void);


int main(void)
{
    setlocale (LC_ALL, "Portuguese");

    menu_principal();
    
    printf("\nPrograma Encerrado.\n");
    
    return 0;
}

void 	limpaTela(void)
{ 
    system("CLS");
}


void	inicia_tabuleiro(char *tabuleiro)
{ 
    int i;

    for (i = 0; i < 9; i++)
	{
    	*tabuleiro = '-';
    	if (i < 8) {
    		tabuleiro++;
		}
	}
}

void	exibe_tabuleiro(char *tabuleiro)
{ 
	int i;
	
    printf("Mapa de Posicoes:\n 0 | 1 | 2\n 3 | 4 | 5\n 6 | 7 | 8\n\n");
	for (i = 0; i < 9; i++)
	{
    	printf(" %c  ", *tabuleiro);
		if (i < 8) {
    		tabuleiro++;
		}
		if (i == 2 || i == 5) {
			printf("\n");
		}
	}
}

void	carregaDados(struct DADOS_RANKING *dados)
{
	FILE *fp_ranking;
	int i;
	
	fp_ranking = fopen("RANKING.txt", "w");
	for (i=0; i<2; i++) {
		fprintf(fp_ranking, "%s\n", dados->jogadores[i]);
		if(dados->resultado == 1 && i == 0) 
		{
			fprintf(fp_ranking, "%s\n", "Ganhou");
		} 
		else if(dados->resultado == 2 && i== 1) 
		{
			fprintf(fp_ranking, "%s\n", "Ganhou");
		} 
		else if(dados->resultado == 3)
		{
			fprintf(fp_ranking, "%s\n", "Empatou");
		}
		else 
		{
			fprintf(fp_ranking, "%s\n", "Perdeu");
		}
	}
	fprintf(fp_ranking, "%d\n", dados->rodada);
	fclose(fp_ranking);
}

void	lerDados(void)
{
	FILE *fp_ranking;
	char jogador_1[30], jogador_2[30];
	char result_1[9], result_2[9];
	int	num_rodadas;
	
	fp_ranking = fopen("RANKING.txt", "r");
	if(fp_ranking == NULL) {
		printf("Erro ao tentar abrir o arquivo.");
	}
	else {
		fscanf(fp_ranking, "%s\n%s\n%s\n%s\n%d\n", jogador_1, result_1, jogador_2, result_2, &num_rodadas);
		printf("Número de Rodadas: %d\nJogador 1(X): %s \t--> %s \nJogador 2(O): %s \t--> %s \n", num_rodadas, jogador_1, result_1, jogador_2, result_2);
	}
	
	fclose(fp_ranking);
}

int		checarJogo(char *tabuleiro, char *reset_tabuleiro, int turno)
{
	/*
	Retorna (0) se ninguem tiver ganhado ou empatado
	Retorna (1) se o jogador 1 tiver ganhado
	Retorna (2) se o jogador 2 tiver ganhado
	Retorna (3) se empatou
	*/
	int i;
	int qtd_posicoes_restantes=0;
	
	for (i = 0; i < 9; i++)
	{
		if (*tabuleiro == '-') {
			qtd_posicoes_restantes++;
		}
		if (i < 8) {
			tabuleiro++;
		}
	}
	
	tabuleiro = reset_tabuleiro;
	
	//	Checando se ganhou ou empatou
	if (turno == 1) 
	{
		// --- possibilidades horizontais ---
		if(*(tabuleiro) == 'X' && *(tabuleiro+1) == 'X' && *(tabuleiro+2) == 'X') {
			return 1;
		} 
		else if (*(tabuleiro+3) == 'X' && *(tabuleiro+4) == 'X' && *(tabuleiro+5) == 'X') {
			return 1;
		} 
		else if (*(tabuleiro+6) == 'X' && *(tabuleiro+7) == 'X' && *(tabuleiro+8) == 'X') {
			return 1;
		}// --- possibilidade verticais ---
		else if (*(tabuleiro) == 'X' && *(tabuleiro+3) == 'X' && *(tabuleiro+6) == 'X') {
			return 1;
		} 
		else if (*(tabuleiro+1) == 'X' && *(tabuleiro+4) == 'X' && *(tabuleiro+7) == 'X') {
			return 1;
		} 
		else if (*(tabuleiro+2) == 'X' && *(tabuleiro+5) == 'X' && *(tabuleiro+8) == 'X') {
			return 1;
		}// --- possibilidades diagonais ---
		else if (*(tabuleiro) == 'X' && *(tabuleiro+4) == 'X' && *(tabuleiro+8) == 'X') {
			return 1;
		} 
		else if (*(tabuleiro+2) == 'X' && *(tabuleiro+4) == 'X' && *(tabuleiro+6) == 'X') {
			return 1;
		}
		else if (qtd_posicoes_restantes == 0) {		// Empatou
			return 3;
		}
		else {		// ninguem resultado ou empatou nessa rodada
			return 0;
		}
	}
	else
	{
				// --- possibilidades horizontais ---
		if(*(tabuleiro) == 'O' && *(tabuleiro+1) == 'O' && *(tabuleiro+2) == 'O') {
			return 2;
		} 
		else if (*(tabuleiro+3) == 'O' && *(tabuleiro+4) == 'O' && *(tabuleiro+5) == 'O') {
			return 2;
		} 
		else if (*(tabuleiro+6) == 'O' && *(tabuleiro+7) == 'O' && *(tabuleiro+8) == 'O') {
			return 2;
		}// --- possibilidade verticais ---
		else if (*(tabuleiro) == 'O' && *(tabuleiro+3) == 'O' && *(tabuleiro+6) == 'O') {
			return 2;
		} 
		else if (*(tabuleiro+1) == 'O' && *(tabuleiro+4) == 'O' && *(tabuleiro+7) == 'O') {
			return 2;
		} 
		else if (*(tabuleiro+2) == 'O' && *(tabuleiro+5) == 'O' && *(tabuleiro+8) == 'O') {
			return 2;
		}// --- possibilidades diagonais ---
		else if (*(tabuleiro) == 'O' && *(tabuleiro+4) == 'O' && *(tabuleiro+8) == 'O') {
			return 2;
		} 
		else if (*(tabuleiro+2) == 'O' && *(tabuleiro+4) == 'O' && *(tabuleiro+6) == 'O') {
			return 2;
		}
		else if (qtd_posicoes_restantes == 0) {		// Empatou
			return 3;
		}
		else {		// ninguem resultado ou empatou nessa rodada
			return 0; 
		}
	}	
}

void	jogo(struct DADOS_RANKING *ranking)	//onde o jogo fica 
{  	
	char *tabuleiro, *reset_tabuleiro;
	int	posicao_jogada;
	int estadodejogo = 1;
	int checar_jogo;
	int rodada = 1;
	int turno = 0;
	int opcao;
	
	tabuleiro = (char*) malloc(sizeof(char) * 9);
	reset_tabuleiro = tabuleiro;
	ranking->rodada = 1;
	
	inicia_tabuleiro(tabuleiro); 
	
	while(rodada < 10 && estadodejogo == 1 )
	{
		tabuleiro = reset_tabuleiro;	// Resetando o endereço do tabuleiro
		exibe_tabuleiro(tabuleiro); 
		 
		printf("\n\nRodada %d\n\n", ranking->rodada);
		if (turno == 0) {
			printf("-> X");
		}
		else{
			printf("-> O");
		}
			
		printf("\n%s :\nDigite a posição[0-8]\n", ranking->jogadores[turno]);
		scanf("%d", &posicao_jogada);
		fflush(stdin);
		
		if (posicao_jogada >= 0 && posicao_jogada <= 8) {
			tabuleiro += posicao_jogada;	
		}
		else {
			limpaTela();
			printf("----- Erro! Posição INVÁLIDA, digite uma posição válida. -----\n\n");
			continue;
		}
		if (*tabuleiro != '-') {
			limpaTela();
			printf("----- Erro! Posição está OCUPADA, escolha outra posição. -----\n\n");
			continue;
		} 
		else if(turno == 0) {
			limpaTela();
			*tabuleiro = 'X';
			turno++;
		}
		else {
			limpaTela();
			*tabuleiro = 'O';
			turno--;
			ranking->rodada++;
		}
		
		tabuleiro = reset_tabuleiro;	// Resetando o endereço do tabuleiro
		
		checar_jogo = checarJogo(tabuleiro, reset_tabuleiro, turno);
	
		if (checar_jogo == 1) {
			ranking->resultado = 1;
			exibe_tabuleiro(tabuleiro);
			printf("\n\n --- %s ganhou em %d rodadas! ---\n", ranking->jogadores[0], ranking->rodada);
			carregaDados(ranking);
			estadodejogo = 0;
		}
		else if (checar_jogo == 2) {
			ranking->resultado = 2;
			exibe_tabuleiro(tabuleiro);
			printf("\n\n --- %s ganhou em %d rodadas! ---\n", ranking->jogadores[1], ranking->rodada);
			carregaDados(ranking);
			estadodejogo = 0;
		}
		else if (checar_jogo == 3) { 
			ranking->resultado = 3;
			exibe_tabuleiro(tabuleiro);
			printf("\n\n --- Empate! ---\n");
			carregaDados(ranking);
			estadodejogo = 0;
		}
		else {
			estadodejogo = 1;
		}
	}
	free(tabuleiro);
	
	printf("\nFim de jogo\n");
	printf("\nDeseja jogar novamente ?\n[1] - Sim\n[2] - Não\n");
	printf("\nInforme a opção que deseja seguir : ");
	scanf("%d", &opcao);
	if (opcao == 1){
		limpaTela();
		jogo(ranking);
	} else {
		limpaTela();
		menu_principal();
	}
}

void	menu_principal(void)
{
	struct DADOS_RANKING dadosJogo, *ranking;
	int opcao = 0;
	int i;
	int len;
	
	ranking = &dadosJogo;
	
	//menu do jogo
	do
	{
		//limpaTela();
	
		printf("Bem vindo ao jogo da velha\nEscolha uma das opções para prosseguir\n");
	
        printf("\n[1] - Iniciar o jogo\n");
        printf("[2] - Sobre o jogo\n");
        printf("[3] - Créditos\n");
        printf("[4] - Ranking\n");
        printf("[5] - Sair do jogo\n");
	
		printf("\nInforme a opção que deseja seguir : ");
		scanf("%d", &opcao);
		fflush(stdin);
	
		switch(opcao){
			case 1:
				limpaTela();
				printf("\nJogo iniciado!\n\n");
				for (i = 0; i < 2; i++) 
				{
					printf("Informe o nome do Jogador %d: ", i+1);
					fgets(ranking->jogadores[i], 30, stdin);
					
					len = strlen(ranking->jogadores[i]);
					if (ranking->jogadores[i][len -1] == '\n') {
						ranking->jogadores[i][len -1] = 0;		// Removendo o Enter(\n) que o fgets põe
					}
				}
				jogo(ranking);
				break;
			case 2:
				limpaTela();
				printf("\nO jogo da velha ou jogo do galo ou três em linha é um jogo e/ou passatempo popular.\n");
				printf("\n-----------------------------------------------------------------------------------\n");
				printf("\nDeseja voltar para o menu ?\n[1] - Sim\n[2] - Não\n");
				printf("\nInforme a opção que deseja seguir: ");
				scanf("%d", &opcao);
				if (opcao == 1){
					limpaTela();
					menu_principal();
					continue;
				}
				break;
			case 3:
				limpaTela();
				printf("\nFeito por Lucas Lira, João Victor Vargens, Rayan Antonio e Hiago Maciel\n");
				printf("\n-----------------------------------------------------------------------\n");
				printf("\nDeseja voltar para o menu ?\n[1] - Sim\n[2] - Não\n");
				printf("\nInforme a opção que deseja seguir: ");
				scanf("%d", &opcao);
				if (opcao == 1){
					limpaTela();
					menu_principal();
				}
				break;
			case 4:
				limpaTela();
				printf("\n----- Ranking -----\n\n");
				lerDados();
				printf("\nDeseja voltar para o menu ?\n[1] - Sim\n[2] - Não\n");
				printf("\nInforme a opção que deseja seguir: ");
				scanf("%d", &opcao);
				if (opcao == 1){
					limpaTela();
					menu_principal();
				}
				break;
			case 5:
				// Saindo do jogo
				break;
			default:
				limpaTela();
				printf(" --- Opção inválida. ---\n");
		}
	}while(opcao < 1 || opcao > 5);
}
