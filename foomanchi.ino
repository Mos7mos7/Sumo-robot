const byte m1_t1=13;
const byte m1_t2=12; //motor 1 is the right one
const byte m2_t1=7;
const byte m2_t2=6; //motor 2 is the left one 
const byte fr =8 , br=9;
bool fir , bir;
byte echo=4;//input
byte trig=3;//output
int dis;
/*we can switch motor numbers later 
 and we should know how each transistor triggers the motor */
void forward();
void backward(); 
void right();
void left();
void turn_off();

int mostafa (byte echo,byte trig);


void setup() {
  pinMode(m1_t1,OUTPUT);
  pinMode(m1_t2,OUTPUT);
  pinMode(m2_t1,OUTPUT);
  pinMode(m2_t2,OUTPUT);
  pinMode(fr,INPUT);
  pinMode(br,INPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
}

void loop() {
  fir=digitalRead(fr);
  bir=digitalRead(br); //maybe we need some delayyy between two reads
  if (fir==0 && bir ==0) //we are in the black area
  {
    if(dis!=-1) {forward();}
    else {right();delay(33);//the purpose of delay here is to give the ultrasonic time to take good measurments}
  }
  else if (fir==1 && bir==1)  {
    forward();
    delay(500);
    left(); // or right it depends
  }
  else if (fir==0 && bir==1)
  {
    forward (); // to try push the opponet away
  }
  else if (fir==1 && bir==0)
  {
    backward();
    turn_off();
    delay(500);// to try push him back , we can escape him depend on our strategy
  }
}





void forward(){
  //move forward
  digitalWrite(m1_t1,HIGH);
  digitalWrite(m1_t2,LOW);
  digitalWrite(m2_t1,HIGH);
  digitalWrite(m2_t2,LOW);
}
void backward() 
{
  digitalWrite(m1_t1,LOW);
  digitalWrite(m1_t2,HIGH);
  digitalWrite(m2_t1,LOW);
  digitalWrite(m2_t2,HIGH);
}
void right()
{
  digitalWrite(m1_t1,LOW);
  digitalWrite(m1_t2,LOW);
  digitalWrite(m2_t1,LOW);//left motor moves forward
  digitalWrite(m2_t2,HIGH); 
}
void left()
{
  digitalWrite(m1_t1,LOW);
  digitalWrite(m1_t2,HIGH);
  digitalWrite(m2_t1,LOW);
  digitalWrite(m2_t2,LOW);
}
void turn_off ()
{
  digitalWrite(m1_t1,LOW);
  digitalWrite(m1_t2,LOW);
  digitalWrite(m2_t1,LOW);
  digitalWrite(m2_t2,LOW);
}
int mostafa (byte echo,byte trig)
{
  long long duration;
  int distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  duration=pulseIn(echo,HIGH);
  distance=(duration*0.034)/2;
  if (distance>=80) {return -1;}
  else {return distance;}
}
