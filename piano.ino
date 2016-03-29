/******************
@ KIDS FOOT PIANO @
@    By dubkov    @
@    29.03.2016   @
******************/

//Известные баги
/*
[РЕШЕНО, ТЕСТИТЬ] в режиме 2: подсвечиваются не играемые ноты, а просто кнопки по порядку
в режиме 3: если сыграна часть мелодии и затем мелодия переключилась, 
			то текущая позиция внутри мелодии не сбрасывается
в режиме 3: не переключается в режим 1 (возможно, переключается только после доигрывания мелодии)
*/

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
#define BTN_MELODY 3

#define LED_MODE_0	14
#define LED_MODE_1	15
#define LED_MODE_2	16


#define aC4 0		   //Дефайны значений кнопок, получаемые через аналоговый вход
#define aD4 3
#define aE4 7
#define aF4 11
#define aG4 16
#define aA4 23
#define aB4 28
#define aC5 33

int aButtons[] = {aC4,aD4,aE4,aF4,aG4,aA4,aB4,aC5};

int ledsNotes[] = {LED_NOTE_C4,LED_NOTE_D4,LED_NOTE_E4,LED_NOTE_F4,
					LED_NOTE_G4,LED_NOTE_A4,LED_NOTE_B4,LED_NOTE_C5};

int freqsNotes[] = {FR_NOTE_C4,FR_NOTE_D4,FR_NOTE_E4,FR_NOTE_F4,
					FR_NOTE_G4,FR_NOTE_A4,FR_NOTE_B4,FR_NOTE_C5};


int melodies[][11] = {
	{0,5,5,4,5,3,0,0,0,0,0},	// В лесу родилась елочка
	{4,2,5,4,1,3,2,1,0,0,0},	// От улыбки станет всем светлей
	{1,1,4,5,6,5,4,0,0,0,0},	// Пусть всегда будет солнце
	{4,2,4,2,4,3,2,1,0,2,4},	// Спят усталые игрушки книжки спят
	{1,2,1,4,5,6,5,1,0,0,0},	// Солнечный круг небо вокруг
	{0,0,0,1,2,2,0,2,4,2,4},	// Ничего на свете лучше нету
	{4,2,2,4,2,2,4,3,2,1,0},	// Маленькой елочке холодно зимой
	{2,4,4,2,3,4,4,0,0,0,0}		// Встаньте дети встаньте в круг
};

int melodysLens[] = {8,9,7,11,8,11,11,7};

int currentNote = 0;
int prevNote = 18;
int currentMelody = 0;
volatile int currentMelodyInModeTwo = 0;
int prevMelody = 18;
int currentNoteToPlay = 0;

volatile int mode = 0;

void setup(){
	for (int i=0; i<9; i++){
		pinMode(ledsNotes[i],OUTPUT);
	}
	pinMode(BTN_MODE, INPUT_PULLUP);
	pinMode(BTN_MELODY, INPUT_PULLUP);
	pinMode(LED_MODE_0, OUTPUT);
	pinMode(LED_MODE_1, OUTPUT);
	pinMode(LED_MODE_2, OUTPUT);
	attachInterrupt(0, switchMode, FALLING);
	attachInterrupt(1, switchMelody, FALLING);
	Serial.begin(19200);
}

void loop(){

	if (mode == 0){
		digitalWrite(LED_MODE_2, LOW);
		digitalWrite(LED_MODE_0, HIGH);
		while(mode == 0){
			prevNote = inputConverter(analogRead(BTN_NOTES)/54);
			delay(5);
  			currentNote = inputConverter(analogRead(BTN_NOTES)/54);
//  			Serial.println(currentNote);
  			if(prevNote == currentNote && currentNote < 15){
				playInModeZero(currentNote);
				
			}
		}		
	}

	else if (mode == 1){
		digitalWrite(LED_MODE_0, LOW);
		digitalWrite(LED_MODE_1, HIGH);
		while(mode == 1){
 			ledsOn(); 
 			prevMelody = inputConverter(analogRead(BTN_NOTES)/54);
			delay(5);
			currentMelody = inputConverter(analogRead(BTN_NOTES)/54);
  			if(prevMelody == currentMelody && currentMelody < 15)
				playInModeOne(currentMelody);
		}
	}

	else if (mode == 2){
		ledsOff();
		digitalWrite(LED_MODE_1, LOW);
		digitalWrite(LED_MODE_2, HIGH);
	//	currentMelody = 0;
		while(mode == 2){
			for (int ntpIter = 0; ntpIter < melodysLens[currentMelodyInModeTwo]; ntpIter++){
				currentNoteToPlay = melodies[currentMelodyInModeTwo][ntpIter];
				digitalWrite(ledsNotes[currentNoteToPlay],HIGH);
				while(currentNote != currentNoteToPlay){
					prevNote = inputConverter(analogRead(BTN_NOTES)/54);
					delay(5);
	  				currentNote = inputConverter(analogRead(BTN_NOTES)/54);
	  			}
	  			tone(BUZZER_PIN, freqsNotes[currentNote], 800);
	  			delay(800);
				digitalWrite(ledsNotes[currentNoteToPlay],LOW);
				currentNote = 18;
  				//playInModeTwo(currentNote, currentNoteToPlay);	
			}	
		}		
	}

}

void playInModeZero(int currentNoteInModeZero){
  ledsOff();
	digitalWrite(ledsNotes[currentNoteInModeZero],HIGH);
	tone(BUZZER_PIN, freqsNotes[currentNoteInModeZero], 100);
//	delay(50);
//	digitalWrite(ledsNotes[currentNoteInModeZero],LOW);
}

void playInModeOne(int currentMelodyInModeOne){
	ledsOff();
	for (int noteInModeOne = 0; noteInModeOne < melodysLens[currentMelodyInModeOne]; noteInModeOne++){
		digitalWrite(ledsNotes[melodies[currentMelodyInModeOne][noteInModeOne]],HIGH);
		tone(BUZZER_PIN, freqsNotes[melodies[currentMelodyInModeOne][noteInModeOne]], 800);
		delay(800);
		digitalWrite(ledsNotes[melodies[currentMelodyInModeOne][noteInModeOne]],LOW);
	}
}

//void playInModeTwo(int currentNoteInModeTwo, int currentNoteToPlayInModeTwo){
//}

int inputConverterArray[] = {0,1,2,3,4,4,5,5,6,6,7,7,
						18,18,18,18,18,18,18};

int inputConverter(int ainput){
	return inputConverterArray[ainput];
}

void switchMode(){
	if (mode == 0){ mode = 1; return; }
	if (mode == 1){ mode = 2; return; }
	if (mode == 2){ mode = 0; return; }
}

void switchMelody(){
	if (currentMelodyInModeTwo == 0){ currentMelodyInModeTwo = 1; return;}
	if (currentMelodyInModeTwo == 1){ currentMelodyInModeTwo = 2; return;}
	if (currentMelodyInModeTwo == 2){ currentMelodyInModeTwo = 3; return;}
	if (currentMelodyInModeTwo == 3){ currentMelodyInModeTwo = 4; return;}
	if (currentMelodyInModeTwo == 4){ currentMelodyInModeTwo = 5; return;}
	if (currentMelodyInModeTwo == 5){ currentMelodyInModeTwo = 6; return;}
	if (currentMelodyInModeTwo == 6){ currentMelodyInModeTwo = 7; return;}
	if (currentMelodyInModeTwo == 7){ currentMelodyInModeTwo = 0; return;}
}

void ledsOff(){
	for (int i=0; i<9; i++)
		digitalWrite(ledsNotes[i],LOW);
}

void ledsOn(){
	for (int i=0; i<9; i++)
		digitalWrite(ledsNotes[i],HIGH);
}
