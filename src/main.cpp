#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Ticker.h>

#define ALARM_PIN 16
#define PIEZO_PIN 14

#define	C0 16.35
#define	Db0	17.32
#define	D0	18.35
#define	Eb0	19.45
#define	E0	20.60
#define	F0	21.83
#define	Gb0	23.12
#define	G0	24.50
#define	Ab0	25.96
#define	LA0	27.50
#define	Bb0	29.14
#define	B0	30.87
#define	C1	32.70
#define	Db1	34.65
#define	D1	36.71
#define	Eb1	38.89
#define	E1	41.20
#define	F1	43.65
#define	Gb1	46.25
#define	G1	49.00
#define	Ab1	51.91
#define	LA1	55.00
#define	Bb1	58.27
#define	B1	61.74
#define	C2	65.41
#define	Db2	69.30
#define	D2	73.42
#define	Eb2	77.78
#define	E2	82.41
#define	F2	87.31
#define	Gb2	92.50
#define	G2	98.00
#define	Ab2	103.83
#define	LA2	110.00
#define	Bb2	116.54
#define	B2	123.47
#define	C3	130.81
#define	Db3	138.59
#define	D3	146.83
#define	Eb3	155.56
#define	E3	164.81
#define	F3	174.61
#define	Gb3	185.00
#define	G3	196.00
#define	Ab3	207.65
#define	LA3	220.00
#define	Bb3	233.08
#define	B3	246.94
#define	C4	261.63
#define	Db4	277.18
#define	D4	293.66
#define	Eb4	311.13
#define	E4	329.63
#define	F4	349.23
#define	Gb4	369.99
#define	G4	392.00
#define	Ab4	415.30
#define	LA4	440.00
#define	Bb4	466.16
#define	B4	493.88
#define	C5	523.25
#define	Db5	554.37
#define	D5	587.33
#define	Eb5	622.25
#define	E5	659.26
#define	F5	698.46
#define	Gb5	739.99
#define	G5	783.99
#define	Ab5	830.61
#define	LA5	880.00
#define	Bb5	932.33
#define	B5	987.77
#define	C6	1046.50
#define	Db6	1108.73
#define	D6	1174.66
#define	Eb6	1244.51
#define	E6	1318.51
#define	F6	1396.91
#define	Gb6	1479.98
#define	G6	1567.98
#define	Ab6	1661.22
#define	LA6	1760.00
#define	Bb6	1864.66
#define	B6	1975.53
#define	C7	2093.00
#define	Db7	2217.46
#define	D7	2349.32
#define	Eb7	2489.02
#define	E7	2637.02
#define	F7	2793.83
#define	Gb7	2959.96
#define	G7	3135.96
#define	Ab7	3322.44
#define	LA7	3520.01
#define	Bb7	3729.31
#define	B7	3951.07
#define	C8	4186.01
#define	Db8	4434.92
#define	D8	4698.64
#define	Eb8	4978.03
// DURATION OF THE NOTES 
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

AsyncWebServer server(80);

const char* ssid = "WiFi";
const char* password = "123456789";

int duration = 0;

//const char* PARAM_MESSAGE = "message";

void Alarm() {
  int f;
  int d = 3;
  unsigned long time_now = 0;
  Serial.println("Alarm");
  digitalWrite(ALARM_PIN, HIGH);

  time_now = millis();
  while(millis() < time_now + duration){
    for(f=635;f<=912;f++){
      tone(PIEZO_PIN, f,d);
      delay(d);
    }
    for(f=911;f>=634;f--){
      tone(PIEZO_PIN, f,d);
      delay(d);
    }
  }
  digitalWrite(ALARM_PIN, LOW);
}

void Light() {
  digitalWrite(ALARM_PIN, HIGH);
  delay(duration);
  digitalWrite(ALARM_PIN, LOW);
}

void Sound() {
  int f;
  int d = 3;
  unsigned long time_now = 0;

  time_now = millis();
  while(millis() < time_now + duration){
    for(f=635;f<=912;f++){
      tone(PIEZO_PIN, f,d);
      delay(d);
    }
    for(f=911;f>=634;f--){
      tone(PIEZO_PIN, f,d);
      delay(d);
    }
  }
}

void Music() {
    //tone(pin, note, duration)
    tone(PIEZO_PIN,LA3,Q);
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(PIEZO_PIN,LA3,Q);
    delay(1+Q);
    tone(PIEZO_PIN,LA3,Q);
    delay(1+Q);
    tone(PIEZO_PIN,F3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);

    tone(PIEZO_PIN,LA3,Q);
    delay(1+Q);
    tone(PIEZO_PIN,F3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    tone(PIEZO_PIN,LA3,H);
    delay(1+H);
    
    tone(PIEZO_PIN,E4,Q); 
    delay(1+Q); 
    tone(PIEZO_PIN,E4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,E4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,F4,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    
    tone(PIEZO_PIN,Ab3,Q);
    delay(1+Q);
    tone(PIEZO_PIN,F3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    tone(PIEZO_PIN,LA3,H);
    delay(1+H);
    
    tone(PIEZO_PIN,LA4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,LA3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,LA3,S);
    delay(1+S);
    tone(PIEZO_PIN,LA4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,Ab4,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,G4,S);
    delay(1+S);
    
    tone(PIEZO_PIN,Gb4,S);
    delay(1+S);
    tone(PIEZO_PIN,E4,S);
    delay(1+S);
    tone(PIEZO_PIN,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(PIEZO_PIN,Bb3,E);
    delay(1+E);
    tone(PIEZO_PIN,Eb4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,D4,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,Db4,S);
    delay(1+S);
    
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    tone(PIEZO_PIN,B3,S);
    delay(1+S);
    tone(PIEZO_PIN,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(PIEZO_PIN,F3,E);
    delay(1+E);
    tone(PIEZO_PIN,Ab3,Q);
    delay(1+Q);
    tone(PIEZO_PIN,F3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,LA3,S);
    delay(1+S);
    
    tone(PIEZO_PIN,C4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,LA3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    tone(PIEZO_PIN,E4,H);
    delay(1+H);
    
    tone(PIEZO_PIN,LA4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,LA3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,LA3,S);
    delay(1+S);
    tone(PIEZO_PIN,LA4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,Ab4,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,G4,S);
    delay(1+S);
    
    tone(PIEZO_PIN,Gb4,S);
    delay(1+S);
    tone(PIEZO_PIN,E4,S);
    delay(1+S);
    tone(PIEZO_PIN,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(PIEZO_PIN,Bb3,E);
    delay(1+E);
    tone(PIEZO_PIN,Eb4,Q);
    delay(1+Q);
    tone(PIEZO_PIN,D4,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,Db4,S);
    delay(1+S);
    
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    tone(PIEZO_PIN,B3,S);
    delay(1+S);
    tone(PIEZO_PIN,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(PIEZO_PIN,F3,E);
    delay(1+E);
    tone(PIEZO_PIN,Ab3,Q);
    delay(1+Q);
    tone(PIEZO_PIN,F3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    
    tone(PIEZO_PIN,LA3,Q);
    delay(1+Q);
     tone(PIEZO_PIN,F3,E+S);
    delay(1+E+S);
    tone(PIEZO_PIN,C4,S);
    delay(1+S);
    tone(PIEZO_PIN,LA3,H);
    delay(1+H);
    
    delay(2*H);
}

Ticker asyncAlarm(Alarm, 1, 1);
Ticker asyncLight(Light, 1, 1);
Ticker asyncSound(Sound, 1, 1);
Ticker asyncMusic(Music, 1, 1);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "Hello, world");
  });

  // Send a GET request to <IP>/tone?f=<frequency>&d=<duration(ms)>
  server.on("/tone", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String freq;
      String dur;

      if (request->hasParam("d") && request->hasParam("f")) {
        freq = request->getParam("f")->value();
        dur = request->getParam("d")->value();
        tone(PIEZO_PIN,freq.toDouble(),dur.toInt());
        request->send(200, "text/plain", "Tone: " + freq);
      }else{
        request->send(200, "text/plain", "Send a GET request to <IP>/tone?f=<frequency>&d=<duration(ms)");
      }
  });

  // Send a GET request to <IP>/music
  server.on("/music", HTTP_GET, [] (AsyncWebServerRequest *request) {
      asyncMusic.start();
      request->send(200, "text/plain", "MUSIC");
  });
  
  // Send a GET request to <IP>/alarm?duration=<ms>&light=<1/0>&sound=<1/0>
  server.on("/alarm", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String light;
    String sound;
    int comb = 0;

    if (request->hasParam("duration") && request->hasParam("light") && request->hasParam("sound")) {
      light = request->getParam("light")->value();
      sound = request->getParam("sound")->value();
      duration = request->getParam("duration")->value().toInt();

      Serial.println(light);
      Serial.println(sound);
      Serial.println(duration);

      Serial.println("");

      if (light == "1"){
        comb += 2;
      }
      if (sound == "1"){
        comb += 4;
      }
      Serial.println(comb);
      switch(comb) {
          case 2 : asyncLight.start(); break;
          case 4 : asyncSound.start(); break;
          case 6 : asyncAlarm.start(); break;
      }
      request->send(200, "text/plain", "OK");
    }else{
      request->send(200, "text/plain", "Send a GET request to <IP>/alarm?duration=<ms>&light=<1/0>&sound=<1/0>");
    }
  });

/*
  // Send a POST request to <IP>/post with a form field message set to <message>
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
      String message;
      if (request->hasParam(PARAM_MESSAGE, true)) {
          message = request->getParam(PARAM_MESSAGE, true)->value();
      } else {
          message = "No message sent";
      }
      request->send(200, "text/plain", "Hello, POST: " + message);
  });
*/
  server.onNotFound(notFound);

  server.begin();
}

void loop() {
  asyncAlarm.update();
  asyncLight.update();
  asyncSound.update();
  asyncMusic.update();
}

