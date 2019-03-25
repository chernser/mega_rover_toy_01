Car Remote Hardware Implementation
==================================


The HAT used for project - [link](www.waveshare.com/wiki/1.44inch_LCD_HAT)

Display Setup
-------------

This config is true for 3 button/1 joystick/display HAT.
Display has 128x128 resolutions. 
It is needed, because car is extandable and more moving parts will need to be controlled. 

Linux Kernel modules:
    *   fbtft
    *   fbtft_device 

Configuration files: 

    /etc/modprobe.d/fbtft.conf
    ```
    options fbtft_device name=adafruit18_green gpios=reset:27,dc:25,cs:8,led:24 speed=40000000 bgr=1 fps=60 custom=1 height=128 width=128 rotate=90
    ```

    /etc/modules-load.d/fbtft.conf
    ```
    spi_bcm2835
    fbtft_device
    ```

    at the end of /boot/cmdline
    ```
    ...  fbcon=map:10
    ```

BLE Programming
---------------

[Python lib](https://github.com/IanHarvey/bluepy)


Buttons Setup
-------------

Buttons on the HAT are using GPIO.
