# Webchat clab Projekt

###### Verfasser: Marius King und Livio Bieri.

##### Beschreibung
> Kleiner einfacher HTTP Webchat der nur das Ardunio Ethernet Shield verwendet. Damit wir nicht HTTP selbst von Grund auf implementieren müssen haben wir eine kleine Library namens Webduino verwendet die diese Tasks für uns übernimmt.

> Die Implementation ist denkbar einfach: Die Chatnachrichten werden in einer `std::list<std::string>>` gespeichert. Eine neue Nachricht kann per POST `?message=bla` hinzugefügt werden. 

![image](http://arduino.cc/en/uploads/Guide/ArduinoWithEthernetShield.jpg)

![image](https://raw.githubusercontent.com/livioso/exploring-arduino-clab/master/webchat/webchat/webchat.png)

##### Erkenntnisse und Schwierigkeiten

+ **Erkenntnisse** 🐣
    + Es stehen erstaunlich viele Libraries stehen zur Verfügung
    + *Standard Template Library* steht standardmässig nicht zur Verfügung. 
      </br> *Alternativ steht ein 
      [Port von uClib++ zur Verfügung](https://github.com/maniacbug/StandardCplusplus).*
      
    + *[Webduino](https://github.com/sirleech/Webduino)* bietet eine spannende Platform um ein kleine
      UIs für den Ardunio zu bauen.
      
    + Casting von `std::string` zu `char[]` mit `.c_str`
    
+ **Probleme** 💩
    + *Memorybeschränkungen* (e.g. Buffersize) sind etwas umständlich

 
