// input force sensor (for the package slope)
int forcePin = A1;
int forceVal = 0;

//output camera (for taking pictures)
//int 

//output sms message
String body = "Hi, you received a package. Visit https://www.amazon.com/progress-tracker/package/ref=ppx_yo_dt_b_track_package?_encoding=UTF8&itemId=kpogsphqtqqpwn&orderId=114-2892787-9919420&packageIndex=0&shipmentId=D7DQDvxB3&vt=YOUR_ORDERS to check it out! Reply yes to accept.";

//output soldenoid lock 12V (opening and locking the package storage)
//int lock = D2;
long t = 0;
Servo myServo;
int angle = 0;
int ServoPin = D2;
//String AUSTIN_DEVICE = "e00fce689c13255696bdc053";


int currentState = 0;
//State 0: read force sensor value
//int currentState = 0;

//State 1: Take a pircture
//int currentState = 1;

//State 2: Send SMS/MMS
//int currentState = 2;

//State 3: Handle user decision
//int currentState = 3;

//State 4: Unlock the lock
//int currentState = 4;

//State 5: Lock held, wait for next force value change
//int currentState = 5;




void setup (){
    
      //set the speed of communication
    Serial.begin(115200);
    
    //force sensor input
    Particle.variable( "force", forceVal );
    
    Particle.variable("currentState", currentState);
    //SMS input
    Particle.publish("twilio_sms", body, PRIVATE);
    
    //camera input
    
    
    //lock input
    //pinMode(forcePin, INPUT_PULLUP);
    //pinMode(lock, OUTPUT);
    myServo.attach(ServoPin);
    //State0
    //Particle.function ("readFSR", doWaitingForSensor);
   
    //State1
    Particle.function ("takePicture", takePicture);
    
    //State2
    Particle.function ("sendMessage", sendMessage);
    
    //State3
    Particle.function ("userDecision", handleUserDecision);
   
    //State4
    Particle.function ("unlock", unlockServoPos);

    Particle.function("setServoPos", setServoPos);
    //State5
    Particle.function ("remainLock", waitForce);
}





// int waitForce()


void loop (){
    //State0 Read force sensor
    if (currentState == 0){
        doWaitingForSensor();
    }
    
    if //State1 Take a pircture
    (currentState == 1){
        doTakePicture();
    }
    
    //State2 
    if (currentState == 2){
        doSendMessage();
    }
    
    //State3
    if (currentState == 3){
        doWaitingForUserDecision(  );
    }
    
    //State4
    if (currentState == 4){
        //doUnlockSolenoid();
        dounlockServoPos();
    }
    
    //State5
    if (currentState == 5){
        doWaitForce();
    }
    
    // Welcome 
    if( currentState == 0 ){
        doWelcome();
    }else if( currentState == 1 ){
        doWaitingForSensor();
    }
    // ... 
}



// State 0
void doWaitingForSensor(){
    forceVal = analogRead(forcePin);
    Serial.println(forceVal);
    
    int isPackage = (forceVal > 2000);

    t = millis();
    
    //unlock when there is a package
    if (isPackage) {
      Serial.println(t);
      currentState == 1;
      isPackage=0;
     }else{
     
     }
    delay( 50 );
}


//State 1
void doTakePicture(){
    currentState = 2;
}


//State2
void doSendMessage(){
    Serial.println("Hi, you've just received a package. Reply yes to accept.");
    delay(60000);
    
    currentState = 3;
}



void doWaitingForUserDecision(){
    

}


//State 4
void dounlockServoPos(){
//void doUnlockSolenoid(){
    long timeNow = millis();
    int stayOpenFor = 1000 * 10;
    
    //digitalWrite(lock, HIGH);
    setServoPos("90");
    delay( 400 ) ;
    while( timeNow < t + stayOpenFor  ){
      // wait until time has elapsed
        timeNow = millis();
        delay( 50 );
    }
    //digitalWrite(lock, LOW);
    setServoPos("0");
    delay( 400 );
    
    currentState = 0; 
}


int setServoPos(String pos) {
    angle = pos.toInt();
    if (angle < 0) {
        return -1;
    }
    if (angle > 180) {
        return -1;
    }
    
    myServo.write(angle);
    return 0;
}



// State 5
void doWaitForce(){
    
    
}



void doWelcome(){
    
}


//int takePicture


//int sendMessage


int takePicture( String cmd ){
    
}


int sendMessage( String cmd ){
    
}

int handleUserDecision( String cmd ) {
    
    ///if( cmd.equals( "YES" ) ){
    //
    //    currentState = 4; // ACCEPT
    //}else{
    //    currentState = 5; // REJECT
    //}

    currentState = 4;
    
    return 4;
  
} 

//Stage 4
int unlockServoPos( String cmd ) {
//int unlockSolenoid( String cmd ) {
    dounlockServoPos();

    //angle = pos.toInt();
    //if (angle < 0) {
    //    return -1;
    //}
    //if (angle > 180) {
    //    return -1;
    //}
    
    //myServo.write(angle);
    //return 0;

}


int waitForce( String cmd ){
    
}

