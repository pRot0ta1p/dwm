/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Siji:pixelsize=16",
                                        "WenQuanYi Micro Hei Mono:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#282828";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#006AFF";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tile",      tile },    /* first entry is default */
	{ "Float",      NULL },    /* no layout function means floating behavior */
	{ "Monocle",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                    chain key   key        function        argument */
	{ MODKEY,                      -1,         XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,            -1,         XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                      -1,         XK_b,      togglebar,      {0} },
	{ MODKEY,                      -1,         XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                      -1,         XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                      -1,         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                      -1,         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                      -1,         XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                      -1,         XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY,                      -1,         XK_Return, zoom,           {0} },
	{ MODKEY,                      -1,         XK_Tab,    view,           {0} },
	{ MODKEY,                      -1,         XK_q,      killclient,     {0} },
	{ MODKEY,                      -1,         XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                      -1,         XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                      -1,         XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                      -1,         XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,            -1,         XK_space,  togglefloating, {0} },
	{ MODKEY,                      -1,         XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,            -1,         XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                      -1,         XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                      -1,         XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,            -1,         XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,            -1,         XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                       -1,         XK_1,                      0)
	TAGKEYS(                       -1,         XK_2,                      1)
	TAGKEYS(                       -1,         XK_3,                      2)
	TAGKEYS(                       -1,         XK_4,                      3)
	TAGKEYS(                       -1,         XK_5,                      4)
	TAGKEYS(                       -1,         XK_6,                      5)
	TAGKEYS(                       -1,         XK_7,                      6)
	TAGKEYS(                       -1,         XK_8,                      7)
	TAGKEYS(                       -1,         XK_9,                      8)
    { MODKEY|ShiftMask,            -1,         XK_r,      self_restart,   {0} },
	{ MODKEY|ShiftMask,            -1,         XK_e,      quit,           {0} },
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
