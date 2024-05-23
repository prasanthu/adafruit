# SPDX-FileCopyrightText: 2021 John Furcean
# SPDX-License-Identifier: MIT

"""I2C rotary encoder simple test example."""

import board
import busio
from adafruit_seesaw import seesaw, rotaryio, digitalio

dir(board)

# i2c = busio.I2C(board.SCL, board.SDA, frequency=1000)

# scan = i2c.scan()
# print(scan)
# for addr in scan:
#     print("Address = {0:3d}, Hex = {1}".format(addr, hex(addr)))

# seesaw = seesaw.Seesaw(i2c, addr=0x36, drdy=None, reset=True)
# exit()

# For use with the STEMMA connector on QT Py RP2040

i2c = board.I2C()  # uses board.SCL and board.SDA
# seesaw = seesaw.Seesaw(i2c, addr=0x36)
seesaw = seesaw.Seesaw(i2c, addr=0x36, drdy=None, reset=True)

seesaw_product = (seesaw.get_version() >> 16) & 0xFFFF
print("Found product {}".format(seesaw_product))
if seesaw_product != 4991:
    print("Wrong firmware loaded?  Expected 4991")

# Configure seesaw pin used to read knob button presses
# The internal pull up is enabled to prevent floating input
seesaw.pin_mode(24, seesaw.INPUT_PULLUP)
button = digitalio.DigitalIO(seesaw, 24)

button_held = False

encoder = rotaryio.IncrementalEncoder(seesaw)
last_position = None

while True:
    # negate the position to make clockwise rotation positive
    position = -encoder.position

    if position != last_position:
        last_position = position
        print("Position: {}".format(position))

    if not button.value and not button_held:
        button_held = True
        print("Button pressed")

    if button.value and button_held:
        button_held = False
        print("Button released")
