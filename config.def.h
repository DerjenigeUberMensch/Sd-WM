/* See LICENSE file for copyright and license details.
 * 4 Tab spaces; No tab characters use spaces for tabs
 * Basic overview of dwm => https://ratfactor.com/dwm
 * For more information about xlib (X11)       visit https://x.org/releases/current/doc/libX11/libX11/libX11.html
 * For a quick peak at commonly used functions visit https://tronche.com/gui/x/xlib/ 
 * For broad information about xlib (X11) visit {
 * List of utils: https://www.freedesktop.org/wiki/Specifications/
 * }
 */
/* window */
#define CFG_BORDER_PX           0       /* border pixel of windows                                          */
#define CFG_TOP_BAR             0       /* 1 show bar on top; 0 for bottom bar                              */
#define CFG_SNAP                15      /* snap window to border in pixels; 0 to disable (NOT RECOMMENDED)  */
#define CFG_WIN_RATE            120     /* max refresh rate when resizing, moving windows;  0 to disable    */
#define CFG_SHOW_WM_NAME        0       /* 1 Show window manager name at end of status bar; 0 to disable    */
#define CFG_HOVER_FOCUS         0       /* 1 on mouse hover focus that window; 0 to disable                 */
#define CFG_BAR_PADDING         0       /* padding in pixels (both sides)                                   */
#define CFG_SHOW_BAR            1       /* 1 to show bar; 0 to disable                                      */
#define CFG_ICON_SIZE           16      /* icon size                                                        */
#define CFG_ICON_SPACE          2       /* space between icon and title                                     */
#define CFG_RESIZE_BASE_WIDTH   150     /* Minimum size for resizing windows, recommend size 50-150         */
#define CFG_RESIZE_BASE_HEIGHT  150     /* Minimum size for resizing windows, recommend size 50-150         */

/* alt-tab configuration */
#define CFG_ALT_TAB_SWITCH_KEY  0x40    /* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `                                          */
#define CFG_ALT_TAB_CYCLE_KEY   0x17    /* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart                    */
#define CFG_ALT_TAB_POS_X           1       /* tab position on X axis, 0 = left, 1 = center, 2 = right          */
#define CFG_ALT_TAB_POS_Y           1       /* tab position on Y axis, 0 = bottom, 1 = center, 2 = top          */
#define CFG_ALT_TAB_TEXT_POS_X      1       /* tab position on x axis, 0 = left , 1 = center, 2 = right         */
#define CFG_ALT_TAB_MAX_WIDTH       600     /* MAX tab menu width                                               */
#define CFG_ALT_TAB_MAX_HEIGHT      200     /* MAX tab menu height                                              */
#define CFG_ALT_TAB_MIN_WIDTH       0       /* Add padding if text length is shorter; 0 to disable              */
#define CFG_ALT_TAB_MAP_WINDOWS     1       /* 1 compositor fadding when switching tabs; 0 to disable           */
#define CFG_ALT_TAB_SHOW_PREVIEW    1       /* shows window preview when alt tabbing                            */
#define CFG_ALT_TAB_FIXED_TILE      0       /* 1 alttab only changes focused window; 0 to disable               */
/* Misc */
#define CFG_MONITOR_FACT            0.55    /* factor of master area size [0.05..0.95]                          */
#define CFG_MAX_CLIENT_COUNT        256     /* max number of clients assuming you can handle this many          */
#define CFG_MASTER_COUNT            1       /* number of clients in master area                                 */
#define CFG_RESIZE_HINTS            1       /* 1 means respect size hints in tiled resizals                     */
#define CFG_LOCK_FULLSCREEN         1       /* 1 will force focus on the fullscreen window                      */
#define CFG_DECOR_HINTS             1       /* 1 Dont ignore Decoration Hints made by windows; 0 to disable     */
#define WM_NAME                     "dwm.exe" /* wm name displayed when using X (type neofetch to see this) */
/* dmenu */
#define CFG_DMENU_TOP_BAR           0       /* 1 show dmenu bar on top; 0 for bottom bar                        */
#define CFG_DMENU_FAST_INPUT        0       /* 1 prioritize input over bar render; 0 to disable                 */
#define CFG_DMENU_CASE_SENSITIVE    1       /* 1 dmenu searches case senstivly; 0 to disable                    */
/* dmenu colours */
#define CFG_DMENU_COL_NORM_BACKGROUND       "#000000" /* dmenu background colour for NON selected items */
#define CFG_DMENU_COL_NORM_FOREGROUND       "#ffffff" /* dmenu text colour for NON selected items       */
#define CFG_DMENU_COL_SEL_BACKGROUND        "#000000" /* dmenu background colour for SELECTED items     */
#define CFG_DMENU_COL_SEL_FOREGROUND        "#ffffff" /* dmenu text colour for SELECTED items           */

static const char *fonts[]      =   {"monospace:size=12" };
static const char dmenufont[]   =   {"monospace:size=12"};


/* COLOURS */
#define COL_BLACK       "#000000"
#define COL_WHITE       "#ffffff"
#define COL_GREY        "#C0C0C0"
#define COL_RED         "#ff0000"
#define COL_PINK        "#FF00FF"
#define COL_BLUE        "#0000FF"
#define COL_YELLOW      "#FFFF00"

/* static char col_term_blue[]   = "#ecffff"; */
static char *colors[][3] = 
{
    /*					        fg         bg          border   */
    [SchemeNorm]            = { COL_WHITE, COL_BLACK, COL_WHITE},
    [SchemeSel]             = { COL_WHITE, COL_BLACK, COL_WHITE},
    [SchemeUrgent]          = { COL_BLUE,  COL_RED,   COL_BLUE},
    [SchemeWarn]            = { COL_WHITE, COL_YELLOW, COL_WHITE},

    [SchemeAltTab]          = { COL_WHITE, COL_BLACK, COL_BLACK},
    [SchemeAltTabSelect]    = { COL_BLACK, COL_WHITE, COL_WHITE},

    [SchemeBarTabActive]    = { COL_BLACK, COL_WHITE, COL_WHITE},
    [SchemeBarTabInactive]  = { COL_WHITE, COL_BLACK, COL_BLACK},
    [SchemeTagActive]       = { COL_BLACK, COL_WHITE, COL_WHITE},

};
/* appearance */
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsel[][2] = {
    /* fg       bg */
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
    {COL_WHITE, COL_BLACK},
};
static const Rule rules[] = 
{
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */

static const Layout layouts[] = 
{
    /* symbol     arrange function */
    { "[T]",      tile },    /* first entry is default */
    { "[F]",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[G]",      grid },

};

/* NOTES:
 * For uncapped resizing of windows (NOT ADVICED) you can go to toggle.c -> resizemouse() and simply set basew and baseh to 0 
 *
 */

