/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=13", "FontAwesome:size=14" };
static const char dmenufont[]       = "monospace:size=13";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#1d2021";
static const char col_gray3[]       = "#a89984";
static const char col_gray4[]       = "#ebdbb2";
static const char col_cyan[]        = "#fb4934";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask  switchtotag   isfloating   monitor */
	{ "Gimp",           NULL, NULL, 0,     1, 1, -1 },
	{ "firefox",        NULL, NULL, 1 << 1,1, 0, -1 },
	{ "zoom",           NULL, NULL, 1 << 7,1, 0, -1 },
	{ "Zathura",        NULL, NULL, 1 << 3,1, 0, -1 },
	{ "Inkspace",       NULL, NULL, 1 << 3,1, 1, -1 },
	{ "mpv",            NULL, NULL, 1 << 4,1, 0, -1 },
	{ "Telegram",       NULL, NULL, 1 << 8,1, 0, -1 },
	{ "Gnome-terminal", NULL, NULL, 1 << 2,1, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */

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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,           XK_f,      togglefullscr,  {0} },
	{ MODKEY,           XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,           XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,           XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,           XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask, XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_space,  zoom,           {0} },
	{ MODKEY,           XK_Tab,    view,           {0} },
	{ MODKEY,           XK_q,      killclient,     {0} },
	{ MODKEY,           XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask, XK_space,  togglefloating, {0} },
	{ MODKEY,           XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,           XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask, XK_h,      togglebar,      {0} },
	/* { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */

	{ MODKEY,           XK_b,                     spawn, SHCMD("firefox") },
	{ MODKEY|ShiftMask, XK_x,                     spawn, SHCMD("slock") },
	{ MODKEY|ShiftMask, XK_q,                     spawn, SHCMD("~/.scripts/prompt.sh 'Do you want to shutdown?' 'shutdown -h now'") },

	{ MODKEY|ShiftMask, XK_b,                     spawn, SHCMD("~/.scripts/firefox_search.sh") },

	{ MODKEY,           XK_p,                     spawn, SHCMD("~/.scripts/papers") },
	{ MODKEY,           XK_o,                     spawn, SHCMD("~/.scripts/open") },
	{ MODKEY,           XK_t,                     spawn, SHCMD("~/Softwares/Telegram/Telegram") },

	{ 0,                XF86XK_AudioMute,         spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	{ 0,                XF86XK_AudioRaiseVolume,  spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +3%") },
	{ 0,                XF86XK_AudioLowerVolume,  spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -3%") },
	{ 0,                XF86XK_AudioMicMute,      spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },

	{ 0,                XF86XK_MonBrightnessUp,   spawn, SHCMD("light -A 1")	},
	{ 0,                XF86XK_MonBrightnessDown, spawn, SHCMD("light -U 1")	},
	{ 0,                XF86XK_Favorites,         spawn, SHCMD("~/.scripts/shortcut.sh")		},
	{ 0,                XK_Print,         spawn, SHCMD("~/.scripts/screenshot.sh")		},
	{ 0,                XF86XK_Display,           spawn, SHCMD("~/.scripts/displayselect.sh")},
	{ MODKEY,           XF86XK_Favorites,         spawn, SHCMD("~/.scripts/dmenu_bmk.sh")},

	{ MODKEY, XK_a, view, {.ui = 7} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

