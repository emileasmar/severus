#include <Arduino.h>
#define trigPin0 7
#define trigPin1 4
#define trigPin2 2
#define echoPin0 8
#define echoPin1 12
#define echoPin2 13
#define smokePin A0

#define output1 9
#define output2 10
#define output3 11

#define neg1 A0
#define pos1 A1
#define pos2 A2
#define neg2 A3

long duration;
int distance;
int environement[3];

typedef struct inputData{
    bool data1;
    bool data2;
    bool data3;
} inputData;

typedef short int direction;

bool obstacle_detected[3] = {0, 0, 0};

direction getDirection(){
    inputData data;
    data.data1 = digitalRead(output1);
    data.data2 = digitalRead(output2);
    data.data3 = digitalRead(output3);
    direction output = data.data3*4+data.data2*2+data.data1*1;

    return output;
}

int getDistance(int trig, int echo)
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(8);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}

void readMH4Task()
{
    int analogSensor = analogRead(smokePin);
}

void envTask()
{
    environement[0] = getDistance(trigPin0, echoPin0);
    environement[1] = getDistance(trigPin1, echoPin1);
    environement[2] = getDistance(trigPin2, echoPin2);

    // Serial.print("Distances: [");
    // Serial.print(environement[0]);
    // Serial.print(", ");
    // delayMicroseconds(100);
    // Serial.print(environement[1]);
    // Serial.print(", ");
    // delayMicroseconds(100);
    // Serial.print(environement[2]);
    // Serial.println("]");

    int limit = 20;
    readMH4Task();

    if (obstacle_detected[0] == 0 && environement[0] < limit)
    {
        Serial.println("OBSTACLE LEFT !!");
        obstacle_detected[0] = 1;
    }
    else if (obstacle_detected[0] == 1 && environement[0] > limit)
    {
        Serial.println("LEFT CLEAR!!");
        obstacle_detected[0] = 0;
    }

    if (obstacle_detected[1] == 0 && environement[1] < limit)
    {
        Serial.println("OBSTACLE CENTER !!");
        obstacle_detected[1] = 1;
    }
    else if (obstacle_detected[1] == 1 && environement[1] > limit)
    {
        Serial.println("CENTER CLEAR!!");
        obstacle_detected[1] = 0;
    }

    if (obstacle_detected[2] == 0 && environement[2] < limit)
    {
        Serial.println("OBSTACLE RIGHT !!");
        obstacle_detected[2] = 1;
    }
    else if (obstacle_detected[2] == 1 && environement[2] > limit)
    {
        Serial.println("RIGHT CLEAR!!");
        obstacle_detected[2] = 0;
    }
}

void forward(){
    digitalWrite(pos1, HIGH);
    digitalWrite(neg1, LOW);
    digitalWrite(pos2, HIGH);
    digitalWrite(neg2, LOW);
}

void backward(){
    digitalWrite(pos1, LOW);
    digitalWrite(neg1, HIGH);
    digitalWrite(pos2, LOW);
    digitalWrite(neg2, HIGH);
}

void left(){
    digitalWrite(pos1, LOW);
    digitalWrite(neg1, HIGH);
    digitalWrite(pos2, HIGH);
    digitalWrite(neg2, LOW);
}

void right(){
    digitalWrite(pos1, HIGH);
    digitalWrite(neg1, LOW);
    digitalWrite(pos2, LOW);
    digitalWrite(neg2, HIGH);
}

void stop(){
    digitalWrite(pos1, LOW);
    digitalWrite(neg1, LOW);
    digitalWrite(pos2, LOW);
    digitalWrite(neg2, LOW);
}

void control(){
    direction rcv = getDirection();
    envTask();
    if (rcv != 0){
        if (rcv == 1 && obstacle_detected[1]==0){
            forward();
            Serial.println("Forward");
        }
        else if (rcv == 2){
            backward();
            Serial.println("Backward");
        }
        else if (rcv == 3 && obstacle_detected[0]==0){
            left();
            Serial.println("Left");
        }
        else if (rcv == 4 && obstacle_detected[2]==0){
            right();
            Serial.println("Right");
        }
        else{
            stop();
        }
    }else{
        stop();
    }
}

void setup()
{
    pinMode(trigPin0, OUTPUT);
    pinMode(trigPin1, OUTPUT);
    pinMode(trigPin2, OUTPUT);
    
    pinMode(echoPin0, INPUT);
    pinMode(echoPin1, INPUT);
    pinMode(echoPin2, INPUT);

    pinMode(output1, INPUT);
    pinMode(output2, INPUT);
    pinMode(output3, INPUT);

    pinMode(pos1, OUTPUT);
    pinMode(neg1, OUTPUT);
    pinMode(pos2, OUTPUT);
    pinMode(neg2, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    control();
    envTask();
}
