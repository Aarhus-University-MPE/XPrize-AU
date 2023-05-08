# 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\PCB\\SBUSTest\\SBUSTest.ino"
# 2 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\PCB\\SBUSTest\\SBUSTest.ino" 2
# 3 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\PCB\\SBUSTest\\SBUSTest.ino" 2

SBUS sbus(Serial);

unsigned long millisLastSBusUpdate = 0;

const int thrtlePin = A3;
const int powerFlagPin = A7;
const int steerPin = 6;
const int systemEnPin = 4;

int throttle = -1;
int steer = -1;

const int maxSteer = 135;
const int minSteer = 45;

const float maxThrottleGain = 0.5f;
const int maxThrottleIncrement = 90 * maxThrottleGain;

Servo ThrottlePWM;
Servo SteerPWM;

const int minChannel = 364;
const int maxChannel = 1684;

// Scale the S.BUS channel values into the range [-100, 100]
int getChannel(int channel) {
  int value = sbus.getChannel(channel);

  int mappedValue = map(value, minChannel, maxChannel, -100, 100);

  return mappedValue;
}

void setup() {
  sbus.begin(false);
  ThrottlePWM.attach(thrtlePin);
  SteerPWM.attach(steerPin);

  ThrottlePWM.write(90);
  SteerPWM.write(90);

  // Power On system
  pinMode(systemEnPin, 0x1);
  pinMode(powerFlagPin, 0x0);
  pinMode(13, 0x1);

  digitalWrite(systemEnPin, false);
}

void loop() {
  sbus.process();

  if (millis() - millisLastSBusUpdate > 100) {
    millisLastSBusUpdate = millis();
    bool powerFlag = analogRead(powerFlagPin) > 300;

    if (powerFlag != digitalRead(systemEnPin)) {
      digitalWrite(systemEnPin, powerFlag);
      digitalWrite(13, powerFlag);
    }

    // Read and convert SBUS values to drivetrain parameters
    steer = map(getChannel(1), -100, 100, minSteer, maxSteer);
    throttle = map(getChannel(2), -100, 100, 90 - maxThrottleIncrement, 90 + maxThrottleIncrement);

    // Check for valid signal
    if (throttle > -130) {
      ThrottlePWM.write(throttle);
      SteerPWM.write(steer);
    }
  }
}
