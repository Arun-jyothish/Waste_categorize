#include <Servo.h>
#include <NewPing.h>
Servo int_lid_Servo;
Servo ext_lid_Servo;
Servo distributor;
#define trig 9
#define echo 10
#define max_dist 1000

NewPing sonar(trig, echo, max_dist);

int wet_bin_angle = 0;
int dry_bin_angle = 90;
int metal_bin_angle = 180;

int dry_led = A0;
int wet_led = A1;
int metal_led = A2;

const int distributor_servo_pin  = 11;
const int int_lid_servo_pin = 6;
const int ext_ext_lid_Servo_pin  = 3;
bool flag = true;

int wet_sensor_pin = 2; /// connect wet sensor pin
int metal_sensor = 7;
int approch_dist = 10;  /// set approching distance
int int_lid_open_angle = 90;   // when metal detect
int int_lid_close_angle = 0; // when no metal detecdt
int ex_close_lid = 0; //when away from system close
int ex_open_lid = 180; // when approch lid open

void setup() {
          pinMode(dry_led,OUTPUT);
                    pinMode(wet_led,OUTPUT);
                              pinMode(metal_led,OUTPUT);
  // put your setup code here, to run once
  int_lid_Servo.attach(int_lid_servo_pin);
  ext_lid_Servo.attach(ext_ext_lid_Servo_pin);
  distributor.attach(distributor_servo_pin);
  pinMode(metal_sensor, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(300);
  bool is_wet = !digitalRead(wet_sensor_pin);

  int dist = sonar.ping_cm();
  Serial.print("ultrasonic sensor read:  ");
  Serial.println(dist);
  if (dist < approch_dist) {
    ext_lid_Servo.write(ex_open_lid);
    digitalWrite(dry_led,LOW);
     
    digitalWrite(wet_led,LOW);
    digitalWrite(metal_led,LOW);
    flag = true;
    Serial.println(" open ext lid servo ");
    delay(2000);
  }
  else {
    ext_lid_Servo.write(ex_close_lid);
    Serial.println("close ext lid servo");
    bool is_metal = digitalRead(metal_sensor);
    if ( is_metal == LOW && flag ) {
      Serial.println("metal detected");
      distributor.write(metal_bin_angle);
              digitalWrite(metal_led,HIGH);
      //delay(2000);
//      int_lid_Servo.write(int_lid_open_angle);
      Serial.println("open int lid servo");
      delay_ts();
    }
    else {


      if ( is_wet && flag ) {
        distributor.write(wet_bin_angle);
                digitalWrite(wet_led,HIGH);
        Serial.println("distributor at wet bin");
//        delay(2000);
//        int_lid_Servo.write(int_lid_open_angle);
        Serial.println("open int lid");
        delay_ts();
      }
      else if(!is_wet && flag ){
        distributor.write(dry_bin_angle);
        digitalWrite(dry_led,HIGH);                                          /// dry led
        Serial.println("distributor at dry bin");
        //delay(2000);
//        int_lid_Servo.write(int_lid_open_angle);
        Serial.println("open int lid");
        delay_ts();
      }
     
    }

  }

}

void delay_ts() {
  Serial.println("dealy ts fn called ");
  delay(3000);
  if (flag) {
    int_lid_Servo.write(int_lid_open_angle);
    delay(2000); // delay dump time
    int_lid_Servo.write(int_lid_close_angle);
    flag = false;
  }
}
