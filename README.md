# LetsTrust-TPM2Go
Things associated with the LetsTrust-TPM2Go USB-Stick


1. Microsoft Windows 11 disclaimer

A LetsTrust-TPM2Go USB Stick is NOT compatible with Microsoft Windows 11 TPM 2.0 requirement!

# LetsTrust-TPM2Go reset cycler

This subfolder contains the source code required to reset the LetsTrust-TPM2Go.

# Installation of the TPM Software Stack for the LetsTrust-TPM2Go

You'll find a script for LetsTrust-TPM and LetsTrust-TPM2Go here:
https://github.com/PaulKissinger/LetsTrust
This will install all dependencies for the tss, the tpm2-abrmd and also the tpm2-tools. The tcti device for the LetsTrust-TPM2Go is included in in the tss.

# How to use the LetsTrust-TPM2Go

The markdown file is a short guide how to use:
https://github.com/tpm2-software/tpm2-tss/blob/master/doc/tcti-spi-ltt2go.md


# LetsTrust-TPM2Go in WSL2

There is a possability to use basic function in the WSL2 under Windows 10 (WSL2 under Windows 11 was not testet yet):

This guide explains how to hand over a USB device into the WSL2:
https://devblogs.microsoft.com/commandline/connecting-usb-devices-to-wsl/

This is functional for the LetsTrust-TPM2Go!

