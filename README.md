CSV-CONVERT(1) - General Commands Manual

# NAME

**csv-convert** - convert a csv file to a more easily parseable format

# SYNOPSIS

**csv-convert**

# DESCRIPTION

The
**csv-convert**
utility takes a
'csv'
file on its standard input and outputs it in
a way that can be parsed more easily by tools such as
awk(1).

Because a field in the
'csv'
file format can be enclosed in double-quotes in order to include the delimiter
character (comma) and newlines, it can be difficult or impossible
to use with tools like
awk(1)
that are designed to operate on files which contain each record on its own
line
(with each field within delimited by a designated delimiter character
that does not appear in any field)
.

**csv-convert**
converts a
'csv'
file to just such a format. Each record is printed on its own line,
with fields delimited by commas. Within each field, the following substitutions
are made:

*	"&#92;c"
	for comma

*	"&#92;n"
	for newline

*	"&#92;&#92;"
	for backslash

# EXIT STATUS

The
**csv-convert**
utility exits 0 on success and 1 on failure.

# EXAMPLES

Assuming the file
'test.csv'
contains:

	OS,Description,Free
	GNU/Linux,"GNU's
	Not
	""UNIX""",yes
	OpenBSD,"Only two remote holes in the default install,
	in a heck of a long time!",yes
	Windows,":( Your PC ran into a problem and needs to restart. \",no

"**csv-convert**
&lt;
*test.csv*"
will print:

	OS,Description,Free
	GNU/Linux,GNU's\nNot\n"UNIX",yes
	OpenBSD,Only two remote holes in the default install\c\nin a heck of a long time!,yes
	Windows,:( Your PC ran into a problem and needs to restart. \\,no

# SEE ALSO

awk(1)

# AUTHORS

Zach Hopkins

Void Linux - April 6, 2020
