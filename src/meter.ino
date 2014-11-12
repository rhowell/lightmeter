/*
   Takes light sensor readings in 3 directions.  Reports via Spark firmware.
 */
int upPin = A6;
int forPin = A5;
int downPin = A4;

const int DATASIZE = 128;
char dataString[DATASIZE + 1];

void setup() {
  digitalWrite(upPin, HIGH);
  digitalWrite(forPin, HIGH);
  digitalWrite(downPin, LOW);
}

void loop() {
  snprintf(dataString, DATASIZE, "{\"up\":%d, \"forward\":%d, \"down\":%d}", analogRead(upPin), analogRead(forPin), analogRead(downPin));
  Spark.variable("light", &dataString, STRING);

  delay(2500);
}
