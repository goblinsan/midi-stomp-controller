//#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "buttonAgent.cpp"
#include "iButton.h"

#include <ArduinoFake.h>

using namespace fakeit;

using ::testing::Return;

class MockButton : public iButton {
public:
    MOCK_METHOD(int, readState, (), (override));
    MOCK_METHOD(bool, isPullUp, (), (override));
};


TEST(agent, canMakeAgentWithButton) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isPullUp()).WillOnce(Return(true));
    EXPECT_NO_THROW(buttonAgent ba(mockButton));
}

TEST(agent, getButtonState_default) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isPullUp()).WillOnce(Return(true));

    buttonAgent ba(mockButton);

    // Default case with no read
    EXPECT_EQ(0, ba.getLastReadingTime());
    EXPECT_FALSE(ba.isDown());
    bool stChange = ba.stateChange();
    bool readDeEx = ba.readDelayExpired();
    EXPECT_FALSE(stChange);
    EXPECT_FALSE(readDeEx);
    EXPECT_FALSE(ba.isSwitched(stChange, readDeEx));
}

TEST(agent, getButtonState_pressed) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isPullUp()).WillOnce(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState()).WillOnce(Return(LOW));
    When(Method(ArduinoFake(Function), millis)).Return(55);

    // HIGH -> LOW after 55 millis
    EXPECT_EQ(PRESSED, ba.getButtonState());
}

TEST(agent, getButtonState_held) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isPullUp()).WillOnce(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW))
            .WillOnce(Return(LOW));
    When(Method(ArduinoFake(Function), millis)).Return(55, 60);

    // grab button press with first mock returns
    ba.getButtonState();
    // STILL LOW after 5 millis
    EXPECT_EQ(HELD, ba.getButtonState());
}

TEST(agent, getButtonState_released) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isPullUp()).WillOnce(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW))
            .WillOnce(Return(HIGH));
    When(Method(ArduinoFake(Function), millis)).Return(55, 200);

    // grab button press with first mock returns
    ba.getButtonState();
    // LOW -> HIGH after 145 millis
    EXPECT_EQ(RELEASED, ba.getButtonState());
}

TEST(agent, getButtonState_up) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isPullUp()).WillOnce(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW))
            .WillOnce(Return(HIGH))
            .WillOnce(Return(HIGH));
    When(Method(ArduinoFake(Function), millis)).Return(55, 200, 205);

    // grab button press with first mock returns
    ba.getButtonState();
    // grab button release with second mock returns
    ba.getButtonState();
    // STILL HIGH after 5 millis
    EXPECT_EQ(UP, ba.getButtonState());
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

int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    if (RUN_ALL_TESTS());
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}

#endif
