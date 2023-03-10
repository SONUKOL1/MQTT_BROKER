//esp8266 board 0.9 module select
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RelayPin1 D4  //D1
#define RelayPin2 D1  //D2
#define RelayPin3 D5  //D5
#define RelayPin4 D6  //D6

#define SwitchPin1 D2  //SD3
#define SwitchPin2 D3  //D3
#define SwitchPin3 D7  //D7
#define SwitchPin4 3   //RX


int toggleState_1 = 1;  //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1;  //Define integer to remember the toggle state for relay 2
int toggleState_3 = 1;  //Define integer to remember the toggle state for relay 3
int toggleState_4 = 1;  //Define integer to remember the toggle state for relay 4


const char* ssid = "OPPO";           //WiFI Name
const char* password = "123456789";  //WiFi Password
const char* mqttServer = "test.mosquitto.org";
const char* mqttUserName = "sonu_UserID";   // MQTT username
const char* mqttPwd = "r_Password";         // MQTT password
const char* clientID = "EspClient0000234";  // client id


#define sub1 "switch1"
#define sub2 "switch2"
#define sub3 "switch3"
#define sub4 "switch4"

#define pub1 "switch1_status"
#define pub2 "switch2_status"
#define pub3 "switch3_status"
#define pub4 "switch4_status"


WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (80)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID)) {
      Serial.println("MQTT connected");
      client.subscribe(sub1);
      client.subscribe(sub2);
      client.subscribe(sub3);
      client.subscribe(sub4);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  if (strstr(topic, sub1)) {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(RelayPin1, LOW);  // Turn the LED on (Note that LOW is the voltage level
      toggleState_1 = 0;
      client.publish(pub1, "0");
    } else {
      digitalWrite(RelayPin1, HIGH);  // Turn the LED off by making the voltage HIGH
      toggleState_1 = 1;
      client.publish(pub1, "1");
    }
  }

  else if (strstr(topic, sub2)) {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(RelayPin2, LOW);  // Turn the LED on (Note that LOW is the voltage level
      toggleState_2 = 0;
      client.publish(pub2, "0");
    } else {
      digitalWrite(RelayPin2, HIGH);  // Turn the LED off by making the voltage HIGH
      toggleState_2 = 1;
      client.publish(pub2, "1");
    }
  } else if (strstr(topic, sub3)) {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(RelayPin3, LOW);  // Turn the LED on (Note that LOW is the voltage level
      toggleState_3 = 0;
      client.publish(pub3, "0");
    } else {
      digitalWrite(RelayPin3, HIGH);  // Turn the LED off by making the voltage HIGH
      toggleState_3 = 1;
      client.publish(pub3, "1");
    }
  } else if (strstr(topic, sub4)) {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(RelayPin4, LOW);  // Turn the LED on (Note that LOW is the voltage level
      toggleState_4 = 0;
      client.publish(pub4, "0");
    } else {
      digitalWrite(RelayPin4, HIGH);  // Turn the LED off by making the voltage HIGH
      toggleState_4 = 1;
      client.publish(pub4, "1");
    }
  } else {
    Serial.println("unsubscribed topic");
  }
}

void manual_control() {
  //Manual Switch Control
  if (digitalRead(SwitchPin1) == LOW) {
    delay(200);
    if (toggleState_1 == 1) {
      digitalWrite(RelayPin1, LOW);  // turn on relay 1
      toggleState_1 = 0;
      client.publish(pub1, "0");
      Serial.println("Device1 ON");
    } else {
      digitalWrite(RelayPin1, HIGH);  // turn off relay 1
      toggleState_1 = 1;
      client.publish(pub1, "1");
      Serial.println("Device1 OFF");
    }
  } else if (digitalRead(SwitchPin2) == LOW) {
    delay(200);
    if (toggleState_2 == 1) {
      digitalWrite(RelayPin2, LOW);  // turn on relay 2
      toggleState_2 = 0;
      client.publish(pub2, "0");
      Serial.println("Device2 ON");
    } else {
      digitalWrite(RelayPin2, HIGH);  // turn off relay 2
      toggleState_2 = 1;
      client.publish(pub2, "1");
      Serial.println("Device2 OFF");
    }
  } else if (digitalRead(SwitchPin3) == LOW) {
    delay(200);
    if (toggleState_3 == 1) {
      digitalWrite(RelayPin3, LOW);  // turn on relay 3
      toggleState_3 = 0;
      client.publish(pub3, "0");
      Serial.println("Device3 ON");
    } else {
      digitalWrite(RelayPin3, HIGH);  // turn off relay 3
      toggleState_3 = 1;
      client.publish(pub3, "1");
      Serial.println("Device3 OFF");
    }
  } else if (digitalRead(SwitchPin4) == LOW) {
    delay(200);
    if (toggleState_4 == 1) {
      digitalWrite(RelayPin4, LOW);  // turn on relay 4
      toggleState_4 = 0;
      client.publish(pub4, "0");
      Serial.println("Device4 ON");
    } else {
      digitalWrite(RelayPin4, HIGH);  // turn off relay 4
      toggleState_4 = 1;
      client.publish(pub4, "1");
      Serial.println("Device4 OFF");
    }
  }
  client.publish("Ran", String(random(10000)).c_str());
  delay(100);
}

void setup() {
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  //During Starting WiFi LED should TURN OFF

  setup_wifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    Serial.println("wifi not con...");
    reconnect();
  } else {
    manual_control();
  }
  client.loop();  
}
