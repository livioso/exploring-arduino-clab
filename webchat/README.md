# Webchat clab Projekt



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