   /*       
      SRF02, TPA81
      5v Vcc    -> 5V
      SDA       -> A4
      SCL       -> A5
      Mode      -> No conectar
      0v Ground -> GND
   */

  #include <Wire.h> // Libreria que permite la comunicacion I2C
  #include <TPA81.h> // Libreria del sensor de temperatura
  #define ADDRESS1 115 // Se definimos la direccion del sensor SRF02 (0xE0) der distancia1 0x73
  #define ADDRESS2 112 // Se definimos la direccion del sensor SRF02 (0xE2) izq distancia2 0x70
  #define ADDRESS3 116 // Se definimos la direccion del sensor SRF02 (0xE3) centro distancia3 0x74

  //Puente H
  //motor A
  #define IN2  9      // IN2 de L298N a pin digital 8
  #define IN1  8      // IN1 de L298N a pin digital 9
  #define ENA  10      // ENA de L298N a pin digital 10

  //motor B
  #define ENB  5      // ENA de L298N a pin digital 5
  #define IN4  7      // IN2 de L298N a pin digital 6  
  #define IN3  6      // IN1 de L298N a pin digital 7


 void Adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 140); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 140); //Velocidad motor B
}

void Atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 120); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 120); //Velocidad motor B
}

void Derecha ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 200); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 100); //Velocidad motor A
}

void Izquierda ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 100); //Velocidad motor A
 
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 200); //Velocidad motor A
}

void Parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
} 
  
void setup(){
   Serial.begin(9600);       //Se inicia el puerto serie
   Wire.begin();  
   
   //Inicializacion de puertos motor A
   pinMode(IN1, OUTPUT);   // pin 2 como salida
   pinMode(IN2, OUTPUT);   // pin 3 como salida  
   pinMode(ENA, OUTPUT);   // pin 5 como salida
   
   //inicializaciond de puertos motor B
   pinMode(IN3, OUTPUT);   // pin 8 como salida
   pinMode(IN4, OUTPUT);   // pin 9 como salida  
   pinMode(ENB, OUTPUT);   // pin 11 como salida
  }
 
void loop(){
   byte ByteAlto, ByteBajo;
   int Distancia1, Distancia2, Distancia3;
  
   //Arrancar motores
   Adelante();

   //Medir distancias
   Wire.beginTransmission(ADDRESS1); // Se empieza la comunicación con el sensor SFR02
   Wire.write(byte(0x00));          // Se escribe en el registro (0x00)
   Wire.write(byte(0x51));          // Devuelve el resultado en centimetros
   Wire.endTransmission();          // Final de la transmisión

   delay(70); // Retardo de 70ms para que el sensor ejecute los comando enviados 
  
   Wire.beginTransmission(ADDRESS1); // Se empieza la comunicación con el sensor SFR02
   Wire.write(byte(0x02));          // Se ubica en el registro #2 para leer el Byte alto de la medida realizada
   Wire.endTransmission();          // Final de la transmisión
   
   Wire.requestFrom(ADDRESS1, 2);    // Se solicita dos Bytes al sensor SFR02 (2 bytes)
  
   while(Wire.available() < 2);     // Se comprueba si los bytes llegan
  
   ByteAlto = Wire.read();  //Se lee el Byte alto
   ByteBajo = Wire.read();  //Se lee el Byte bajo
 
   Distancia1 = ((ByteAlto<<8) + ByteBajo); //Calcula la distancia de un objeto al frente del sensor*/

   Wire.beginTransmission(ADDRESS2); // Se empieza la comunicación con el sensor SFR02
   Wire.write(byte(0x00));          // Se escribe en el registro (0x00)
   Wire.write(byte(0x51));          // Devuelve el resultado en centimetros
   Wire.endTransmission();          // Final de la transmisión

   delay(70); // Retardo de 70ms para que el sensor ejecute los comando enviados 
  
   Wire.beginTransmission(ADDRESS2); // Se empieza la comunicación con el sensor SFR02
   Wire.write(byte(0x02));          // Se ubica en el registro #2 para leer el Byte alto de la medida realizada
   Wire.endTransmission();          // Final de la transmisión
   
   Wire.requestFrom(ADDRESS2, 2);    // Se solicita dos Bytes al sensor SFR02 (2 bytes)
  
   while(Wire.available() < 2);     // Se comprueba si los bytes llegan
  
   ByteAlto = Wire.read();  //Se lee el Byte alto
   ByteBajo = Wire.read();  //Se lee el Byte bajo
 
   Distancia2 = ((ByteAlto<<8) + ByteBajo); //Calcula la distancia de un objeto al frente del sensor

   Wire.beginTransmission(ADDRESS3); // Se empieza la comunicación con el sensor SFR02
   Wire.write(byte(0x00));          // Se escribe en el registro (0x00)
   Wire.write(byte(0x51));          // Devuelve el resultado en centimetros
   Wire.endTransmission();          // Final de la transmisión

   delay(70); // Retardo de 70ms para que el sensor ejecute los comando enviados 
  
   Wire.beginTransmission(ADDRESS3); // Se empieza la comunicación con el sensor SFR02
   Wire.write(byte(0x02));          // Se ubica en el registro #2 para leer el Byte alto de la medida realizada
   Wire.endTransmission();          // Final de la transmisión
   
   Wire.requestFrom(ADDRESS3, 2);    // Se solicita dos Bytes al sensor SFR02 (2 bytes)
  
   while(Wire.available() < 2);     // Se comprueba si los bytes llegan
  
   ByteAlto = Wire.read();  //Se lee el Byte alto
   ByteBajo = Wire.read();  //Se lee el Byte bajo
 
   Distancia3 = ((ByteAlto<<8) + ByteBajo); //Calcula la distancia de un objeto al frente del sensor

  
    Serial.print("Distancia 1: ");
    Serial.println(Distancia1, DEC);
    Serial.print("Distancia 2: ");
    Serial.println(Distancia2, DEC);
     Serial.print("Distancia 3: ");
    Serial.println(Distancia3, DEC);

   if ( Distancia3 < 50){
            Parar();
            delay(100);
            Derecha();
            delay(120);
      }else if(Distancia1 < 50 && Distancia3 < 50){
            Parar();
            delay(100);
            Izquierda();
            delay(120);
      }
      else if ( Distancia2 < 50 and Distancia3 < 50 and Distancia1 < 50){
            Parar();
            delay(100);
        Atras();
        delay(500);
      }
   else {
      Adelante(); 
     } 
  }

//funciones de sentido de giro, marcha y paro de motors
