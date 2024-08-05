.PHONY: build deploy, clean

build: src/main.c src/ultrasonic_distance.c
	avr-gcc -O -mmcu=atmega328p $^ -Isrc/ -DF_CPU=20000000 -DLEFT_MOTOR=PD3 -DRIGHT_MOTOR=PD5 -DULTRASONIC_TRIGGER=PD2 -DULTRASONIC_ECHO=PD4 -DIR_DIODE=PD7 -DRUN_BUTTON=PB0 -o main
	avr-objcopy -O ihex -R .eeprom main main.hex

deploy: build
	avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

clean:
	rm -f main main.hex
