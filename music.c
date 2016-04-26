/* Here's a look at how I created a quick music player for use with GBDK.
It basically defines how to play a note, and then stores an array of notes
to be played as a timer interates through the beats */

#include "songs_gunsriders.c"

UINT16 currentBeat;
UINT8 timerCounter;
UINT8 moreSpeed;
UINT8 muteChannel1;
UINT8 muteChannel4;

//function to set sound registers based on notes chosen
void setNote(note *n){
    switch((*n).i){
            case MELODY:
                    NR10_REG = 0x00U; //pitch sweep
                    NR11_REG = 0x84U; //wave duty
                    NR12_REG = (*n).env; //envelope
                    NR13_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
                    NR14_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8); //high bits of frequency (and sound reset)
            break;
            case HARMONY:
                    NR10_REG = 0x00U;
                    NR11_REG = 0x00U; //wave duty for harmony is different
                    NR12_REG = (*n).env;
                    NR13_REG = (UBYTE)frequencies[(*n).p];
                    NR14_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8);
            break;
            case SNARE:
                    NR21_REG = 0x00U;
                    NR22_REG = (*n).env;
                    NR23_REG = (UBYTE)frequencies[(*n).p];
                    NR24_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8);
                    NR51_REG |= 0x22;
            break;
            case WAVE:

            break;
            case CYMBAL:
                NR41_REG = 30;//0x0FU; //Duration
                NR42_REG = 55;         //Volumen
                NR43_REG = 50;         //Tone
                NR44_REG = 0xC0U;
                NR51_REG |= 0x88;
            break;
    }
}

void playMusicMenu(){
    setNote(&song_menu_ch1[currentBeat]);
    setNote(&song_menu_ch2[currentBeat]);
    setNote(&song_menu_ch4[currentBeat]);
    NR51_REG |= 0x11U; //enable sound on channel 1
}

void playMusicGameover(){
    setNote(&song_gameover_ch1[currentBeat]);
    setNote(&song_gameover_ch2[currentBeat]);
    NR51_REG |= 0x11U; //enable sound on channel 1
}

void playMusicGameplay(){
    if (muteChannel1 == 0)
        setNote(&song_gameplay_ch1[currentBeat]);
    setNote(&song_gameplay_ch2[currentBeat]);
    if (muteChannel4 == 0)
        setNote(&song_gameplay_ch4[currentBeat]);
    NR51_REG |= 0x11U; //enable sound on channel 1
}

//Timer function gets called 16 times a second
void updateMusicMenu(){
    if (timerCounter >= 7){ //every 4 ticks is a beat, or 4 beats per second
            timerCounter = 0;
            currentBeat = currentBeat == 60 ? 0 : currentBeat+1;
            playMusicMenu(); //every beat, play the sound for that beat
    }
    timerCounter++;
}

void updateMusicGameover(){
    if (timerCounter >= 7 && currentBeat <= 25){ //every 4 ticks is a beat, or 4 beats per second
            timerCounter = 0;
            currentBeat = currentBeat == 25 ? 0 : currentBeat+1;
            playMusicGameover(); //every beat, play the sound for that beat
    }
    timerCounter++;
}

void updateMusicGameplay(){
    if (timerCounter >= 7 - moreSpeed){ //every 4 ticks is a beat, or 4 beats per second
            timerCounter = 0;
            if (currentBeat < 352)
            {
                currentBeat++;
            }
            else
            {
                currentBeat = 0;
                if (moreSpeed < 5)
                {
                    moreSpeed++;
                }
            }
            playMusicGameplay(); //every beat, play the sound for that beat
    }
    timerCounter++;
    if (muteChannel1 != 0)
    {
        muteChannel1++;
        if (muteChannel1 > 10)
        {
            muteChannel1 = 0;
        }
    }
    if (muteChannel4 != 0)
    {
        muteChannel4++;
        if (muteChannel4 > 10)
        {
            muteChannel4 = 0;
        }
    }
}

