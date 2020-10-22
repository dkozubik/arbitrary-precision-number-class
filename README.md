# arbitrary-precision-number-class

Class <number> represents a real number with an arbitrary number of digits.
The class have operrators "+, -, /, *, ==, >, >=, <, <=" as well as <power(int)> and <sqrt(int)> <const> methods.
Argument of <power> is the exponent and argument of <sqrt> represents the number of decimal digits
that should be exact in the result => for example number(8).sqrt(4) represents number like "2.8284xxxxx...". /* 4 fractional digits*/

Constructor of <number> takes a single integer argument and constructs an instance of ‹number› with the argument
as its value. Default constructed <number> is 0.
  
Short example how this class works:

number a( 7 ), b( 25 );

number c = number( 5 ).power( 2 );

assert(c == b);

number s = number( 145 ).sqrt( 3 ); /* 3 fractional digits */

number lower = number( 120415 ) * number( 10 ).power( -4 );

number upper = number( 120425 ) * number( 10 ).power( -4 );

assert( s > lower );

assert( s < upper );


