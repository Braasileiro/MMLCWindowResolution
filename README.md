# MMLCWindowResolution
A program to change the window size of the Mega Man Legacy Collection.

# Installing
Installation instructions can be found in the guide of Steam created by me: [MMLCWindowResolution Tool](http://steamcommunity.com/sharedfiles/filedetails/?id=647930410)

# Building
```
windres MMLCWindowResolution.rc -O coff -o MMLCWindowResolution.res
gcc -Wall -static-libgcc MMLCWindowResolution.c -o MMLCWindowResolution.exe MMLCWindowResolution.res
```
