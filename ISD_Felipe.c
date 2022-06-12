#include <p18f4520.h>
#include <delays.h>
#include <stdio.h>// Necessario para manipular saídas de dados
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config PWRT=ON
#pragma config BOREN=ON
#pragma config BORV=1
#pragma config PBADEN=OFF
#pragma config LVP=OFF
/* Este programa coloca um número de dois bits em dois displays de 7 segmentos*/

#define unidade PORTBbits.RB0
#define dezena PORTBbits.RB1

unsigned char mat[2];
int t=10;

void escreve_dezena (void)
{
//Conecta o display da dezena no barramento de dados
	dezena=1;
	unidade=0;

	switch (mat[2,0]) //Coloca o código de 7 seg. para o número da dezena
	{

		case 48:
			PORTD=0b11000000;
			break;
		case 49:
			PORTD=0b11111001;
			break;
		case 50:
			PORTD=0b10100100;
			break;
		case 51:
			PORTD=0b10110000;
			break;
		case 52:
			PORTD=0b10011001;
			break;
		case 53:
			PORTD=0b10010010;
			break;
		case 54:
			PORTD=0b10000011;
			break;
		case 55:
			PORTD=0b11111000;
			break;
		case 56:
			PORTD=0b10000000;
			break;
		case 57:
			PORTD=0b10011000;
			break;
		case 32:
			PORTD=0b11111111;
			break;

			
	}
}
void escreve_unidade (void)
{
//Conecta o display da unidade no barramento de dados
	dezena=0;
	unidade=1;

switch (mat[2,1]) //Coloca o código de 7 seg. para o número da unidade
	{
		case 48:
			PORTD=0b11000000;
			break;
		case 49:
			PORTD=0b11111001;
			break;
		case 50:
			PORTD=0b10100100;
			break;
		case 51:
			PORTD=0b10110000;
			break;
		case 52:
			PORTD=0b10011001;
			break;
		case 53:
			PORTD=0b10010010;
			break;
		case 54:
			PORTD=0b10000011;
			break;
		case 55:
			PORTD=0b11111000;
			break;
		case 56:
			PORTD=0b10000000;
			break;
		case 57:
			PORTD=0b10011000;
			break;
		case 32:
			PORTD=0b11111111;
			break;
}
}


void main()
{
TRISB=0b11111100;//apenas os bits RB0 e RB1 como saída.
TRISD=0b00000000;//todos os pinos do portC definidos como saída.
PORTD=0b00000000;
dezena=0;
unidade=0;
t=7;
sprintf (mat,"%2i",t);//o número "t" inteiro é formatado e carregado

while(1)
{
escreve_dezena();
Delay10KTCYx(5); //Esperar o tempo de 10ms para não piscar o display
dezena=0; //desliga o display

escreve_unidade();
Delay10KTCYx(5); //Esperar o tempo de 10ms para não piscar o display
unidade=0; //desliga o display

// Esta seção carrega um número de dois digitos na matriz

}

}