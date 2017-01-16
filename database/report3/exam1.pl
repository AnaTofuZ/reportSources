#!/usr/bin/env perl
use strict;
use warnings;
use utf8;

use DBI;
use Time::HiRes;

die "Use:$0 arg2 for username  pass" if(@ARGV != 2);

my $dbh = DBI->connect("DBI:mysql:exam2","$ARGV[0]","$ARGV[1]");
