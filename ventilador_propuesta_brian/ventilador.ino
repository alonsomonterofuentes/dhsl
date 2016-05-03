#include <math.h> //se añade el paquete math.h 
//se declaran las variables
const int termistor = A0;       //Se adjudica sensorPin al pin 0.
const int motor = 9;     //Se adjudica motor al pin 9.
int sensorValue = 0; 
int i;
int first_input_server;
int second_input_server;
int value_max;
int valorSensibilidad;
char input_server[6];
char valorSensibilidadChar;
String x;
String lecturaSerial;
double temperaturaC;

void setup()
{
      Serial.begin(9600);
      pinMode(termistor, INPUT);     
      pinMode(motor, OUTPUT);  
}
double temperaturaCentigrados(){
		int lecturaTermistor = analogRead(termistor);
		double voltage = (lecturaTermistor * 5.0) / (1023);
		double resistencia = (voltage) / (5 - voltage);
		double temperaturaC = pow(0.003356 + log(resistencia/50)*0.0002379, -1) -273;
		return temperaturaC;
}
void encenderMotor(){ 
		digitalWrite(motor, HIGH); 
}
void apagarMotor(){
		digitalWrite(motor, LOW);
}
void controlAutomatico(){
    while(Serial.available()==false){
		if(temperaturaC > valorSensibilidad ){ //se define el parametro  bajo el cual se encendera el motor
	    	      encenderMotor();
		}
		else{   //sino el motor se apaga 
		      apagarMotor();
                }
        delay(1000);              //esperar un segundo
    }
}
void loop()                     // Los siguientes comandos se ejecutan en ciclo.
 {
    while(Serial.available()){
    x = Serial.readString();
    x.toCharArray(input_server,6);
    first_input_server = atoi(&input_server[0]);
    second_input_server = atoi(&input_server[1]);
    value_max = atoi(&input_server[2-4]);
    switch(first_input_server){         // SE COMPRUEBA EL CONTROL MANUAL SI SE ACTIVA O NO
      case '0':                          // NO SE ACTIVA EL CONTROL MANUAL
        valorSensibilidad = value_max;
        controlAutomatico();             // SE DA PASO AL CONTROL AUTOMATICO
        break;
      case '1':                            // SE ACTIVA EL CONTROL MANUAL
        if(second_input_server == '1') {
          encenderMotor();                // SE DESEA TENER EL MOTOR ENCENDIDO CON EL CONTROL MANUAL
        }
        else {
          apagarMotor();                  // SE DESEA TENER EL MOTOR APAGADO CON EL CONTROL MANUAL
        }
        break;
      }
  }
}
