#include "s21_cat.h"

void parcer(int argc, char *argv[], opt *options);
void Cat_Print_i(int argc, char *argv[], opt *options);

void Cat_Printf(int argc, char *argv[]) {
  if (argc == 1) {
    char cur = getchar();
    while (cur != EOF) {
      printf("%c", cur);
      cur = getchar();
    }
  } else {
    parcer(argc, argv, &options);
    Cat_Print_i(argc, argv, &options);
  }
}

void parcer(int argc, char *argv[], opt *options) {
  int opt = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default:
        fprintf(stderr, "usage: cat [-benstuv] [file ...]\n");
    }
  }
}

void Cat_Print_i(int argc, char *argv[], opt *options) {
  int cur = 0;
  while (optind < argc) {
    FILE *fp = fopen(argv[optind], "r");
    if (fp) {
      int str_count = 1;
      int counter = 1;
      while ((cur = fgetc(fp)) != EOF) {
        if (cur == '\n' && counter > 1 && options->s) {
          continue;
        }
        if (options->b && counter && cur != '\n') {
          printf("%6d\t", str_count++);
          counter = 0;
        }
        if ((options->n && counter) && !(options->b)) {
          printf("%6d\t", str_count++);
        }
        if (options->e && cur == '\n') {
          printf("$");
        }
        if (options->t && cur == '\t') {
          printf("^I");
          counter = 0;
          continue;
        }
        if (options->v) {
          if ((cur < 9 || cur > 10) && cur < 32) {
            printf("%c", '^');
            cur = cur + 64;
          }
          if (cur > 127 && cur < 160) {
            printf("%c%c%c", 'M', '-', '^');
            cur = cur + 192;
          } else if (cur == 127) {
            cur = '?';
            printf("^");
          }
        }
        if (cur == '\n') {
          counter++;
        } else {
          counter = 0;
        }
        putchar(cur);
      }
      fclose(fp);
    } else {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[optind]);
    }
    optind++;
  }
}
