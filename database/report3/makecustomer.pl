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

for  (1..10000000){
    my $randomNum = int(rand(3000)) +1;

    my $randomChar = String::Random->new->randregex('[A-M]');
    $sth->execute($randomNum,"$randomChar$randomChar","$sex[int(rand(2))]");

}

$dbh->disconnect;
