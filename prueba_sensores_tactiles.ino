const int sensorPin = 2;  // Pin donde está conectado el sensor (OUT)
const int ledPin = 13;    // Pin del LED en el Arduino (o usa un LED externo)

void setup() {
  pinMode(sensorPin, INPUT);  // Configurar el pin del sensor como entrada
  pinMode(ledPin, OUTPUT);    // Configurar el pin del LED como salida
}

void loop() {
  int sensorState = digitalRead(sensorPin);  // Leer el estado del sensor

  if (sensorState == HIGH) {
    digitalWrite(ledPin, HIGH);  // Encender el LED cuando se toca el sensor
  } else {
    digitalWrite(ledPin, LOW);   // Apagar el LED cuando no se toca el sensor
  }
}
