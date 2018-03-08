#!/usr/bin/perl -w

# This program is showing the usage of scalars.

use v5.8.8;
use strict;
use warnings;

my $name = "Arthur";
my $whoaim = 'Just Another Perl Hacker';
my $meaning_of_life = 42;
my $number_less_than_1 = 0.000001;
my $very_large_number = 3.27e17; # 3.27 by 10 to the power of 17

# Adding an integer to a floating point number.
my $sum = $meaning_of_life + $number_less_than_1;
print "sum = $meaning_of_life + $number_less_than_1 = $sum\n";

# Here we're putting the number in the middle of a string we want to print.
print "$name says, 'The meaing of life is $meaning_of_life.'\n";

# single quotes don't interpolate...
my $price = '$9.95';
# my $unit = "$dollar";

# double quotes interpolate...
my $invoice_item = "24 widgets at $price each\n";
print $invoice_item;

print 'Here\'s an example';
print 'It was Jamie\'s birthday.\n';
print "He said, \"Hello!\"\n";

print "The price is \$300\n";
print 'This is a backslash: \\'."\n";

my $what = "jumper";
print "I have 4 $what"."s"."\n";
print "I have 4 ${what}s\n";

=begin
say "Hello world!\n";
=end
=cut
print "Hello world!\n";

print "C:\\WINDOWS\\SYSTEM\\\n";
print 'C:\WINDOWS\SYSTEM\\'."\n";
