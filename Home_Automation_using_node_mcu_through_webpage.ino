/*
 * Program for Home Automation Project
 * Controll Apliances through Webpage
 */
 #include<ESP8266WiFi.h>
 const char* ssid = "Honor 9 Lite";
 const char* password = "abhishek11";
 WiFiClient client;
 WiFiServer server(80);
 #define led D5 
void setup() 
{
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("..");
    delay(2000);
  }
  Serial.println();
  Serial.println("Node MCU is connected");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();
  if(client == 1)
  {
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /led1on HTTP/1.1")
    {
      digitalWrite(led,HIGH);  
    }
    if(request == "GET /led1off HTTP/1.1")
    {
      digitalWrite(led,LOW);  
    }
    if(request == "GET /led2on HTTP/1.1")
    {
      digitalWrite(LED_BUILTIN,LOW);  
    }
    if(request == "GET /led2off HTTP/1.1")
    {
      digitalWrite(LED_BUILTIN,HIGH);
    }
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Context-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>ESP Server</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Home Automation</h1>");
  client.println("<h2>Control the Appliances</h2>");
  client.println("<br>");
  client.println("<a href=\"/led1on\"\"><button>Light 1 ON</button></a>");
  client.println("<a href=\"/led1off\"\"><button>Light 1 OFF</button></a><br/>");
  client.println("<br>");
  client.println("<a href=\"/led2on\"\"><button>Light 2 ON</button></a>");
  client.println("<a href=\"/led2off\"\"><button>Light 2 OFF</button></a><br/>");
  client.println("</body>");
  client.println("</body>");
}

