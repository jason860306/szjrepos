#!/usr/bin/perl -w

use strict;
use warnings;

my @fruits = ("apples", "oranges", "guavas", "passionfruit", "grapes");
my @magic_numbers = (23, 42, 69);
my @random_scalars = ("numble", 123.45, "will the wombat", -300);

#=begin
print @fruits."\n";
print @magic_numbers."\n";
print @random_scalars."\n";
#=end
#=cut

print $fruits[0]; # prints "apples"
print "\n";
print $random_scalars[2]; # prints "willy the wombat"
print "\n";
$fruits[0] = "pineapples"; # changes "apples" to "pineapples"
print $fruits[0]."\n";

my @fruits1 = @fruits[1, 2, 3]; # oranges, guavas, passionfruit
my @fruits2 = @fruits[3, 1, 2]; # passionfruit, oranges, guavas
my @magic_num = @magic_numbers[0..2]; # 23, 42, 69
my @magic_num1 = @magic_numbers[1..5];
@magic_numbers[1..5] = (46, 19, 88, 12, 23); # assigns new magic numbers
my @fruits3 = $fruits[1]; # array slice of one element

print "My favourite fruits are @fruits\n"; # whole array
print "Two types of fruit are @fruits[0,2]\n"; # array slice
print "My favourite fruit is $fruits[3]\n"; # single element
print "@fruits\n"; # whole array
# say "@fruits"; # the same
print "@fruits\n"; # the same
# say @fruits; # not the same
print @fruits."\n"; # not the same

print $fruits[-1]."\n"; # Last fruit in the array, grapes in this case.
print $fruits[-3]."\n"; # Third last fruit: guavas.

my $fruit_count = @fruits; # 5 elements in @fruits
print "The count of fruits is $fruit_count\n";
print "There are ", scalar(@fruits), " in my list of fruits.\n";

my $last_index_used = $#fruits; # index of last element.
print "The index of last element in my list of fruits is $last_index_used(starts at zero).\n";
my $last_fruit = $fruits[$last_index_used];
print "The last fruit is $last_fruit.\n";

my $number_of_fruits = $#fruits + 1;
print "The number of the count of my list of fruits is $number_of_fruits.\n";

my @fruits4 = qw/apples oranges guavas passionfruit grapes/;
print "@fruits4"."\n";
print @fruits4."\n";
print join("|", @fruits4)."\n";

my @months = qw(January February March April June July August September October November December);
print "@months\n";
print @months."\n";
print join("|", @months)."\n";

my @weeks = qw"Monday Tuesday Wednesday Thursday Friday Saturday Sunday";
print "@weeks\n";
print @weeks."\n";
print join("|", @weeks)."\n";

my @fruits5 = @fruits4; # list context
my $num_fruits = @fruits4; # scalar context
my $num = scalar(@fruits4); # scalar context again (explicitly)
