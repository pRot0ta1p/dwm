/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
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
	[SchemeNorm]  = { col_gray3, col_gray1, col_gray2 },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance       title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,          NULL,              0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,          NULL,              1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,          NULL,              0,         0,          1,           0,        -1 },
	{ NULL,      NULL,          "Event Tester",    0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,		 "spterm",		NULL,		     SPTAG(0),	  1,		  1,           0,        -1 },
	{ NULL,		 "spfm",		NULL,		     SPTAG(1),	  1,		  1,           0,        -1 },
	{ NULL,		 "keepassxc",	NULL,		     SPTAG(2),	  0,		  0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
#define MODKEY Mod1Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "selfrestart.c"
#include "shiftview.c"


static Key keys[] = {
	/* modifier                     chain key   key              function              argument */
	{ MODKEY,                       -1,         XK_p,            spawn,                {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             -1,         XK_Return,       spawn,                {.v = termcmd } },
	{ MODKEY,                       -1,         XK_b,            togglebar,            {0} },
	{ MODKEY,                       -1,         XK_j,            focusstack,           {.i = +1 } },
	{ MODKEY,                       -1,         XK_k,            focusstack,           {.i = -1 } },
	{ MODKEY,                       -1,         XK_i,            incnmaster,           {.i = +1 } },
	{ MODKEY,                       -1,         XK_d,            incnmaster,           {.i = -1 } },
	{ MODKEY,                       -1,         XK_h,            setmfact,             {.f = -0.05} },
	{ MODKEY,                       -1,         XK_l,            setmfact,             {.f = +0.05} },
	{ MODKEY|ShiftMask,             -1,         XK_h,            setcfact,             {.f = +0.25} },
	{ MODKEY|ShiftMask,             -1,         XK_l,            setcfact,             {.f = -0.25} },
	{ MODKEY|ShiftMask,             -1,         XK_o,            setcfact,             {.f =  0.00} },
	{ MODKEY,                       -1,         XK_Return,       zoom,                 {0} },
	{ MODKEY|Mod4Mask,              -1,         XK_u,            incrgaps,             {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_u,            incrgaps,             {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_i,            incrigaps,            {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_i,            incrigaps,            {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_o,            incrogaps,            {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_o,            incrogaps,            {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_6,            incrihgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_6,            incrihgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_7,            incrivgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_7,            incrivgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_8,            incrohgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_8,            incrohgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_9,            incrovgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_9,            incrovgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_0,            togglegaps,           {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_0,            defaultgaps,          {0} },
	{ MODKEY,                       -1,         XK_Tab,          view,                 {0} },
	{ MODKEY|ShiftMask,	            -1,         XK_Tab,          shiftview,            { .i = 1 } },
	{ MODKEY|ControlMask,           -1,         XK_space,        focusmaster,          {0} },
	{ MODKEY|ShiftMask,             -1,         XK_c,            killclient,           {0} },
	{ MODKEY,                       -1,         XK_space,        setlayout,            {0} },
	{ MODKEY|ShiftMask,             -1,         XK_f,            togglefullscr,        {0} },
	{ MODKEY|ShiftMask,             -1,         XK_space,        togglefloating,       {0} },
	{ MODKEY,                       -1,         XK_0,            view,                 {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,         XK_0,            tag,                  {.ui = ~0 } },
	{ MODKEY,                       -1,         XK_comma,        focusmon,             {.i = -1 } },
	{ MODKEY,                       -1,         XK_period,       focusmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         XK_comma,        tagmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,         XK_period,       tagmon,               {.i = +1 } },
	{ MODKEY,                       -1, 		XK_y,  	         togglescratch,        {.ui = 0 } },
	{ MODKEY,                       -1, 		XK_u,	         togglescratch,        {.ui = 1 } },
	{ MODKEY,                       -1, 		XK_x,	         togglescratch,        {.ui = 2 } },
	TAGKEYS(                        -1,         XK_1,                                  0)
	TAGKEYS(                        -1,         XK_2,                                  1)
	TAGKEYS(                        -1,         XK_3,                                  2)
	TAGKEYS(                        -1,         XK_4,                                  3)
	TAGKEYS(                        -1,         XK_5,                                  4)
	TAGKEYS(                        -1,         XK_6,                                  5)
	TAGKEYS(                        -1,         XK_7,                                  6)
	TAGKEYS(                        -1,         XK_8,                                  7)
	TAGKEYS(                        -1,         XK_9,                                  8)
    { MODKEY|ShiftMask,             -1,         XK_r,            self_restart,         {0} },
	{ MODKEY|ShiftMask,             -1,         XK_q,            quit,                 {0} },
	{ MODKEY,                       XK_a,       XK_d,            spawn,                {.v = dmenucmd } },
	{ MODKEY,                       XK_a,       XK_t,            spawn,                {.v = termcmd } },
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
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
