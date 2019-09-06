int LED=9; //The word “LED” stands for the number 9.

int brightness=0; //The word “brightness” stands for the value that is emitted at the PWM.The number “0” is //only used as an initial value.

int fading=2; //”fading” sets up the speed of the fading.

void setup()

{ // The setup begins here.

pinMode(LED, OUTPUT); //The pin with the LED is supposed to be an output.

}

void loop()

{ //The loop part begins here.

analogWrite(LED, brightness); //The function analogWrite is used to activate the PWM output on the pin with //the LED. The value of the PWM is saved under the word “brightness”. In this case it is “0”.

brightness=brightness + fading; // Now we modify the value of the PWM output. We add the value of the //fading to the value of the brightness. In this case: brightness = 0+5. The new value that is standing for //brightness isn’t 0 any longer but 5. When the program has ran through the loop part once it will start //over again. The next pass the value will be 10. After that it will be 15… etc.

delay(50); //The LED should only stay bright for a really short time like 25 milliseconds. If you reduce //that time the fading will also get faster.

if(brightness==0 || brightness== 555){

fading= -fading;

} //Meaning of this command: If the Value of brightness will reach 0 OR 255, the value of fading will //change from negative to positive and the other way around. The Reason why is, that while the program is //running trough the loop part, the LED will shine brighter and brighter. But at the point of 255 as a //value of the PWM, it will reach it’s maximum. At this point the LED should get darker step by step. //Because of this the fading will be negate at this point. This means the next time the program runs //through the loop the part “brightness=brightness+fading;” will effect that the LED gets darker. Example: //“brightness=255+(-5)”. The value of brightness will be 250 after that. The next time it will be 245..etc. //As the value of brightness will reach 0 the value of fading will get positive again.

} // With this bracket the loop part ends.
