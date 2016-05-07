#include <math.h> 

const int termistor = A0, motor = 9;;
int sensorValue = 0, i, value_max, valorSensibilidadInt, valorMaxInt;
char input_server[6], valorMaxChar, valorSensibilidadChar[5];
String x, lecturaSerial;
double temperaturaC;

//se inicializan los pines y el serial
void setup(){
      Serial.begin(9600);
      pinMode(termistor, INPUT);     
      pinMode(motor, OUTPUT);  
}

//retorna lo que lee el fotoresistor en grados centigrados
double temperaturaCentigrados(){
		int lecturaTermistor = analogRead(termistor);
		double voltage = (lecturaTermistor * 5.0) / (1023);
		double resistencia = (voltage) / (5 - voltage);
		double temperaturaC = pow(0.003356 + log(resistencia/50)*0.0002379, -1) -273;
		return temperaturaC;
}

//enciende el motor
void encenderMotor(){ 
		digitalWrite(motor, HIGH); 
}

//apaga el motor
void apagarMotor(){
		digitalWrite(motor, LOW);
}

//compara lo que lee el termistor con el valor establecido por el usuario para encender o apagar el motor
void controlAutomatico(){
		while(Serial.available()==false){
				if(temperaturaCentigrados() > valorSensibilidadInt ){ 
						encenderMotor();
				}
				else{   
						apagarMotor();
				}
    }
}

//lee los datos recibidos por serial, los convierte a un string para ser analizados
void recibirDatos(){  
	while(Serial.available()){
		lecturaSerial=Serial.readString();
		lecturaSerial.toCharArray(input_server,7);
		valorSensibilidadChar[0] = input_server[2];
		valorSensibilidadChar[1] = input_server[3];
		valorSensibilidadChar[2] = input_server[4];
		valorSensibilidadInt = atoi(valorSensibilidadChar);
	}
}

//retorna verdadero si el usuario activo el control manual, sino retorna falso
boolean controlManualActivado(char inputUsuario){
		if(inputUsuario == '1'){return true;}
		else if(inputUsuario == '0'){return false;}
}

//si el control manual fue activado se revisa el estado que pide el usuario para el led
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

//funcion principal que corre el ciclo infinito
void loop(){
		recibirDatos();
		controlManual();
}

