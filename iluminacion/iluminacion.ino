const int led = 13;
const int fotoresistor = A0;
int valorFotoresistor = 0;
int i;
int valorMaxInt;
char inputServer[8];
char valorMaxChar[4];
String x;
 //para ultrasonico
const int  echo = 11;
const int trig = 12;
long duracion; 
long distancia;
char valorSensibilidadChar[4];
int valorSensibilidadInt;
void setup(){
  
 pinMode(led, OUTPUT) ;// Se declara el pin como salida
 Serial.begin(9600);// Configuracion de la conexion serial y velocidad
 pinMode(fotoresistor, INPUT); // Se declara el pin como entrada
 pinMode(echo, INPUT);     // declara el pin como entrada
 pinMode(trig, OUTPUT);    // dvlara el pin como salida
}

void ctrl_light(int a){
  valorFotoresistor = analogRead(fotoresistor);
  if (valorFotoresistor < a ){
    digitalWrite(led, HIGH);    
  }
  else {
    digitalWrite(led, LOW);
  }
}

boolean hayMovimiento(int sensibilidad){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duracion = pulseIn(echo, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  if(distancia < sensibilidad){
    return true;
  }//terminad if distancia<sensibilidad
  else{return false;}
}

void loop(){
 while(Serial.available()){
    x = Serial.readString();
    x.toCharArray(inputServer,9);
    valorMaxChar[0] = inputServer[2];
    valorMaxChar[1] = inputServer[3];
    valorMaxChar[2] = inputServer[4];
    valorMaxInt = atoi(valorMaxChar);
    valorSensibilidadChar[0] = inputServer[5];
    valorSensibilidadChar[1] = inputServer[6];
    valorSensibilidadChar[2] = inputServer[7];
    valorSensibilidadInt = atoi(valorSensibilidadChar);
    while(inputServer[0]=='0'){ //pide control manual apagado
      if(Serial.available()){
      break;
      }//termina if serialavailable
      while(hayMovimiento(valorSensibilidadInt) == true){
         ctrl_light(valorMaxInt);     
      }//termina while haymovimiento ==true
    }//termina while [0] = '0'
    if(inputServer[0]=='1'){ //pide control manual encendido
      if(inputServer[1]=='0'){
         digitalWrite(led, LOW);
      }//termina if estado apagado
      else if(inputServer[1]=='1'){
         digitalWrite(led, HIGH);
      }//termina if estado apagado
    }//termina if control manual
  }//termina while serialavailable
}//termina loop
