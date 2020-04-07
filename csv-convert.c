#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void
err_quote(const char *progname)
{
	fflush(stdout);
	fprintf(stderr, "\n%s: error: unmatched quote\n", progname);
}

int
main(int argc, char **argv)
{
	const char *progname = argv[0];
	bool inq = false;	/* are we in quotes? */
	int c;
	int next;
	while ((c = getchar()) != EOF) {
		if (!inq) {
			/* 
			 * enter quotes if necessary and discard the '"',
			 * or just print
			 */
			if (c == '"') {
				inq = true;
			} else {
				putchar(c);
			}
		} else {
			/* 
			 * check if exiting quotes,
			 * otherwise print (with necessary substitutions)
			 */
			if (c == '"') {
				if ((next = getchar()) == EOF) {
					err_quote(progname);
				}
				/* '"' is used to escape itself */
				if (next == '"') {
					putchar('"');
				} else {
					putchar(next);
					inq = false;
				}
			} else if (c == '\\') {
				putchar('\\');
				putchar('\\');
			} else if (c == '\n') {
				putchar('\\');
				putchar('n');
			} else if (c == ',') {
				putchar('\\');
				putchar('c');
			} else {
				putchar(c);
			}
		}
	}

	if (inq)
		err_quote(progname);
	else
		return 0;
}
