#define RS PORTDbits.RD4
#define EN PORTDbits.RD6
#define D4 PORTDbits.RD0
#define D5 PORTDbits.RD1
#define D6 PORTDbits.RD2
#define D7 PORTDbits.RD3


void envia_byte(int comando_dado,char palavra)  // comando 0  dado 1
	{
	RS=comando_dado;
	D7=palavra>>7;
	D6=palavra>>6;
	D5=palavra>>5;
	D4=palavra>>4;
	EN=1;
	EN=0;
	D7=palavra>>3;
	D6=palavra>>2;
	D5=palavra>>1;
	D4=palavra;	
	EN=1;
	EN=0;	
	Delay1KTCYx(5);
	}

void escreve_lcd(const rom char *recebe)
	{
	while(*recebe!=0)
		{
		envia_byte(1,*recebe);
		recebe++;
		}	
	}
void escreve(char recebe)
	{
	envia_byte(1,recebe);
	}

void limpa_lcd()
	{
	envia_byte(0,0x01);
	EN=1;
	EN=0;
	Delay1KTCYx(25);
	}

void ini_lcd()
	{
	int z=0;
	RS=0;
	for(z=0;z<3;z++)
		{
		D7=0;
		D6=0;
		D5=1;
		D4=1;
		EN=1;
		EN=0;
		Delay1KTCYx(25);
		}
	D4=0;
	EN=1;
	EN=0;
	Delay1KTCYx(5);
	envia_byte(0,0x28);
	Delay1KTCYx(5);
	envia_byte(0,0x0C);
	Delay1KTCYx(5);	
	limpa_lcd();
	Delay1KTCYx(5);
	envia_byte(0,0x06);
	Delay1KTCYx(5);			
	}	

void xy_lcd(int a,int b)
	{
	if(a==1)
		{
		envia_byte(0,0x80-1+b);  // ou (0,0x7F+b)  variavel->  signed int  ... para valores negativos
		}
	if(a==2)
		{
		envia_byte(0,0xC0-1+b);
		}
	}
void escreve_lcd_bf(char *bf)   // *bf primeira posição que o programa ira buscar o dado, 
	{ 							//	bf++ para deslocar o proximo dado até a ultima posição para
	char w=0;					//	que possa ser feito a leitura dos dados. * (ponteiro)
	while(w<16)								 							
		{
		envia_byte(1,*bf);
		bf++;		
		w++; 			//  w++ para a condição rodar até que rode as 16 posições.
		}
	}
