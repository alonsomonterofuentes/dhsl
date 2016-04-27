#include <math.h> //se añade el paquete math.h 

//se declaran las variables
const int inPin = 0; //Se adjudica sensorPin al pin 0.
const int outPin = 9;     //Se adjudica motor al pin 9.
int sensorValue = 0; //
int i;
int first_input_server;
int second_input_server;
int value_max;
char input_server[6];
String x;

// setup() - esta funcion se inicializa una vez que se encende el Arduino
      
void setup()
{
      Serial.begin(9200);      /* Se inicializa la coneccion seria con la computadora 
                                  para ver la tesnsion, la resistencia y la temperatura 
                                  en el monitor serial (control+shift+m). */
      pinMode(outPin, OUTPUT);  // Se define la variable motor como una variabla de salida.
}
    
void ctrl_temp(int a){
   // Se toma lectura de la medida de tension del termistor. 
     int reading = analogRead(inPin);  
     
     // Se convierte esa lectura a volts. 
     double voltage = reading * 5.0;
     voltage /= 1023.0; 
     
     // Se imprime la tension. 
     Serial.print(voltage); Serial.println(" volts");
     
     // Se determina la resistencia del termistor a partir de la tension.
     double resistencia = (voltage)/(5-(voltage));
     Serial.print(resistencia); Serial.println(" kohm"); 
     
     // Se utiliza la ecuacion de Steinhart-Hart para calcular la temperatura el Kelvin y luego se pasa Celsius 
     double temperaturaC = pow(0.003356 + log(resistencia/50)*0.0002379, -1) -273;
     Serial.print(temperaturaC); Serial.println(" degrees C");
     
     if(temperaturaC > a){ //se define el parametro  bajo el cual se encendera el motor
     digitalWrite(outPin, HIGH);
     }
     
     else{   //sino el motor se apaga 
     digitalWrite(outPin, LOW);
     }
     
     delay(1000);                                     //esperar un segundo
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
          digitalWrite(outPin, LOW);
        }
        else {
          digitalWrite(outPin, HIGH);
        }
        break;
      }
  }
}
