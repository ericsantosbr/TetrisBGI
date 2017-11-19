/*
main.cpp

	**************************************************************************************************************************
	* Projeto de TETRIS desenvolvido usando a biblioteca BGI, como parte de um teste para a matéria de Programação II,       *
	* ministrada pelo professor Luis Sergio Banin, no curso de Jogos Digitas da Fatec São Caetano do Sul.                    *
	**************************************************************************************************************************

INFOS IMPORTANTES:
	* Por conta de erros de compatibilidade da BGI, foi padronizado o uso de imagens padrao .gif, ao inves de .bmp como recomendado
	pelo professor Banin, apesar da unica imagem usada com padrao bitmap ser a mascara das imagens!
	
	* Por conta do comeco de minha pratica com documentacao, talvez a documetnacao desse jogo fique meio confusa, por favor,
	releve!
	
	* Apenas por informacao de contagem, enquanto esse comentario e escrito, o codigo esta com cerca de 300 linhas, mas no codigo que
	tenho em mente no momento, sao esperadas cerca de 1000 linhas ainda para vir! Estou um tanto empolgado com esse projeto! :)
	
	* O codigo e livre para ser baixado, modificado e usado, mas espero apenas o bom senso de quem o fizer de citar a fonte
	
	* Partes do codigos que estejam precedidas com um comentario que comece com "TESTE" devem ser cortadas do programa antes de se
	finalizar, ja que como o nome ja diz, sao apenas testes
	

Desenvolvedor:
	Eric Santos
	E-mail: ericsantosbr2@gmail.com
	GitHub: https://github.com/ericsantosbr

TODO: 
		* Trabalho com Hashes para facilitar a transmissão de texto entre servidor-cliente
		* Definir funcao de controle de blocos
		* Separar o jogo por "fases", estruturando por funcoes, sendo algumas de exemplo:
			- Tela Principal: Tela de selecao de fases, configuracoes de jogo, selecao de lingua, creditos e sair
			- Principal: O modo de jogo tradicional, incluindo, antes do inicio desta, uma tela de selecao de dificuldade
			- Multiplayer: Nesse caso, configurar os soquetes de conexao, efetivamente realizar a conexao e colocar o jogo pra rodar
		* Dentro da parte multiplayer do jogo, definir como o jogo vai se comportar quanto a transferencia de dados
      
DONE:
		Definir os if's que desenham as cores dos blocos no laco principal

*/

#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>

using namespace std;

enum cores{
	azul_claro = 0,
	verde_claro,
	verde_escuro,
	vermelho,
	azul_escuro,
	rosa,
	laranja,
	amarelo,
	roxo
};

struct bloco {
	int cor;
};

struct linha {
	int x1, y1, x2, y2;
};

struct ponto{
	int x, y;
};

struct manipulado{
	int x, y, cor;
};
// LinhasxColunas com índice 0
struct bloco blocos[20][10];

// Blocos em si, "puxados" pela funcao associa
void *b_azul_claro, *b_amarelo, *b_vermelho, *b_azul_escuro, *b_verde_claro, *b_verde_escuro, *b_roxo, *b_rosa, *b_laranja, *mascara;


// Tamanho Padrao das Imagens
int tam;

// Tamanho padrao dos lados dos blocos
int passo;

void associa();
void inicial();
void single();
int checacampo();
void quebra(int linha);
// TESTE: Funcao para testes
void teste();

int main(){
	// Fase de declaração de variáveis e structs usadas em jogo
	int i, j, x1, y1, x2, y2, mantem, page;
	passo = 26;
	char tecla = '1';
	struct manipulado manipulados[4];
	
	initwindow(900, 600, "Tetris BGI");
	printf("%d", getactivepage());
	
	// Passa os blocos do HD para a RAM
	associa();
	
	// Limpeza de blocos (fase de testes)
	printf("\nLimpeza de blocos\n");
	for(i = 0; i < 20; i++){
		for(j = 0; j < 10; j++){
			blocos[i][j].cor = azul_claro;
		}
	}
	
	// TESTE: alguns blocos configurados para testar apenas! :)
	teste();

	
	// Tela inicial do jogo
	// TESTE: Descomentar linha a seguir
	inicial();
	
	// Loop principal
	// Desenho do campo com base na matriz campos
	struct ponto origem;
	struct ponto ponto1;
	
	single();
	
//	setactivepage(0);
//	while(tecla == '1'){
//		if(GetKeyState(VK_ESCAPE) & 0x80) tecla = '0';
//		if(getactivepage() == 0) setactivepage(1);
//		else setactivepage(0);
//		cleardevice();
//		
//		// Desenha fundo
//		setfillstyle(1, BLACK);
//		bar(0, 0, getmaxx(), getmaxy());
//		
//		// Informações de pontos, próxima peça, etc
//		setcolor(WHITE);
//		outtextxy(10, 10, "Pontos");
//		
//		ponto1.x = (getmaxx() / 2) - ((passo / 2) + (passo * 5));
//		ponto1.y = 45;
//		origem = ponto1;
//		for(i = 0; i < 20; i++){
//			for(j = 0; j < 10; j++){
//				// Condicionais para identificar cor dos blocos e imprimí-los
//				if(blocos[i][j].cor == azul_claro){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_azul_claro, OR_PUT);
//				}
//				else if(blocos[i][j].cor == amarelo){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_amarelo, OR_PUT);
//				}
//				else if(blocos[i][j].cor == vermelho){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_vermelho, OR_PUT);
//				}
//				else if(blocos[i][j].cor == azul_escuro){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_azul_escuro, OR_PUT);
//				}
//				else if(blocos[i][j].cor == verde_claro){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_verde_claro, OR_PUT);
//				}
//				else if(blocos[i][j].cor == verde_escuro){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_verde_escuro, OR_PUT);
//				}
//				else if(blocos[i][j].cor == roxo){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_roxo, OR_PUT);
//				}
//				else if(blocos[i][j].cor == rosa){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_rosa, OR_PUT);
//				}
//				else if(blocos[i][j].cor == laranja){
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
//					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_laranja, OR_PUT);
//				}
//				// Imprime a grade
//				setcolor(BLACK);
//				rectangle(ponto1.x - (passo / 2), ponto1.y - (passo / 2), ponto1.x + (passo / 2), ponto1.y + (passo / 2));
//				ponto1.x = ponto1.x + passo;
//			}
//			ponto1.x = origem.x;
//			ponto1.y = ponto1.y + passo;
//		}
//		ponto1 = origem;
//		
//		// Controle de movimentação dos blocos, posição e colisão
//
//		if(checacampo() != -1){
//			quebra(checacampo());
//		}
//		
//		if(getactivepage() == 0) setvisualpage(0);
//		else setvisualpage(1);
//	}
	closegraph();
	return 0;
}

// Associa os blocos com as imagens

void associa(){
	// Declaração e associação dos tijolinhos
	setactivepage(3);
	tam = imagesize(0, 0, passo, passo);
	mascara = malloc(tam);
	readimagefile("Mascara.bmp", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, mascara);
	
	b_azul_claro = malloc(tam);
	readimagefile("Bloco Azul Claro.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_azul_claro);
	
	b_amarelo = malloc(tam);
	readimagefile("Bloco Amarelo.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_amarelo);
	
	b_vermelho = malloc(tam);
	readimagefile("Bloco Vermelho.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_vermelho);
	
	b_azul_escuro = malloc(tam);
	readimagefile("Bloco Azul Escuro.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_azul_escuro);
	
	b_verde_claro = malloc(tam);
	readimagefile("Bloco Verde Claro.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_verde_claro);
	
	b_verde_escuro = malloc(tam);
	readimagefile("Bloco Verde Escuro.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_verde_escuro);
	
	b_roxo = malloc(tam);
	readimagefile("Bloco Roxo.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_roxo);
	
	b_rosa = malloc(tam);
	readimagefile("Bloco Rosa.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_rosa);
	
	b_laranja = malloc(tam);
	readimagefile("Bloco Laranja.gif", 0, 0, passo, passo);
	getimage(0, 0, passo - 1, passo - 1, b_laranja);
	
	tam = imagesize(0, 0, 500, 100);
}

void inicial(){
	// Controle do While
	int rolando = 1;
	int contador, passo;
	unsigned int diferenca;
	struct ponto posicao;
	posicao.x = getmaxx() / 2;
	posicao.y = -30;
	contador = 6;
	passo = 1;
	
	// Logo descendo
	diferenca = clock();
	printf("%d", posicao.y);
	while(rolando == 1){
		if(getactivepage() == 0) setactivepage(1);
		else setactivepage(0);
		cleardevice();
		
		
		if(clock() - diferenca >= contador && posicao.y < (getmaxy() / 2)){
			posicao.y += passo;
			printf("\n%d", posicao.y);
			diferenca = clock();
		}
		if(posicao.y >= (getmaxy() / 2)){
			rolando = 0;
		}
		
		
		if(getactivepage() == 0) setvisualpage(0);
		else setvisualpage(1);
	}
	
	printf("\n\n%d", posicao.y);
	
	delay(2000);
	
	// Tela de "licensas" e desenvolvedores
	
}

void single(){
	int i, j, k;
	char tecla = '1';
	// Desenho do campo com base na matriz campos
	struct ponto origem;
	struct ponto ponto1;
	
	// Loop principal
	setactivepage(0);	
	while(tecla == '1'){
		if(GetKeyState(VK_ESCAPE) & 0x80) tecla = '0';
		if(getactivepage() == 0) setactivepage(1);
		else setactivepage(0);
		cleardevice();
				
		// Informações de pontos, próxima peça, etc
		setcolor(WHITE);
		outtextxy(10, 10, "Pontos");
		
		ponto1.x = (getmaxx() / 2) - ((passo / 2) + (passo * 5));
		ponto1.y = 45;
		origem = ponto1;
		for(i = 0; i < 20; i++){
			for(j = 0; j < 10; j++){
				// Condicionais para identificar cor dos blocos e imprimí-los
				if(blocos[i][j].cor == azul_claro){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_azul_claro, OR_PUT);
				}
				else if(blocos[i][j].cor == amarelo){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_amarelo, OR_PUT);
				}
				else if(blocos[i][j].cor == vermelho){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_vermelho, OR_PUT);
				}
				else if(blocos[i][j].cor == azul_escuro){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_azul_escuro, OR_PUT);
				}
				else if(blocos[i][j].cor == verde_claro){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_verde_claro, OR_PUT);
				}
				else if(blocos[i][j].cor == verde_escuro){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_verde_escuro, OR_PUT);
				}
				else if(blocos[i][j].cor == roxo){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_roxo, OR_PUT);
				}
				else if(blocos[i][j].cor == rosa){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_rosa, OR_PUT);
				}
				else if(blocos[i][j].cor == laranja){
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  mascara, AND_PUT);
					putimage(ponto1.x - (passo / 2), ponto1.y - (passo / 2),  b_laranja, OR_PUT);
				}
				// Imprime a grade
				setcolor(BLACK);
				rectangle(ponto1.x - (passo / 2), ponto1.y - (passo / 2), ponto1.x + (passo / 2), ponto1.y + (passo / 2));
				ponto1.x = ponto1.x + passo;
			}
			ponto1.x = origem.x;
			ponto1.y = ponto1.y + passo;
		}
		ponto1 = origem;
		
		// Controle de movimentação dos blocos, posição e colisão

		if(checacampo() != -1){
			quebra(checacampo());
		}
		
		if(getactivepage() == 0) setvisualpage(0);
		else setvisualpage(1);
	}
}

// TODO Checa uma linha, caso a linha esteja COMPLETAMENTE preenchida com blocos
// que não sejam azuis, retorna a linha preenchida pro main quebrar
// Retorna -1 caso não hajam linhas para serem quebradas

int checacampo(){
	int i, j, cont;
	cont = 0;
	for(i = 0; i < 20; i++){
		for(j = 0; j < 10; j++){
			if(blocos[i][j].cor != azul_claro){
				cont++;
			}
		}
		if(cont == 10){
			return i;
		}
		cont = 0;
	}
	return -1;
}

void quebra(int linha){
	int i, j, k, cont;
	printf("\nLinha eliminada: %d", linha);
	for(i = linha; i > 0; i--){
		for(j = 0; j < 10; j++){
				blocos[i][j].cor = blocos[i - 1][j].cor;
		}
		for(k = 0; k < 10; k++){
			blocos[0][k].cor = azul_claro;
		}
	}
}

void teste(){
	int i, j, k;
	
	// TESTE: Cria linha de blocos
	int teste = laranja;
	for(i = 3; i < 10; i++){
		blocos[15][i].cor = teste;
	}
	for(i = 1; i < 9; i++){
		blocos[17][i].cor = teste;
	}
	for(i = 2; i < 9; i++){
		blocos[18][i].cor = teste;
	}
	for(i = 2; i < 8; i++){
		blocos[16][i].cor = teste;
	}
	for(i = 0; i < 10; i++){
		blocos[19][i].cor = teste;
	}
}
