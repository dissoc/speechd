/*
 * options.c - Parse and process possible command line options
 *
 * Copyright (C) 2003 Brailcom, o.p.s.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this package; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * $Id: options.c,v 1.1 2003-07-17 11:57:02 hanke Exp $
 */

/* NOTE: Be careful not to include options.h, we would
   get repetitive initializations warnings */

#include "speechd.h"

#include "options.h"

#define SPD_OPTION_SET_INT(param) \
    val = strtol(optarg, &tail_ptr, 10); \
    if(tail_ptr != optarg){ \
        param ## _set = 1; \
        param = val; \
    }

void
options_print_help(char *argv[])
{
    assert(argv);
    assert(argv[0]);

    printf("Usage: %s [-{d|s}] [-l {1|2|3|4|5}] [-p=port] | [-h]\n", argv[0]);
    printf("Speech Dispatcher -- Common interface for Speech Synthesis (GNU GPL)\n\n");
    printf("-d, --run-daemon     -      Run as a daemon\n"
    "-s, --run-single     -      Run as single application\n"
    "-l, --log-level      -      Set log level (1..5)\n"
    "-p, --port           -      Specify a port number\n"
    "-h, --help           -      Print this info\n\n"
    "Copyright (C) 2003 Brailcom, o.p.s.\n"
    "This is free software; you can redistribute it and/or modify it\n"
    "under the terms of the GNU General Public License as published by\n"
    "the Free Software Foundation; either version 2, or (at your option)\n"
    "any later version. Please see COPYING for more details.\n\n"
    "Please report bugs to <speechd@freebsoft.org>\n\n");

}

void
options_parse(int argc, char *argv[])
{
    char* tail_ptr;
    int c_opt;
    int option_index;
    int val;

    assert (argc>0);
    assert(argv);

    while(1){
        option_index = 0;
    
        c_opt = getopt_long(argc, argv, spd_short_options, spd_long_options,
                            &option_index);
        if (c_opt == -1) break;
        switch(c_opt){
        case 'd': 
            spd_mode = SPD_MODE_DAEMON;
            break;
        case 's':
            spd_mode = SPD_MODE_SINGLE;
            break;
        case 'l':
            SPD_OPTION_SET_INT(spd_log_level);
            break;
        case 'p':
            SPD_OPTION_SET_INT(spd_port);
            break;
        case 'h':
            options_print_help(argv);
            exit(0);
            break;
        default:
            MSG(2, "Unrecognized option\n");
            options_print_help(argv);
            exit(1);
        }
    }
}