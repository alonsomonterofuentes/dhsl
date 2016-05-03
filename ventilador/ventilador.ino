#include <math.h> //se añade el paquete math.h 
//se declaran las variables
const int termistor = A0	; //Se adjudica sensorPin al pin 0.
const int motor = 9;     //Se adjudica motor al pin 9.
int sensorValue = 0; //
int i;
int first_input_server;
int second_input_server;
int value_max;
char input_server[6];
String x;
void setup()
{
      Serial.begin(9600);     
      pinMode(outPin, OUTPUT);  
}
double temperaturaCentigrados():
		int lecturaTermistor = analogRead(termistor)
		double voltage = (reading * 5.0)/1023;
		double resistencia = (voltage)/(5-(voltage));
		double temperaturaC = pow(0.003356 + log(resistencia/50)*0.0002379, -1) -273;
		return temperaturaC;
void ctrl_temp(int a){
     if(temperaturaCentigrados > a){ //se define el parametro  bajo el cual se encendera el motor
     digitalWrite(motor, HIGH);
     }
     else{   //sino el motor se apaga 
     digitalWrite(motor, LOW);
     }
     delay(1000);                                     //esperar un segundo
}
boolean controlManualActivado(char inputUsuario){
		if(inputUsuario == '1'){return true;}
		else if(inputUsuario == '0'){return false;}
}//termina controlmanual activado
void loop()                     // Los siguientes comandos se ejecutan en ciclo.
 {
    while(Serial.available()){
    x = Serial.readString();
    x.toCharArray(input_server,6);
    first_input_server = atoi(&input_server[0]);
    second_input_server = atoi(&input_server[1]);
    value_max = atoi(&input_server[2-4]);
    switch(first_input_server){
      case '0':
        ctrl_temp(value_max);  
        break;
      case '1':
        if(second_input_server) {
          digitalWrite(outPin, LOW);
        }
        else {
          digitalWrite(outPin, HIGH);
        }
        break;
      }
  }
}
