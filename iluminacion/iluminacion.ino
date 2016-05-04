/*
*El protocolo de comunicacion entre el arduino y el servidor consiste en enviar y recibir
*Strings que son descompuestas en componentes[caracteres] que representan datos importantes para el programa
*Podemos representarlos asi
*[0] -> tiene valores de 1(encendido) o 0(apagado), representa el control manual
*[1] -> tiene valores de 1(encendido) o 0(apagado), representa el estado del led
*[2] -| 
*[3]  |-> unidos nos dan un valor entre 000 y 999, representanda el valor maximo de luminosidad
*[4] -|
*[5] -|
*[6]  |-> unidos nos dan un valor entre 000 y 999, representa el valor la sensibilidad del sensor ultrasonico(cm) 
*[7] -|
**[\0]
*/
const int led = 13; 
const int  echo = 11;
const int trig = 12;
const int fotoresistor = A0;
long duracion; 
long distancia;
int i;
int valorMaxInt; 
int valorSensibilidadInt;
String lecturaSerial;
char serverInput[10];
char serverOutput[8]; 
char valorMaxChar[4];
char valorSensibilidadChar[4];
void setup(){
		pinMode(led,OUTPUT);
		pinMode(fotoresistor,INPUT);
		Serial.begin(9600);
}//termina setup
int lecturaFotoresistor(){
		return analogRead(fotoresistor);
}//termina lecturaFotoresistor
int lecturaUltrasonico(){
		digitalWrite(trig, LOW);
		delayMicroseconds(2);
		digitalWrite(trig, HIGH);// genera el pulso de triger por 10ms
		delayMicroseconds(10);
		digitalWrite(trig, LOW);
		duracion = pulseIn(echo, HIGH);
		distancia = (duracion/2) / 29;	// calcula la distancia en centimetros
		return distancia;
}//termina lecturaUltrasonico
boolean hayMovimiento(int distanciaLeida, int distanciaEstablecida){
		if(distanciaLeida<distanciaEstablecida){
				return true;
		}
		else{
				return false;
		}
}//termina hayMovimiento
void encenderLed(){ 
		digitalWrite(led, HIGH); 
}//termina encenderLed
void apagarLed(){
		digitalWrite(led,LOW); 
}//termina apagarLed
void recibirDatos(){
		while(Serial.available()){
				lecturaSerial=Serial.readString();          //recibe un string por medio de serial
				lecturaSerial.toCharArray(serverInput,9);   //convierte ese string en char de 9
				valorMaxChar[0] = serverInput[2];	    //la tercera entrada se sI es la primera de mL
				valorMaxChar[1] = serverInput[3];	    //lo mismo sucede para esta 
				valorMaxChar[2] = serverInput[4];	    //y para esta
				valorMaxInt = atoi(valorMaxChar);
				valorSensibilidadChar[0] = serverInput[5];
				valorSensibilidadChar[1] = serverInput[6];
				valorSensibilidadChar[2] = serverInput[7];
				valorSensibilidadInt = atoi(valorSensibilidadChar);
		}	//termina while serial.available	
}//termina recibirDatos
boolean controlManualActivado(char inputUsuario){
		if(inputUsuario == '1'){return true;}
		else if(inputUsuario == '0'){return false;}
}//termina control manual activado
void controlManual(){
		if(controlManualActivado(serverInput[0])==true){	
				if(serverInput[1]=='0'){
						apagarLed();
				}
				else if(serverInput[1] == '1'){
						encenderLed();	
				}				
		}
		//(controlManualActivado(serverInput[0])==false){
		else if(controlManualActivado(serverInput[0])==false){controlAutomatico();}
}//termina control manual
void controlAutomatico(){
						while(hayMovimiento(lecturaUltrasonico(),valorSensibilidadInt) == true && Serial.available()==false){			
								if(valorMaxInt<lecturaFotoresistor()){
										encenderLed();
								}//termina if	
								else {
										apagarLed();
								}//termina else
		}//termina while
}//termina control automatico
void loop(){
		recibirDatos();
		controlManual();
		}//termina loop	

