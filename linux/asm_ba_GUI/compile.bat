//g++ -o ./bin/asm_ba ./src/asm_ba.cpp ./src/infix_to_postfix.cpp ./src/karnaugh.cpp ./src/quine_mccluskell.cpp
g++ `pkg-config --cflags gtk+-3.0` -o asm_ba ./src/asm_ba.cpp ./src/infix_to_postfix.cpp ./src/karnaugh.cpp ./src/quine_mccluskell.cpp `pkg-config --libs gtk+-3.0`
