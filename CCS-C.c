#include <16F877A.h>
#use     delay(clock = 4000000)
#fuses   XT,NOWDT,NOLVP,NOBROWNOUT                
#include <lcd.c>
#include <sensor.c>
#use     rs232(uart1,baud = 9600,ERRORS)
#use     fast_io(d)
#use     fast_io(e)
#priority INT_RDA,INT_TIMER1

/////////DEÐÝSKENLER//////////
char gelen = 0;
int8 timer1_sayac = 0;
int8 isi = 0;
int8 nem = 0;
int8 role1 = 0;
int8 role2 = 0;
int8 role3 = 0;
int8 sayac1 = 0;
int8 sayac2 = 0;
int8 sayac3 = 0;

/////////FONKSÝYONLAR/////////
void setup();
void basla();
void dur();
void lcd_temizle();
void data_al_gonder();
void elle_sicaklik_al();
void elle_kontrol();
void otomatik_kontrol();
void role1_kontrol();
void role2_kontrol();
void role3_kontrol();
void android_baslangic();
void android_sicaklik_al();

/////////KESMELER////////////
#int_rda
void rda_kesme(){
   
   gelen = getch();
   
      if(gelen == 'B')
      {   
         basla();
         data_al_gonder();
      }
      if(gelen == 'K')
      {
         dur();
      }
      if(gelen == 'E')
      {
         disable_interrupts(INT_TIMER1);
         elle_kontrol();
      
      }
      if(gelen == 'O')
      {  
         otomatik_kontrol();
      }
      if(gelen == '1')
      { 
         role1_kontrol();
      }
      if(gelen == '2')
      {
         role2_kontrol();
      }
      if(gelen == '3')
      {
         role3_kontrol();
      }
      if(gelen == '4')
      {
         role1 = 1;
         output_high(PIN_E0);
         sayac1 = 1;
      }
      if(gelen == '5')
      {
         role1 = 0;
         output_low(PIN_E0);
         sayac1 = 0;
      } 
      if(gelen == '6')
      {
         role2 = 1;
         output_high(PIN_E1);
         output_high(PIN_B1);
         sayac2 = 1;
      }
      if(gelen == '7')
      {
         role2 = 0;
         output_low(PIN_E1);
         output_low(PIN_B1);
         sayac2 = 0;
      } 
      if(gelen == '8')
      {
         role3 = 1;
         output_high(PIN_E2);
         sayac3 = 1;
      }
      if(gelen == '9')
      {
         role3 = 0;
         output_low(PIN_E2);
         sayac3 = 0;
      }
      if(gelen == 'A')
      {
         elle_sicaklik_al();
      }
/////////////ANDROÝD/////////////    

      if(gelen == 'C')
      {
         android_baslangic();
      }
      if(gelen == 'D')
      {
         android_sicaklik_al();
      }  
   gelen = 0;
}
#int_timer1
void timer1_kesme()
{

   set_timer1(0);
   timer1_sayac++;
   if(timer1_sayac == 6)
   {

         data_al_gonder();
         timer1_sayac = 0;         
   }
}

void main(){

   setup();
      while(TRUE){
    
      }
}
void setup(){

   setup_adc_ports(NO_ANALOGS);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc(ADC_OFF);
   setup_ccp1(CCP_OFF);
   setup_ccp2(CCP_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   set_tris_d(0x00);
   set_tris_e(0x00);
   set_tris_b(0x00);
   output_d(0x00);
   output_e(0x00);
   output_b(0x00);
   role1 = 0;
   role2 = 0;
   role3 = 0;
   lcd_init();
   dht_start();
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
}
void basla(){
   
   enable_interrupts(INT_TIMER1);
   lcd_putc("  HOSGELDINIZ");
   delay_ms(2000);
   lcd_putc("\f");
  
}
void dur(){
	
   disable_interrupts(INT_TIMER1);
   lcd_putc("\f");
   lcd_putc("    GULE GULE");
   lcd_putc("\n   MIKRO PROJE");
   delay_ms(1500);
   lcd_putc("\f");
   role1 = 0;
   role2 = 0;
   role3 = 0;
   sayac1 = 0;
   sayac2 = 0;
   sayac3 = 0;
   output_e(0x00);

}
void data_al_gonder(){

   take_data();
   delay_us(10);
   isi = degerler[2];
   nem = degerler[0];
   delay_us(10);
   printf("%d",nem);
   printf(" %d",isi);
   lcd_putc("\f");
   printf(lcd_putc,("Nem = %c%d\n"),37,nem);
   printf(lcd_putc,("Sicaklik = %d%cC"),isi,223);
   
}
void elle_kontrol(){
  
   lcd_putc("\f");
   lcd_putc("  ELLE KONTROL");
   delay_ms(1500);
   lcd_putc("\f");
   lcd_putc("1.R    2.R   3.R");
   printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
   
}
void otomatik_kontrol(){

   printf("R%d %d %d",role1,role2,role3);
   lcd_putc("\f");
   lcd_putc("OTOMATIK KONTROL");
   delay_ms(1500);
   data_al_gonder();
   enable_interrupts(INT_TIMER1);
     
}
void role1_kontrol(){
      
      sayac1++;
      if(sayac1%2 == 1 )
      {
         role1 = 1;
         lcd_putc("\f");
         lcd_putc("1.R    2.R   3.R");
         printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
         output_high(PIN_E0);
      }              
      else if(sayac1%2 == 0 )
      {
         role1 = 0;
         lcd_putc("\f");
         lcd_putc("1.R    2.R   3.R");
         printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
         output_low(PIN_E0);               
      }
      
}
void role2_kontrol(){

   sayac2++;
      if(sayac2%2 == 1 )
      {
         role2 = 1;
         lcd_putc("\f");
         lcd_putc("1.R    2.R   3.R");
         printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
         output_high(PIN_E1);
         output_high(PIN_B1);
      }              
      else if(sayac2%2 == 0 )
      {
         role2 = 0;
         lcd_putc("\f");
         lcd_putc("1.R    2.R   3.R");
         printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
         output_low(PIN_E1);
         output_low(PIN_B1);
      }
}
void role3_kontrol(){
   
   sayac3++;
      if(sayac3%2 == 1 )
      {
         role3 = 1;
         lcd_putc("\f");
         lcd_putc("1.R    2.R   3.R");
         printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
         output_high(PIN_E2);
      }              
      else if(sayac3%2 == 0 )
      {
         role3 = 0;
         lcd_putc("\f");
         lcd_putc("1.R    2.R   3.R");
         printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);
         output_low(PIN_E2);
      }
}
void elle_sicaklik_al(){

   take_data();
   printf("%d %d",degerler[0],degerler[2]);

}

void android_baslangic(){
   
   setup();
   lcd_putc("\f  HOSGELDINIZ");
   lcd_putc("  Android Mod");
   delay_ms(1500);
   lcd_putc("\f1.R    2.R   3.R");
   printf(lcd_putc,("\n-%d-    -%d-   -%d-"),role1,role2,role3);

   
}

void android_sicaklik_al(){
   
   elle_sicaklik_al();
   
}









