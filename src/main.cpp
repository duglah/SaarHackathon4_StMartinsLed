#include <Arduino.h>
#include <WS2812FX.h>
#include <mutex>
#include "bluetooth.hpp"
#include "led.hpp"
#include <numeric>

#define RSSI_DEVICE_ABSENT -1000
#define PROXIMITY_TIME_FRAME 1500  // In millis

// stores last time device received ble signal and signal strength from device with the specified service uuid
struct BleTime {
  private:
  std::mutex mutex;
  uint64_t time;
  int rssi;

  public:
    void set(int rssi) {
      std::lock_guard<std::mutex> lock(mutex);
      this->time = millis();
      this->rssi = rssi;
    }

    uint64_t getTime() {
      std::lock_guard<std::mutex> lock(mutex);
      return time;
    }

    int getMaxRssi() {
      std::lock_guard<std::mutex> lock(mutex);
      return rssi;
    }
} bleTime;

// Callback function of the bluetooth thread. Gets called with the results of every device search .
std::function<void(std::vector<BLEAdvertisedDevice>)> handleBleDevices = [&](std::vector<BLEAdvertisedDevice> v) {
  int maxDeviceRssi = RSSI_DEVICE_ABSENT;

  for (auto& device: v) {
    if (device.haveServiceUUID() && device.isAdvertisingService(BLE::SERVICE_UUID)) {
      Serial.printf("BLE Advertised Device found: ");
      Serial.printf("Rssi: %d\n", device.getRSSI());
      int rssi = device.getRSSI();
      maxDeviceRssi = max(rssi, maxDeviceRssi);
    }
  }

  if (maxDeviceRssi != RSSI_DEVICE_ABSENT) {
    bleTime.set(maxDeviceRssi);
  }
};

// Gets called once at boot time
void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  LED::setup();
  BLE::setup(&handleBleDevices);

  Serial.println("Starting Arduino BLE Client application...");
}


// Gets automatically called every tick
void loop() {
  bool deviceIsClose = millis() - bleTime.getTime() < PROXIMITY_TIME_FRAME;
  LED::loop(deviceIsClose, bleTime.getMaxRssi());
}
