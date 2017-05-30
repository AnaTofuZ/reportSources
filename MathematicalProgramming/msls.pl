#!/usr/bin/env perl
use strict;
use warnings;
use List::Util;
use DDP { deparse => 1};

my $firstSolutionNumber =  shift // 6;
$firstSolutionNumber--;

# 配列リファレンスにとりあえず入れていく
# 問題的な意味で0番目に0いれてる

my $A_g =[0,6,1,9,3];
my $B_g =[0,2,5,7,8];
my $C_g =[0,6,3,5,4];
my $D_g =[0,3,5,2,1];


my $grad = [0,$A_g,$B_g,$C_g,$D_g];

my $setupArray =sub {

    my $start = shift;
    my $number = shift;

    my $arrayLef;

    for  ($start..$number){
        @{$arrayLef->[$_]} =List::Util::shuffle(1..4);
        unshift @{$arrayLef->[$_]},0;
    }
    return $arrayLef;

};


my $Operator = $setupArray->(0,$firstSolutionNumber);

my $reminder = 10;

my $calc = calculator($grad);
my $med = 0;
my $max = $firstSolutionNumber;
my $result = {};

while ($reminder >= 0) {

    for  ($med..$max){
            $result->{"@{$Operator->[$_]}"} = $calc->($Operator->[$_]);
        $Operator->[$_+$firstSolutionNumber+1] = perturbation($Operator->[$_]);
    }

    $med += $firstSolutionNumber+1;
    $max += $firstSolutionNumber+1;
    $reminder--;
}

my @sort_keys = sort { $result->{$a} <=> $result->{$b}} keys %$result;

print "$sort_keys[0] => $result->{$sort_keys[0]}\n";

# 摂動を与える
sub perturbation {

    my ($arrayLef) = @_;
    my $returnLef =[0,];
    shift (@{$arrayLef});

    for  (@$arrayLef){
        if ($_ == 1){
            $_ =4;
        }else{
            $_-=1;
        }
        push @{$returnLef},$_;
    }

    return $returnLef;
}


# 数値計算

sub calculator {
    my $grad = shift;

    return sub {
        my $lenarray = shift;
        my $resultTime =0;

        for (my $i = 1; $i < @$lenarray; $i++) {
            $resultTime += $grad->[$i]->[$lenarray->[$i]];
        }
        return $resultTime;
    }
}
