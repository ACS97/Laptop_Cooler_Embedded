#include <laptop_cooler.h>   //Proje header
//LCD Konfig�rasyon
#define LCD_ENABLE_PIN PIN_C2
#define LCD_RS_PIN PIN_C0
#define LCD_RW_PIN PIN_C1
#define LCD_DATA4 PIN_C4
#define LCD_DATA5 PIN_C5
#define LCD_DATA6 PIN_C6
#define LCD_DATA7 PIN_C7
#include <lcd.c>

//Buton Konfig�rasyon
int buton=0;
void Buton_Say()
{
   if(input(pin_b0)==1)
   {
    buton++;
    delay_ms(200);
   }
}
//S�cakl�k De�eri Okuma
float VREF_VAL=5.0F;
float RESOLUTION_VAL=1024.0F;
void Sicaklik_Degeri()
{
   set_adc_channel(0);
   delay_us(50);
   float sensor = (float)read_adc();
   float Sicaklik = (sensor*(VREF_VAL/RESOLUTION_VAL)*100.0F)/64.0F;
   //LCD Ekrana Yazma
   printf(lcd_putc,"\f Mode: %d \n Sicaklik:%f C",buton,Sicaklik);
   delay_ms(40); 
  if (Sicaklik>80.0F && Sicaklik<90.0F)
  {
   output_high(pin_d1);
  }
  else if(Sicaklik>90.0F)
  {
  output_high(pin_d3);
  }
  else if(Sicaklik<80.0F)
  {
   output_low(pin_d1);
   output_low(pin_d3);
  }
}
//ana program ak�s�
void main()
{   
   //Anologtan Dijitale �evrim Konfig�rasyonu
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   //Port �nput Outuput Konfig�rasyonu
   set_tris_b(0b11111111);
   set_tris_d(0b00000000);
   //LCD �nitialize
   lcd_init();
   //Program D�ng�s�
   for (;;)
   {  
      Sicaklik_Degeri();
      if(buton==0)
      {
       output_low(pin_d0);
       output_low(pin_d2);
       Buton_Say();
       Sicaklik_Degeri();
      }
      else if(buton==1)
      {
       output_high(pin_d0);
       output_low(pin_d2);
       Buton_Say();
       Sicaklik_Degeri();
      }
      else if(buton==2)
      {
       output_high(pin_d0);          
       output_high(pin_d2);
       Buton_Say();
       Sicaklik_Degeri();
      }
      else if(buton==3)
      {
       buton=0; 
      }
   }

}
