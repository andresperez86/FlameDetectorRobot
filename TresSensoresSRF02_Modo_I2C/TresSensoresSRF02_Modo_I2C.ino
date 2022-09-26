   /* Código para Sensor de medición ultrasónico SRF02 utilizando Arduion Uno ó Arduino Nano,
      por comunicacion I2C
      
      SRF02       Arduino
      5v Vcc    -> 5V
      SDA       -> A4
      SCL       -> A5
      Mode      -> No conectar
      0v Ground -> GND
   */

  #include <Wire.h> // Libreria que permite la comunicacion I2C
  
  #define ADDRESS1 112 // Se definimos la direccion del sensor SRF02 (0xE0)
  #define ADDRESS2 114 // Se definimos la direccion del sensor SRF02 (0xE2)
  #define ADDRESS3 115 // Se definimos la direccion del sensor SRF02 (0xE3)
  #define sirena 6    // Declaracion del pin para activar sumbador

  void setup(){
   Serial.begin(9600);       //Se inicia el puerto serie
   pinMode(sirena, OUTPUT);
   Wire.begin();
  }
 
  void loop(){
   byte ByteAlto, ByteBajo;
   int Distancia1, Distancia2, Distancia3;

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
 
   Distancia1 = ((ByteAlto<<8) + ByteBajo); //Calcula la distancia de un objeto al frente del sensor

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

  if (Distancia1 < 20){
      digitalWrite(sirena, HIGH);   
     }
    else {
      digitalWrite(sirena, LOW);    
     } 

    Serial.print("Distancia 1: ");
    Serial.println(Distancia1, DEC);
    Serial.print("Distancia 2: ");
    Serial.println(Distancia2, DEC);
     Serial.print("Distancia 3: ");
    Serial.println(Distancia3, DEC);
 
   delay(500);
  }
