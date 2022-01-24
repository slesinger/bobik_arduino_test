#include <Arduino.h>

struct motor_pins_t
{
    uint8_t in1;
    uint8_t in2;
    uint8_t ena;
};

struct caster_settings_t
{
    int id;
    struct motor_pins_t fl_rot;
    struct motor_pins_t fl_drive;
    struct motor_pins_t fr_rot;
    struct motor_pins_t fr_drive;
    struct motor_pins_t  r_rot;
    struct motor_pins_t  r_drive;
};

caster_settings_t caster_settings;

void init_caster() {
  caster_settings.fl_rot = {32, 34, 44};
  caster_settings.fl_drive = {28, 30, 4};
  caster_settings.fr_rot = {40, 42, 45};
  caster_settings.fr_drive = {36, 38, 5};
  caster_settings.r_rot = {41, 43, 46};
  caster_settings.r_drive = {37, 39, 6};
}

void drive(const char* name, motor_pins_t pins) {

  Serial.print(name);
  Serial.println(" caster drive fwd.");
  pinMode(pins.in1, OUTPUT);
  pinMode(pins.in2, OUTPUT);
  pinMode(pins.ena, OUTPUT);
  digitalWrite(pins.in1, HIGH);
  digitalWrite(pins.in2, LOW);
  for (int i = 0; i < 256; i+=1) {
    analogWrite(pins.ena, i);
    delay(20);
  }
  delay(1000);
  for (int i = 255; i >= 0; i-=1) {
    analogWrite(pins.ena, i);
    delay(20);
  }
  delay(1000);

  Serial.print(name);
  Serial.println(" caster drive bwd");
  digitalWrite(pins.in1, LOW);
  digitalWrite(pins.in2, HIGH);
  for (int i = 0; i < 256; i+=1) {
    analogWrite(pins.ena, i);
    delay(20);
  }
  delay(1000);
  for (int i = 255; i >= 0; i-=1) {
    analogWrite(pins.ena, i);
    delay(20);
  }

}


#define PWM_SPD 255
#define PWM_TIME 3000
void rot(const char* name, motor_pins_t pins) {
  Serial.print(name);
  Serial.println(" caster rotation left.");
  pinMode(pins.in1, OUTPUT);
  pinMode(pins.in2, OUTPUT);
  pinMode(pins.ena, OUTPUT);

  digitalWrite(pins.in1, HIGH);
  digitalWrite(pins.in2, LOW);
  analogWrite(pins.ena, PWM_SPD);
  delay(PWM_TIME);

  Serial.println(" caster rotation right.");
  digitalWrite(pins.in1, LOW);
  digitalWrite(pins.in2, HIGH);
  analogWrite(pins.ena, PWM_SPD);
  delay(PWM_TIME*2);

  Serial.println(" caster rotation left back to center.");
  digitalWrite(pins.in1, HIGH);
  digitalWrite(pins.in2, LOW);
  analogWrite(pins.ena, PWM_SPD);
  delay(PWM_TIME);
  analogWrite(pins.ena, 0);
}

void test_caster_drive_fl() {
    init_caster();
    drive("FL", caster_settings.fl_drive);
}

void test_caster_drive_fr() {
    init_caster();
    drive("FR", caster_settings.fr_drive);
}

void test_caster_drive_r() {
    init_caster();
    drive("R", caster_settings.r_drive);
}


void test_caster_rot_fl() {
    init_caster();
    rot("FL", caster_settings.fl_rot);
}

void test_caster_rot_fr() {
    init_caster();
    rot("FR", caster_settings.fr_rot);
}

void test_caster_rot_r() {
    init_caster();
    rot("R", caster_settings.r_rot);
}

