const int NO_INPUT = -1;
const int UNKNOWN_COMMAND = 0;
const int PING_COMMAND = 1;
const int HELP_COMMAND = 2;

const int PINGER = 4;
const int LED_BLUE = 5;
const int LED_RED = 6;
const int HARDWARE_BUTTON = 7;

const int pingDuration_ms = 40;

void setup()
{
  // USB is always 12 Mbit/sec, regardless of the value passed in here.
  Serial.begin(9600); 
  
  pinMode(PINGER, OUTPUT);
  digitalWrite(PINGER, LOW);
  
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(HARDWARE_BUTTON, INPUT);
  
  // Pull LED pins low to illuminate. 
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(100);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  
  PerformUsageCommand();
}

void loop()
{
  int command = ReadCommand();
  switch (command)
  {
    case PING_COMMAND:
      PerformPingCommand(pingDuration_ms);
      break;
      
    case HELP_COMMAND:
    case UNKNOWN_COMMAND:
      PerformUsageCommand();
      break;
  }
  
  if (ButtonPressed())
  {
    PerformPingCommand(pingDuration_ms);
    delay(500);
  }
}

boolean ButtonPressed()
{
  int reading = digitalRead(HARDWARE_BUTTON);
  return reading == LOW; 
}

int ReadCommand()
{
  String input = "";
  char incomingChar; 
  while (Serial.available())
  {    
    // Gobble whitespace until we have a command.
    incomingChar = char(Serial.read());
    if (!IsWhitespace(incomingChar))
    {
      input += incomingChar;
    }
    
    if (IsWhitespace(incomingChar))
    {
      if (input == "ping") { return PING_COMMAND; }
      if (input == "help") { return HELP_COMMAND; }
      // Add other commands here...      
      
      if (input.length() != 0) { return UNKNOWN_COMMAND; }
    }
  }
  
  // If there's no characters available we should probably
  // store what we've got so far and loop, but for now, just
  // say that there was no input. 
  return NO_INPUT;
}

boolean IsWhitespace(char c)
{
  // We'll treat all ASCII characters equal to or less than 32 (' ') as whitespace
  return c <= 32;
}

void PerformPingCommand(int durationMs)
{
  digitalWrite(PINGER, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(durationMs);
  
  digitalWrite(PINGER, LOW);
  digitalWrite(LED_BLUE, HIGH);
  Serial.println("Ping!");
}

void PerformUsageCommand()
{
  // Echo some helpful text to the serial port.
  Serial.println("Usage: ");
  Serial.println("Send commands separated by whitespace characters.");
  Serial.println("  ping  Ping the bell");
  Serial.println("  help  Display this message");
  Serial.println();
}
