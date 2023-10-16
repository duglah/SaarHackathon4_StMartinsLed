#include <WS2812FX.h>

namespace LED
{

#define LED_COUNT 12
#define LED_PIN 16
enum class DISTANCE {
    VERY_CLOSE,
    CLOSE,
    AWAY
} lastDeviceDistance;

const int RSSI_THRESHOLD_CLOSE  = -80;
const int RSSI_THRESHOLD_VERY_CLOSE = -55;

    WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

    void setup()
    {
        ws2812fx.init();
        ws2812fx.setBrightness(100);
        ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
        ws2812fx.setSpeed(10000);
        ws2812fx.start();
    }

    void loop(bool deviceIsClose, int rssi)
    {
        auto updateColor = [&]()
        {
            auto veryClose = [&]()
            {
                ws2812fx.init();
                ws2812fx.setBrightness(100);
                ws2812fx.setMode(FX_MODE_BLINK);
                ws2812fx.setSpeed(100);
                ws2812fx.setColor(255, 0, 255);
                ws2812fx.start();
            };

            auto close = [&]()
            {
                ws2812fx.init();
                ws2812fx.setBrightness(100);
                ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
                ws2812fx.setSpeed(7000);
                ws2812fx.start();
            };

            auto farAway = [&]()
            {
                ws2812fx.init();
                ws2812fx.setBrightness(100);
                ws2812fx.setMode(FX_MODE_STATIC);
                ws2812fx.setColor(255, 0, 0);
                ws2812fx.setSpeed(100);
                ws2812fx.start();
            };

            if (deviceIsClose)
            {
                if (rssi >= RSSI_THRESHOLD_VERY_CLOSE)
                {
                    if (lastDeviceDistance != DISTANCE::VERY_CLOSE)
                    {
                        veryClose();
                        lastDeviceDistance = DISTANCE::VERY_CLOSE;
                    }
                }
                else if (rssi < RSSI_THRESHOLD_VERY_CLOSE && rssi >= RSSI_THRESHOLD_CLOSE)
                {
                    if (lastDeviceDistance != DISTANCE::CLOSE)
                    {
                        close();
                        lastDeviceDistance = DISTANCE::CLOSE;
                    }
                }
                else
                {
                    if (lastDeviceDistance != DISTANCE::AWAY)
                    {
                        farAway();
                        lastDeviceDistance = DISTANCE::AWAY;
                    }
                }
            }
            else
            {
                if (lastDeviceDistance != DISTANCE::AWAY)
                    farAway();
                    lastDeviceDistance = DISTANCE::AWAY;
            }
        };

        updateColor();

        LED::ws2812fx.service();
    }
}
