/* queue.c - This program does the messages spooling
   RCS Identication ; $Revision: 5688 $ ; $Date: 2009-04-30 14:49:42 +0200 (jeu 30 avr 2009) $ 

   Sympa - SYsteme de Multi-Postage Automatique
   Copyright (c) 1997, 1998, 1999, 2000, 2001 Comite Reseau des Universites
   Copyright (c) 1997,1998, 1999 Institut Pasteur & Christophe Wolfhugel

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <sysexits.h>
#include <string.h>
#include <stdlib.h>

static char rcsid[] = "(@)$Id: queue.c 5688 2009-04-30 12:49:42Z david.verdin $";

static char     qfile[128];
static char     buf[16384];
static int      i, fd;

/* For HP-UX */
#ifndef EX_CONFIG
# define EX_CONFIG 78
#endif

#ifndef CONFIG
# define CONFIG		"/etc/sympa.conf"
#endif

char *
readconf(char *file)
{
   FILE			*f;
   char	buf[16384], *p, *r, *s;

   r = NULL;
   if ((f = fopen(file, "r")) != NULL) {
      while (fgets(buf, sizeof buf, f) != NULL) {
	/* Search for the configword "queue" and a whitespace after it */
	if (strncmp(buf, "queue", 5) == 0 && isspace(buf[5])) {
            /* Strip the ending \n */
            if ((p = strrchr((char *)buf, '\n')) != NULL)
               *p = '\0';
            p = buf + 5;
            while (*p && isspace(*p)) p++;
            if (*p != '\0')
               r = p;
            break;
         }
      }
   fclose(f);
   }
   else {
      printf ("SYMPA internal error : unable to open %s",file);
      exit (-1);
   }

   if (r != NULL) {
      s = malloc(strlen(r) + 1);
      if (s != NULL)
         strcpy(s, r);
   }
   return s;
}


/*
** Main loop.
*/
int
main(int argn, char **argv)
{
   char	*queuedir;
   char        *listname;
   unsigned int		priority;
   int			firstline = 1;

   /* Usage : queue list-name */
   if ((argn < 2) || (argn >3)) {
     fprintf(stderr,"%s: usage error, one one list-name argument expected.\n",
            argv[0]);
      exit(EX_USAGE);
   }

   if (argn == 2) {
      listname = malloc(strlen(argv[1]) + 1);
      if (listname != NULL)
         strcpy(listname, argv[1]);
   }

   /* Old style : queue priority list-name */
   if (argn == 3) {
      listname = malloc(strlen(argv[2]) + 1);
      if (listname != NULL)
         strcpy(listname, argv[2]);
   }

   if ((queuedir = readconf(CONFIG)) == NULL){
     fprintf(stderr,"%s: cannot read configuration file '%s'.\n",
            argv[0],CONFIG);
      exit(EX_CONFIG);
   }
   if (chdir(queuedir) == -1) {
     char* buffer=(char*)malloc(strlen(argv[0])+strlen(queuedir)+80);
     sprintf(buffer,"%s: while changing dir to '%s'",argv[0],queuedir);
     perror(buffer);
     exit(EX_NOPERM);
   }
   umask(027);
   snprintf(qfile, sizeof(qfile), "T.%s.%ld.%d", listname, time(NULL), getpid());
   fd = open(qfile, O_CREAT|O_WRONLY, 0600);
   if (fd == -1){
     char* buffer=(char*)malloc(strlen(argv[0])+strlen(queuedir)+80);
     sprintf(buffer,"%s: while opening queue file '%s'",argv[0],qfile);
     perror(buffer);
     exit(EX_TEMPFAIL);
   }
   write(fd, "X-Sympa-To: ", 12);
   write(fd, listname, strlen(listname));
   write(fd, "\n", 1);
   while (fgets(buf, sizeof buf, stdin) != NULL) {
      if (firstline == 1 && strncmp(buf, "From ", 5) == 0) {
         firstline = 0;
         continue;
      }
      firstline = 0;
      write(fd, buf, strlen(buf));
   }
   while ((i = read(fileno(stdin), buf, sizeof buf)) > 0)
   close(fd);
   rename(qfile, qfile + 2);
   sleep(1);
   exit(0);
}









