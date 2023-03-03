# Network
The network has two types of communications. He communicates via TCP for everything that is outside of the game and during the game the communication will be in UDP.  
We made protocols for both communications that are available to read here.
For the [TCP protocol](https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-2-rtype-luc1.schmitt/blob/main/rfc888_TCP.txt) and the [UDP protocol](https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-2-rtype-luc1.schmitt/blob/main/rfc999_UDP.txt)

## How does it work ?
The client/server communicates via binary communication. You serialize struct in binary form and deserialize it in his original form that is the different struct that we have in the headers.hpp file.  
The first thing that is sent is the header struct, which has the id and the data type, followed by the struct data that was specified in the header.

## Add commands
To add a command you have to write two things in the Headers.hpp file:  
* **server/client enum :**
Add an element in the server/client enum with a Int16 linked to it for the new command that you want to add.

* **Struct for the new command :**
Add a new struct where you add the parameters that you need for the command that you add in the enum.