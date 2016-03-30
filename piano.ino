//v23

#define DOUBLE_TAP_DELAY 6 //меняй это

/******************
@ KIDS FOOT PIANO @
@    By dubkov    @
@    29.03.2016   @
******************/

//Известные баги
/*
в режиме 3: если сыграна часть мелодии и затем мелодия переключилась, 
			то текущая позиция внутри мелодии не сбрасывается
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

#define ANALOG_READ_DIVIDER	50

int ledsNotes[] = {LED_NOTE_C4,LED_NOTE_D4,LED_NOTE_E4,LED_NOTE_F4,
					LED_NOTE_G4,LED_NOTE_A4,LED_NOTE_B4,LED_NOTE_C5};

int freqsNotes[] = {FR_NOTE_C4,FR_NOTE_D4,FR_NOTE_E4,FR_NOTE_F4,
					FR_NOTE_G4,FR_NOTE_A4,FR_NOTE_B4,FR_NOTE_C5};

// ноты мелодий 

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

int melodysLens[] = {8,9,7,11,8,11,11,7}; 	// длины мелодий

int currentNote = 0;
int prevNote = 18;
int currentMelody = 0;
volatile int currentMelodyInModeTwo = 0;
int prevMelody = 18;
int currentNoteToPlay = 0;
volatile int mode = 0;
int currentNoteInModeTwo = 18;
int prevNoteInModeTwo = 18;

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
Serial.println("XUY");
	if (mode == 0){
		digitalWrite(LED_MODE_2, LOW);
		digitalWrite(LED_MODE_0, HIGH);
		while(mode == 0){
			prevNote = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);
			delay(DOUBLE_TAP_DELAY);
  			currentNote = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);
  			if(prevNote == currentNote && currentNote < 15){
				ledsOff();
				digitalWrite(ledsNotes[currentNote],HIGH);
				tone(BUZZER_PIN, freqsNotes[currentNote], 100);
			}
		}		
	}

	if (mode == 1){
		digitalWrite(LED_MODE_0, LOW);
		digitalWrite(LED_MODE_1, HIGH);
		while(mode == 1){
 			ledsOn(); 
 			prevMelody = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);
			delay(DOUBLE_TAP_DELAY);
			currentMelody = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);
  			if(prevMelody == currentMelody && currentMelody < 15){
				ledsOff();
				for (int noteInModeOne = 0; noteInModeOne < melodysLens[currentMelody]; noteInModeOne++){
					digitalWrite(ledsNotes[melodies[currentMelody][noteInModeOne]],HIGH);
					tone(BUZZER_PIN, freqsNotes[melodies[currentMelody][noteInModeOne]], 800);
					delay(800);
					digitalWrite(ledsNotes[melodies[currentMelody][noteInModeOne]],LOW);
				}
			}
		}
	}

	else if (mode == 2){
                Serial.println("MODE 2");
		ledsOff();
		digitalWrite(LED_MODE_1, LOW);
		digitalWrite(LED_MODE_2, HIGH);
                currentNoteToPlay = 0;
		while(mode == 2){
			for (int ntpIter = 0; ntpIter < melodysLens[currentMelodyInModeTwo]; ntpIter++){                                
				currentNoteInModeTwo = 18;				
				currentNoteToPlay = melodies[currentMelodyInModeTwo][ntpIter];
  				digitalWrite(ledsNotes[currentNoteToPlay],HIGH);
				//while(currentNoteInModeTwo != currentNoteToPlay){
					//prevNoteInModeTwo = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);
					//delay(DOUBLE_TAP_DELAY);
                                for(;;){
                                        prevNoteInModeTwo = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);	  			
	                                delay(DOUBLE_TAP_DELAY);
                                        currentNoteInModeTwo = inputConverter(analogRead(BTN_NOTES)/ANALOG_READ_DIVIDER);
                                        if (prevNoteInModeTwo == currentNoteInModeTwo && currentNoteInModeTwo == currentNoteToPlay) break;
                                        if (mode != 2) break;
                                }
	  			//}
	  			if (mode != 2) break;
	  			tone(BUZZER_PIN, freqsNotes[currentNoteInModeTwo], 800);
	  			delay(800);
				digitalWrite(ledsNotes[currentNoteToPlay],LOW);
				
			}
                        if (mode == 2){
                          ledsOn();
                          delay(1000);
                          ledsOff();	
                        }
		}		
	}

}

int inputConverterArray[] = {0,0,0,0,0,1,2,3,4,4,4,5,6,7}; // TUNE THIS for yur keyboard

int inputConverter(int ainput){
	return inputConverterArray[ainput];
}

void switchMode(){
	if (mode == 0){ mode = 1; return; }
	if (mode == 1){ mode = 2; return; }
	if (mode == 2){ mode = 0; return; }
}

void switchMelody(){
	currentMelodyInModeTwo += 1;
	if (currentMelodyInModeTwo == 8)
		currentMelodyInModeTwo = 0;
	return;
}

void ledsOff(){
	for (int i=0; i<9; i++)
		digitalWrite(ledsNotes[i],LOW);
}

void ledsOn(){
	for (int i=0; i<9; i++)
		digitalWrite(ledsNotes[i],HIGH);
}
