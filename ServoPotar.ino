#include Servo.h //On oublie pas d'ajouter la bibliothèque !
 
const int potar = 0; //notre potentiomètre
Servo monServo;
 
void setup()
{
    //on déclare le servo sur la broche 2 (éventuellement régler les bornes)
    monServo.attach(3);
    //on oublie pas de démarrer la voie série
    Serial.begin(9600);
}
 
void loop()
{
    //on lit la valeur du potentiomètre
    int val = analogRead(potar);
    //on convertit la valeur lue en angle compris dans l’intervalle [0;180]
    int angle = val / 5.7;
    //on met à jour l'angle sur le servo
    monServo.write(angle);
    //on renvoie l'angle par la voie série pour superviser
    Serial.println(angle);
    //un petit temps de pause
    delay(100);
}
