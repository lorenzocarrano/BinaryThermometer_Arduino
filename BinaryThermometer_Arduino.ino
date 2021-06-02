#include <74HC595.h>

SHR_74HC595 ShiftReg;

int ThermistorPin = 0; //Il termistore è collegato al pin A0
int Vo;
float R1 = 10000; //valore termistore
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //coefficienti del termistore
float T_cels; //temperatura in Celsius
float T_last = -273; //ultima temperatura registrata
float sum = 0;
int it_counter = 0;
int buffer_Output[8];

void setup() {
  Serial.begin(9600); 
  pinMode(3, INPUT_PULLUP); //di default il pin sarà HIGH, premendo il pulsante andrà LOW (-->da ciò dipende la modalità di trigger dell'interrupt)
  attachInterrupt(digitalPinToInterrupt(3), toggle_output_state, FALLING); //il pin 10 è il pin dal quale potrà essere invocato l'interrupt, triggerato sul fronte di discesa
  ShiftReg.reset();
  ShiftReg.EnableOutputs();
  pinMode(4, OUTPUT); //pin 4 usato per segnalare approssimazione
}
void loop() {
  Vo = analogRead(ThermistorPin); //tensione letta dal pin A0
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; //temperatura in Farenheit
  T_cels = (T - 32)/1.8; //temperatura in Celsius

  if(it_counter == 20){

    T_cels = sum/it_counter;
    it_counter = 0;
    sum = 0;

    Serial.print("Temperature: "); 
    Serial.print(T_cels);
    Serial.println(" C");
    convT2Bin(buffer_Output);
    ShiftReg.ConfigureOutputs(buffer_Output);
    ShiftReg.ConfirmOutputs();
    delay(5000);
  }

  else{

    sum += T_cels;
    it_counter++;
  }
  //n_iter++;
  //if(n_iter == 100);
    //n_iter = 0;
  delay(500);
}

void toggle_output_state(){
  static int last_toggle_iter = 0;
  //if(last_toggle_iter != n_iter){
    ShiftReg.ToggleOutputsState();
    digitalWrite(4, LOW); //if the red LED is ON, now it has to be forced OFF
    //last_toggle_iter = n_iter;
  //} 
}

void convT2Bin(int * bufferOutput){
  
  int p_int, p_dec; //parte intera e parte decimale della temperatura letta
   
  p_int = (int)T_cels;
  p_dec = (int)((T_cels - p_int)*100); //arrotondamento a due cifre

  p_dec = (p_dec%10 > 5) ? (int)p_dec/10 + 1 : (int)p_dec/10; //arrotondamento a una cifra
  
  if(p_dec >= 8 && ShiftReg.GetOutputsState() == true)

     digitalWrite(4, HIGH);

  else digitalWrite(4, LOW);

  Serial.print(p_int);
  Serial.print(p_dec);
  int j;
  for(int i = 0, j = 0; i < 3; i++, j++){

      *(bufferOutput+j) = (p_dec%2 == 0) ? 0 : 1;
      p_dec /= 2;
      
  }

  for(int i = 0, j = 3; i < 5; i++, j++){

       *(bufferOutput+j) = (p_int%2 == 0) ? 0 : 1;
       p_int /= 2;
  }
}
