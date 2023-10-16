//#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "buttonAgent.h"
#include "iButton.h"

using ::testing::Return;

class MockButton : public iButton {
public:
    MOCK_METHOD(int, readState, (), (override));
    MOCK_METHOD(bool, isSwitched, (), (override));
    MOCK_METHOD(bool, isDown, (), (override));
};

TEST(agent, canMakeAgentWithButton) {
    MockButton mockButton;
    EXPECT_NO_THROW(buttonAgent ba(mockButton));
}

TEST(agent, doOnPress) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isSwitched())
            .WillOnce(Return(true));
    EXPECT_CALL(mockButton, isDown())
            .WillOnce(Return(true));
    buttonAgent ba(mockButton);
    EXPECT_EQ(0, ba.onPress());
}

TEST(agent, doOnRelease) {
    MockButton mockButton;
    EXPECT_CALL(mockButton, isSwitched())
            .WillOnce(Return(true));
    EXPECT_CALL(mockButton, isDown())
            .WillOnce(Return(false));
    buttonAgent ba(mockButton);
    EXPECT_EQ(0, ba.onRelease());
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
