#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use feature qw( say );
use String::Random;
use DBI;
use Time::HiRes qw( usleep gettimeofday tv_interval );

die "Use:$0 arg2 for username  pass" if(@ARGV != 2);

my $dbh = DBI->connect("DBI:mysql:exam2","$ARGV[0]","$ARGV[1]");

my $random = String::Random->new->randregex('[A-M]');

my $query = $dbh->prepare("CREATE TABLE CUSTOMER(NAME char(20),NEDAN int,KOSUU int,NEBIKI double)");

$query->execute;

my $sth =$dbh->prepare("INSERT INTO CUSTOMER VALUES(?,?,?,?)");
my @NEDANs = (0,2000..2000000);

for  (1..10000000){
    my $KOKUU = int(rand(2001)) ;

    my $NEDAN = int(int(rand(2000001))/100)*100;

    my $NAME = String::Random->new->randregex('[A-M]{5}');
    $sth->execute("$NAME",$NEDANs[$NEDAN+1],$KOKUU,0.85);

}

$dbh->disconnect;
