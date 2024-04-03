#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("iot", "project1234");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("..");
    delay(200);
  }
  Serial.println();
  Serial.println("NodeMCU is Connected!");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led D5

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("iot", "project1234");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(led, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /ledon HTTP/1.1")
    {
      digitalWrite(led, HIGH);
    }
    if(request == "GET /ledoff HTTP/1.1")
    {
      digitalWrite(led, LOW);
    }
  }
}

#include <NODEMCU.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>








#define USE_DHT11  1

#ifdef USE_DHT11

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN D1
#define DHTTYPE    DHT11
DHT_Unified dht(DHT_PIN, DHTTYPE);

uint32_t delayMSDHT11;
uint32_t lastDHTRead;

struct{
  double temp = 0.0;
  double humidity = 0.0;
  int error = 0;
} DHT11Data;


void setUpDHT11(){
dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMSDHT11 = (sensor.min_delay / 1000)+200;
  lastDHTRead = millis();
}



boolean isDHTReady(){
  if( ((lastDHTRead + delayMSDHT11) < millis()) &&  ((lastDHTRead + 1000) < millis())){
    return true;
  }
  else{
    return false;
  }
}

void readDHT11(boolean printdebug){
  DHT11Data.error = 0;
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    if(printdebug){
      Serial.println(F("Error reading temperature!"));
    }
    DHT11Data.error = 1;
  }
  else {
    if(printdebug){
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }
    DHT11Data.temp =  event.temperature;
    Serial.println(sizeof(event.temperature));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    if(printdebug){
      Serial.println(F("Error reading humidity!"));
    }
    DHT11Data.error = 1;
  }
  else {
    if(printdebug){
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    DHT11Data.humidity =  event.relative_humidity;
  }
  lastDHTRead = millis();
}
#endif //USE_DHT11











///*******************************************************///
///*******************************************************///
///              SERVER CODE START FROM HERE              ///
///*******************************************************///
///*******************************************************///
#define LOLIN_LED D4
#define PRODUCTION  1
//#define DEBUG_SERVER  1
String HOME = "/"; 

/* Global vareiables are here */
unsigned long timestamp = 0;


/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);


//@auto generated code
//QR Format
//WIFI:S:MySSID;T:WPA;P:MyPassW0rd;;
//hotspot config
const char* hotspot_name = "iota1118-slr-rbt";
const char* hotspot_password = "iota1118";

struct{
	String message;
	String message_class = "hide";

	float temperature;
	String temperature_class = "success";

	String fan;
	String fan_class = "success";

	String btn_fwd = "FORWARD";
	String btn_fwd_cmd;
	String btn_fwd_class = "success";

	String btn_right = "RIGHT";
	String btn_right_cmd;
	String btn_right_class = "success";

	String btn_left = "LEFT";
	String btn_left_cmd;
	String btn_left_class = "success";

	String btn_stop = "STOP";
	String btn_stop_cmd;
	String btn_stop_class = "success";

	String btn_back = "BACK";
	String btn_back_cmd;
	String btn_back_class = "success";

	String btn_on_off = "ON";
	String btn_on_off_cmd;
	String btn_on_off_class = "success";

	String btn_mode = "AUTO";
	String btn_mode_cmd;
	String btn_mode_class = "success";

} dataPacket;


struct{
	 const int BTN_NONE = -1;
	 const int BTN_FWD = 1000;
	 const int BTN_RIGHT = 1001;
	 const int BTN_LEFT = 1002;
	 const int BTN_STOP = 1003;
	 const int BTN_BACK = 1004;
	 const int BTN_ON_OFF = 1005;
	 const int BTN_MODE = 1006;
} btnAction;
int userBtnAction = btnAction.BTN_NONE;


#ifdef PRODUCTION 
String getDataJson(){
	return "{\"message\":\""+dataPacket.message+"\",\"message_class\":\""+dataPacket.message_class+"\", "
	"\"temperature\":\""+String(dataPacket.temperature)+"\",\"temperature_class\":\""+dataPacket.temperature_class+"\", "
	"\"fan\":\""+dataPacket.fan+"\",\"fan_class\":\""+dataPacket.fan_class+"\", "
	"\"btn_fwd\":\""+dataPacket.btn_fwd+"\",\"btn_fwd_class\":\""+dataPacket.btn_fwd_class+"\", "
	"\"btn_right\":\""+dataPacket.btn_right+"\",\"btn_right_class\":\""+dataPacket.btn_right_class+"\", "
	"\"btn_left\":\""+dataPacket.btn_left+"\",\"btn_left_class\":\""+dataPacket.btn_left_class+"\", "
	"\"btn_stop\":\""+dataPacket.btn_stop+"\",\"btn_stop_class\":\""+dataPacket.btn_stop_class+"\", "
	"\"btn_back\":\""+dataPacket.btn_back+"\",\"btn_back_class\":\""+dataPacket.btn_back_class+"\", "
	"\"btn_on_off\":\""+dataPacket.btn_on_off+"\",\"btn_on_off_class\":\""+dataPacket.btn_on_off_class+"\", "
	"\"btn_mode\":\""+dataPacket.btn_mode+"\",\"btn_mode_class\":\""+dataPacket.btn_mode_class+"\"}";
}
#endif


void handel_UserAction(){
	for (uint8_t i = 0; i < server.args(); i++) {
		if(server.argName(i)== "btn_fwd"){
				userBtnAction = btnAction.BTN_FWD;
				dataPacket.btn_fwd_cmd = server.arg(i);
		}
		else if(server.argName(i)== "btn_right"){
				userBtnAction = btnAction.BTN_RIGHT;
				dataPacket.btn_right_cmd = server.arg(i);
		}
		else if(server.argName(i)== "btn_left"){
				userBtnAction = btnAction.BTN_LEFT;
				dataPacket.btn_left_cmd = server.arg(i);
		}
		else if(server.argName(i)== "btn_stop"){
				userBtnAction = btnAction.BTN_STOP;
				dataPacket.btn_stop_cmd = server.arg(i);
		}
		else if(server.argName(i)== "btn_back"){
				userBtnAction = btnAction.BTN_BACK;
				dataPacket.btn_back_cmd = server.arg(i);
		}
		else if(server.argName(i)== "btn_on_off"){
				userBtnAction = btnAction.BTN_ON_OFF;
				dataPacket.btn_on_off_cmd = server.arg(i);
		}
		else if(server.argName(i)== "btn_mode"){
				userBtnAction = btnAction.BTN_MODE;
				dataPacket.btn_mode_cmd = server.arg(i);
		}
	}
	server.send(200, "text/json", getDataJson());
}
 client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>Welcome to the Webpage!</h1>");
  client.println("<h3>LED Controls<h3>");
  client.println("<br>");
  client.println("<a href=\"/led1on\"\"><button>LED 1 ON</button></a>");
  client.println("<a href=\"/led1off\"\"><button>LED 1 OFF</button></a><br/>");
  client.println("<a href=\"/led2on\"\"><button>LED 2 ON</button></a>");
  client.println("<a href=\"/led2off\"\"><button>LED 2 OFF</button></a><br/>");
  client.println("</html>");
}
