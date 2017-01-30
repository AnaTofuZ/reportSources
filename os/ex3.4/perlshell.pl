#!/usr/bin/env perl
use strict;
use warnings;
use utf8;

binmode STDIN,':utf8';
binmode STDOUT,':utf8';

$|=0;

while (<>) {
    chomp;
  
    if (fork) {
        
        print "Parent $$\n";

        wait;

        print "Child end\n";
    } else {
        print "Child $$\n";

       &pipe_manage($_) if(/.*\|.*/);

        print "Child end 1234\n";
    }
}


sub pipe_manage {
  
    print "hoo\n";
}
