/* This program is protected under the GNU GPL (See COPYING) */

#include "defs.h"

struct session *gts;
struct global_data *gtd;

pthread_t input_thread;
pthread_t output_thread;

int command_prompt = TRUE;

int main(int argc, char **argv) {
  signal(SIGTERM, abort_and_trap_handler);
  signal(SIGSEGV, abort_and_trap_handler);
  signal(SIGHUP, abort_and_trap_handler);
  signal(SIGABRT, abort_and_trap_handler);
  signal(SIGINT, abort_and_trap_handler);
  signal(SIGTSTP, suspend_handler);
  signal(SIGPIPE, pipe_handler);
  signal(SIGWINCH, winch_handler);

  init_program();

  if (argc > 1) {
    int c;

    optind = 1;

    while ((c = getopt(argc, argv, "e: h c: t:")) != EOF) {
      switch (c) {
      case 't':
        printf("\033]0;%s\007", optarg);
        break;
      case 'c':
        if (access(optarg, R_OK) == 0) {
          do_read(optarg);
        }
        break;
      case 'e':
        command_prompt = FALSE;
        script_driver(optarg);
        break;
      case 'h':
        help_menu(FALSE, c, argv[0]);
        break;
      default:
        help_menu(TRUE, c, argv[0]);
        break;
      }
    }

    if (argv[optind] != NULL) {
      do_read(argv[optind]);
    }
  } else {
    display_printf("%cHELP for more info", gtd->command_char);
  }

  if (getenv("HOME") != NULL) {
    char filename[256];
    sprintf(filename, "%s", ".chromatermrc");

    if (access(filename, R_OK) == 0) {
      do_read(filename);
    } else {
      sprintf(filename, "%s/%s", getenv("HOME"), ".chromatermrc");

      if (access(filename, R_OK) == 0) {
        do_read(filename);
      }
    }
  }

  if (pthread_create(&input_thread, NULL, poll_input, NULL) != 0) {
    quitmsg("faild to create input thread", 1);
  }

  pthread_join(input_thread, NULL);

  quitmsg(NULL, 0);
  return 0;
}

void init_program() {
  int index;

  gts = (struct session *)calloc(1, sizeof(struct session));
  gtd = (struct global_data *)calloc(1, sizeof(struct global_data));

  for (index = 0; index < LIST_MAX; index++) {
    /* initial size is 8, but is dynamically resized as required */
    gts->list[index] = init_list(index, 8);
  }

  gts->socket = 1;

  init_screen_size();

  gtd->quiet++;
  do_configure("CHARSET    UTF-8");
  do_configure("COMMAND    #");
  do_configure("CONVERT    OFF");
  do_configure("HIGHLIGHT  ON");
  gtd->quiet--;

  init_terminal();
}

void help_menu(int error, char c, char *proc_name) {
  if (error) {
    display_printf("Unknown option '%c'", c);
  }

  display_printf("ChromaTerm-- v%s", VERSION);
  display_printf("Usage: %s [OPTION]... [FILE]...", proc_name);
  display_printf("    -e       Execute function");
  display_printf("    -h       This help section");
  display_printf("    -c       Specify configuration file");
  display_printf("    -t       Set title");

  quitmsg(NULL, error);
}

void quitmsg(char *message, int exit_signal) {
  int i;

  reset_terminal();
  cleanup_session();

  if (input_thread) {
    pthread_kill(input_thread, 0);
  }

  if (output_thread) {
    pthread_kill(output_thread, 0);
  }

  for (i = 0; i < LIST_MAX; i++) {
    while (gts->list[i]->used) {
      delete_index_list(gts->list[i], 0);
    }
    free(gts->list[i]->list);
    free(gts->list[i]);
  }

  free(gts);
  free(gtd);

  if (message) {
    printf("\n%s\n", message);
  }

  fflush(stdout);
  exit(exit_signal);
}

void abort_and_trap_handler(int sig) { quitmsg("abort_and_trap_handler", sig); }

void pipe_handler(int sig) { display_printf("broken_pipe: %i", sig); }

void suspend_handler(int sig) { quitmsg("suspend_handler", sig); }

void winch_handler(int sig) {
  if (sig) {
    /* Just to make a compiler warning shut up */
  }
  init_screen_size();
}
