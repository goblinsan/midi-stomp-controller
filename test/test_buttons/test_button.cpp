#include <gtest/gtest.h>
#include "button.cpp"
#include "muxButton.cpp"
#include <ArduinoFake.h>

using namespace fakeit;

TEST(readButton, nonMuxRead) {
    int8_t testPin = 4;
    int randoNumber = 42;
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();

    button b(testPin);

    When(Method(ArduinoFake(), digitalRead).Using(testPin)).Return(randoNumber);

    EXPECT_EQ(randoNumber, b.readState());
}

TEST(readButton, pullUp) {
    int8_t testPin = 4;
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();

    button b(testPin);
    EXPECT_TRUE(b.isPullUp());

    button b_notPullUp(testPin, false);
    EXPECT_FALSE(b_notPullUp.isPullUp());
}

TEST(mux, bitShiftyReadings) {
    const int sp[4] = {3, 4, 5, 6};
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();

    muxButton mb(0, 2, sp);
    muxButton mb2(10, 2, sp);

    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead).Using(2)).Return(7);

    EXPECT_EQ(7, mb.readState());

    Verify(Method(ArduinoFake(), digitalWrite).Using(3, 0)).Exactly(2);
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, 0)).Exactly(2);
    Verify(Method(ArduinoFake(), digitalWrite).Using(5, 0)).Exactly(2);
    Verify(Method(ArduinoFake(), digitalWrite).Using(6, 0)).Exactly(2);

    ArduinoFake().ClearInvocationHistory();

    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead).Using(2)).Return(7);

    mb2.readState();

    Verify(Method(ArduinoFake(), digitalWrite).Using(3, 0)).Exactly(2);
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, 0)).Exactly(1); // init
    Verify(Method(ArduinoFake(), digitalWrite).Using(4, 1)).Exactly(1);
    Verify(Method(ArduinoFake(), digitalWrite).Using(5, 0)).Exactly(2);
    Verify(Method(ArduinoFake(), digitalWrite).Using(6, 0)).Exactly(1); // init
    Verify(Method(ArduinoFake(), digitalWrite).Using(6, 1)).Exactly(1);

}

#if defined(ARDUINO)

#include <Arduino.h>

void setup() {
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    ::testing::InitGoogleTest();
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
    ::testing::InitGoogleTest(&argc, argv);
    if (RUN_ALL_TESTS())
    ;
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
#endif