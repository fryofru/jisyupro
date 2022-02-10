#include <Servo.h>      // Servoライブラリの読み込み
#include <DFRobot_DHT20.h>

DFRobot_DHT20 dht20;

Servo servo0, servo1,servo2,servo3,servo4,servo5;// Servoオブジェクトの宣言
Servo servos[] = {servo0, servo1,servo2,servo3,servo4,servo5};
const int PINS[] = {2,3,4,5,6,7};   // PINを設定
int ang[] = {90,90,90,90,90,90};//各サーボの角度

int wait_time = 300;
int wait_l = 1000;
void setup(){
  Serial.begin(115200);
  //Initialize sensor
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
  }
  
  for (int i=0; i<6; i++){
    servos[i].attach(PINS[i], 500, 2400);  // サーボの割当(パルス幅500~2400msに指定)
    servos[i].write(ang[i]); //サーボを初期値へ
  }
  
  gather();
  reset();
  

}

void loop(){
  //Get ambient temperature
  float t = dht20.getTemperature();
  Serial.print("temperature:"); Serial.print(t);Serial.print("C");
  //Get relative humidity
  float h = dht20.getHumidity()*100;
  Serial.print("  humidity:"); Serial.print(h);Serial.println(" %RH");
  

  
  delay(1000);

  if (Serial.available() > 0) {
    String input = Serial.readString();
    int input_int = input.toInt();
    Serial.println(input);
    if (input.equals("t")){
      disp_Num(t);
    }
    else if(input.equals("h")){
      disp_Num(h);
    }
    else if(input.equals("d")){
      demo_09();
    }
    else{
      makeNum(input_int);
    }
  }
  
  
}

void move_mag(int num,int goal){
  int rev = (goal - ang[num])/abs(goal - ang[num]);

  while (ang[num] != goal){
    ang[num] += rev*1;
    servos[num].write(ang[num]);
    delay(100);
    
  }
 
}

void move_mags(int target[],int goals[],int n){
  //Serial.println(n);
  int angs_tmp[n];
  int pass_list[n]={0};
  for (int i=0; i<n; i++){
    //Serial.println(i);
    angs_tmp[i] = ang[target[i]]; //現在の角度を格納
  }

  while (!array_equal(angs_tmp,goals,n)){
    for (int i=0; i<n; i++){
      if (!pass_list[i]){
        int rev = (goals[i] - angs_tmp[i])/abs(goals[i] - angs_tmp[i]);
        angs_tmp[i] += rev*1;
        servos[target[i]].write(angs_tmp[i]); 

        //Serial.println(angs_tmp[i]);

        if (angs_tmp[i] == goals[i]){
          pass_list[i] = 1;
          //Serial.println(i);
        }
       }
      
      
    }
    delay(100);
    

  }

  for (int i=0; i<n; i++){
    ang[target[i]] = angs_tmp[i]; //現在の角度に戻す
    //Serial.println("store");
  }
  Serial.println("end move");

}



void reset(){
  int a1 = 40,a2 = 120;
  
  int target[] = {0,1,2,3,4,5};
  int goals[] = {a1,a1,120,90,130,55};
  move_mags(target,goals,sizeof(target)/sizeof(int));
  
}

void gather(){
  int target[] = {0,1,2,3,4,5};
  int goals[] = {110,100,75,100,90,70,100};
  move_mags(target,goals,sizeof(target)/sizeof(int));
  delay(wait_l);
}


void make0(){
  int target1[] = {0,1,2,3,4,5};
  int goals1[] = {90,90,90,90,70,100};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  delay(wait_time);
  int target2[] = {3,4,5};
  int goals2[] = {70,90,80};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  delay(wait_time);
  int target3[] = {0,1,3};
  int goals3[] = {110,125,90};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  delay(wait_time);
  int target4[] = {0,1,3};
  int goals4[] = {90,85,115};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  move_mag(3,90);
  
}

void make1(){
  int target[] = {1,2,3,5};
  int goals[] = {80,110,80,55};
  move_mags(target,goals,sizeof(target)/sizeof(int));
  //seg2 and 3
  
  delay(wait_time);
  move_mag(3,120);
  move_mag(3,100);
  
}

void make2(){
  
  int target0[] = {4,5};
  int goals0[] = {85,105};
  move_mags(target0,goals0,sizeof(target0)/sizeof(int));
  delay(wait_time);
  int target1[] = {4,5};
  int goals1[] = {100,90};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  int target2[] = {3,5};
  int goals2[] = {70,65};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  int target3[] = {3,2,5};
  int goals3[] = {75,55,75};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  delay(wait_time);
  int target4[] = {2,0,1};
  int goals4[] = {90,115,120};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  int target5[] = {0,1};
  int goals5[] = {90,95};
  move_mags(target5,goals5,sizeof(target5)/sizeof(int));
  
}


void make3(){
  int target0[] = {4,5};
  int goals0[] = {100,105};
  move_mags(target0,goals0,sizeof(target0)/sizeof(int));
  delay(wait_time);
  int target1[] = {3,5};
  int goals1[] = {75,80};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  int target2[] = {3,2};
  int goals2[] = {95,55};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  int target3[] = {0,2,1};
  int goals3[] = {80,85,115};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  
  delay(wait_time);
  int target6[] = {3};
  int goals6[] = {120};
  move_mags(target6,goals6,sizeof(target6)/sizeof(int));
  delay(wait_time);
  int target7[] = {1,3};
  int goals7[] = {90,90};
  move_mags(target7,goals7,sizeof(target7)/sizeof(int));
  
  
}

void make4(){
  int target1[] = {1,2,3,4,5};
  int goals1[] = {90,90,75,90,55};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  int target2[]={3};
  int goals2[]={115};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  int target3[]={2};
  int goals3[]={60};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  int target4[]={2,4,3};
  int goals4[]={95,65,90};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  move_mag(4,90);
  

}

void make5(){
  int target1[] = {0,1,2,3,4,5};
  int goals1[] = {85,100,70,110,50,80};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  delay(wait_time);
  int target2[] = {4};
  int goals2[] = {90};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  delay(wait_time);
  int target4[] = {2};
  int goals4[] = {80};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  int target5[] = {3};
  int goals5[] = {125};
  move_mags(target5,goals5,sizeof(target5)/sizeof(int));
  delay(wait_time);
  int target6[] = {0,1,3,4};
  int goals6[] = {75,120,110,85};
  move_mags(target6,goals6,sizeof(target6)/sizeof(int));
  
}


void make6(){
  int target1[] = {0,1,2,3,4,5};
  int goals1[] = {90,90,90,95,120,90};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  delay(wait_time);
  int target2[] = {};
  int goals2[] = {};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  delay(wait_time);
  int target3[] = {0,1};
  int goals3[] = {110,125};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  delay(wait_time);
  int target4[] = {0,1,3};
  int goals4[] = {90,85,115};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  int target5[] = {2,3};
  int goals5[] = {60,95};
  move_mags(target5,goals5,sizeof(target5)/sizeof(int));
  delay(wait_time);
  int target6[] = {2,5};
  int goals6[] = {93,125};
  move_mags(target6,goals6,sizeof(target6)/sizeof(int));

  
}


void make7(){
  int target1[] = {1,2,3,4,5};
  int goals1[] = {90,120,80,80,100};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  int target2[]={3,4,5};
  int goals2[]={120,90,90};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  move_mag(3,100);

}
void make8(){
  int target1[] = {0,1,2,3,4,5};
  int goals1[] = {90,90,90,90,70,100};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  delay(wait_time);
  int target2[] = {3,4,5};
  int goals2[] = {70,90,80};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  delay(wait_time);
  int target3[] = {0,1,3};
  int goals3[] = {110,125,90};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  delay(wait_time);
  int target4[] = {0,1,3};
  int goals4[] = {90,85,115};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  move_mag(3,90);
  move_mag(2,65);
  int target5[] = {4,2};
  int goals5[] = {80,90};
  move_mags(target5,goals5,sizeof(target5)/sizeof(int));
  
  
}

void make88(){
  int target1[] = {0,1,2,3,4,5};
  int goals1[] = {90,90,90,90,70,100};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  delay(wait_time);
  int target2[] = {2,3,4,5};
  int goals2[] = {65,65,90,80};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  delay(wait_time);
  int target3[] = {0,1,2,3};
  int goals3[] = {110,110,85,90};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  delay(wait_time);
  int target4[] = {0,1,3};
  int goals4[] = {90,85,110};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  delay(wait_time);
  move_mag(3,90);
  
}

void make9(){
  int target1[] = {1,3,4,5};
  int goals1[] = {90,90,90,100};
  move_mags(target1,goals1,sizeof(target1)/sizeof(int));
  int target2[]={3,5};
  int goals2[]={110,90};
  move_mags(target2,goals2,sizeof(target2)/sizeof(int));
  move_mag(3,70);
  int target3[]={2,3};
  int goals3[]={65,110};
  move_mags(target3,goals3,sizeof(target3)/sizeof(int));
  int target4[]={2,4};
  int goals4[]={95,70};
  move_mags(target4,goals4,sizeof(target4)/sizeof(int));
  //move_mag(2,95);
  //move_mag(4,65);
  delay(wait_time);
  move_mag(4,90);
  

}

void demo_09(){
  
  for(int i=0;i<10;i++){
    makeNum(i);
    
    
  }
}

bool array_equal(int *array1,int *array2,int array_size){

  for (int i=0; i<array_size; i++){
    if (array1[i] != array2[i]){
      return false;
    }
  }
  return true;
}

void makeNum(int n){
  Serial.print("make ");Serial.println(n);
  reset();
  
  switch(n){
    case 0:make0();break;
    case 1:make1();break;
    case 2:make2();break;
    case 3:make3();break;
    case 4:make4();break;
    case 5:make5();break;
    case 6:make6();break;
    case 7:make7();break;
    case 8:make8();break;
    case 9:make9();break;

    default:Serial.println("not num from 0 to 9");
    
  }
  delay(2000);
  
}


void disp_Num(float num){
  int a1 = num/10;//10の位
  int a2 = num - a1*10; //1の位
  
  makeNum(a1);
  
  makeNum(a2);
  

}
