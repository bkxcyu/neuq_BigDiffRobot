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
#define Limit 18000
#define MID 520
#define soft_pram 500
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

int start_flag=0;
int stop_flag=0;

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
void soft_start(int freq)
{
  int step_=freq/soft_pram;
  for(int i=0;i<soft_pram;i++)
  {
      freq1.play(step_*i);
      freq2.play(step_*i);
      freq3.play(step_*i);
      freq4.play(step_*i);
//      Serial.println(step_*i);
  }
  start_flag=1;
}
void soft_stop()
{
  Serial.println("stop");
  int step_=Limit/soft_pram;
  for(int i=0;i<soft_pram;i++)
  {
      freq1.play(Limit-step_*i);
      freq2.play(Limit-step_*i);
      freq3.play(Limit-step_*i);
      freq4.play(Limit-step_*i);
//      Serial.println(step_*i);
  }
  stop_flag=1;  
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
    Serial.println("receive:");
    Serial.println(comdata);

    if (comdata == "f") // qian
    {
      digitalWrite(pls1,HIGH);
      digitalWrite(dir1,HIGH);
      digitalWrite(pls2,HIGH);
      digitalWrite(dir2,HIGH);
      digitalWrite(pls3,LOW);
      digitalWrite(dir3,LOW);
      digitalWrite(pls4,LOW);
      digitalWrite(dir4,LOW);
      if(!start_flag)
        soft_start(Limit);
      else
       {  
        freq1.play(Limit);
        freq2.play(Limit);
        freq3.play(Limit);
        freq4.play(Limit);
       }
       stop_flag=0;
    }
    if (comdata == "b") //  hou
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
      stop_flag=0;
    }
    if (comdata == "r") // you
    {
      digitalWrite(pls1,LOW);
      digitalWrite(dir1,LOW);
      digitalWrite(pls2,LOW);
      digitalWrite(dir2,LOW);
      digitalWrite(pls3,LOW);
      digitalWrite(dir3,LOW);
      digitalWrite(pls4,LOW);  
      digitalWrite(dir4,LOW);
      freq1.play(8000);
      freq2.play(8000);
      freq3.play(8000);
      freq4.play(8000);
      stop_flag=0;
    }
    if (comdata == "l") //zuo
    {
      digitalWrite(pls1,HIGH);
      digitalWrite(dir1,HIGH);
      digitalWrite(pls2,HIGH);
      digitalWrite(dir2,HIGH);
      digitalWrite(pls3,HIGH);
      digitalWrite(dir3,HIGH);
      digitalWrite(pls4,HIGH);
      digitalWrite(dir4,HIGH);
      freq1.play(8000);
      freq2.play(8000);
      freq3.play(8000);
      freq4.play(8000);
      stop_flag=0;
    }
    if (comdata == "s") //ting
    {
      if(!stop_flag)
        soft_stop();
      else
      {
        freq1.play(0);
        freq2.play(0);
        freq3.play(0);
        freq4.play(0);
      }
      start_flag=0;
      stop_flag=1;
    }
    comdata="";
  }
//  else
//  {
//    freq1.play(0);
//    freq2.play(0);
//    freq3.play(0);
//    freq4.play(0);
//  }
}
