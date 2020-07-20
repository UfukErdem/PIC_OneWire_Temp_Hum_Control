unsigned char degerler[5]= {0};

void dht_start(){

   output_float(PIN_A0);
   restart_wdt();
   delay_ms(1000);
   
}
unsigned char get_byte(){
   
   unsigned char s = 0; 
   unsigned char value = 0; 

   for(s = 0; s < 8; s += 1) 
   { 
      value <<= 1;
      restart_wdt();
      while(!input(PIN_A0));
      restart_wdt();
      delay_us(30); 

      if(input(PIN_A0)) 
      { 
          value |= 1; 
      } 
      while(input(PIN_A0)); 
   } 
   return value;
}

unsigned char  take_data(){

   short chk = 0; 
   unsigned char s = 0; 

   output_high(PIN_A0); 
   output_low(PIN_A0); 
   delay_ms(18); 
   output_high(PIN_A0); 
   delay_us(26); 
    
   chk = input(PIN_A0); 
   if(chk) 
   { 
      return 1; 
   }
   restart_wdt();
   delay_us(80); 
    
   chk = input(PIN_A0); 
   if(!chk) 
   { 
      return 2; 
   } 
   delay_us(80); 
   restart_wdt();
   for(s = 0; s <= 4; s += 1) 
   { 
       degerler[s] = get_byte(); 
   } 
  
   output_high(PIN_A0); 
}

unsigned char check_sum(){

   unsigned char sum = 0;
   
   for(int i=0; i<=3; i++){
   
      sum += degerler[i];
      
   
   }  
   if(sum == degerler[4]){
   return 1;}
   else{
   return 0;}
}
