// in Adafruit_TinyUSB.h we need to include these for the noteButtonAgent:
//     #include "arduino/ports/esp32/tusb_config_esp32.h"
//     #include "arduino/midi/Adafruit_USBD_MIDI.h"
#include <gmock/gmock.h>
#include <ArduinoFake.h>
#include "iButton.h"
#include "inputListner.h"
#include "midiStompTypes.h"

using namespace fakeit;

using ::testing::Return;

class MockButton : public iButton {
public:
    MOCK_METHOD(int, readState, (), (override));
    MOCK_METHOD(bool , isPullUp, (), (override));
};

class MockAgent : public iButtonAgent {
public:
    MockButton mockButton;
    MockAgent() : iButtonAgent(mockButton) {}
    MOCK_METHOD(buttonState, getButtonState, (), (override));
    MOCK_METHOD(bool , isDown, (), (override));
    MOCK_METHOD(int , onPress, (), (override));
    MOCK_METHOD(int , onRelease, (), (override));
};


TEST(listner, canActOnInput) {
    MockAgent mockAgent1;
    MockAgent mockAgent2;
    iButtonAgent* agents[2];
    agents[0] = &mockAgent1;
    agents[1] = &mockAgent2;
    inputListner testObject = inputListner(agents, 2);


    EXPECT_CALL(mockAgent1, getButtonState)
            .WillOnce(Return(UP))
            .WillOnce(Return(UP))
            .WillOnce(Return(UP))
            .WillOnce(Return(UP));

    EXPECT_CALL(mockAgent2, getButtonState)
            .WillOnce(Return(UP))
            .WillOnce(Return(UP))
            .WillOnce(Return(UP))
            .WillOnce(Return(UP));

    EXPECT_FALSE(testObject.actOnInput()); // 1 is switched
    EXPECT_FALSE(testObject.actOnInput()); // none are switched
    EXPECT_FALSE(testObject.actOnInput()); // 2 is switched
    EXPECT_FALSE(testObject.actOnInput()); // both are switched
}


#if defined(ARDUINO)

#include <Arduino.h>

void setup() {
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    ::testing::InitGoogleMock();
//    ::testing::InitGoogleTest();
}

void loop() {
    // Run tests
    if (RUN_ALL_TESTS());

    // sleep 1 sec
    delay(1000);
}

#else
int main(int argc, char **argv)
{
//    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    if (RUN_ALL_TESTS())
        ;
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
#endif
