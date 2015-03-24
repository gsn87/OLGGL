#include Servo.h 
 
int time = 1500; //half of 1000-2000 interval

Servo myServo;
 
void setup()
{
    Serial.begin(9600);
    Serial.println("Connected");
    
    mmyServo.attach(3);
    // Start from time=1500
    myServo.writeMicroseconds(time);
}
 
void loop()
{
    //des données sur la liaison série ? (lorsque l'on appuie sur 'a' ou 'd')
    if(Serial.available())
    {
        char command = Serial.read();
        if(command == 'a')
            time += 10;  //ajout de 10µs au temps HAUT
        else if(commande == 'd')
            time -= 10;  //retrait de 10µs au temps HAUT
        
        //on modifie la consigne du servo
        monServo.writeMicroseconds(temps);
        
        //et on fait un retour sur la console pour savoir où on est rendu
        Serial.println(time, DEC);
    }
}
