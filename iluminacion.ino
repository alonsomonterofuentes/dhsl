const int outPin = 13; // Pin dedicado a la salida
const int inPin = A0; // Pin dedicado a la entrada
int sensorValue = 0;
int i;
int first_input_server;
int second_input_server;
int value_max;
char input_server[6];
String x;



 
void setup(){
  // Se declara el pin como salida
 pinMode(outPin, OUTPUT) ;
  // Configuracion de la conexion y velocidad
 Serial.begin(9600);
 // Se declara el pin como entrada
 pinMode(inPin, INPUT);
}

void ctrl_light(int a){
  sensorValue = analogRead(inPin);
  if (sensorValue < a ){
    digitalWrite(outPin, HIGH);    
  }
  else {
    digitalWrite(outPin, LOW);
  }
}

void loop(){
  while(Serial.available()){
    x = Serial.readString();
    x.toCharArray(input_server,6);
    first_input_server = atoi(&input_server[0]);
    second_input_server = atoi(&input_server[1]);
    value_max = atoi(&input_server[2-4]);
    switch(first_input_server){
      case '0':
        ctrl_light(value_max);  
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
