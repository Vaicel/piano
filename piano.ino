/******************
Code made by Vaicel. 2016.
******************/

#define NOTE_C4  262   //Дефайны нот
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define aC4 9		   //Дефайны значений кнопок, получаемые через аналоговый вход
#define aD4 8
#define aE4 7
#define aF4 6
#define aG4 5
#define aA4 4
#define aB4 3
#define aC5 1
#define tonePin 10
#define del 100
int digit;             //Включенный светодиод
void setup()
{
	for(int i=2; i<10; i++){
	    pinMode(i, OUTPUT);
	}
}
void loop()
{
	/***********************************
	Далее программа состит из одинаковых блоков:
	/Сначала проверяется, включен ли этот светодиод,
	Если да, то продолжаем тянуть ноту
	Если нет, то выключаем прошлый светодиод, включаем наш
	И тянем ноту/
	***********************************/
	if(analogRead(A1)/45==aC4){
		if(digit!=2){
		   digitalWrite(digit, LOW);
		   digit=2;
	       tone(tonePin, NOTE_C4, del);
	       digitalWrite(digit, HIGH);
		}
        tone(tonePin, NOTE_C4, del);
	}
	else if(analogRead(A1)/45==aD4){
		if(digit!=3){
		   digitalWrite(digit, LOW);
		   digit=3;
	       tone(tonePin, NOTE_D4, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_D4, del);
	}
	else if(analogRead(A1)/45==aE4){
		if(digit!=4){
		   digitalWrite(digit, LOW);
	       digit=4;
	       tone(tonePin, NOTE_E4, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_E4, del);
	}
	else if(analogRead(A1)/45==aF4){
		if(digit!=5){
		   digitalWrite(digit, LOW);
	       digit=5;
	       tone(tonePin, NOTE_F4, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_F4, del);
	}
	else if(analogRead(A1)/45==aG4){
		if(digit!=6){
		   digitalWrite(digit, LOW);
	       digit=6;
	       tone(tonePin, NOTE_G4, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_G4, del);
	}
	else if(analogRead(A1)/45==aA4){
		if(digit!=7){
		   digitalWrite(digit, LOW);
	       digit=7;
	       tone(tonePin, NOTE_A4, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_A4, del);
	}
	else if(analogRead(A1)/45==aB4){
		if(digit!=8){
		   digitalWrite(digit, LOW);
	       digit=8;
	       tone(tonePin, NOTE_B4, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_B4, del);
	}
	else if(analogRead(A1)/45==aC5){
		if(digit!=9){
		   digitalWrite(digit, LOW);
	       digit=9;
	       tone(tonePin, NOTE_C5, del);
	       digitalWrite(digit, HIGH);
	    }
	    tone(tonePin, NOTE_C5, del);
	}
	else{
		digitalWrite(digit, LOW); //выключение светодиода, при отпускании кнопки
		digit=0;
	}
	delay(del);
}