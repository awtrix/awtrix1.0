#include <AwtrixSound.h>
#include <Arduino.h>

#define c1 261     	
#define d1 294    	
#define e1 329     	
#define f1 349     	
#define g1 392     	
#define a1 440     	
#define b1 493    
#define c2 523    
#define P 0

int BUZZER= D3;

int melodie[]={e1,a1,P,a1,g1,a1,e1};
int dauer[] ={300,200,300,300,300,300,200};

void spiele_Melodie(){  
 
  for(int i=0; i<sizeof(melodie)/2;i++){
 
    if (melodie[i]!=P) tone(BUZZER, melodie[i]);
    delay(dauer[i]);
    noTone(BUZZER);}
 
}

void AwtrixSound::setup(){
    pinMode(BUZZER,OUTPUT);
    playMelody();
}

void AwtrixSound::playMelody() {
   
   spiele_Melodie();

}

