#include <stdlib.h>
#include <Tone.h>
#define pls1 2//左后,LOW为前进
#define dir1 3
#define pls2 4//左前,LOW为前进
#define dir2 5
#define pls3 6//右后,HIGH为前进
#define dir3 7
#define pls4 8//右前,HIGH为前进
#define dir4 9
#define startV 0
#define Limit 12000
#define MID 520
Tone freq1;
Tone freq2;
Tone freq3;
Tone freq4;
static int f1=startV;
static int f2=startV;
static int f3=startV;
static int f4=startV;
String comdata="";
String stopcom="";
void setup()
{  
  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode(pls1, OUTPUT);   
  pinMode(pls2, OUTPUT); 
  pinMode(pls3, OUTPUT);   
  pinMode(pls4, OUTPUT); 
  pinMode(dir1, OUTPUT);   
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);   
  pinMode(dir4, OUTPUT);
  freq1.begin(pls1);
  freq2.begin(pls2);
  freq3.begin(pls3);
  freq4.begin(pls4);
  digitalWrite(pls1,LOW);
  digitalWrite(dir1,LOW);
  digitalWrite(pls2,LOW);
  digitalWrite(dir2,LOW);
  digitalWrite(pls3,HIGH);
  digitalWrite(dir3,HIGH);
  digitalWrite(pls4,HIGH);
  digitalWrite(dir4,HIGH);
}
double pid(double measured)
{
    double Kp=18;
    double Ki=0;
    double Kd=0;
    double result;
    double bias;
    static double bias_last=0;
    static double bias_i=0;
    bias=measured-MID;
    bias_i+=bias;
    result=Kp*bias+Ki*bias_i+Kd*(bias-bias_last);
    bias_last=bias;
    return result;
}
void loop() 
{
  static int mid=MID;
  static int pid_r=0;
  while (Serial.available()>0)
  {
    comdata+=char(Serial.read());
    delay(2);
  }
  if(comdata.length()>0)
  {
    Serial.println(comdata);
    mid=comdata.toInt();
    Serial.write("mid:");
    Serial.print(mid);
    comdata="";
  }
  while (Serial1.available()>0)
  {
    stopcom+=char(Serial1.read());
    delay(2);
  }
  if(stopcom.length()>0)
  {
    Serial.println(stopcom);
    if (stopcom == "a") //  qianjin
    {
      digitalWrite(pls1,LOW);
  digitalWrite(dir1,LOW);
  digitalWrite(pls2,LOW);
  digitalWrite(dir2,LOW);
  digitalWrite(pls3,HIGH);
  digitalWrite(dir3,HIGH);
  digitalWrite(pls4,HIGH);
  digitalWrite(dir4,HIGH);
      freq1.play(Limit);
      freq2.play(Limit);
      freq3.play(Limit);
      freq4.play(Limit);
    }
    if (stopcom == "c") // hou
    {
        digitalWrite(pls1,HIGH);
        digitalWrite(dir1,HIGH);
        digitalWrite(pls2,HIGH);
        digitalWrite(dir2,HIGH);
        digitalWrite(pls3,LOW);
        digitalWrite(dir3,LOW);
        digitalWrite(pls4,LOW);
        digitalWrite(dir4,LOW);
      freq1.play(Limit);
      freq2.play(Limit);
      freq3.play(Limit);
      freq4.play(Limit);
    }
    if (stopcom == "d") // you
    {
        digitalWrite(pls1,LOW);
        digitalWrite(dir1,LOW);
        digitalWrite(pls2,LOW);
        digitalWrite(dir2,LOW);
        digitalWrite(pls3,LOW);
        digitalWrite(dir3,LOW);
        digitalWrite(pls4,LOW);  
        digitalWrite(dir4,LOW);
      freq1.play(5000);
      freq2.play(5000);
      freq3.play(5000);
      freq4.play(5000);
    }
    if (stopcom == "b") //zuo
    {
        digitalWrite(pls1,HIGH);
        digitalWrite(dir1,HIGH);
        digitalWrite(pls2,HIGH);
        digitalWrite(dir2,HIGH);
        digitalWrite(pls3,HIGH);
        digitalWrite(dir3,HIGH);
        digitalWrite(pls4,HIGH);
        digitalWrite(dir4,HIGH);
      freq1.play(5000);
      freq2.play(5000);
      freq3.play(5000);
      freq4.play(5000);
    }
    if (stopcom == "j") //ting
    {
      freq1.play(0);
      freq2.play(0);
      freq3.play(0);
      freq4.play(0);
    }
    stopcom="";
  }
}
