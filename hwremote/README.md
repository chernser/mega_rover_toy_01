Car Remote Hardware Implementation
==================================


Display Setup
-------------

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

