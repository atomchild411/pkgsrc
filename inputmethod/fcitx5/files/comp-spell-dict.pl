#!/usr/bin/env perl
#
# Build-host stand-in for src/modules/spell/comp_spell_dict.cpp in cross
# builds: the first argument is the target's comp-spell-dict, which the
# build host cannot run.  The .fscd format is little-endian on every
# host, so the output is the same.

use strict;
use warnings;

my (undef, $action, $in, $out) = @ARGV;
die "comp-spell-dict: usage: TOOL --comp-dict IN OUT\n"
    unless defined $out && $action eq "--comp-dict";

open(my $ifh, "<:raw", $in) or die "comp-spell-dict: $in: $!\n";
my $data = do { local $/; <$ifh> };
close($ifh);

my @lines = split(/\n/, $data, -1);
pop(@lines) if @lines && $lines[-1] eq "";

my $body = "";
foreach my $l (@lines) {
	$l =~ /^\s*([+-]?\d+) (.*)$/s
	    or die "comp-spell-dict: $in: bad line: $l\n";
	my $ceff = $1 > 65535 ? 65535 : $1;
	$body .= pack("v", $ceff & 0xffff) . $2 . "\0";
}

open(my $ofh, ">:raw", $out) or die "comp-spell-dict: $out: $!\n";
print $ofh "FSCD0000", pack("V", scalar(@lines)), $body;
close($ofh) or die "comp-spell-dict: $out: $!\n";
