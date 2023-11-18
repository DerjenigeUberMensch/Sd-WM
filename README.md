# dwm

> _"dwm is an extremely fast, small, and dynamic window manager for X."_

**_Not for long._**

## Patches applied:

1.  **Actual fullscreen**
2.  **Alt Tab**
3.  **maximize**
4.  **refreshrate**
5.  **noborderflicker**
6.  resize anywhere
7.  Alt-Tab minimal

## Preview:

![alttab](/cool_images/alt_tab.png "AltTab.")

## Requirements
1. pactl
2. playerctl
3. brightnessctl
4. dmenu
5. st
6. scrot   
7. x11 (xlib)

You can download these via your package manager
**Pacman && yay **
```
sudo pacman -S --needed libpulse playerctl brightnessctl dmenu scrot libx11 && yay -S st
```

## Usage 
To **use** Sd-WM you must first **compile it**.
Afterwards you must put `exec dwm` in your `~/.xinitrc` file. **See Below.**


## Compiling
1. Clone this repository: 
https://github.com/DerjenigeUberMensch/Sd-WM.git
2. `cd Sd-WM` into the repository
3. Configure it See **Configuration** (Optional)
4. `sudo make clean install` to compiled
5. Ignore any warnings (compiled with O0)
5. Enjoy!

*-O1+ compilation not fully supported.*

## Configuration
To **configure** Sd-WM head on over to `config.def.h` and change the variables there to fit your needs.
If you feel like **patching** Sd-WM **yourself** you may do so and find **documentation** **[here](https://dwm.suckless.org/customisation/)**. 
Once you **finish** `rm config.h` if it exists and **recompile.**

## Troubleshoot
This is an **_experimental_** build and may contain bugs, 

It is recommened to have vsync enabled in your compositor or driver settings as to remove tearing issues.
