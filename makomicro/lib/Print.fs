######################################################
##
##  Print:
##
##  A lexicon for printing numbers and characters
##  via the debug port. Mostly compatible with
##  ANS Forth definitions.
##
##  John Earnest
##
######################################################

:vector emit CO ! ;

: cr      10 emit ;
: tab      9 emit ;
: space   32 emit ;
: spaces  1 - for space next ;

: /mod    2dup mod >r / r> ;
: .number 10 /mod 48 + swap dup if .number else drop then emit ;
: .num    dup 0 < if 45 emit -1 * then .number ;
: .       .num space ;
: ?       @ . ;

: type    loop dup @ dup if emit else 2drop exit then 1 + again ;
: typeln  type cr ;