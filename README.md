# R-TYPE - Epitech Project
![](https://img.shields.io/badge/Project-Made%20with%20Love-ff69b4)
<a href="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" alt="Cmake">
        <img src="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" alt="Conan">
        <img src="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-blue" alt="C++">
        <img src="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-blue" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" alt="SFML">
        <img src="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" /></a>

This project is from our advanced C++ knowledge unit. It introduced us to networked video game develop
ment, while giving us opportunity to explore in-depth advanced development topics as well as to learn
good software engineering practices.
Our goal was to implement a multithreaded server and a graphical client for a game called R-Type, using an en
gine of your own design.

## R-TYPE - The game
R-type is informally called a Horizontal Shmup (e.g. [Shoot’em’up](https://en.wikipedia.org/wiki/Shoot_%27em_up#Scrolling_shooters)), and while R-Type is not the first one of
its category, this one has been a huge success amongst gamers in the 90’s, and had several ports, spin-offs,
and 3D remakes on modern systems.
Other similar and well known games are the Gradius series and Blazing Star on Neo Geo.

## Use Docker
The project can be launched via a docker image if you don't want to use Docker you can skip this part. 
**Install Docker :**

[Official installation guide](https://docs.docker.com/engine/install/)

**Use Docker :**
```Launch Docker Desktop
On a terminal : docker build -t <image_name> .
docker run -it <image_name>
```

You are now in a Linux-like environment. Enjoy! 

## Installation
**Linux :**
```
cmake . -DCMAKE_BUILD_TYPE=Release && cmake --build . --config Release && cpack -C Release
```
**Windows :**
```
Launch Visual Studio
(cmake . -DCMAKE_BUILD_TYPE=Release) -and (cmake --build . --config Release) -and (cpack -C Release)
```

## Usage
**For the server, in a terminal :**
```
./bin/r-type_server
```
**For a client, in another terminal :**
```
./bin/r-type_client <host>
```

## Requirements
* **Supported platforms : Linux and Windows**
* **Buildsystem : Cmake**
* **Package manager: Conan**
* **Language : C++**
* **Library : SFML**

## Documentation
**Doxygen :**   
Our documentation is made with doxygen. Here are the commands if you wanna check it.
* **Linux :**
```
your_web_browser html/index.html
```
* **Windows :**
```
start (your_web_browser).exe html/index.html
```

**Engine-focused/Network-focused documentation :**  
With both Readmes you'll be able to understand the engine or network and use them.

* **[Engine](https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-2-rtype-luc1.schmitt/tree/main/Engine)**
* **[Network](https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-2-rtype-luc1.schmitt/tree/main/include)**


## Authors
  * **Yosra Hassan** - [@yosracandy](https://github.com/yosracandy)
  * **Royale Badiabo** - [@broyale](https://github.com/broyale)
  * **Yohan Henry** - [@yoyokaseur](https://github.com/yoyokaseur)
  * **Brice Boualavong** - [@efroza](https://github.com/Efroza)
  * **Luc Schmitt** - [@lucsc](https://github.com/Lucsc)