/*
   Takes light sensor readings in 3 directions.  Reports via Spark firmware.
 */
int upPin = A6;
int forPin = A5;
int downPin = A4;
int heatPin = A0;

const int DATASIZE = 128;
char dataString[DATASIZE + 1];

void setup() {
  digitalWrite(upPin, HIGH);
  digitalWrite(forPin, HIGH);
  digitalWrite(downPin, LOW);
}

void loop() {
  snprintf(dataString, DATASIZE, "{\"up\":%d, \"forward\":%d, \"down\":%d, \"temperature\":%.2f}", analogRead(upPin), analogRead(forPin), analogRead(downPin), analogRead(heatPin)/24.34f);
  Spark.variable("light", &dataString, STRING);

  delay(2500);
}
