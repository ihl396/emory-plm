# boot.py -- run on boot-up
# can run arbitrary Python, but best to keep it minimal

import machine
import pyb
#pyb.main('main.py') # main script to run after this one
pyb.usb_mode('CDC+MSC') # act as a serial and a storage device
#pyb.usb_mode('CDC+HID') # act as a serial device and a mouse
pyb.freq(4000000) #Set frequency as the lowest possible card while SD card writing.
