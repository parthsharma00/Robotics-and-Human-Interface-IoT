#include <SPI.h>
#include <LoRa.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LoRa Syncing...");

  LoRa.setPins(10, 9, 2);
  if (!LoRa.begin(433E6)) {
    lcd.clear();
    lcd.print("LoRa Failed!");
    while (1);
  }
  
  LoRa.setSyncWord(0xF3); // The "Sync" password
  lcd.clear();
  lcd.print("Ready to Receive");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data Received:");
    
    lcd.setCursor(0, 1);
    while (LoRa.available()) {
      String data = LoRa.readString();
      lcd.print(data);
    }
    
    lcd.setCursor(0, 3);
    lcd.print("RSSI: ");
    lcd.print(LoRa.packetRssi());
  }
}