/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=9" };
static const char dmenufont[]       = "monospace:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_red[]         = "#AA0000";
static const char col_black[]       = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_black, col_gray2 },
	[SchemeSel]  = { col_gray4, col_black,  col_red  },
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
	{ "Discord",  NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[@]",      spiral },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* helper for spawning a command in a terminal */
#define STCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray4, "-sb", col_black, "-sf", col_red, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *screenshotcmd[] = { "scrot", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *discordcmd[] = { "discord", NULL };
static const char *zathuracmd[] = { "zathura", NULL };

static const char *mpctogglecmd[] = { "mpc", "toggle", NULL};
static const char *mpcnextcmd[] = { "mpc", "next", NULL};
static const char *mpcprevcmd[] = { "mpc", "prev", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,						XK_x,      spawn,          {.v = screenshotcmd } },
    { MODKEY|ShiftMask,				XK_x,      spawn,          SHCMD("sleep 1s;scrot --select") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
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
	{ MODKEY|ShiftMask,             XK_c,      quit,	       {0} },

	{ MODKEY|ShiftMask,				XK_p,	   spawn,		   {.v = mpctogglecmd } },
    { MODKEY|ShiftMask,				XK_n,      spawn,          {.v = mpcnextcmd} },
	{ MODKEY|ShiftMask,				XK_b,      spawn,		   {.v = mpcprevcmd} },

	{ MODKEY|ControlMask,			XK_n,	   spawn, 		   STCMD("ncmpcpp") },
	{ MODKEY|ControlMask,			XK_a,	   spawn, 		   STCMD("alsamixer") },
	{ MODKEY|ControlMask,			XK_h,	   spawn, 		   STCMD("htop") },
    { MODKEY|ControlMask,			XK_m,	   spawn, 		   STCMD("bin/mutt.sh") },
	{ MODKEY|ControlMask,			XK_f,	   spawn,		   {.v = browsercmd } },
	{ MODKEY|ControlMask,			XK_d,	   spawn,		   {.v = discordcmd } },
	{ MODKEY|ControlMask,			XK_c,	   spawn,		   STCMD("bin/dwmconf.sh") },
	{ MODKEY|ControlMask,			XK_b,	   spawn,		   STCMD("newsboat") },
	{ MODKEY|ControlMask,			XK_g,	   spawn,		   SHCMD("bin/emu.sh") },
	{ MODKEY|ControlMask,			XK_v,	   spawn,		   STCMD("bin/projects.sh") },
	{ MODKEY|ControlMask,			XK_w,	   spawn,		   SHCMD("bin/bookmarks.sh") },
	{ MODKEY|ControlMask,			XK_z,	   spawn,		   {.v = zathuracmd} },		   
	{ MODKEY|ControlMask,			XK_slash,	   spawn,		   STCMD("bin/mansearch.sh") } 
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

