#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use feature qw( say );
use String::Random;
use DBI;
use Time::HiRes qw( usleep gettimeofday tv_interval );

die "Use:$0 arg2 for username  pass" if(@ARGV != 2);

#my $dbh = DBI->connect("DBI:mysql:exam2","$ARGV[0]","$ARGV[1]");

my $random = String::Random->new->randregex('[A-M]');
print "$random$random\n";
