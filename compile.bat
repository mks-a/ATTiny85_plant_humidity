:: -g generate debug information
:: -c compile only
cls
"D:\Arduino\arduino_1.8.3\hardware\tools\avr/bin/avr-gcc" -c -g -Os -w -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=attiny85 -DF_CPU=16500000L .\code\main.c -o tmp\main.o
"D:\Arduino\arduino_1.8.3\hardware\tools\avr/bin/avr-gcc" -c -g -Os -w -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=attiny85 -DF_CPU=16500000L .\timer0\timer0.c -o tmp\timer0.o
"D:\Arduino\arduino_1.8.3\hardware\tools\avr/bin/avr-gcc" -mmcu=attiny85 -o main.elf tmp\main.o tmp\timer0.o -lm -emain
::"D:\Arduino\arduino_1.8.3\hardware\tools\avr/bin/avr-gcc" -mmcu=attiny85 -o main.elf tmp\main.o -lm -emain
"D:\Arduino\arduino_1.8.3\hardware\tools\avr/bin/avr-objcopy" -O ihex -R .eeprom main.elf main.hex

