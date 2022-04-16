#include "speaker.h"
#include "../io/io.h"

 //Play sound using built in speaker
 static void speaker_play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
    //And play the sound using the PC speaker
 	tmp = insb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
 static void speaker_nosound() {
 	uint8_t tmp = insb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
 }
 
 //Make a beep
 void speaker_beep() {
 	 speaker_play_sound(1000);
 	 timer_wait(10);
 	 speaker_nosound();
          //set_PIT_2(old_frequency);
 }