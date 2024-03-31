# PLC Introduction For Arduino Friends

Examples, and slides for my talk given at the Santa Barbara hackerspace 3/28/2024.

Livestream talk recording is on youtube https://www.youtube.com/watch?v=k32zjzcFPZ0

Slides are in [2024 PLC intro from Arduino background - Nick Winters.pdf](<2024 PLC intro from Arduino background - Nick Winters.pdf>)

## Example Programs
1. [NucleoBlink](NucleoBlink/NucleoBlink.ino): Arduino IDE blink example
2. [NucleoHello](NucleoHello/NucleoHello.ino): Arduino IDE example with button input, LED output, and an incrementing counter printed to serial.
3. [NucleoQwiicCombined](NucleoQwiicCombined/NucleoQwiicCombined.ino): Arduino IDE example combining two I2C devices: An oled display and ambient light sensor.
4. [ClickHello](ClickHello.ckp) - Read inputs and copy them to outputs
5. [ClickStartStop](ClickStartStop.ckp) - Logic example for start and stop buttons to turn on and off the first output.
6. [ClickExampleWithBlink](ClickExampleWithBlink.ckp) - Use inverted contact and turn on and turn off timers to blink lamp.
7. [OptaArduinoTestInputs](OptaArduinoTestInputs/OptaArduinoTestInputs.ino) - Arduino IDE example to read the analog inputs on Opta and print them to serial.
8. [OptaArduinoTestOutputs](OptaArduinoTestOutputs/OptaArduinoTestOutputs.ino) - Arduino IDE example to turn on each of the relay outputs on opta one at a time.
9. OptaPlcLadderStartStop
10. OptaPlcLadderBlink
11. OptaPlcStStartStop
12. OptaPlcModbusTcpServer
13. OptaPlcFunctionBlockSubprocedureBlink
14. [MegaEthernetModbusServerDangerShield](MegaEthernetModbusServerDangerShield/MegaEthernetModbusServerDangerShield.ino) - Arduino IDE example of Modbus TCP combined with sparkfun danger shield analog inputs, 7-segment and LED outputs.
15. [ClickStartStopModbusClient](ClickStartStop-ModbusClient.ckp) - Modbus client to read and write to MegaEthernetModbusServerDangerShield. This needed some extra logic to wait for the Arduino.
