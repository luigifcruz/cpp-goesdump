# cpp-goesdump
***Warning:*** Work in Progress.<br>
This program receives the packets created by OSP's xritDecoder via TCP and parse them into .lrit files.
It works with LRIT and HRIT packets from NOAA Geostationary Satellites (GOES-13, GOES-15, GOES-16 and GOES-14). 
This is a C++ implementation of C# [GOES Dump](https://github.com/opensatelliteproject/goesdump). 
You can use XRIT2PIC to convert the generated .lrit files into an image.

### Installation 
Using CMake:
```
git clone https://github.com/luigifreitas/cpp-goesdump.git
mkdir build
cd build
cmake ..
make
```

### Dependencies 
- [Simple-Web-Server](https://github.com/eidheim/Simple-Web-Server)
- [libaec](https://github.com/MathisRosenhauer/libaec)
- [libsathelper](https://github.com/opensatelliteproject/libsathelper)

### Todo 
- [x] Add CMake.
- [x] Implement Weather Data dumping.
- [x] Implement Text Data dumping. 
- [ ] Finish WebUI.
- [ ] Check the frame CRC.
- [ ] Improve CPU usage.

