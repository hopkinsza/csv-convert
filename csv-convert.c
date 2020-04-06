#include <stdlib.h>
#include <stdio.h>

void err_quote() {
	fflush(stdout);
	fprintf(stderr, "\n[error: unmatched quote]\n");
	exit(1);
}

int main() {
	/* in quotes */
	int inq = 0;
	int c;
	int next;
	while ( (c = getchar()) != EOF) {
		if (!inq) {
			/* entering quotes */
			if (c == '"') {
				inq = 1;
			}
			/* or just print */
			else {
				putchar(c);
			}
		}
		else {
			/* encountering another quote;
			 * is this the end-quote? */
			if (c == '"') {
				if ( (next = getchar()) == EOF) {
					err_quote();
				}
				/* no, it is to escape a literal '"' */
				if (next == '"') {
					putchar('"');
				}
				/* yes */
				else {
					putchar(next);
					inq = 0;
				}
			}
			/* replace problematic characters
			 * with escape sequences */
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
		err_quote();
	else
		return 0;
}
