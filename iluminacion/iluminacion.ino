/*
 *Programa en que se entran datos establecidos por el usuario por medio de serial
 *Estos datos son ingresados en un orden especial, que el programa tomara como 
 *Parametros bajo los cuales se realizaran las acciones correspondientes
 */	

const int led = 13, echo = 11, trig = 12, fotoresistor = A0;
char serverInput[10],serverOutput[8],valorMaxChar[4],valorSensibilidadChar[4];
long duracion, distancia;
int i,valorMaxInt,valorSensibilidadInt;
String lecturaSerial;

//se inicializan los pines y el serial
void setup(){
		pinMode(led,OUTPUT);
		pinMode(fotoresistor,INPUT);
		Serial.begin(9600);
}

//retorna lo que esta leyendo el fotoresistor
int lecturaFotoresistor(){
		return analogRead(fotoresistor);
}

//retorna lo que esta leyendo el sensor ultrasonico
int lecturaUltrasonico(){
		digitalWrite(trig, LOW);
		delayMicroseconds(2);
		digitalWrite(trig, HIGH);// genera el pulso de triger por 10ms
		delayMicroseconds(10);
		digitalWrite(trig, LOW);
		duracion = pulseIn(echo, HIGH);
		distancia = (duracion/2) / 29;	// calcula la distancia en centimetros
		return distancia;
}

//retorna verdadero si el sensor ultrasonico detecta movimiento(mide una distancia menor a la establecida
boolean hayMovimiento(int distanciaLeida, int distanciaEstablecida){
		if(distanciaLeida<distanciaEstablecida){
				return true;
		}
		else{
				return false;
		}
}

//enciende el led
void encenderLed(){ 
		digitalWrite(led, HIGH); 
}

//apaga el led
void apagarLed(){
		digitalWrite(led,LOW); 
}

//lee los datos recibidos por serial, los convierte a un string para ser analizados
void recibirDatos(){
		while(Serial.available()){
				lecturaSerial=Serial.readString();          
				lecturaSerial.toCharArray(serverInput,9);   
				//convierte parte del string en un int que representa el parametro bajo el que se encendera la luz
				valorMaxChar[0] = serverInput[2];	    
				valorMaxChar[1] = serverInput[3];	   
				valorMaxChar[2] = serverInput[4];	    
				valorMaxInt = atoi(valorMaxChar);
				//convierte parte del string en un int que representa el parametro bajo el que se leera el movimiento
				valorSensibilidadChar[0] = serverInput[5];
				valorSensibilidadChar[1] = serverInput[6];
				valorSensibilidadChar[2] = serverInput[7];
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
		if(controlManualActivado(serverInput[0])==true){	
				if(serverInput[1]=='0'){
						apagarLed();
				}
				else if(serverInput[1] == '1'){
						encenderLed();	
				}				
		}
		else if(controlManualActivado(serverInput[0])==false){
				controlAutomatico();}
}

//revisa si hay movimiento, para realizar el control automatico
//el control automatico compara el nivel de luz medido por el fotoresistor con el valor establecido por el usuario, para 
//encender o apagar el led
void controlAutomatico(){
		while(hayMovimiento(lecturaUltrasonico(),valorSensibilidadInt) == true && Serial.available()==false){			
				if(valorMaxInt<lecturaFotoresistor()){
						encenderLed();
				}
				else {
						apagarLed();
				}
		}
}

//funcion principal que corre en ciclo infinito
void loop(){
		recibirDatos();
		controlManual();
		}

