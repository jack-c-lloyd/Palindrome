/*
 * Copyright (C) 2025  Jack C. Lloyd
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAL_VERSION 202503L

static int iglower; /* Ignore Case Sensitivity */
static int igpunct; /* Ignore Punctuation */
static int igspace; /* Ignore Whitespace */

static struct option lopts[] = { /* Long Options */
  { "help",        no_argument, NULL, 'h' },
  { "lower",       no_argument, NULL, 'l' },
  { "punctuation", no_argument, NULL, 'p' },
  { "space",       no_argument, NULL, 's' },
  { "version",     no_argument, NULL, 'v' },
  { NULL,          no_argument, NULL,  0  }
};

static const char *ldescs[] = { /* Long Descriptions */
  "display this usage message",
  "ignore case sensitivity",
  "ignore punctuation",
  "ignore whitespace",
  "display the program version",
  NULL
};

static const char *loptstr = "chpsv"; /* Long Option String */

void
usage (char *argv[])
{
  fprintf (stderr, "usage: %s [options] string...\n", argv[0]);
  fprintf (stderr, "\toptions:\n");

  for (int idx = 0; lopts[idx].name != NULL; ++idx)
    {
      fprintf (stderr, "\t\t-%c, --%s: %s\n", lopts[idx].name[0],
                                              lopts[idx].name,
                                              ldescs[idx]);
    }
}

void
options (int argc, char *argv[])
{
  if (argc < 2)
    {
      usage (argv);
      exit (EXIT_FAILURE);
    }

  int opt = 0; /* Option */
  int idx = 0; /* Index */

  while ((opt = getopt_long (argc, argv, loptstr, lopts, &idx)) != -1)
    {
      switch (opt)
        {
        case 0:
          /* ... */
          break;

        case 'h':
          usage (argv);
          exit (EXIT_SUCCESS);

        case 'l':
          iglower = 1;
          break;

        case 'p':
          igpunct = 1;
          break;

        case 's':
          igspace = 1;
          break;

        case 'v':
          printf ("version: %ld\n", PAL_VERSION);
          exit (EXIT_SUCCESS);

        case '?':
          /* ... */
          break;

        default:
          abort ();
        }
    }
}

int
skip (int c)
{
  return (igpunct && ispunct(c)) || (igspace && isspace(c));
}

int
ispalin (const char *str)
{
  size_t len;

  if (str == NULL || (len = strlen (str)) == 0)
    {
      return EXIT_FAILURE;
    }

  size_t i = 0;
  size_t j = len - 1;

  while (i < j)
    {
      int l = str[i];
      int r = str[j];

      if (skip (l))
        {
          ++i;
          continue;
        }

      if (skip (r))
        {
          --j;
          continue;
        }

      if (iglower)
        {
          l = tolower (l);
          r = tolower (r);
        }

      if (l != r)
        {
          return EXIT_FAILURE;
        }

      ++i;
      --j;
    }

  return EXIT_SUCCESS;
}

int
main (int argc, char *argv[])
{
  options (argc, argv);

  while (optind < argc)
    {
      char *str = argv[optind++];

      if (str == NULL || *str == '\0')
        {
          fprintf (stderr, "%s\n", "EMPTY");
          continue;
        }

      if (ispalin (str) == EXIT_SUCCESS)
        {
          fprintf (stderr, "%s\n", "SUCCESS");
        }
      else /* EXIT_FAILURE */
        {
          fprintf (stderr, "%s\n", "FAILURE");
        }
    }

  return EXIT_SUCCESS;
}
