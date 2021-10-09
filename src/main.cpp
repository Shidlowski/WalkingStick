// #include <Arduino.h>
// #include <Wire.h>
// #include <Tone32.h>

// #include <Adafruit_I2CDevice.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// #define PIN_BTN_SOS 34
// #define PIN_BTN_OLED 23
// #define PIN_ZUMMER 25
// #define BUZZER_CHANNEL 0

// bool is_sos = false;
// bool is_btn_oled = false;
// int wait_btn_oled = 0;

// String utf8rus(String source);

// void setup() {
//   pinMode(PIN_ZUMMER, OUTPUT);
//   pinMode(PIN_BTN_OLED, INPUT);
//   pinMode(PIN_BTN_SOS, INPUT);

//   ledcSetup(0, 2000, 8);
//   ledcAttachPin(PIN_ZUMMER, 0);

//   Serial.begin (9600);  
 
//   Wire.begin (21, 22);   // sda= GPIO_21 /scl= GPIO_22  

//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // инициализация дисплея по интерфейсу I2C, адрес 0x3C
//   display.cp437(true);
//   display.clearDisplay(); // очистка дисплея
//   display.setRotation(2); // rotate 180 degrees
//   display.setTextSize(3); // установка размера шрифта
//   display.setTextColor(WHITE); // установка цвета текста
//   display.setCursor(5, 0); // установка курсора в позицию X = 0; Y = 0
//   display.print (utf8rus("ТРОСТЬ")); // записываем в буфер дисплея нашу фразу
//   display.display(); // и её выводим на экран
// }

// void loop() {
//   if(digitalRead(PIN_BTN_SOS)){
//       is_sos = true;
//       display.clearDisplay(); // очистка дисплея
//       display.setTextSize(2); // установка размера шрифта
//       display.setRotation(2); // rotate 180 degrees
//       display.setTextColor(WHITE); // установка цвета текста
//       display.setCursor(5, 0); // установка курсора в позицию X = 0; Y = 0
//       display.print (utf8rus("ПОМОГИТЕ!    SOS")); // записываем в буфер дисплея нашу фразу
//       display.display(); // и её выводим на экран

//       wait_btn_oled = 0;
//   }

//   if(digitalRead(PIN_BTN_OLED)){
//         Serial.println(digitalRead(PIN_BTN_OLED));
//         is_sos = false;
//         display.clearDisplay(); // очистка дисплея
//         display.setTextSize(2); // установка размера шрифта
//         display.setRotation(2); // rotate 180 degrees
//         display.setTextColor(WHITE); // установка цвета текста
//         display.setCursor(5, 0); // установка курсора в позицию X = 0; Y = 0
//         display.print (utf8rus("ВСЕ ХОРОШО")); // записываем в буфер дисплея нашу фразу
//         display.display(); // и её выводим на экран
//         is_btn_oled = true;
//         wait_btn_oled = 0;
//   } 
  
//   if(is_sos){    
//     tone(PIN_ZUMMER, 4965, 5, BUZZER_CHANNEL);
//   } else{
//     noTone(PIN_ZUMMER, BUZZER_CHANNEL);
//   }

// }

// /* Функция перекодировки русских букв из UTF-8 в Win-1251 */
// String utf8rus(String source)
// {
//   int i,k;
//   String target;
//   unsigned char n;
//   char m[2] = { '0', '\0' };
//   k = source.length(); i = 0;
//   while (i < k) {
//     n = source[i]; i++;
//     if (n >= 0xC0) {
//       switch (n) {
//         case 0xD0: {
//           n = source[i]; i++;
//           if (n == 0x81) { n = 0xA8; break; }
//           if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
//           break;
//         }
//         case 0xD1: {
//           n = source[i]; i++;
//           if (n == 0x91) { n = 0xB8; break; }
//           if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
//           break;
//         }
//       }
//     }
//     m[0] = n; target = target + String(m);
//   }
// return target;
// }

#include <Arduino.h>
#include <Wire.h>
#include <Tone32.h>

#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

#define PIN_BTN_SOS 34
#define PIN_BTN_OLED 23
#define PIN_ZUMMER 25
#define BUZZER_CHANNEL 0

bool is_sos = false;
bool is_btn_oled = false;
int wait_btn_oled = 0;
int wait_btn_sos = 0;


String utf8rus(String source);
void setText(String text,int size, int x, int y);

void setup() {
  pinMode(PIN_ZUMMER, OUTPUT);
  pinMode(PIN_BTN_OLED, INPUT);
  pinMode(PIN_BTN_SOS, INPUT);

  ledcSetup(0, 2000, 8);
  ledcAttachPin(PIN_ZUMMER, 0);

  Serial.begin (9600);  
  Wire.begin (21, 22);   // sda= GPIO_21 /scl= GPIO_22  

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // инициализация дисплея по интерфейсу I2C, адрес 0x3C
  display.cp437(true);  
  // setText("ТРОСТЬ",3,5,0);
  String tmp_str="Запуск";
  for(int i=0;i<15;i++){
    setText(tmp_str,2,5,0);
    tmp_str+=".";
    delay(100);
  }
  setText("ТРОСТЬ",3,5,5);
}

void loop() {

  if(digitalRead(PIN_BTN_SOS)){
      setText("ПОМОГИТЕ!    SOS",2,5,0);
      is_btn_oled = false;
      is_sos = true;

      wait_btn_oled=0;
  }

  if(digitalRead(PIN_BTN_OLED)){
        setText("ВСЕ ХОРОШО",2,0,10);
        is_sos = false;
        is_btn_oled = true;

        wait_btn_oled = 0;
  } 
  
  if(not digitalRead(PIN_BTN_SOS) && is_btn_oled && wait_btn_oled<=1000){
    Serial.println(wait_btn_oled);
    wait_btn_oled+=1;
    delay(10);
    Serial.println(wait_btn_oled);
  }

  if(is_btn_oled && wait_btn_oled>700){
    setText("Активация сна............",2,0,0); /// очистим дисплей
  }

  if(is_btn_oled && wait_btn_oled>1000){
    Serial.println("YES");
    is_btn_oled = false;
    wait_btn_oled = 0;
    setText("                     ",2,0,0); /// очистим дисплей
  }

  if(is_sos){    
    tone(PIN_ZUMMER, 4965, 5, BUZZER_CHANNEL);
  } else{
    noTone(PIN_ZUMMER, BUZZER_CHANNEL);
  }

}

/* Функция перекодировки русских букв из UTF-8 в Win-1251 */
String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}

void setText(String text, int size, int x, int y){
    is_sos = false;
    display.clearDisplay(); // очистка дисплея
    display.setTextSize(size); // установка размера шрифта
    display.setRotation(2); // rotate 180 degrees
    display.setTextColor(WHITE); // установка цвета текста
    display.setCursor(x, y); // установка курсора в позицию X = 0; Y = 0
    display.print (utf8rus(text)); // записываем в буфер дисплея нашу фразу
    display.display(); // и её выводим на экран
}