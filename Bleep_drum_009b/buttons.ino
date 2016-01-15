
void BUTTONS() {
  shift=digitalRead(7);

  if (shift==0 && prevshift==1){
    shift_latch++;
    shift_latch%=2;
  }

  prevshift=shift;
  ///////////////////////////////////////////////////sequence select

    if (shift==0&&recordbutton==1){
    prevpot2=pot2;
    if (button1==0 ){ //red
      banko=63;

    }
    if (button4==0){  //yellow
      banko=31;
      bankpr=4;
      bankpg=4;
      bankpb=0;
    }
    if (button2==0 || banko==0){   //blue
      banko=0;
      bankpr=0;
      bankpg=0;
      bankpb=8;
    }
    if (button3==0){//green
      banko=95;
      bankpr=0;
      bankpg=3;
      bankpb=0;

    }


    if (tapb==LOW){

      play=1;
      ratepot=(analogRead(14));
      taptempo=ratepot<<14;
    }
    revbutton = digitalRead(3);
    if (revbutton==0 && prevrevbutton==1){
      playmode++;
      playmode%=2;

    }
    prevrevbutton=revbutton;
  }
  
      if( banko==63){

      bankpr=4;
      bankpg=0;
      bankpb=0;
      }
      if( banko==31){
      bankpr=4;
      bankpg=4;
      bankpb=0;
    }
      if( banko==0){
      bankpr=0;
      bankpg=0;
      bankpb=8;
    }      
    
      if( banko==95){
      bankpr=0;
      bankpg=3;
      bankpb=0;

    }
  

  if (shift==1){
 //       if (bf1==1){

    if (bf1==1 || midi_note_check==60){
      B1_trigger=1;  
    }
    else{
      B1_trigger=0;
    }
//    if (bf4==1){

    if (bf4==1 || midi_note_check==65){
      B4_trigger=1; 
    }
    else{
      B4_trigger=0;
    }
//    if (bf2==1){

    if (bf2==1 || midi_note_check==62){
      B2_trigger=1; 
    }
    else{
      B2_trigger=0;
    }
 //   if (bf3==1){
    if (bf3==1 || midi_note_check==64){
      B3_trigger=1; 
    }
    else{
      B3_trigger=0;
    }

  }



  ////////////////////////////////////////////

}

int midi_note_on(){

 int type, note, velocity, channel, d1, d2;
byte r= MIDI.read();
  if (r==1) {                    // Is there a MIDI message incoming ?
    byte type = MIDI.getType();
    switch (type) {
      case NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
         if (velocity == 0) {
		 note=0;
        }
              
        break;
      case NoteOff:
         note=0;
        break;
       
       case ControlChange:
       if (MIDI.getData1()==70){
        midicc1 = (MIDI.getData2()<<2)+3;
       }
       
        if (MIDI.getData1()==71){
        midicc2 = (MIDI.getData2()<<2)+3;
       }
       
             if (MIDI.getData1()==72){
        midicc3 = (MIDI.getData2()<<2);
       }
       
             if (MIDI.getData1()==73){
        midicc4 = (MIDI.getData2()<<2);
       }
/*
                 if (MIDI.getData1()==74){
        midicc5 = (MIDI.getData2());
       }
       
                 if (MIDI.getData1()==75){
        midicc6 = (MIDI.getData2());
       }
       
                 if (MIDI.getData1()==76){
        midicc7 = (MIDI.getData2());
       }
       
                 if (MIDI.getData1()==77){
        midicc8 = (MIDI.getData2());
       }
   */
       
       
      default:
         note=0;

    }
  }
  
  else{
        note=0;
  }
    
    return note;
}

