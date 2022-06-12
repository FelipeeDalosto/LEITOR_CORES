// Descrição da aplicação:
/* Programa TCC Leitor de Cores   */
// Incluir bibliotecas de funções que serão usadas no programa
#include <p18f4520.h>  //biblioteca padrão do MPLAB
#include <delays.h> //biblioteca padrão do MPLAB, para funções de atraso
#include "LCD4bits.h" //biblioteca com funções para display de LCD (Prof. Josemi)
#include <stdio.h> //biblioteca com funções de saídas de dados (ex.:sprintf)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configurar o PIC conforme as aplicações do programa:
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config PWRT=ON
#pragma config BOREN=ON
#pragma config BORV=1
#pragma config PBADEN=OFF
#pragma config LVP=OFF
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definir nomes para pinos de entrada e saída e para comandos (facilita a escrita do programa e montagem do circuito):
#define s0 PORTBbits.RB0 // Dá um nome para o bit RBO (Pino que define a frequencia do sensor)
#define s1 PORTBbits.RB1 // Dá um nome para o bit RB1 (Pino que define a frequencia do sensor)
#define s2 PORTBbits.RB2 // Dá um nome para o bit RB2 (Pino que define a cor que sera lida pelo sensor)
#define s3 PORTBbits.RB3 // Dá um nome para o bit RB3 (Pino que define a cor que sera lida pelo sensor)
#define led PORTBbits.RB5 // Dá um nome para o bit RB5 (Vcc do led do sensor)
#define out PORTBbits.RB4 // Dá um nome para o bit RB4 (Pino que recebe a saida com a frequencia da cor do sensor)
#define led1 PORTCbits.RC0 // Liga o led1 que identificara a cor azul
#define led2 PORTCbits.RC1 // Liga o led1 que identificara a cor vermelho
#define led3 PORTCbits.RC2 // Liga o led1 que identificara a cor verde
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definir nomes para pinos de entrada e saída e para comandos (facilita a escrita do programa e montagem do circuito):
////// Definidos em "LCD4bits.h":
	// D4 PORTDbits.RD0
	// D5 PORTDbits.RD1
	// D6 PORTDbits.RD2
	// D7 PORTDbits.RD3
	// RS PORTDbits.RD4 // RS: Register Select: 0: instrução; 1: dado;
	// EN PORTDbits.RD6 // EN: Enable: 0: Desabilita; 1: habilita; para gravar nos registradores de dado ou de intrução
	// RW ligado em VSS(Gnd) // RW: Read/Write: 0: escrita; 1: leitura; ficará somente como leitura pela ligação no VSS (GND)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definir as variaveis do programa:
long vermelho= 0;
long verde= 0;
long azul= 0;
long semFiltro=0;
long corm= 0;
int cor=0;
int frequencia=0;
float branco_vermelho=0,branco_verde=0,branco_azul=0;
float porc_vermelho=0, porc_verde=0, porc_azul=0;
long cont =0;
unsigned char display[16];
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definir as funções das rotinas do programa:
void setup()
{
//Configuração frequencia igual a 2%
if (frequencia == 2){
	s0=0;
	s1=1;		
}
//Configuração frequencia igual a 20%
if (frequencia == 20){
	s0=1;
	s1=0;		
}
//Configuração frequencia igual a 100%
if (frequencia == 100){
	s0=1;
	s1=1;	
}
//Liga o led do sensor
	led=1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void leVermelho(){
//Define os pinos s2 e s4 para ler a cor vermelha
	s2=0;
	s3=0;
//Verefica a cor vermelha
vermelho=0;
if(out==0){
	while(out==0){
	vermelho++;
	}
	while(out==1){
	vermelho++;
	}
}
if(vermelho>3000){
cor=1;
}
//vermelho=cont*0.000002;
//Delay10KTCYx(100);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void leVerde(){
//Define os pinos s2 e s4 para ler a cor verde
	s2=1;
	s3=1;
//Verefica a cor verde
verde=0;
if(out==0){
	while(out==0){
	verde++;
	}
	while(out==1){
	verde++;
	}
}
if(verde>4800){
cor=2;
}
//verde=cont*0.000002;
//Delay10KTCYx(100);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void leAzul(){
//Define os pinos s2 e s4 para ler a cor azul
	s2=1;
	s3=0;
//Verefica a cor azul
azul=0;
if(out==0){
	while(out==0){
	azul++;
	}
	while(out==1){
	azul++;
	}
}
if(azul<900){
cor=3;
}
//azul=cont*0.000002;
//Delay10KTCYx(100);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void leitura(){
//corm=(verde+azul+vermelho);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void aciona_lcd(void){
sprintf (display,"valor     %06lu",vermelho);
if(cor==1){
xy_lcd(1,1);
escreve_lcd("azul            ");
led1=0;
led2=0;
led3=1;
}
if(cor==2){
xy_lcd(1,1);
escreve_lcd("vermelho        ");
led1=1;
led2=0;
led3=0;
}
if(cor==3){
xy_lcd(1,1);
escreve_lcd("verde           ");
led1=0;
led2=1;
led3=0;
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostra_cor()
{
aciona_lcd();//carrega o buffer display
xy_lcd(2,1); //coloca o cursor na linha 2 e coluna 1.
escreve_lcd_bf(display); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define a função principal
void main (void)
{
ADCON1=0X0F;
//configuração dos periféricos:
TRISA=0b11111111; // todos os pinos do portA como entrada;
TRISB=0b00010000; //RB0 a RB3 como entrada e RB4 a RB7 como saída (configuração validas para todas as aplicações)
TRISC=0b00000000; //todos como saída (configuração validas para todas as aplicações)
TRISD=0b00000000; //todos como saída (configuração validas para todas as aplicações)
TRISE=0b00000000;  //todos como saída (configuração validas para todas as aplicações)
limpa_lcd();
//valores iniciais das variáveis e ports:
//looping do programa:
PORTC=0;
PORTD=0;
PORTE=0;
frequencia=2;
ini_lcd();
while (1)
{
setup();
leVermelho();
leVerde();
leAzul();
leitura();
mostra_cor();
Delay10TCYx(100);
}
} 