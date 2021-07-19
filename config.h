/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
        "tamzen:size=12",
    "newfire:size=12"
};
static const char dmenufont[]       = "EB Garamond:size=12";
static const unsigned int gappx     = 6;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char normbordercolor[] = "#000033";
static const char normbgcolor[]     = "#01010b";
static const char normfgcolor[]     = "#c04400";
static const char selbgcolor[]      = "#2a0001";
static const char selfgcolor[]      = "#fcffb6";
static const char selbordercolor[]  = "#000088";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = {normfgcolor,normbgcolor,normbordercolor  },
    [SchemeSel]  = {selfgcolor,selbgcolor,selbordercolor},
    [SchemeWarn] = {"#161813", normfgcolor, "#ff0000"},
    [SchemeUrgent] = {"#fdffac", selbgcolor, "#ff0000"},
};

/* False means using the scroll wheel on a window will not change focus */
static const Bool focusonwheelscroll = False;

/* tagging */
//static const char *tags[] = { "\ue1ec", "\ue26d", "3", "\ue072", "5", "6", "7", "\ue05c", "9" };
static const char *tags[] = {"1","2","3","4","5","6","7","8","9"};
static const char *occtag[] = {"\ue1ec"};

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating    isfloatsingle   monitor */
    {"Luakit",        NULL,       NULL,       1<<1,         0,           0,            -1 },
    {"MuPDF",         NULL,       NULL,       1<<3,         0,           0,            -1 },
    {"Opera",         NULL,       NULL,       1<<2,         0,           0,            -1 },
    {"st-256color",   NULL,       NULL,       1,            0,           1,            -1 },
    {"Claws-mail",    NULL,       NULL,       1<<4,         0,           0,            -1 },
    {"Spotify",       NULL,       NULL,       1<<7,         0,           0,            -1 },
    {"TelegramDesktop",NULL,      NULL,       1<<6,         0,           0,            -1 },
    {"mpv",           NULL,       NULL,       1<<8,         0,           0,            -1 },
    {"firefox",       NULL,       NULL,       1<<5,         0,           0,            -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *concertcmd[] = { "concertcmd", NULL };
static const char *mpctoggle[] = { "mpdcontrol", NULL };
static const char *spotifyplaypause[] = { "playerctl", "play-pause", NULL};
static const char *spotifynext[] = { "playerctl", "next", NULL};
static const char *spotifyprevious[] = { "playerctl", "previous", NULL};
static const char *windowshot[] = { "windowshot", NULL};
static const char *screenshot[] = { "screenshot", NULL};
static const char *opener[] = { "plumber", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_o,      spawn,          {.v = opener } },
    { MODKEY,                       XK_s,      spawn,          {.v = spotifyplaypause } },
    { MODKEY,                       XK_n,      spawn,          {.v = spotifynext } },
    { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = spotifyprevious } },
    { MODKEY,                       XK_c,      spawn,          {.v = concertcmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = mpctoggle } },
    { MODKEY,                       XK_w,      spawn,          {.v = windowshot } },
    { MODKEY|ShiftMask,             XK_w,      spawn,          {.v = screenshot } },
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

