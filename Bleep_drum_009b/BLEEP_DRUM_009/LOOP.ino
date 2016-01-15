unsigned long recordoffsettimer,offsetamount,taptempof;
int potX;



void loop() {

  midi_note_check=midi_note_on();

  button1=digitalRead(2);
  button2=digitalRead(19);
  button3=digitalRead(17);
  button4=digitalRead(18);
  tapb=digitalRead(8);

  if (button1==0 && pbutton1==1){
    bf1=1;
  }
  else{
    bf1=0;
  }
  if (button2==0 && pbutton2==1){
    bf2=1;
  }
  else{
    bf2=0;
  }

  if (button3==0 && pbutton3==1){
    bf3=1;
  }
  else{
    bf3=0;
  }
  if (button4==0 && pbutton4==1){
    bf4=1;
  }
  else{
    bf4=0;
  }
  if (tapb==0 && ptapb==1){
    bft=1;
  }
  else{
    bft=0;
  }
  if (midi_note_check==58){
    miditap2=1;
    //   digitalWrite(5,HIGH);
  }
  else{
    //      digitalWrite(9,HIGH);
    miditap2=0;
  }
  if (midi_note_check==57){
    midistep=1;    
    miditempo=1;
    digitalWrite(5,HIGH);
  }
  
  else{
    //      digitalWrite(9,HIGH);
    midistep=0;
  }
  
  if (midi_note_check==67){

    play++;
    play%=2;
    //   digitalWrite(5,HIGH);
  }

  if (midi_note_check==69){
    playmode++;
    playmode%=2;
    //   digitalWrite(5,HIGH);
  }


  if (midi_note_check==70){
    midinoise=1;
    shift_latch=1;
    noise_mode++;
    noise_mode%=2;
    //   digitalWrite(5,HIGH);
  }

  if (midi_note_check==72){
banko=0; //blue
  }
  if (midi_note_check==74){
banko=31; // yellow
  }
    if (midi_note_check==76){
banko=63; //red
  }
    if (midi_note_check==77){
banko=95; //green
  }


  pbutton1=button1;
  pbutton2=button2;
  pbutton3=button3;
  pbutton4=button4;
  ptapb=tapb;
  pmiditap=miditap;
  pmidistep=midistep;

  LEDS();
  BUTTONS();
  RECORD();

  // dd++;
  // if (dd==0){
  //pot1=analogRead(1);
  //  pot1=12;
  //  pot2=256;
  //pot2=(analogRead(0));

  if (noise_mode==0){
    pot1=((analogRead(1))>>1)+2;
    pot2=((analogRead(0))>>2)+96;
  }

  if (noise_mode==1){

    if (midinoise==1){
      pot1=(midicc1>>1)+1;
      pot2=(midicc2>>2)+1;
      pot3=(midicc3+1)<<4;
      pot4=(midicc4+1)<<2;

    }
    if (midinoise==0){


      if (shift_latch==0){
        pot1=((analogRead(1))>>1)+1;
        pot2=((analogRead(0))>>2)+1;
      }
      if (shift_latch==1){

        pot3=(analogRead(1))<<4; ////////////////MAKE ME BETTERERER  
        pot4=analogRead(0)<<2;

      }
    }
  }

  trigger_in_read=digitalRead(16);

  if (trigger_in_read==1 && prev_trigger_in_read==0){
    trigger_input=1;
  }
  else{
    trigger_input=0;

  }
  prev_trigger_in_read=trigger_in_read;

  eigth=loopstep%4;

  if(eigth==0){
    digitalWrite(12, HIGH);
    // tl++;
  }
  else{
    digitalWrite(12, LOW);
  }
  /*
   if (tl>3){
   trigger_out_latch=0;
   digitalWrite(12, LOW);
   tl=0l;
   }
   */


  //  }
  //  dd%=4;

  // cc++;

  //Serial.print(B3_latch);    Serial.print("  "); 
  //Serial.print(B1_latch);    Serial.print("  "); 
  //Serial.println(pot3);  //  Serial.print(","); 
  //Serial.println(pot4);

  ////////////////////////////////////////////

  taptempof=taptempo;

  recordoffsettimer=micros()-prev ;
  offsetamount=taptempof-(taptempof>>2 );
  //  offsetamount=0;
  //prev=micros();
  if ((recordoffsettimer)>(offsetamount))
  {

    loopstepf=loopstep+1;
    loopstepf%=32;

  }

  if (play==1){

    if (onetime==1){
      taptempo=4000000;
      onetime=0;
    }
    else{
      prevloopstep=loopstep;
      preva=eigth;

      if (recordmode==1 && miditempo==0){
        if (micros() - prev > (taptempof) ) {
          // trigger_out_latch=1;
          prev = micros();    
          //  ledstep=(loopstep%8); 
          loopstep++;
          loopstep%=32;

          //   half=loopstep%16;
          //   eigth=loopstep%4;
        }

      }

      if (miditempo==1){

        if (midistep==1){

          loopstep++;
          loopstep%=32;
        }
      }



    }

    B4_loop_trigger=B4_sequence[loopstep+banko];
    B1_loop_trigger=B1_sequence[loopstep+banko];
    B2_loop_trigger=B2_sequence[loopstep+banko];
    B3_loop_trigger=B3_sequence[loopstep+banko];
  }

  if (play==0){
    loopstep=31;
    prev==0;
    B4_loop_trigger=0;
    B1_loop_trigger=0;
    B2_loop_trigger=0;
    B3_loop_trigger=0;

  }

  if (loopstep!=prevloopstep && B3_loop_trigger==1){

    B3_seq_trigger=1;
    //freq3=kickfreqsequence[loopstepf];
  }
  else {
    B3_seq_trigger=0;
  }

  if (loopstep!=prevloopstep && B2_loop_trigger==1){

    B2_seq_trigger=1;
    //freq3=kickfreqsequence[loopstepf];
  }
  else {
    B2_seq_trigger=0;
  }

  if (loopstep!=prevloopstep && B4_loop_trigger==1){

    B4_seq_trigger=1;
    //freq3=kickfreqsequence[loopstepf];
  }
  else {
    B4_seq_trigger=0;
  }

  if (loopstep!=prevloopstep && B1_loop_trigger==1){

    B1_seq_trigger=1;
  }
  else {
    B1_seq_trigger=0;
  }



  if (B3_trigger==1 || B3_seq_trigger==1){
    index3=0;
    accumulator3=0;
    B3_latch=1;
  }

  if (B4_trigger==1 || B4_seq_trigger==1){
    index4=0;
    accumulator4=0;
    B4_latch=1;
  }
  if (B1_trigger==1){
    index=0;
    accumulator=0;
    B1_latch=1;
  }

  if (B1_seq_trigger==1){
    index_freq_1=0;
    accu_freq_1=0;
    B1_seq_latch=1;
  }
  if (B2_seq_trigger==1){
    index_freq_2=0;
    accu_freq_2=0;
    B2_seq_latch=1;
  }

  if (B2_trigger==1){
    index2=0;
    accumulator2=0;
    B2_latch=1;
  }





  //////////////////////////////////////////////////////////////// T A P

  //what=digitalRead(16);
  // tapbutton = digitalRead(18);

  if (shift==1){

    if (bft==1 || trigger_input==1 || miditap2==1){

      t++;
      t%=2;
      tapbank[t]=((micros())-prevtap)>>2;
      taptempo=((tapbank[0]+tapbank[1])>>1);
      // taptempo=((micros())-prevtap)>>2;
      prevtap=micros();
      //   loopstep=31;
      // prev=0;
    }
    else{
    }
    // ptapbutton= tapbutton;
    // pwhat=what;
  }


}





