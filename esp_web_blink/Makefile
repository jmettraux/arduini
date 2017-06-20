
# from https://github.com/sudar/Arduino-Makefile/issues/494

ARDUINO_DIR:=/Applications/Arduino.app/Contents/Java
ARDUINO_MORE:=$(HOME)/Library/Arduino15
ESPTOOL:=$(ARDUINO_MORE)/packages/esp8266/tools/esptool/0.4.9/esptool
SKETCH:=source.ino
TARGET_DIR:=$(CURDIR)/build-esp8266
ESP_PORT:=/dev/cu.SLAB_USBtoUART
CPU_FREQUENCY:=80
#CPU_FREQUENCY:=160
UPLOAD_SPEED:=115200

#/Applications/Arduino.app/Contents/Java/arduino-builder
#-compile -logger=machine
#-hardware /Applications/Arduino.app/Contents/Java/hardware
#-hardware /Users/jmettraux/Library/Arduino15/packages
#-tools /Applications/Arduino.app/Contents/Java/tools-builder
#-tools /Applications/Arduino.app/Contents/Java/hardware/tools/avr
#-tools /Users/jmettraux/Library/Arduino15/packages
#-built-in-libraries /Applications/Arduino.app/Contents/Java/libraries
#-libraries /Users/jmettraux/Documents/Arduino/libraries
#-fqbn=esp8266:esp8266:nodemcuv2:CpuFrequency=160,UploadSpeed=115200,FlashSize=4M3M
#-ide-version=10802
#-build-path /var/folders/nc/k69p4qld1lzgtr6ktqwkvxn40000gn/T/arduino_build_699676
#-warnings=none
#-build-cache /var/folders/nc/k69p4qld1lzgtr6ktqwkvxn40000gn/T/arduino_cache_144344
#-prefs=build.warn_data_percentage=75
#-prefs=runtime.tools.mkspiffs.path=/Users/jmettraux/Library/Arduino15/packages/esp8266/tools/mkspiffs/0.1.2 -prefs=runtime.tools.esptool.path=/Users/jmettraux/Library/Arduino15/packages/esp8266/tools/esptool/0.4.9
#-prefs=runtime.tools.xtensa-lx106-elf-gcc.path=/Users/jmettraux/Library/Arduino15/packages/esp8266/tools/xtensa-lx106-elf-gcc/1.20.0-26-gb404fb9-2
#-verbose /Users/jmettraux/Library/Arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/esp8266/examples/Blink/Blink.ino


all:
	@ mkdir -p $(TARGET_DIR)

	$(ARDUINO_DIR)/arduino-builder -compile -logger=machine \
	-hardware "$(ARDUINO_DIR)/hardware" \
    -hardware "$(ARDUINO_MORE)/packages" \
	-tools "$(ARDUINO_DIR)/tools-builder" \
	-tools "$(ARDUINO_DIR)/hardware/tools/avr" \
	-tools "$(ARDUINO_MORE)/packages" \
	-built-in-libraries "$(ARDUINO_DIR)/libraries" \
	-fqbn=esp8266:esp8266:nodemcuv2:CpuFrequency=$(CPU_FREQUENCY),UploadSpeed=$(UPLOAD_SPEED),FlashSize=4M3M \
	-ide-version=10802 \
	-build-path "$(TARGET_DIR)" \
	-warnings=none \
	-prefs=build.warn_data_percentage=75 \
	-verbose "$(SKETCH)"
    #-libraries "$(ARDUINO_MORE)/packages/esp8266/hardware/esp8266/2.3.0/libraries" \

flash:
	$(ESPTOOL) -v -cd nodemcu -cb $(UPLOAD_SPEED) -cp $(ESP_PORT) -ca 0x00000 -cf $(TARGET_DIR)/$(SKETCH).bin

upload: all flash

clean:
	rm -rf $(TARGET_DIR)

monitor:
	screen $(ESP_PORT) 9600

