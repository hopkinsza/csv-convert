#include <stdbool.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

void
err_quote(unsigned lineno)
{
	fflush(stdout);
	fprintf(stderr, "\n");
	errx(1, "line %u: unmatched quote", lineno);
}

int
main(int argc, char **argv)
{
	bool inq = false;	/* are we in quotes? */
	unsigned lineno = 1;
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
				if (c == '\n')
					lineno++;
				putchar(c);
			}
		} else {
			/* 
			 * check if exiting quotes,
			 * otherwise print (with necessary substitutions)
			 */
			if (c == '"') {
				if ((next = getchar()) == EOF)
					err_quote(lineno);
				/* '"' is used to escape itself */
				if (next == '"') {
					putchar('"');
				} else {
					if (next == '\n')
						lineno++;
					putchar(next);
					inq = false;
				}
			} else if (c == '\\') {
				putchar('\\');
				putchar('\\');
			} else if (c == '\n') {
				lineno++;
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
		err_quote(lineno);
	else
		return 0;
}
