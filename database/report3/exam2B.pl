#!/usr/bin/env perl
use strict;
use warnings;
use utf8;

use DBI;
use feature qw( say );
use Time::HiRes qw( usleep gettimeofday tv_interval );

die "Use:$0 arg2 for username  pass" if(@ARGV != 2);

my $dbh = DBI->connect("DBI:mysql:exam2","$ARGV[0]","$ARGV[1]",
    {
        PrintError => 0,
        AutoCommit => 0
    });


my $sth = $dbh->prepare('select * from noti1 where B = "AA"');
say('select * from noti1 where B = "AA"');

my $result = 0;

for(0..9){
    my $t0 = [gettimeofday];

    $sth->execute;

    my $elapsed = tv_interval($t0);

    say(int($elapsed * 1000),"ms");

    $result +=(int($elapsed * 1000));
}

say("Result for",$result/10,"ms");
$result=0;
say("-----------------------");

$sth = $dbh->prepare("CREATE INDEX indb on noti1(B)");
say("CREATE INDEX indb on noti1(B)");
$sth->execute;


$sth = $dbh->prepare('select * from noti1 where B = "AA"');
say('select * from noti1 where B = "AA"');

for(0..9){
    my $t0 = [gettimeofday];

    $sth->execute;

    my $elapsed = tv_interval($t0);

    say(int($elapsed * 1000),"ms");

    $result +=(int($elapsed * 1000));
}

say("Result for",$result/10,"ms");

$sth->finish;
$dbh->disconnect;
