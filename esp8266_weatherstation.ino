#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//test

// Sensor pinouts
// 0 - 5V
// 1 - signal, Arduino pin D3
// 2 - not used
// 3 - GND


// Display pinouts
// VCC
// GND
// SCL - Arduino pin D1
// SDA - Arduino pin D2
     
// Temperature bits
    #define DHTPIN D3     // what pin we're connected to
    #define DHTTYPE DHT22   // DHT 22  (AM2302)
     
    int maxHum = 99;
    int maxTemp = 40;

    float humid;
    float temp;
     
    DHT dht(DHTPIN, DHTTYPE);

// Display bits

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);
    
     
    void setup() {
      Serial.begin(115200); 
      //Temperature bits
      dht.begin();

      //Display bits
      OLED.begin();
      OLED.clearDisplay();
 
      //Add stuff into the 'display buffer'
      OLED.setTextWrap(false);
      OLED.setTextSize(1);
      OLED.setTextColor(WHITE);
      OLED.setCursor(0,0);
      OLED.println("Initializing...");
 
      OLED.display(); //output 'display buffer' to screen  
      //OLED.startscrollleft(0x00, 0x0F); //make display scroll 

      
    }
     
    void loop() {
      // Wait a few seconds between loops
      delay(2000);
     
      
     determineTemperature(); 
     updateSerial();
     updateDisplay();
    }

    void determineTemperature()
    {
      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      humid = dht.readHumidity();
      // Read temperature as Celsius
      temp = dht.readTemperature();
    }
    
    void updateDisplay()
    {
      OLED.clearDisplay();
      OLED.setCursor(0,0);
      OLED.print("Humidity: ");
      OLED.print(humid);
      OLED.println(" %");
      OLED.print("Temp:     ");
      OLED.print(temp);
      OLED.println(" c");
      OLED.display();
      updateDisplay();
    }

    void updateSerial()
    {
      Serial.print("Humidity: "); 
      Serial.print(humid);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(temp);
      Serial.println(" *C ");
    }

