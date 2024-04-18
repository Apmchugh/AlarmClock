// Use Flag variables for executions for IR_Remote

#include <DIYables_IRcontroller.h> // DIYables_IRcontroller library
#include <LiquidCrystal.h>
#define IR_RECEIVER_PIN 7 // The Arduino pin connected to IR controller

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200); // debounce time is 200ms

//Global Variables
int pressed = 0;
String number_pressed;
int mode = 0;
int hours, minutes, seconds;
int hours1, minutes1;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long previousMillis;
const unsigned long interval = 1000;  // 1 second
String h1, h2, m1, m2;
int h3, m3;
int count = 0;


void IRController() {
  Key21 key = irController.getKey();
  if (key != Key21::NONE) {

    switch (key) {

      case Key21::KEY_CH_MINUS:
        Serial.println("CH-");
        pressed = 1;
        break;

      case Key21::KEY_CH:
        //Serial.println("CH"); // This is the mode button
        pressed = 1;
        mode = 1;
        break;

      case Key21::KEY_CH_PLUS:
        //Serial.println("CH+"); // This is the mute button
        pressed = 1;
        break;

      case Key21::KEY_PREV:
        Serial.println(">||");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_NEXT:
        Serial.println("<<");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_PLAY_PAUSE:
        Serial.println(">>");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_MINUS:
        Serial.println("EQ");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_EQ:
        Serial.println("+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("-");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_100_PLUS:
        Serial.println("100+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_200_PLUS:
        Serial.println("200+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_0:
        //Serial.println("0");
        pressed = 1;
        number_pressed = "0";
        break;

      case Key21::KEY_1:
        //Serial.println("1");
        pressed = 1;
        number_pressed = "1";
        break;

      case Key21::KEY_2:
        //Serial.println("2");
        pressed = 1;
        number_pressed = "2";
        break;

      case Key21::KEY_3:
        //Serial.println("3");
        pressed = 1;
        number_pressed = "3";
        break;

      case Key21::KEY_4:
        //Serial.println("4");
        pressed = 1;
        number_pressed = "4";
        break;

      case Key21::KEY_5:
        //Serial.println("5");
        pressed = 1;
        number_pressed = "5";
        break;

      case Key21::KEY_6:
        //Serial.println("6");
        pressed = 1;
        number_pressed = "6";
        break;

      case Key21::KEY_7:
        //Serial.println("7");
        pressed = 1;
        number_pressed = "7";
        break;

      case Key21::KEY_8:
        //Serial.println("8");
        pressed = 1;
        number_pressed = "8";
        break;

      case Key21::KEY_9:
        //Serial.println("9");
        pressed = 1;
        number_pressed = "9";
        break;

      default:
        Serial.println("WARNING: undefined key:");
        break;
    }
  }
}
void setup() {
  Serial.begin(9600);
  irController.begin();
  Serial.setTimeout(100);  // 100ms timeout for serial input
  Serial.println("Set Time in hh:mm:ss format");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Set time in");
  lcd.setCursor(0, 1);
  lcd.print("hh:mm:ss format");
  delay(500);
  lcd.clear();
  pinMode(52, OUTPUT); // defining buzzer signal pins
  pinMode(53, OUTPUT);
  digitalWrite(52, HIGH); // defaulting them to off (*this can change depending on model of buzzer)
  digitalWrite(53, LOW);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // When previousMillis would be set to currentMillis,
    // then a delay in the code would delay the clock.
    // When previousMillis is incremented with 1 second,
    // then it stays synchronized.
    previousMillis += interval;  // increment with 1 second

    seconds += 1;
    if (seconds >= 60) {
      seconds = 0;
      minutes += 1;
    }
    if (minutes >= 60) {
      minutes = 0;
      hours += 1;
    }
    if (hours >= 24) {
      hours = 0;
    }

    // Update the time to the serial monitor and lcd!
    // The format is  hh:mm:ss.
    if (hours < 10) {
      Serial.print("0");
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.setCursor(1, 1);
      lcd.print(hours);
      Serial.print(hours);
    } else {
      lcd.setCursor(0, 1);
      lcd.print(hours);
      Serial.print(hours);
    }
    lcd.setCursor(0, 1);
    Serial.print(":");
    lcd.setCursor(2, 1);
    lcd.print(":");
    if (minutes < 10) {
      Serial.print("0");
      lcd.setCursor(3, 1);
      lcd.print("0");
      lcd.setCursor(4, 1);
      lcd.print(minutes);
      Serial.print(minutes);
    } else {
      Serial.print(minutes);
      lcd.setCursor(3, 1);
      lcd.print(minutes);
    }
    Serial.print(":");
    lcd.setCursor(5, 1);
    lcd.print(":");
    if (seconds < 10) {
      Serial.print("0");
      lcd.setCursor(6, 1);
      lcd.print("0");
      lcd.setCursor(7, 1);
      lcd.print(seconds);
      Serial.print(seconds);
    } else {
      Serial.print(seconds);
      lcd.setCursor(6, 1);
      lcd.print(seconds);
    }
    Serial.println();
  }

  IRController(); // 

  if (pressed == 1) {

    while (mode == 1) {
      lcd.setCursor(0, 0);
      lcd.println("Set Alarm hhmm");
      //Serial.println("Set Alarm hhmm");

      // Need a way to get the values for each button press without using break statements. Might have to rewrite code for IR using count instead of case to avoid break statements.
      // <<Put this code here>>
      IRController();

      //Serial.println(pressed);
      //Serial.println(number_pressed);
      if (pressed == 1) {
        pressed = 0;
        count += 1;
        Serial.print("\t");
        //Serial.println(count);

        if (count == 2) {
          h1 = number_pressed;
        }

        if (count == 3) {
          h2 = number_pressed;
          h3 = (String(h1) + String(h2)).toInt();
          h1 = "";
          h2 = "";
          Serial.print(h3);
        }

        if (count == 4) {
          m1 = number_pressed;
        }

        if (count == 5) {
          m2 = number_pressed;
          m3 = (String(m1) + String(m2)).toInt();
          Serial.print(m3);
          m1 = "";
          m2 = "";
          hours1 = constrain(h3, 0, 23);
          minutes1 = constrain(m3, 0, 59);
          lcd.setCursor(0, 0);
          lcd.print("Alarm Set");
          count = 0;
          pressed = 0;
          break; // nessecary to get out of while loop
        }
      }
    }
    int h = (String(number_pressed[0]) + String(number_pressed[1])).toInt(); // defining all variables to their correct types
    int m = (String(number_pressed[2]) + String(number_pressed[3])).toInt();
    int s = (String(number_pressed[4]) + String(number_pressed[5])).toInt();
    hours = constrain(h, 0, 23);
    minutes = constrain(m, 0, 59);
    seconds = constrain(s, 0, 59);
    number_pressed = ""; // think about this

    // Serial.println(number_pressed[0]);
    // Serial.print(number_pressed[1]);
    // Serial.print(number_pressed[2]);
    // Serial.print(number_pressed[3]);
    // Serial.print(number_pressed[4]);
    // Serial.println(number_pressed[5]);
    //Serial.println(hours);
    pressed = 0;
  }
  if ((hours1 == hours) && (minutes1 == minutes) && (currentMillis > 60000)) { // so alarm does't go off right away (*alarm can never go off in less than a minute)
    digitalWrite(52, LOW);
    delayMicroseconds(500);
    digitalWrite(52, HIGH);
    delayMicroseconds(500);
    digitalWrite(53, HIGH);
    delayMicroseconds(500);
    digitalWrite(53, LOW);
    delayMicroseconds(500);
  }
}
