#include <WS2812FX.h>

namespace LED
{

#define LED_COUNT 12
#define LED_PIN 16

    enum class PROXIMITY
    {
        ADJACENT,
        CLOSE,
        AWAY
    } previousDeviceProximity;

    const int RSSI_THRESHOLD_CLOSE = -80;
    const int RSSI_THRESHOLD_ADJACENT = -55;

    WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

    void setup()
    {
        ws2812fx.init();
        ws2812fx.setBrightness(100);
        ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
        ws2812fx.setSpeed(10000);
        ws2812fx.start();
    }

    void onAdjacent()
    {
        ws2812fx.init();
        ws2812fx.setBrightness(100);
        ws2812fx.setMode(FX_MODE_BLINK);
        ws2812fx.setSpeed(100);
        ws2812fx.setColor(255, 0, 255);
        ws2812fx.start();
    }

    void onClose()
    {
        ws2812fx.init();
        ws2812fx.setBrightness(100);
        ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
        ws2812fx.setSpeed(7000);
        ws2812fx.start();
    }

    void onFarAway()
    {
        ws2812fx.init();
        ws2812fx.setBrightness(100);
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(255, 0, 0);
        ws2812fx.setSpeed(100);
        ws2812fx.start();
    }

    void updateColor(bool deviceIsClose, int rssi)
    {

        if (!deviceIsClose && previousDeviceProximity != PROXIMITY::AWAY)
        {
            onFarAway();
            return;
        }

        if (rssi >= RSSI_THRESHOLD_ADJACENT 
            && previousDeviceProximity != PROXIMITY::ADJACENT)
        {
            onAdjacent();
            previousDeviceProximity = PROXIMITY::ADJACENT;
            return;
        }

        if (rssi < RSSI_THRESHOLD_ADJACENT 
            && rssi >= RSSI_THRESHOLD_CLOSE 
            && previousDeviceProximity != PROXIMITY::CLOSE)
        {
            onClose();
            previousDeviceProximity = PROXIMITY::CLOSE;
            return;
        }

        if (previousDeviceProximity != PROXIMITY::AWAY)
        {
            onFarAway();
            previousDeviceProximity = PROXIMITY::AWAY;
            return;
        }
    }

    void loop(bool deviceIsClose, int rssi)
    {

        updateColor(deviceIsClose, rssi);

        LED::ws2812fx.service();
    }
}