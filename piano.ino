/******************
Code made by Vaicel. 2016.
//dubkov branch
******************/

// Частоты 

#define FR_NOTE_C4  262 
#define FR_NOTE_D4  294
#define FR_NOTE_E4  330
#define FR_NOTE_F4  349
#define FR_NOTE_G4  392
#define FR_NOTE_A4  440
#define FR_NOTE_B4  494
#define FR_NOTE_C5  523

#define LED_NOTE_C4	4
#define LED_NOTE_D4	5
#define LED_NOTE_E4	6
#define LED_NOTE_F4	7
#define LED_NOTE_G4	8
#define LED_NOTE_A4	9
#define LED_NOTE_B4	10
#define LED_NOTE_C5	11

#define BUZZER_PIN 12

#define BTN_NOTES 17

#define BTN_MODE 2

#define LED_MODE_0	14
#define LED_MODE_1	15
#define LED_MODE_2	16

/*
#define aC4 9		   //Дефайны значений кнопок, получаемые через аналоговый вход
#define aD4 8
#define aE4 7
#define aF4 6
#define aG4 5
#define aA4 4
#define aB4 3
#define aC5 1
#define kdel 100  //delay
*/



int ledsNotes[] = {LED_NOTE_C4,LED_NOTE_D4,LED_NOTE_E4,LED_NOTE_F4,
					LED_NOTE_G4,LED_NOTE_A4,LED_NOTE_B4,LED_NOTE_C5};

int melodies = {
	{1,2,3,4,5,6,7,0},
	{2,3,4,5,6,7,0,1},
	{3,4,5,6,7,0,1,2},
	{4,5,6,7,0,1,2,3},
	{5,6,7,0,1,2,3,4},
	{6,7,0,1,2,3,4,5},
	{7,0,1,2,3,4,5,6},
	{0,1,2,3,4,5,6,7}
}

int currentMelody[] = {1,1,1,1,1,1,1,1};

volatile int mode = 0;

void setup(){
	for (int i=0; i<9; i++)
		pinMode(ledNotes[i],OUTPUT);
	pinMode(BTN_MODE, INTPUT_PULLUP);
	pinMode(13, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(2), switchMode, FALLING);
}

void loop(){
	goto modeZero;
}

modeZero:
	while(1){
		blink(1000);
	}
modeOne:
	while(1){
		blink(500);
	}	
modeTwo:
	while(1){
		blink(200);
	}


void blink(int btime){
	digitalWrite(13,HIGH);
	delay(btime);
	digitalWrite(13,LOW);
	delay(btime);	
}

void switchMode(){
	if (mode == 0){ mode = 1; goto modeOne; }
	if (mode == 1){ mode = 2; goto modeTwo; }
	if (mode == 2){ mode = 0; goto modeZero; }
}

