dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

Requirements
------------
In order to build dwm you need the Xlib header files.

```bash
sudo apt install build-essential libx11-dev libxft-dev libxinerama-dev libfreetype6-dev libfontconfig1-dev
```

Installation
------------
Edit `config.mk` to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

Running dwm
-----------
Add the dwm as `.desktop` format.

Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

Patches
-------
I have applied the following patches found in [dwm](https://dwm.suckless.org/)

- dwm-actualfullscreen-20191112-cb3f58a.diff
- dwm-alwayscenter-20200625-f04cac6.diff
- dwm-combo-6.1.diff
- dwm-switchtotag-6.2.diff
- dwm-uselessgap-20211119-58414bee958f2.diff
- dwm-warp-6.4.diff

Recommendations
------------
- `dmenu` for application menu.
- `slstatus` for status bar.
- `slock` for lockscreen.
- checkout [font awesome](https://fontawesome.com/v4/cheatsheet/) for icons in status bar, tags...

Last updated: Feb 22, 2024
