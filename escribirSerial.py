import ConfigParser
import serial
class escribirSerial:
		#el init pide el puerto en que esta conectado el arduino de iluminacion(uno) y el puerto donde esta el arduino de ventilacion(dos)
		#despues escibe los datos del archivo de configuracion por medio del serial
		def __init__(self,uno,dos):
						self.Config = ConfigParser.ConfigParser()
						#inicializa comunicacion al puerto "uno" a 9600 bauds
						self.ser = serial.Serial("/dev/ttyACM"+uno,9600)
						#lee del archivo de configuracion
						self.Config.read("config.ini")
						controlManualIluminacion =self.Config.get("Iluminacion","controlManual")		
						#lee los datos requeridos del archivo de configuracion, luego escribe al serial las opciones de la configuracion
						if(controlManualIluminacion == "0"):
								dato  = str(self.Config.get("Iluminacion","controlManual")+self.Config.get("Bombillo","estado")+self.Config.get("Iluminacion","max")+self.Config.get("Ultrasonico","sensibilidad"))
								self.ser.write(dato)
						elif(controlManualIluminacion == "1"):
								dato  = str(self.Config.get("Iluminacion","controlManual")+self.Config.get("Bombillo","estado")+self.Config.get("Iluminacion","max")+self.Config.get("Ultrasonico","sensibilidad"))
								self.ser.write(dato)
						#hace lo mismo que la seccion anterior pero en este caso se conecta al puerto "dos"
						self.ser2 = serial.Serial("/dev/ttyACM"+dos,9600)
						controlManualTemperatura = self.Config.get("Temperatura","controlManual")
						if(controlManualTemperatura == "0"):
								dato2 = str(self.Config.get("Temperatura","controlManual")+self.Config.get("Abanico","estado")+self.Config.get("Temperatura","max"))
								self.ser2.write(dato2)
						elif(controlManualTemperatura == "1"):
								dato2 = str(self.Config.get("Temperatura","controlManual")+self.Config.get("Abanico","estado")+self.Config.get("Temperatura","max"))
								self.ser2.write(dato2)

