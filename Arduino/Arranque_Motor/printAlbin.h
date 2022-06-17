
float temp_c;         //Temperatura C° Sensor SHT1x
float temp_f;         //Temperatura F° Sensor SHT1x
float humidity;       //Humedad Sensor SHT1x

float dhth;           //Humedad Sensor DHT
float dhtt;           //Temperatura C° Sensor DHT
float dhtf;           //Temperatura F° Sensor DHT
float hif;            //Indice de calor en F° Sensor DHT
float hic;            //Indice de calor en C° Sensor DHT

float tempCmax1;      //Temperatura C° Sensor max6675 1
float tempFmax1;      //Temperatura F° Sensor max6675 1

float tempCmax2;      //Temperatura C° Sensor max6675 2
float tempFmax2;      //Temperatura F° Sensor max6675 2

struct printAlbin{
  void printDATA(){
      //Serial.print("Sensor SHT interno");
      //Serial.print(datos)
      Serial.print(temp_c);
      Serial.print(",");
      Serial.print(temp_f);
      Serial.print(",");
      Serial.print(humidity);
      Serial.print(",");
      //Serial.println("Sensor DHT Externo")
      Serial.print(dhtt);
      Serial.print(",");
      Serial.print(dhtf);
      Serial.print(",");
      Serial.print(dhth);
      Serial.print(",");
      Serial.print(hic);
      Serial.print(",");
      Serial.print(hif);
      Serial.print(",");
      //Serial.println("Sensor max6675 1")
      Serial.print(tempCmax1);
      Serial.print(",");
      Serial.print(tempFmax1);
      Serial.print(",");
      //Serial.println("Sensor max6675 2");
      Serial.print(tempCmax2);
      Serial.print(",");
      Serial.println(tempFmax2);
  };
 
};
