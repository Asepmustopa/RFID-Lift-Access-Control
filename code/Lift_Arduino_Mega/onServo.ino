void initialServo(Servo pi, int pin)
{
  pi.attach(pin);
}
void onServo(Servo pi, int pos)
{
  pi.write(pos);
}
