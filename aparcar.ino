int ledV = 2;
int ledA = 3;
int ledR = 4;

const byte trig = 5;
const byte echo = 6;

int piezo = 9;

const float vsonido = 34300.0;
const float dLejos = 30.0;
const float dMedio = 20.0;
const float dCerca = 10.0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledV, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(piezo, OUTPUT);
  
  apagarLEDs();
}

void loop()
{
  //Preparamos el sensor ultrasonido
  iniciarTrigger();
  
  //Obtenemos distancia
  float distancia = calcularDistancia();
  
  //apagar LEDs
  apagarLEDs();
  
  //medir si está en un rango apropiado
  if(distancia < dLejos){
    //emepzar con el sonido
    alarmas(distancia);
  }
}

void apagarLEDs(){
  digitalWrite(ledV,LOW);
  digitalWrite(ledA,LOW);
  digitalWrite(ledR,LOW);
}

void iniciarTrigger(){
  //ponemos el Trigger en estado bajo
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  //ponemos el Trigger en estado alto
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  
  //ponemos el Trigger en estado bajo
  digitalWrite(trig, LOW);
}

float calcularDistancia(){
  //La función pulseIn obtiene el tiempo que tarda en cambiar entre estados,
  //aquí a HIGH
  
  unsigned long tiempo = pulseIn(echo,HIGH);
  
  //Obtenemos la distanca en cm, hay que convertir el tiempo en segu
  //tiempo/2; //entre 2 porque va y viene
  float distancia = tiempo *0.0000001 * vsonido /2.0;
  //float distancia = tiempo/58;
  Serial.print(distancia);
  Serial.println(" cm");
  delay(500);
  
  return distancia;
}

void alarmas(float distancia){
  if(distancia <= dLejos && distancia > dMedio)
  {
    //Encendemos led verde
    digitalWrite(ledV, HIGH);
    tone(piezo, 2000, 200); //piezo, frecuencia, 200 milisegundos
  }
  else if (distancia <= dMedio && distancia > dCerca)
  {
    //Encendemos led amarillo
    digitalWrite(ledA, HIGH);
    tone(piezo, 2500, 200);
  }
   else if (distancia <= dCerca)
  {
    //Encendemos led rojo
    digitalWrite(ledR, HIGH);
    tone(piezo, 3000, 200);
  }
}
