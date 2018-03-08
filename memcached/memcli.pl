#!/usr/bin/perl -w

# add third-part library into this module.
#
# method 1
# use lib qw(/opt/perl/lib/perl5/site_perl/5.8.8/Cache/);
#
# method 2
# BEGIN {
# unshift @INC, qw(/opt/perl/lib/perl5/site_perl/5.8.8/Cache/);
# }

BEGIN {
	unshift @INC, qw(/opt/perl/lib/perl5/site_perl/5.8.8/);
}

use strict;
use warnings;
use Cache::Memcached;

my $memcached = Cache::Memcached->new(
	{servers => ["127.0.0.1:11211"], compress_threshold => 10_000}
);

my $key = "foo";
my $value = "bar";
my $expires = 3600; # 1 hour

$memcached->add($key, $value, $expires);
my $ret = $memcached->get($key);
print "$key => $ret\n";
print "\n=======================================================\n";

use String::CRC32;

my @nodes = ('node1', 'node2', 'node3');
my @keys = ('tokyo', 'kanagawa', 'chiba', 'saitama', 'gunma');

foreach my $key (@keys) {
	my $crc = crc32($key);
	my $mod = $crc % ($#nodes + 1);
	my $server = $nodes[$mod];
	printf "%s => %s\n", $key, $server;
}
print "\n=======================================================\n";

my @nodes1 = $ARGV;
my @keys1 = ('a'..'z');
my %nodes1;

foreach my $key1 (@keys1) {
	my $hash = crc32($key1);
	my $mod1 = $hash % ($#nodes1 + 1);
	my $server1 = $nodes1[$mod1];
	printf "nodes1 => %nodes1\n";
	printf "server1 => $server1\n";
	push @{$nodes1{$server1}}, $key1;
}

foreach my $node (sort keys(%nodes1)) {
	printf "%s: %s\n", $node, join ",", @{$nodes1{$node}};
}
print "\n=======================================================\n";

