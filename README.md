# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X ([suckless.org](https://dwm.suckless.org/)).


# This build

Based on version 6.2.

Patches:

* [alpha](https://dwm.suckless.org/patches/alpha/): allows dwm to have translucent bars, while keeping all the text on it opaque.
* [extrabar](https://dwm.suckless.org/patches/extrabar/): enables an extra status bar in dwm, allowing more status modules (see my [dwmblocks build](https://github.com/ygregw/dwmblocks)).
* [swallow](https://dwm.suckless.org/patches/swallow/): adds window swallowing, avoiding cluttering the screen with unusable terminals.
* [xresources](https://dwm.suckless.org/patches/xresources/): lets Xresources handle color, opacity, etc.

# Installation

```
make
sudo make install
```

