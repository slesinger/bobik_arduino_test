#include <Arduino.h>
#include <stdint.h>
#include "main.h"
#include "test_caster.h"

void setup() {
  Serial.begin(9600);
  Serial.println(" caster rot fwd. Get ready in 2000ms");
  delay(2000);

  // test_caster_drive_fl();
  // test_caster_drive_fr();
  // test_caster_drive_r();
  test_caster_rot_fl();
  // test_caster_rot_fr();
  // test_caster_rot_r();
}


void loop() {
  Serial.println("End of Test");
  delay(60000);

}
