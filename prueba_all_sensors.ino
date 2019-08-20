//Universidad del Valle
// Curso de Tecnologías Geomáticas
//Docente: Ing. Carlos Quiroga

//Hecho por:
//Vanessa Hernandez Bedoya y Jose Miguel Vera Saavedra

// librerias sensor GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Libreias sensro Atmosférico
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Libreria sensor de Temperatura
#include <OneWire.h>                
#include <DallasTemperature.h>

//GPS
SoftwareSerial serial_connection(0, 1); //RX=pin 0, TX=pin 1 Donde se entabla la conexión al puerto serial
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

//Atmosférico
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;


//Temp
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire);


void setup() {//función para el sensor de temperatura
  Serial.begin(9600);
//GPS  
  serial_connection.begin(9600);
  //Atm
    while(!Serial);    // time to get serial running
    

    unsigned status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1);
           }


    //Temperature------------------------------------------------------------------------
    sensors.begin();

    //------------------------------------------------------------------------------------
    Serial.println("-- Iniciando la lectura --");
    Serial.println();
   
}



void loop() 
{
  
    miGps();
  
    
}

void miGps(){

  //GPS----------------------------------------------------------------------------------------------
   while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
    
    
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    
    Serial.print(gps.time.hour());
    Serial.print(",");
    Serial.print(gps.time.minute());
    Serial.print(",");
    Serial.print(gps.time.second()); 
    Serial.print(",");
    Serial.print(gps.date.year());
    Serial.print(",");
    Serial.print(gps.date.month());
    Serial.print(","); 
    Serial.print(gps.date.day());
    Serial.print(",");
    Serial.print(gps.satellites.value());
    Serial.print(",");
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
    Serial.print(",");
    Serial.print(gps.altitude.meters());
    Serial.print(",");
    
    delay(1000);//se define el tiempo de lectura en milisegundos
    
    atmosferico();
    temperatura();
    conductividad();
    
  }

  }


//función para el sensor atmosférico
  void atmosferico(){ 
    
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.print(",");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.print(",");
    Serial.print(bme.readHumidity());
    Serial.print(",");
    Serial.print(bme.readTemperature());
    Serial.print(",");
    delay(500); 
    }

//función para el sensor de Temperatura
  void temperatura(){
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp= sensors.getTempCByIndex(0); 
    Serial.print(temp);
    Serial.print(",");
    delay(500); 
    }

//función para el sensor de conductividad
  void conductividad(){
    Serial.println(0.0048828125*analogRead(0));
    delay(500);
    }
