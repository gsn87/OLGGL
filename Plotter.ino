#include <Servo.h>

//define CALIBRATION

#define O1X 56.5
#define O1Y -25
#define O2X 81.5
#define O2Y -25

#define L1 57
#define L2 99
#define L3 13.2

#define SERVOLEFTNULL 1660
#define SERVORIGHTNULL 1070
 
Servo ServoL;
Servo ServoR;
int timeL = 1660;
int timeR = 1100;

int SERVOFAKTOR_LEFT = 650;
int SERVOFAKTOR_RIGHT = 650;

volatile double lastX = 78;
volatile double lastY = 58;
 
void setup()
{
    Serial.begin(9600);
    Serial.println("Connected");
    
    ServoL.attach(2);
    ServoR.attach(3);
    
    drawTo(78,58);

    //ServoL.writeMicroseconds(timeL);
    //ServoR.writeMicroseconds(timeR);
}
 
void loop()
{
  
  #ifdef CALIBRATION

    // Servohorns will have 90° between movements, parallel to x and y axis
    delay(500);
    drawTo(-12, 76);
    delay(500);
    drawTo(142, 76);
    delay(500);
    //lift(0);

  #else 
    //des données sur la liaison série ? (lorsque l'on appuie sur 'a' ou 'd')
    if(Serial.available())
    {
        char command = Serial.read();
        if(command == 'x') {
            drawTo(lastX+5,lastY);}
        else if(command == 'c') {
            drawTo(lastX-5, lastY); }
        else if(command == 'y') {
            drawTo(lastX, lastY+5); }
        else if(command == 'u') {
            drawTo(lastX, lastY-5); }
        
        //et on fait un retour sur la console pour savoir où on est rendu
        Serial.println(lastX);
        Serial.println(lastY);        
    }
  #endif
}

void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor( 2*sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

  }

  lastX = pX;
  lastY = pY;
}


double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty) 
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // polar lemgth (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); // 
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);

  ServoL.writeMicroseconds(floor(((a2 + a1 - M_PI) * SERVOFAKTOR_LEFT) + SERVOLEFTNULL));

  // calculate joinr arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, (L2 - L3), c);

  ServoR.writeMicroseconds(floor(((a1 - a2) * SERVOFAKTOR_RIGHT) + SERVORIGHTNULL));

}
