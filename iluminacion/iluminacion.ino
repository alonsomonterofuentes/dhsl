const int led = 13;
const int fotoresistor = A0;
int valorFotoresistor = 0;
int i;
int valorMaxInt;
char inputServer[6];
char valorMaxChar[4];
String x;

void setup(){
  // Se declara el pin como salida
 pinMode(led, OUTPUT) ;
  // Configuracion de la conexion y velocidad
 Serial.begin(9600);
 // Se declara el pin como entrada
 pinMode(fotoresistor, INPUT);
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

void loop(){
 while(Serial.available()){
    x = Serial.readString();
    x.toCharArray(inputServer,6);
    valorMaxChar[0] = inputServer[2];
    valorMaxChar[1] = inputServer[3];
    valorMaxChar[2] = inputServer[4];
    valorMaxInt = atoi(valorMaxChar);
    while(inputServer[0]=='0'){ //pide control manual apagado
      if(Serial.available()){
      break;
      }//termina if serialavailable
     ctrl_light(valorMaxInt);     
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
