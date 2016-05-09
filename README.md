<H1>Domótica con Herramientas de software Libre</H1>
<ul>
<li>Alonso Montero
<li>Brian Morera
<li>Isaac Gómez
</ul>
<H1>Instrucciones de Instalación y Uso</H1>
<H2>Requerimientos</H2>
<ul>
<li>Python 2.7
<li>Arduino IDE
<li>Raspberry Pi
<li>2 x Arduino Uno
</ul>
<H2>Preparación del Raspberry Pi</H2>
<img src="https://github.com/alonsomonterofuentes/dhsl/blob/master/ventilador.png" style="width:304px;height:228px;">
<img src="https://github.com/alonsomonterofuentes/dhsl/blob/master/iluminacion.png" style="width:304px;height:228px;">
<p>
Para el proyecto se utilizó la distribución <a href="https://www.raspbian.org">Raspbian</a> como el sistema operativo que corre en el Raspberry Pi. Para instalar este sistema operativo, siga las <a href="https://www.raspberrypi.org/documentation/installation/installing-images/">instrucciones</a> oficiales de instalación.
</p>
<H2>Preparación de los arduinos</H2>
Los arduinos deben estar conectados a los sensores y actuadores de la siguiente manera:

<H2>Obtención del código</H2>
<p>Vaya al directorio donde quiere instalar el programa</p>
<code>pi@raspberrypi:~$ git clone https://github.com/alonsomonterofuentes/dhsl</code>
<p>

<H2>Instalación del Sistema</H2>
Una vez dentro del sistema operativo, instale Arduino IDE. Puede hacer esto desde la terminal con:
</p>
<code>
pi@raspberrypi:~$ sudo apt-get install arduino
</code>
<p>
Cuando Arduino IDE esté instalado, ejecútelo:
</p>
<code>pi@raspberrypi:~$ arduino</code>
<p>
Ahora de ahí,abra el archivo <code>iluminacion.ino</code>
</p>
<p>Conecte un arduino y presione <code>ctrl+u</code> para subir el programa al arduino.</p> 
<p>Observe en la esquina derecha inferior a cual puerto está conectado el arduino, por ejemplo</p>
<code>Arduino Uno on /dev/tty/ACM0 </code>
<p>Conecte el segundo arduino y suba* el programa <code>ventilador.ino</code>.</p>
<p>*Asegurarse de que no se este subiendo al mismo puerto, esto puede ser verificado como en esta imagen:</p>
<img src="https://www.arduino.cc/en/uploads/Guide/Edison_linux_port_select.png" style="width:304px;height:228px;">
<p>Cuando los arduinos esten conectados, se debe conectar una cámara web al Raspberry Pi</p>
<H1>Instrucciones de uso (menú)</H1>
<p>
Una vez que ambos arduinos estén conectados, y con su programa subido, vaya el directorio donde clonó el repositorio y corra el comando </p>
<code>pi@raspberrypi:~/dhsl$ python menu.py</code>
<p>
Esto correrá el menu principal del programa. 
</p>
En la opción de <code>Configurar Servidor</code> se encontrán las opciones de <code>arduino1</code> y <code>arduino2</code>. Estos representan el arduino para iluminación y ventilación respectivamente. Estos deben ser configurados con sus puertos respectivos.
<p>Ademas de estas opciones de encontrarán las opciones para Temperatura:</p>
<ul>
<li><code>max</code> : Representa el valor en grados Centígrados sobre el cual se encederá el ventilador en modo automático.
<li><code>controlmanual</code> : 1 representa control manual activado, 0 representa control automático activado.
</ul>
<p> Si se activa el control manual, debe además establecerse el estado del abanico, esto se encuentra en la opción de abanico:
<ul>
<li> <code>estado</code> : Toma valores de 1 para encendido y 0 para apagado
</ul>
<p> Para controlar la iluminación se selecciona iluminación, sus opciones son:
<ul>
<li><code>max</code> : Representa el valor sobre el cual se encederá el bombillo en modo automático.
<li><code>controlmanual</code> : 1 representa control manual activado, 0 representa control automático activado.
</ul>
<p> Si se activa el control manual, debe además establecerse el estado del bombillo, esto se encuentra en la opción de bombillo:
<ul>
<li> <code>estado</code> : Toma valores de 1 para encendido y 0 para apagado
</ul>
Si se selecciona control automático, es importante darle un valor a la distancia bajo la cual el sensor ultrasónico leerá movimiento, esto se hará en la opción Ultrasonico:
<ul>
<li> <code>sensibilidad</code> : Toma valores entre 0 y 500 centímetros.
</ul>
</p>Al terminar de configurar las opciones se debe seleccionar la opción <code>Escribir a arduino</code> para que las opciones tomen efecto.</p>
<p>Si se desea tomar una foto se debe seleccionar la opción <code>Tomar Foto</code> e ingresarle el nombre que quiere que tenga la foto.</p>
