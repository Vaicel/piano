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

int freqsNotes[] = {FR_NOTE_C4,FR_NOTE_D4,FR_NOTE_E4,FR_NOTE_F4,
					FR_NOTE_G4,FR_NOTE_A4,FR_NOTE_B4,FR_NOTE_C5};


int melodies[][8] = {
	{1,2,3,4,5,6,7,0},
	{2,3,4,5,6,7,0,1},
	{3,4,5,6,7,0,1,2},
	{4,5,6,7,0,1,2,3},
	{5,6,7,0,1,2,3,4},
	{6,7,0,1,2,3,4,5},
	{7,0,1,2,3,4,5,6},
	{0,1,2,3,4,5,6,7}
};

int currentNote = 0;
int currentMelody = 0;
int currentNoteToPlay = 0;

volatile int mode = 0;

void setup(){
	for (int i=0; i<9; i++)
		pinMode(ledsNotes[i],OUTPUT);
	pinMode(BTN_MODE, INPUT_PULLUP);
	pinMode(13, OUTPUT);
	pinMode(LED_MODE_0, OUTPUT);
	pinMode(LED_MODE_1, OUTPUT);
	pinMode(LED_MODE_2, OUTPUT);
	attachInterrupt(0, switchMode, FALLING);
}

void loop(){
	if (mode == 0){
		digitalWrite(LED_MODE_2, LOW);
		digitalWrite(LED_MODE_0, HIGH);
		while(mode == 0){
  			currentNote = analogRead(BTN_NOTES);
  			if(currentNote < ???)
				playInModeZero(currentNote);
		}		
	}
	else if (mode == 1){
		digitalWrite(LED_MODE_0, LOW);
		digitalWrite(LED_MODE_1, HIGH);
		while(mode == 1){
 			ledsOn(); 
			currentMelody = analogRead(BTN_NOTES);
  			if(currentNote < ???)
				playInModeOne(currentMelody);
		}
	}
	else if (mode == 2){
		digitalWrite(LED_MODE_1, LOW);
		digitalWrite(LED_MODE_2, HIGH);
		while(mode == 2){
			for (int ntpIter = 0; ntpIter < 8; ntpIter++){
				currentNoteToPlay = melodies[currentMelody][ntpIter];
				digitalWrite(ledsNotes[currentNoteToPlay],HIGH)
				currentNote = analogRead(BTN_NOTES);
  				playInModeTwo(currentNote, currentNoteToPlay);	
		}		
	}
}


void blink(int btime){
	digitalWrite(13,HIGH);
	delay(btime);
	digitalWrite(13,LOW);
	delay(btime);	
}

void switchMode(){
	if (mode == 0){ mode = 1; return; }
	if (mode == 1){ mode = 2; return; }
	if (mode == 2){ mode = 0; return; }
}

void ledsOff(){
	for (int i=0; i<9; i++)
		digitalWrite(ledsNotes[i],LOW);
}

void ledsOn(){
	for (int i=0; i<9; i++)
		digitalWrite(ledsNotes[i],HIGH);
}

void playInModeZero(int currentNoteInModeZero){
	digitalWrite(ledsNotes[currentNoteInModeZero],HIGH);
	tone(BUZZER_PIN, freqsNotes[currentNoteInModeZero], 1000);
	digitalWrite(ledsNotes[currentNoteInModeZero],LOW);
}

void playInModeOne(int currentMelodyInModeTwo){
	ledsOff();
	for (int noteInModeOne = 0; noteInModeOne < 8; noteInModeOne++){
		playInModeZero(melodies[currentMelodyInModeTwo][noteInModeOne]);
	}
	ledsOn();
}

void playInModeTwo(int currentNoteInModeTwo, int currentNoteToPlayInModeTwo){
	while(currentNoteInModeTwo != currentNoteToPlayInModeTwo);
	tone(BUZZER_PIN, freqsNotes[currentNoteInModeTwo], 1000);
	digitalWrite(ledsNotes[currentNoteToPlayInModeTwo],LOW);

}
