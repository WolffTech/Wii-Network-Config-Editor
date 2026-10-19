# Wii-Network-Config-Editor
This Wii homebrew program allows you to change your Wifi Settings without going to the Wii Menu. Especially useful for portable consoles that haven't got a bluetooth module.

WARNING : This program makes permanent changes to the NAND, use (and/or modify) at your own risks.
Please make a NAND Backup before using my program, just in case.

## What is this program and what it does:

This program is a Wifi settings editor designed especially for Portable Wiis that cannot access the Wii menu to change Network settings.

However it works fine with normal Wii's also (if you are too lazy to go to the wii menu or you can't access it for some reason).

This program changes the Network type(Wireless/Wired), SSID, Password, and security type of the first network, in the configuration file named "config.dat" located at /shared2/sys/net/02/config.dat on the NAND.


## Installing on a Wii that already has homebrew

These steps assume the Homebrew Channel is already installed.

1. Make a NAND backup first (for example with BootMii) if you don't have one.
2. On your SD card or USB drive, create the folder `apps/WiiNetworkConfigEditor/`.
3. Copy `BOOT.dol` from this repository into that folder and rename it to `boot.dol`, so the path is `apps/WiiNetworkConfigEditor/boot.dol`.
4. Put the card or drive back in the Wii, open the Homebrew Channel, and launch the app.

You can also send it over the network without copying anything: open the Homebrew Channel on the Wii, then from your computer run `wiiload BOOT.dol` with the `WIILOAD` environment variable set to `tcp:<your Wii's IP address>`.

## Controls

- Point at a button and press A to select it. Without a sensor bar, use the D-pad to move between buttons and keys, then press A.
- B erases the last character on the keyboards and goes back from the Credits and Connection Test screens.
- HOME saves your changes (from the main menu and the keyboards).
- A GameCube controller works too: the D-pad and A/B work the same, and START replaces HOME.
