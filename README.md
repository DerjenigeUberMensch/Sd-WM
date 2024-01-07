# dwm

> _"dwm is an extremely fast, small, and dynamic window manager for X."_

**_Not for long._**

## Patches applied:

- **Actual fullscreen**
- **Alt-Tab**
- **maximize**
- **refreshrate**
- **noborderflicker**
- **activetagindicatorbar**
- **activemonitor**
- **stacker**
- **grid**
- **winicon**
- **restartsig**
- **restoreafterrestart**
- **windowmap**
- **rainbowtags**
- **updatemotifhints**
- **ewmhtags**

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
8. xorg
9. xorg-xinit
10. libxcursor
11. 8MiB <~> 15MiB + (xorg RAM) depending on your system this number may vary though legacy systems may use less RAM

**Pacman && yay**
```
sudo pacman -S --needed libpulse playerctl brightnessctl dmenu scrot libx11 xorg xorg-xinit imlib2 libxcursor && yay -S st
```

## Usage 
To **use** Sd-WM you must first **compile it**.
Afterwards you must put `exec dwm` in your `~/.xinitrc` file. **See Below.**


## Compiling
1. Clone this repository: 
https://github.com/DerjenigeUberMensch/Sd-WM.git
2. ```cd Sd-WM``` into the repository
3. ```git checkout origin/Experimental```
3. Configure it See **Configuration** (Optional)
4. `sudo make install` to compile or 'make' to compile but not install on system
5. Done.

## Configuration
To **configure** Sd-WM head on over to `config.def.h` and change the variables there to fit your needs.
If you feel like **patching** Sd-WM **yourself** you may do so and find **documentation** **[here](https://dwm.suckless.org/customisation/)**. 
Once you **finish** `rm config.h` if it exists and **recompile.**

## Troubleshoot
This is an **_experimental_** build and may contain bugs,
Screen tearing can be mitigated by using a compositor or by enabling it in your driver setting
HOWEVER do note that using a compositor may reduce performance when having a large amounts of windows open +50

If you have any **major** **issues** with a **current** commit you can **revert** to a **previous commit** for a generally stabler version.
Or you can open an **[issue](https://github.com/DerjenigeUberMensch/Sd-WM/issues)** about it.
