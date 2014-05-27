/* Web_Buzzer.pde - example sketch for Webduino library */

#include "SPI.h"
#include "Ethernet.h"
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <WebServer.h>
#include <string>
#include <cstring>
#include <vector>

/* CHANGE THIS TO YOUR OWN UNIQUE VALUE.  The MAC number should be
 * different from any other devices on your network or you'll have
 * problems receiving packets. */
static uint8_t mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xEA, 0x17 };

/* all URLs on this server will start with /buzz because of how we
 * define the PREFIX value.  We also will listen on port 80, the
 * standard HTTP service port */
#define PREFIX "/buzz"
WebServer webserver(PREFIX, 80);
std::vector<std::string> messages;

/* the piezo speaker on the Danger Shield is on PWM output pin #3 */
#define BUZZER_PIN 3

/* this is the number of microseconds to wait after turning the
 * speaker on before turning it off. */
int buzzDelay = 0;

/* toggle is used to only turn on the speaker every other loop
iteration. */
char toggle = 0;

/* This command is set as the default command for the server.  It
 * handles both GET and POST requests.  For a GET, it returns a simple
 * page with some buttons.  For a POST, it saves the value posted to
 * the buzzDelay variable, affecting the output of the speaker */
void buzzCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those
       * buffers. */
      repeat = server.readPOSTparam(name, 16, value, 16);

      /* this is a standard string comparison function.  It returns 0
       * when there's an exact match.  We're looking for a parameter
       * named "buzz" here. */
      if (strcmp(name, "message") == 0)
      {
	/* use the STRing TO Unsigned Long function to turn the string
	 * version of the delay number into our integer buzzDelay
	 * variable */
        
        
        messages.push_back(value);
        Serial.println(messages.at(0).c_str());
      }
    } while (repeat);
    
    // after procesing the POST data, tell the web browser to reload
    // the page using a GET method. 
    server.httpSeeOther(PREFIX);
    return;
  }

  /* for a GET or HEAD, send the standard "it's all OK headers" */
  server.httpSuccess();

  /* we don't output the body for a HEAD request */
  if (type == WebServer::GET)
  {
//    messages.push_back("asdf");
//        messages.push_back("asdf2");
    /* store the HTML in program memory using the P macro */
    std::string html = 
    "<body>\
    <form action='/buzz' method='POST'>\
        <label>Message:</label><input type='text' name='message'/>\
        <input type='submit' value='Senden'>\
    </form>\
    <div id='messages'>";
     
    for (std::vector<std::string>::const_iterator iter = messages.begin(); iter != messages.end(); ++iter) {
      html.append("<p>");  
      html.append(*iter);
      html.append("</p>");
    }
    
    html.append("</div>\
    </body>");
  
  const unsigned char* c = (const unsigned char*) html.c_str();
  char* cstr = new char[html.length()+1];
  std::strncpy (cstr, html.c_str(), html.size());
  Serial.println(cstr);
    server.printP(cstr);
  }
}

void setup()
{ 
  Serial.begin(9600);
  
  // set the PWM output for the buzzer to out
  pinMode(BUZZER_PIN, OUTPUT);

   // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  Ethernet.begin(mac);
  Serial.println(Ethernet.localIP());
  
  /* register our default command (activated with the request of
   * http://x.x.x.x/buzz */
  webserver.setDefaultCommand(&buzzCmd);

  /* start the server to wait for connections */
  webserver.begin();
}

void loop()
{
  // process incoming connections one at a time forever
  webserver.processConnection();

  /* every other time through the loop, turn on and off the speaker if
   * our delay isn't set to 0. */
  if ((++toggle & 1) && (buzzDelay > 0))
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(buzzDelay);
    digitalWrite(BUZZER_PIN, LOW);
  }
}
