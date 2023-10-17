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
    MOCK_METHOD(bool , isPullUp, (), (override));
};


TEST(agent, canMakeAgentWithButton) {
    MockButton mockButton;
    EXPECT_NO_THROW(buttonAgent ba(mockButton));
}

TEST(agent, isSwitched) {
    MockButton mockButton;
    ON_CALL(mockButton, isPullUp()).WillByDefault(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW))
            .WillOnce(Return(HIGH))
            .WillOnce(Return(LOW));

    When(Method(ArduinoFake(Function), millis)).Return(55, 120, 122);

    EXPECT_TRUE(ba.isSwitched());
    EXPECT_TRUE(ba.isSwitched());
    GTEST_EXPECT_FALSE(ba.isSwitched());
}

TEST(agent, isDown) {
    MockButton mockButton;
    ON_CALL(mockButton, isPullUp()).WillByDefault(Return(true));

    buttonAgent ba(mockButton);

    GTEST_EXPECT_FALSE(ba.isDown());

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW));
    When(Method(ArduinoFake(Function), millis)).Return(55);

    EXPECT_TRUE(ba.isSwitched());

    EXPECT_TRUE(ba.isDown());

}

TEST(agent, doOnPress) {
    MockButton mockButton;
    ON_CALL(mockButton, isPullUp()).WillByDefault(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW));
    When(Method(ArduinoFake(Function), millis)).Return(55);

    EXPECT_TRUE(ba.onPress());
}

TEST(agent, doOnRelease) {
    MockButton mockButton;
    ON_CALL(mockButton, isPullUp()).WillByDefault(Return(true));

    buttonAgent ba(mockButton);

    EXPECT_CALL(mockButton, readState())
            .WillOnce(Return(LOW))
            .WillOnce(Return(HIGH));
    When(Method(ArduinoFake(Function), millis)).Return(55, 155);
    ba.isSwitched();

    EXPECT_TRUE(ba.onRelease());
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
