





#include"vfdcommands.h"
#include"motor.h"


#define SYNCPIN 2



enum Mode {
  NOSYNC,
  SYNC,
  A_B,
  B_A
};

Mode mode = NOSYNC;

float relatedRate;

// A for false, B for true
bool syncCh = false;

VFDMotor a;
VFDMotor b;

String cmd;


void updateControl() {
  String str = Serial.readStringUntil('\n');
  unsigned char s[64];
  str.getBytes(s, 64);
  s[str.length()] = '\0';
  packet p = packetStrParser((char*)s);

  // Handles stop all case, cause thats usually bad
  if (p.code == findCode(STOPALL)) {
    a.stop();
    b.stop();
    return;
  } else if (p.code == findCode(ACK)) {
    // ACK code is just to check the other is alive
    return;
  } else if (p.code == findCode(PING)) {
    // If this device gets pinged, we send a message back
    Serial.println(packetStrBuilder((packet){findCode(ACK) == -1 ? 0 : findCode(ACK),0}));
  } else if (p.code == findCode(A_CH_START)) {
    a.start();
  } else if (p.code == findCode(A_CH_STOP)) {
    a.stop();
  } else if (p.code == findCode(A_CH_SPEED)) {
    a.setSpeed(p.num);
  } else if (p.code == findCode(A_CH_SYNC)) {
    syncCh = false;
  } else if (p.code == findCode(A_CH_MAX_SPEED)) {
    a.setMaxSpeed(p.num);
  } else if (p.code == findCode(A_CH_MAX_ACCEL)) {
    a.setMaxAccel(p.num);
  } else if (p.code == findCode(B_CH_START)) {
    b.start();
  } else if (p.code == findCode(B_CH_STOP)) {
    b.stop();
  } else if (p.code == findCode(B_CH_SPEED)) {
    b.setSpeed(p.num);
  } else if (p.code == findCode(B_CH_SYNC)) {
    syncCh = true;
  } else if (p.code == findCode(B_CH_MAX_SPEED)) {
    b.setMaxSpeed(p.num);
  } else if (p.code == findCode(B_CH_MAX_ACCEL)) {
    b.setMaxAccel(p.num);
  } else if (p.code == findCode(NO_SYNC)) {
    mode = NOSYNC;
  } else if (p.code == findCode(A_B_SYNC)) {
    mode = SYNC;
  } else if (p.code == findCode(A_OVER_B_SYNC)) {
    relatedRate = p.num;
  } else if (p.code == findCode(B_OVER_A_SYNC)) {
    relatedRate = p.num;
  } else {
    Serial.println(packetStrBuilder((packet){0,0}));
  }
}




void setup() {
  Serial.begin(9600);
  pinMode(SYNCPIN, OUTPUT);
  digitalWrite(SYNCPIN, LOW);
}

void loop() {
  updateControl();
}
