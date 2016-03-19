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
void note(int digitality, int tonote){
	/***********************************
	/Сначала проверяется, включен ли этот светодиод,
	Если да, то продолжаем тянуть ноту
	Если нет, то выключаем прошлый светодиод, включаем наш
	И тянем ноту/
	***********************************/
	if(digit!=digitality){
	    digitalWrite(digit, LOW);
	    digit=digitality;
	    tone(tonePin, tonote, del);
	    digitalWrite(digit, HIGH);
	}
    tone(tonePin, tonote, del);
}
void setup()
{
	for(int i=2; i<10; i++){
	    pinMode(i, OUTPUT);
	}
}
void loop()
{
	switch (analogRead(A1)/45) {
	    case aC4:
	      note(2, NOTE_C4);
	      break;
	    case aD4:
	      note(3, NOTE_D4);
	      break;
	    case aE4:
	      note(4, NOTE_E4);
	      break;
	    case aF4:
	      note(5, NOTE_F4);
	      break;
	    case aG4:
	      note(6, NOTE_G4);
	      break;
	    case aA4:
	      note(7, NOTE_A4);
	      break;
	    case aB4:
	      note(8, NOTE_B4);
          break;
        case aC5:
          note(9, NOTE_C5);
          break;
	    default:
	      digitalWrite(digit, LOW); //выключение светодиода, при отпускании кнопки
		  digit=0;
	}
	delay(del);
}