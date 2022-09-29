/* interval between updates (in ms) */
const unsigned int interval = 500;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 * datetime            date and time                   format string (%F %T)
 * run_command         custom shell command            command (echo foo)
 */

static const struct arg args[] = {
	/* function 	format          argument */
	{ run_command,		"%s",			"~/dotfiles/scripts/bar/RAMusage/RAMusage.out --separator"				},
	{ run_command,		"%s",			"~/dotfiles/scripts/bar/diskUsage/diskUsage.out --separator"			},
	{ run_command,		"%s",			"~/dotfiles/scripts/bar/cpuUsage/cpuUsage.out --separator"				},
	{ run_command,	    "%s",			"~/dotfiles/scripts/bar/battery/battery.py --separator"					},
	{ run_command,	    "%s",			"~/dotfiles/scripts/bar/eth/eth.out --separator"						},
	{ run_command,	    "%s",			"~/dotfiles/scripts/bar/wifi/wifi.py --separator"						},
	{ run_command,	    "%s",			"~/dotfiles/scripts/bar/mullvadCheck/mullvadCheck.py --separator"		},
	{ datetime, 	    "%s",			"%F - %T"																},
};
