#include <canbus.h>
#include <PWMHandler.h>
#include <Temperature.h>
#include <Current.h>
#include <Voltage.h>
#include <RelayHandler.h>

CANBUS can;
Currents currents;
Temperatures temperatures;
Voltages voltages;
RelayHandler relay;
PWMHandler pwm;

void setup() {

  can.setupCAN();
}

void loop() {
  uint16_t dataToSend[] = { 1 };
  int dataLength = sizeof(dataToSend) / sizeof(dataToSend[0]);
  can.sendMessage(0x21, dataToSend, dataLength);
  delay(2000);

  float temperature = temperatures.getTemperatures();
  if (temperature) {
    // DO SOMETHING
  }

  float voltage = voltages.getVoltage(voltages.PIN_24V, voltages.RATIO_24V);
  if (voltage) {
    // DO SOMETHING
  }

  currents.readVoltages();
  currents.toCurrents();
  // DO SOMETHING WITH THE ARRAY OF CURRENTS


  bool stateFromCan = 0;
  relay.setRelayState(stateFromCan, relay.PIN10);


  float dutyCyclesFromCAN[] = { 10.0f, 90.0f, 40.0f, 60.0f };
  float frequenciesFromCAN[] = { 100.0f, 200.0f, 50.0f, 75.0f };
  pwm.sendPWMSignal(dutyCyclesFromCAN, frequenciesFromCAN);
}
