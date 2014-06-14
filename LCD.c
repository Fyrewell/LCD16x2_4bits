/*
SANTA CRUZ DO SUL - RS
Autor: Diego Cardoso
Design in CCS
*/
//------------------------//
//CONFIGURACOES DO PIC
//------------------------//
#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES XT                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected

#use delay(clock=4000000)
//------------------------------//
//DEFINICAO DE ATALHOS UTILIZADOS
//-----------------------------//
#define rs pin_b0
#define en pin_b1

//-----------------------------//
//CABECALHOS DE FUNCOES PARA SIMPLIFICACAO
//-----------------------------//
void lcd_comandos(unsigned int8 dado);
void lcd_dados(unsigned int8 dado);
void lcd_inicia(void);

//------------------------------//
//VARIAVEIS CUNHO GLOBAL
//-----------------------------//
   
void main()
{
//------------------------//
//CONFIGURACOES UTILIZADAS
//-----------------------//
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_inicia();
   lcd_comandos(0x40);    //GRAU! (°)
   lcd_dados(0b00000110);
   lcd_dados(0b00001001);
   lcd_dados(0b00001001);
   lcd_dados(0b00000110);
   lcd_dados(0b00000000);
   lcd_dados(0b00000000);
   lcd_dados(0b00000000);
   lcd_dados(0b00000000); //linha cursor
   lcd_comandos(0x01);
   
while(TRUE){
   printf(lcd_dados,"%c",0x00);
}
}

//------------------------------//
//FUNCOES PARA SIMPLIFICACAO
//-----------------------------//

void lcd_comandos(unsigned int8 dado){     //HABILITA COMANDO
   output_low(rs);
   if (bit_test(dado,7)==0){
      output_low(pin_d7);
   }else
      output_high(pin_d7);
   if (bit_test(dado,6)==0){
      output_low(pin_d6);
   }else
      output_high(pin_d6);
   if (bit_test(dado,5)==0){
      output_low(pin_d5);
   }else
      output_high(pin_d5);
   if (bit_test(dado,4)==0){
      output_low(pin_d4);
   }else
      output_high(pin_d4);
   
   output_high(en);
   output_low(en);
   
   if (bit_test(dado,3)==0){
      output_low(pin_d7);
   }else
      output_high(pin_d7);
   if (bit_test(dado,2)==0){
      output_low(pin_d6);
   }else
      output_high(pin_d6);
   if (bit_test(dado,1)==0){
      output_low(pin_d5);
   }else
      output_high(pin_d5);
   if (bit_test(dado,0)==0){
      output_low(pin_d4);
   }else
      output_high(pin_d4);
      
   output_high(en);
   output_low(en);
   delay_ms(2);
}

void lcd_dados(unsigned int8 dado){     //HABILITA A ESCRITA
   output_high(rs);
   
   if (bit_test(dado,7)==0){
      output_low(pin_d7);
   }else
      output_high(pin_d7);
   if (bit_test(dado,6)==0){
      output_low(pin_d6);
   }else
      output_high(pin_d6);
   if (bit_test(dado,5)==0){
      output_low(pin_d5);
   }else
      output_high(pin_d5);
   if (bit_test(dado,4)==0){
      output_low(pin_d4);
   }else
      output_high(pin_d4);
   
   output_high(en);
   output_low(en);
   
   if (bit_test(dado,3)==0){
      output_low(pin_d7);
   }else
      output_high(pin_d7);
   if (bit_test(dado,2)==0){
      output_low(pin_d6);
   }else
      output_high(pin_d6);
   if (bit_test(dado,1)==0){
      output_low(pin_d5);
   }else
      output_high(pin_d5);
   if (bit_test(dado,0)==0){
      output_low(pin_d4);
   }else
      output_high(pin_d4);
      
   output_high(en);
   output_low(en);
}

void lcd_inicia(void){     //INICIA LCD
   output_low(RS);
   delay_ms(15);  //tempo de "power on"
   output_high(pin_d4);
   output_high(pin_d5);
   output_high(en);  //etapa1
   output_low(en);
   delay_ms(5);
   output_high(en);  //etapa2
   output_low(en);
   delay_us(100);
   
   lcd_comandos(0x2);      //INTERFACE 4BITS
   lcd_comandos(0x28);     //DEFINE TAMANHO DO DISPLAY
   lcd_comandos(0x06);     //DEFINE TIPO DE ESCRITA
   lcd_comandos(0x0c);     //DESATIVA CURSOR
   lcd_comandos(0x01);    //LIMPA TELA
   delay_ms(2);
}

