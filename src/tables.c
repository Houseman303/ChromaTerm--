// This program is protected under the GNU GPL (See COPYING)

#include "defs.h"

struct command_type command_table[] = {{"commands", do_commands},
                                       {"config", do_configure},
                                       {"exit", do_exit},
                                       {"help", do_help},
                                       {"highlight", do_highlight},
                                       {"quit", do_exit},
                                       {"read", do_read},
                                       {"run", do_run},
                                       {"unhighlight", do_unhighlight},
                                       {"write", do_write},
                                       {"", NULL}};

struct list_type list_table[LIST_MAX] = {
    {"CONFIG", "CONFIGURATIONS", ALPHA, 2},
    {"HIGHLIGHT", "HIGHLIGHTS", PRIORITY, 3}};

struct config_type config_table[] = {
    {"CHARSET", "The character set encoding used", config_charset},
    {"COMMAND CHAR", "The character used for commands", config_commandchar},
    {"CONVERT META", "Convert meta and control characters", config_convertmeta},
    {"HIGHLIGHT", "Highlight according to rules", config_highlight},
    {"", "", NULL}};

struct color_type color_table[] = {
    {"bold", "<188>"},         {"dim", "<288>"},
    {"underscore", "<488>"},   {"blink", "<588>"},
    {"azure", "<abd>"},        {"b azure", "<ABD>"},
    {"b black", "<880>"},      {"b blue", "<884>"},
    {"b cyan", "<886>"},       {"b ebony", "<G04>"},
    {"b green", "<882>"},      {"b jade", "<ADB>"},
    {"b lime", "<BDA>"},       {"b magenta", "<885>"},
    {"b orange", "<DBA>"},     {"b pink", "<DAB>"},
    {"b red", "<881>"},        {"b silver", "<CCC>"},
    {"b tan", "<CBA>"},        {"b violet", "<BAD>"},
    {"b white", "<887>"},      {"b yellow", "<883>"},
    {"black", "<808>"},        {"blue", "<848>"},
    {"cyan", "<868>"},         {"ebony", "<g04>"},
    {"green", "<828>"},        {"jade", "<adb>"},
    {"light azure", "<acf>"},  {"light ebony", "<bbb>"},
    {"light jade", "<afc>"},   {"light lime", "<cfa>"},
    {"light orange", "<fca>"}, {"light pink", "<fac>"},
    {"light silver", "<eee>"}, {"light tan", "<eda>"},
    {"light violet", "<caf>"}, {"lime", "<bda>"},
    {"magenta", "<858>"},      {"orange", "<dba>"},
    {"pink", "<dab>"},         {"red", "<818>"},
    {"silver", "<ccc>"},       {"tan", "<cba>"},
    {"violet", "<bad>"},       {"white", "<878>"},
    {"yellow", "<838>"},       {"", "<099>"}};

struct cursor_type cursor_table[] = {
    {"BACKSPACE", "Delete backward character", "", cursor_backspace},
    {"BACKWARD", "Move cursor backward", "", cursor_left},
    {"CLEAR LEFT", "Delete from cursor to start of input", "",
     cursor_clear_left},
    {"CLEAR LINE", "Delete the input line", "", cursor_clear_line},
    {"CLEAR RIGHT", "Delete from cursor to end of input", "",
     cursor_clear_right},
    {"CONVERT META", "Meta convert the next character", "",
     cursor_convert_meta},
    {"CTRL DELETE", "Delete one character, exit on an empty line", "",
     cursor_delete_or_exit},
    {"DELETE", "Delete character at cursor", "[3~", cursor_delete},
    {"DELETE WORD LEFT", "Delete backwards till next space", "",
     cursor_delete_word_left},
    {"DELETE WORD RIGHT", "Delete forwards till next space", "",
     cursor_delete_word_right},
    {"END", "Move cursor to end of input", "", cursor_end},
    {"ENTER", "Process the input line", "", cursor_enter},
    {"EXIT", "Exit current session", "", cursor_exit},
    {"FORWARD", "Move cursor forward", "", cursor_right},
    {"HOME", "Move the cursor to start of input", "", cursor_home},
    {"INSERT", "Turn insert mode on or off", "", cursor_insert},
    {"NEXT WORD", "Move cursor to the next word", "f", cursor_right_word},
    {"PASTE BUFFER", "Paste the previously deleted input text", "",
     cursor_paste_buffer},
    {"PREV WORD", "Move cursor to the previous word", "b", cursor_left_word},
    {"REDRAW INPUT", "Redraw the input line", "", cursor_redraw_input},
    {"SUSPEND", "Suspend program, return with fg", "", cursor_suspend},
    {"TEST", "Print debugging information", "", cursor_test},

    {"", "", "OM", cursor_enter},
    {"", "", "[7~", cursor_home},
    {"", "", "[1~", cursor_home},
    {"", "", "OH", cursor_home},
    {"", "", "[H", cursor_home},
    {"", "", "OD", cursor_left},
    {"", "", "[D", cursor_left},
    {"", "", "[8~", cursor_end},
    {"", "", "[4~", cursor_end},
    {"", "", "OF", cursor_end},
    {"", "", "[F", cursor_end},
    {"", "", "OC", cursor_right},
    {"", "", "[C", cursor_right},
    {"", "", "", cursor_backspace},
    {"", "", "", cursor_delete_word_left},
    {"", "", "d", cursor_delete_word_right},
    {"", "", "", NULL}};
