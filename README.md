# cpp-goesdump
Warning Work in Progress. This program currently only outputs decompressed RICE images. All files will be supported soon.
This is a C++ implementation of C# [GOES Dump](https://github.com/opensatelliteproject/goesdump). You can use XRIT2PIC to convert the generated .lrit files to an image.

### Installation 
CMake will be available soon.

```
git clone https://github.com/luigifreitas/cpp-goesdump.git
cd cpp-goesdump
make
```

### Dependencies 
[Simple-Web-Server](https://github.com/eidheim/Simple-Web-Server)
[libaec](https://github.com/MathisRosenhauer/libaec)
[libsathelper](https://github.com/opensatelliteproject/libsathelper)

### Todo 
- [ ] Finish WebUI.
- [ ] Check the frame CRC.
- [ ] Implement Weather Data dumping.
- [ ] Implement Text Data dumping. 
- [ ] Improve CPU usage.

