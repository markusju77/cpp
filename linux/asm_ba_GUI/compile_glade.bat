//gcc `pkg-config --cflags gtk+-3.0` -Wno-format -o toka toka.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --libs=gtk+-3.0` -export-dynamic
gcc `pkg-config --cflags gtk+-3.0` -o toka toka.c `pkg-config --libs gtk+-3.0`
gcc `pkg-config --cflags gtk+-3.0` -o auttava auttava.c `pkg-config --libs gtk+-3.0`
