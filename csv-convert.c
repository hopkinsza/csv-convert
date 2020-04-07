#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void err_quote(const char *progname) {
	fflush(stdout);
	fprintf(stderr, "\n%s: error: unmatched quote\n", progname);
}

int main(int argc, char **argv) {
	const char *progname = argv[0];
	bool inq = false; /* are we in quotes? */
	int c;
	int next;
	while ( (c = getchar()) != EOF) {
		if (!inq) {
			/* entering quotes */
			if (c == '"') {
				inq = true;
			}
			/* or just print */
			else {
				putchar(c);
			}
		}
		else {
			/*
			 * encountering another quote;
			 * get the next char to see if it's actually
			 * just escaping a literal '"'
			 */
			if (c == '"') {
				if ( (next = getchar()) == EOF) {
					err_quote(progname);
				}

				if (next == '"') {
					putchar('"');
				}
				else {
					putchar(next);
					inq = false;
				}
			}
			/*
			 * replace problematic chars
			 * with escape sequences
			 */
			else if (c == '\\') {
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
