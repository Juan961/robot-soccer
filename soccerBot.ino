#include <ESP32Servo.h>
#include <BluetoothSerial.h>

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

String device_name = "BestSoccerRobot";

Servo servoMotor;

const int RIGHT_WHEEL_FORWARD_PIN = 26;
const int RIGHT_WHEEL_BACKWARD_PIN = 27;
const int RIGHT_WHEEL_VELOCITY_PIN = 25;

const int LEFT_WHEEL_FORWARD_PIN = 12;
const int LEFT_WHEEL_BACKWARD_PIN = 14;
const int LEFT_WHEEL_VELOCITY_PIN = 13;

const int MAX_VELOCITY = 255;

const int servoPin = 23; // Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33

// ====================== MOTORS ======================
void right () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 1);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 0);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
}

void left () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 0);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 1);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
}

void forward () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 0);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 0);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY / 2);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
}

void backward () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 1);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 1);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY / 2);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
}

void stop () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 0);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 0);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, 0);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, 0);
}

void topRight () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 0);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 0);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY / 2);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
}

void topLeft () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 0);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 1);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 0);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY / 2);
}

void backRight () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 1);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 1);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY / 2);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
}

void backLeft () {
  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 1);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 1);

  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, MAX_VELOCITY);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, MAX_VELOCITY / 2);
}

void shoot () {
  servoMotor.attach(servoPin);
  servoMotor.write(90);
  delay(500);

  servoMotor.write(180);
  delay(500);

  servoMotor.detach();
}

// ====================== SETUP ======================
void setup() {
  Serial.begin(115200);
  Serial.println("============================== Setup start");

  // ================================================== BLUETOOTH
  SerialBT.begin(device_name); // Bluetooth device name
  // SerialBT.deleteAllBondedDevices(); // Uncomment to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

  // ================================================== SERVO

  pinMode(RIGHT_WHEEL_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_WHEEL_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_WHEEL_VELOCITY_PIN, OUTPUT);

  pinMode(LEFT_WHEEL_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_WHEEL_BACKWARD_PIN, OUTPUT);
  pinMode(LEFT_WHEEL_VELOCITY_PIN, OUTPUT);

  digitalWrite(RIGHT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(RIGHT_WHEEL_BACKWARD_PIN, 0);
  analogWrite(RIGHT_WHEEL_VELOCITY_PIN, 0);

  digitalWrite(LEFT_WHEEL_FORWARD_PIN, 0);
  digitalWrite(LEFT_WHEEL_BACKWARD_PIN, 0);
  analogWrite(LEFT_WHEEL_VELOCITY_PIN, 0);

  Serial.println("============================== Setup end");
}

// ====================== LOOP ======================
void loop() {
  if (SerialBT.available()) {
    int message = SerialBT.read();

    delay(5);

    if (message == 5) { left(); }
    else if (message == 4) { right(); }
    else if (message == 2) { forward(); }
    else if (message == 3) { backward(); }
    else if (message == 1) { stop(); }
    else if (message == 7) { topRight(); }
    else if (message == 6) { topLeft(); }
    else if (message == 9) { backRight(); }
    else if (message == 8) { backLeft(); }
    else if (message == 0) { shoot(); }
    else { stop(); }
  }

  delay(10);
}
