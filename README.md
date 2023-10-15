# Saar Hackathon #04 - St Martins LED

<img src="doc/Lantern.jpg" width="700px" />

## Idee
~~WLAN~~ BLE Fähige LED St. Martins Laterne mit Microcontroller.
Als Controller Software wird WS2812FX und Arduino ESP32 Ble verwendet.

Laternen advertisen einen BLE-Service und gleichtzeitig scannen nach diesem.
Dadurch können die Laternen den Abstand zueinander ermitteln und verändern die Leucht animation.

# Hardware
ESP32 + WS2812 RGB LED (Strip) + 5V Powerbank + Lanterne

# 3D Model
<img src="doc/Rendering.jpg" width="400px" />

<a href="lantern_model/SaarHackathonLantern.stl">SaarHackathonLantern.stl</a>

# Modi

## Keine Laterne in der Nähe: Rot
<img src="doc/ToFarAway.jpg" width="480px" />

## Lanterne in der Nähe: Regenbogen
https://github.com/duglah/SaarHackathon4_StMartinsLed/assets/3907597/91483c53-8666-48b6-8741-02812c0bc819

## Lanternen berühren sich: PARRRTTTYYYY 🎉🥳
https://github.com/duglah/SaarHackathon4_StMartinsLed/assets/3907597/8d8949d4-4163-4ff2-8dfa-97adc51bd50c

# How to flash?
https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/flashing-firmware.html