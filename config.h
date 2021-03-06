/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx           = 5;        /* border pixel of windows */
static const unsigned int snap               = 32;       /* snap pixel */
static const unsigned int gappih             = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv             = 5;       /* vert inner gap between windows */
static const unsigned int gappoh             = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov             = 5;       /* vert outer gap between windows and screen edge */
static const unsigned int systraypinning     = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing     = 4;        /* systray spacing */
static const int topbar                      = 1;        /* 0 means bottom bar */
static const int showbar                     = 1;        /* 0 means no bar */
static const int user_bh                     = 26;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static       int smartgaps                   = 1;        /* 1 means no outer gap when there is only one window */
static const int showsystray                 = 1;        /* 0 means no systray */
static const int swallowfloating             = 0;        /* 1 means swallow floating windows by default */
static const int systraypinningfailfirst     = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const char *fonts[]                   = { "xos4 Terminus:size=14",
                                                 "Siji:pixelsize=16",
                                                 "WenQuanYi WenQuanYi Bitmap Song:size=14",
                                                 "monospace:size=14"};
static const char dmenufont[]                = "monospace:size=14";

/* colors */
static const char color0[]                   = "#0E2B41";
static const char color1[]                   = "#6F95C3";
static const char color2[]                   = "#78A7D3";
static const char color3[]                   = "#8DA3B4";
static const char color4[]                   = "#8DB4DE";
static const char color5[]                   = "#A8C3DF";
static const char color6[]                   = "#ADD0EC";
static const char color7[]                   = "#e2e8ef";
static const char color8[]                   = "#9ea2a7";
static const char color9[]                   = "#6F95C3";
static const char color10[]                  = "#78A7D3";
static const char color11[]                  = "#8DA3B4";
static const char color12[]                  = "#8DB4DE";
static const char color13[]                  = "#A8C3DF";
static const char color14[]                  = "#ADD0EC";
static const char color15[]                  = "#e2e8ef";
static const char colorgreen[]               = "#8ec07c";
static const char colormagenta[]             = "#d3869b";
static const char colorred[]                 = "#fb4934";
static const char coloryellow[]              = "#fabd2f";
static const char colorblue[]                = "#83a598";
static const char colorwhite[]               = "#ffffff";
static const char colorblack[]               = "#000000";

enum { SchemeNorm, SchemeSel, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeCol7, SchemeCol8 }; /* color schemes */

static const char *colors[][3]      = {
  /*               fg             bg               border */         /* dwmblocks colors code*/
    [SchemeNorm]  = { color7,       color0,        color0 },         /*  */
    [SchemeSel]   = { color0,       color2,        color6 },         /*  */
	[SchemeCol1]  = { color7,       colorgreen,    color8 },         /*  */
	[SchemeCol2]  = { color7,       colormagenta,  color8 },         /*  */
	[SchemeCol3]  = { color7,       colorred,      color8 },         /*  */
	[SchemeCol4]  = { color7,       coloryellow,   color8 },         /*  */
	[SchemeCol5]  = { color7,       colorblue,     color8 },         /*  */
	[SchemeCol6]  = { color0,       colorwhite,    color8 },         /*  */
	[SchemeCol7]  = { color7,       colorblack,    color8 },         /*  */
	[SchemeCol8]  = { color7,       color0,        color8 },         /*  */
};

/* scratchpads configs */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL , "-n", "spterm", "-g", "80x26", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance       title              tags mask      isfloating  isterminal  noswallow  monitor */
	{ "Gimp",      NULL,          NULL,              1 << 8,        0,          0,           0,        -1 },
	{ TERMCLASS,   NULL,          NULL,              0,             0,          1,           0,        -1 },
	{ NULL,        NULL,          "Event Tester",    0,             0,          0,           1,        -1 }, /* xev */
	{ NULL,		   "spterm",      NULL,		         SPTAG(0),	    1,          1,           0,        -1 }, /*scrath pad*/
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
/* MODKEY + NUM : View tag of NUM */
/* MODKEY + ControlMask + NUM : View current tag with toggleable selected tags */
/* MODKEY + ShiftMask + NUM : Send Selected window to tag NUM */
/* MODKEY + ControlMsk + ShiftMask + NUM : Let selected window be sticky in toggleable selected tags */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]                  = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]                   = { TERMINAL, NULL };

#include "selfrestart.c"
#include "shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                    chain key    key              function            argument */
	{ MODKEY,                      -1,         XK_r,             spawn,              {.v = dmenucmd } },
	{ MODKEY|ShiftMask,            -1,         XK_Return,        spawn,              {.v = termcmd } },
	{ MODKEY,                      -1,         XK_b,             togglebar,          {0} },
	{ MODKEY,                      -1,         XK_j,             focusstack,         {.i = +1 } },
	{ MODKEY,                      -1,         XK_k,             focusstack,         {.i = -1 } },
	{ MODKEY,                      -1,         XK_i,             incnmaster,         {.i = +1 } },
	{ MODKEY,                      -1,         XK_d,             incnmaster,         {.i = -1 } },
	{ MODKEY,                      -1,         XK_h,             setmfact,           {.f = -0.02} },
	{ MODKEY,                      -1,         XK_l,             setmfact,           {.f = +0.02} },
	{ MODKEY|ShiftMask,            -1,         XK_j,             setcfact,           {.f = +0.25} },
	{ MODKEY|ShiftMask,            -1,         XK_k,             setcfact,           {.f = -0.25} },
	{ MODKEY|ShiftMask,            -1,         XK_o,             setcfact,           {.f =  0.00} },
	{ MODKEY,                      -1,         XK_Return,        zoom,               {0} },
	{ MODKEY|Mod1Mask,             -1,         XK_j,             incrgaps,           {.i = +1 } },
	{ MODKEY|Mod1Mask,             -1,         XK_k,             incrgaps,           {.i = -1 } },
	{ MODKEY|Mod1Mask,             -1,         XK_t,             togglegaps,         {0} },
	{ MODKEY|Mod1Mask,             -1,         XK_0,             defaultgaps,        {0} },
	{ MODKEY,                      -1,         XK_Tab,           view,               {0} },
	{ MODKEY|ShiftMask,	           -1,         XK_Tab,           shiftview,          { .i = 1 } },
	{ MODKEY,                      -1,         XK_f,             focusmaster,        {0} },
	{ MODKEY,                      -1,         XK_q,             killclient,         {0} },
	{ MODKEY,                    XK_t,         XK_1,             setlayout,          {.v = &layouts[0]} },
	{ MODKEY,                    XK_t,         XK_2,             setlayout,          {.v = &layouts[1]} },
	{ MODKEY,                    XK_t,         XK_3,             setlayout,          {.v = &layouts[2]} },
	{ MODKEY,                    XK_t,         XK_4,             setlayout,          {.v = &layouts[3]} },
	{ MODKEY,                    XK_t,         XK_5,             setlayout,          {.v = &layouts[4]} },
	{ MODKEY,                    XK_t,         XK_6,             setlayout,          {.v = &layouts[5]} },
	{ MODKEY,                    XK_t,         XK_7,             setlayout,          {.v = &layouts[6]} },
	{ MODKEY,                    XK_t,         XK_8,             setlayout,          {.v = &layouts[7]} },
	{ MODKEY,                    XK_t,         XK_9,             setlayout,          {.v = &layouts[8]} },
	{ MODKEY,                    XK_t,         XK_0,             setlayout,          {.v = &layouts[9]} },
	{ MODKEY,                    XK_t,         XK_a,             setlayout,          {.v = &layouts[10]} },
	{ MODKEY,                    XK_t,         XK_s,             setlayout,          {.v = &layouts[11]} },
	{ MODKEY,                    XK_t,         XK_d,             setlayout,          {.v = &layouts[12]} },
	{ MODKEY|ShiftMask,            -1,         XK_f,             togglefullscr,      {0} },
	{ MODKEY|ShiftMask,            -1,         XK_space,         togglefloating,     {0} },
	{ MODKEY,                      -1,         XK_0,             view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,            -1,         XK_0,             tag,                {.ui = ~0 } },
	{ MODKEY,                      -1,         XK_comma,         focusmon,           {.i = -1 } },
	{ MODKEY,                      -1,         XK_period,        focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,            -1,         XK_comma,         tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,            -1,         XK_period,        tagmon,             {.i = +1 } },
	{ MODKEY,                      -1, 		   XK_u,             togglescratch,      {.ui = 0 } },
	TAGKEYS(                       -1,         XK_1,                         0)
	TAGKEYS(                       -1,         XK_2,                         1)
	TAGKEYS(                       -1,         XK_3,                         2)
	TAGKEYS(                       -1,         XK_4,                         3)
	TAGKEYS(                       -1,         XK_5,                         4)
	TAGKEYS(                       -1,         XK_6,                         5)
	TAGKEYS(                       -1,         XK_7,                         6)
	TAGKEYS(                       -1,         XK_8,                         7)
	TAGKEYS(                       -1,         XK_9,                         8)
    { MODKEY|ShiftMask,            -1,         XK_r,             self_restart,       {0} },
	{ MODKEY|ShiftMask,            -1,         XK_e,             quit,               {0} },
	/* 3rd-party app key bindings */
	{ 0,                           -1, XF86XK_AudioLowerVolume,  spawn,              SHCMD("SoundControl -d 10") },
	{ 0,                           -1, XF86XK_AudioRaiseVolume,  spawn,              SHCMD("SoundControl -i 10") },
	{ 0,                           -1, XF86XK_AudioMute,         spawn,              SHCMD("SoundControl -m") },
	{ 0,                           -1, XF86XK_MonBrightnessUp,   spawn,              SHCMD("light -A 5") },
	{ 0,                           -1, XF86XK_MonBrightnessDown, spawn,              SHCMD("light -U 5") },
	{ MODKEY,                    XK_x,         XK_b,             spawn,              SHCMD("$BROWSER") },
	{ MODKEY,                    XK_x,         XK_e,             spawn,              SHCMD("emacsclient -c -a emacs") },
	{ MODKEY|ShiftMask,            -1,         XK_l,             spawn,              SHCMD("i3lock-blur") },
	{ MODKEY,                      -1,         XK_p,             spawn,              SHCMD("touchpad-toggle") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
 	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
 	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
 	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
