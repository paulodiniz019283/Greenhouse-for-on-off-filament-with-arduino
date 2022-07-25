
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>


//Declarando variaveis para os pinos

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int pinoPOT = A15;
int p1r = 13;
int sens = A0;
int luz = 10;
int tensaopot = 0;
int temperaturaConvertida =0;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  pinMode(pinoPOT, INPUT); //Pino do Potenciometro
  pinMode(p1r, OUTPUT);    //Pino do Relé
  pinMode(sens,INPUT);     //Pino do sensor
  Serial.begin(9600);
  lcd.init();              // initialize the lcd  
  
  // Print a message to the LCD.
  lcd.backlight();
  dht.begin();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(0,1);
  lcd.print("Umid: ");
}

void loop()
{

  //Variaveis que estamos utilizando para reconhecer a temperatura
  tensaopot = map(analogRead(pinoPOT), 0, 1023, 0, 60);
  int temp = dht.readTemperature();
  int umid = dht.readHumidity();
  delay(500);

  // Comparando a temperatura interna x Temperatura Externa
  if (tensaopot > temp){
    // Acionando a Lâmpada através do relé
    digitalWrite(p1r,HIGH);
  }else{
    // Desligando a Lâmpada atrves do relé
    digitalWrite(p1r,LOW);
  }
  delay(250);

  //Imprimindo no visor as informacoes
  lcd.setCursor(5,0);
  lcd.print(temperaturaConvertida);
  lcd.print("/");
  lcd.print(temp);
  lcd.setCursor(5,1);
  lcd.print(umid);

  
}
