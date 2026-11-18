# Lineparse fixture independent reference
Accept one fully consumed base-10 integer in [-100,100], including a leading
plus sign, and output its square followed by newline, exit 0 and empty stderr.
Reject other strings with exit 2, empty stdout and `invalid\n` on stderr.
The reference is a mathematical specification independent of both executables.

## seven
7 and +7 produce `49\n`.
## boundary
-100 produces `10000\n`.
## invalid
`bad` is rejected as described above.
