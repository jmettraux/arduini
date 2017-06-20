
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


all:
	@mkdir -p $(TARGET_DIR)

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
      #-libraries "$(CURDIR)/libraries" \

flash:
	$(ESPTOOL) -v -cd nodemcu \
      -cb $(UPLOAD_SPEED) -cp $(ESP_PORT) -ca 0x00000 \
      -cf $(TARGET_DIR)/$(SKETCH).bin

upload: all flash

clean:
	rm -rf $(TARGET_DIR)

monitor:
	#screen $(ESP_PORT) 9600
	screen $(ESP_PORT) 115200

