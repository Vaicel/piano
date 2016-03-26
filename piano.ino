/******************
Code made by Vaicel. 2016.
//dubkov branch
******************/

// Частоты 

#define NOTE_C4  262 
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523


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

int notes = {
	{1,2,3,4,5,6,7,8},
	{2,3,4,5,6,7,8,1},
	{3,4,5,6,7,8,1,2},
	{4,5,6,7,8,1,2,3},
	{5,6,7,8,1,2,3,4},
	{6,7,8,1,2,3,4,5},
	{7,8,1,2,3,4,5,6},
	{8,1,2,3,4,5,6,7}
}

volatile int mode = 0;

void setup(){
	attachInterrupt(digitalPinToInterrupt(2), switchMode, RISING);
}

void loop(){
 	
}

void switchMode(){
	mode += 1;
	if (mode == 3) mode = 0;
}

// выбор режима 

