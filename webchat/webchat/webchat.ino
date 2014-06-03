/* Web_Buzzer.pde - example sketch for Webduino library */

#include "SPI.h"
#include "Ethernet.h"
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <WebServer.h>
#include <string>
#include <sstream>
#include <cstring>
#include <list>

/* CHANGE THIS TO YOUR OWN UNIQUE VALUE.  The MAC number should be
 * different from any other devices on your network or you'll have
 * problems receiving packets. */
static uint8_t mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xEA, 0x17 };

/* all URLs on this server will start with /buzz because of how we
 * define the PREFIX value.  We also will listen on port 80, the
 * standard HTTP service port */
#define PREFIX "/chat"
WebServer webserver(PREFIX, 80);
std::list<std::string> messages;
std::string username;
std::stringstream ss;


/* This command is set as the default command for the server.  It
 * handles both GET and POST requests.  For a GET, it returns a simple
 * page with some buttons.  For a POST, it saves the value posted to
 * the buzzDelay variable, affecting the output of the speaker */
void chatCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
//  ss << "asdf";
//  std::string str(ss.str());
//  server.print(str.c_str());
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

          messages.push_front(value);
      }
      if (strcmp(name, "username") == 0)
      {
  /* use the STRing TO Unsigned Long function to turn the string
   * version of the delay number into our integer buzzDelay
   * variable */

          username = value;
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
    /* store the HTML in program memory using the P macro */

    std::string html =
    "<html>\
    <meta http-equiv='content-type' content='text/html; charset=UTF-8'>\
    <body>\
    <style type='text/css'>\
        body {\
            font: 16px Helvetica, Arial;\
        }\
        h2 {\
            margin-top: 2em;\
        }\
        .message span {\
            padding-right: 2em;\
        }\
    </style>\
    <h1>Arduino Webchat ({{IP-Adresse/buzz}})</h1>\
    <p>Livio Bieri & Marius Küng clabC 2iCa</p>\
    <form action='/chat' method='POST'>\
        <p><label>Benutzername:</label><input type='text' name='username' value='";
        server.print(html.c_str());
        server.print(username.c_str());
        server.print("'/></p><p><label>Nachricht:</label><input type='text' name='message'/></p><input type='hidden' value='{{username}}'><input type='submit' value='Senden'></form><h2>Chat</h2><div id='messages'>");

   

    for (std::list<std::string>::const_iterator iter = messages.begin(); iter != messages.end(); ++iter) {
        server.print("<p class='message'><span><strong>");
        server.print(username.c_str());
        server.print("</strong> 30.05.14 11:00:</span>");
        server.print(iter->c_str());
        server.print("</p>");
    }

    server.print("</div></body></html>");

  }
}

void setup()
{
  Serial.begin(9600);

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
  webserver.setDefaultCommand(&chatCmd);

  /* start the server to wait for connections */
  webserver.begin();
}

void loop()
{
  // process incoming connections one at a time forever
  webserver.processConnection();
}

