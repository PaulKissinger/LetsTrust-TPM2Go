# LetsTrust-TPM2Go reset toggle

This folder contains the sources necessary to toggle the hardware reset line on a LetsTrust-TPM2Go USB-Stick.

Occasionally, it may be necessary to hardware reset a TPM.
LetsTrust-TPM2Go Reset, or LTT2G RST for short, will execute this reset pulse across the USB-SPI bridge using the libusb-1.0 library.


## 1.1 Prerequisistes

GCC, libusb-1.0, and a LetsTrust-TPM2Go are required to build the ltt2g rst.

This has not been tested, but LTT2G RST may run on many other little-endian hardware and software configurations capable of running Linux with the libusb-1.0.


## 1.2 Starting Out

LetsTrust-TPM2Go USB-Sticks are available for purchase at [buyzero.de Webshop] (www.buyzero.de).

Before you can execute LTT2G RST, you must compile it:
1. Navigate to the folder containing the LTT2G RST source code
2. Type the command below to compile the source code:
make

Remember that this tool works without root! Please use this resource as a guide or for testing.


# 2. Utilization of LTT2G RST

# 2.1 Generic usage

LTT2G RST operates as specified:

Call: './ltt2g_rst <option>'

For a summary of the available commands, run './ltt2g_rst -h' to obtain the help page.

option | explanation
------|--------
'-c' --cycle : cycle the reset line of the TPM
'-l' --level [option] : set the reset line of the TPM to high or low [\"high\",\"low\"]
'-h' --help : print this help


# 2.2 Example

- Send the command to cycle: './ltt2g_rst -c'

# 3 FAQ and troubleshooting

If you encounter any error, please make sure
- gcc and libusb-1.0 installed
- the LetsTrust-TPM2Go is recognised on demsg
  - dmesg

    [ 2023.051400] usb 3-2: new full-speed USB device number 5 using xhci_hcd
    [ 2023.051410] usb 3-2: New USB device found, idVendor=04b4, idProduct=0004, bcdDevice= 0.00
    [ 2023.051437] usb 3-2: New USB device strings: Mfr=1, Product=2, SerialNumber=3
    [ 2023.051459] usb 3-2: Product: LetsTrust-TPM2Go
    [ 2023.051478] usb 3-2: Manufacturer: www.pi3g.com
    [ 2023.051489] usb 3-2: SerialNumber: xxxxx
