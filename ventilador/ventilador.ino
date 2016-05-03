#include <math.h> //se añade el paquete math.h 
//se declaran las variables
const int termistor = A0;       //Se adjudica sensorPin al pin 0.
const int motor = 9;     //Se adjudica motor al pin 9.
int sensorValue = 0; //
int i;
int first_input_server;
int second_input_server;
int value_max;
int valorSensibilidad;
int valorMaxInt;
char input_server[6];
char valorMaxChar;
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
     delay(1000);                                     //esperar un segundo
    }
}
void recibirDatos(){  //Recibe dato Serial y obtiene el valor de la sensibilidad del terminstor
	while(Serial.available()){
		lecturaSerial=Serial.readString();
		lecturaSerial.toCharArray(input_server,6);
//		valorMaxInt=atoi(valorMaxChar);
		valorSensibilidadChar[0] = input_server[2];
		valorSensibilidadChar[1] = input_server[3];
		valorSensibilidadChar[2] = input_server[4];
		valorSensibilidad = atoi(valorSensibilidadChar);
	}
}
boolean controlManualActivado(char inputUsuario){
		if(inputUsuario == '1'){return true;}
		else if(inputUsuario == '0'){return false;}
}//termina controlmanual activado
void controlManual(){
		if(controlManualActivado(input_server[0])==true){	
				if(input_server[1]=='0'){
						apagarMotor();
				}
				else if(input_server[1] == '1'){
						encenderMotor();
				}				
		}
		else if(controlManualActivado(input_server[0])==false){controlAutomatico();}
}

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
          apagarMotor();
        }
        else {
          encenderMotor();
        }
        break;
      }
  }
}
