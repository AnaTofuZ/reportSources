#!/usr/bin/env perl
use strict;
use warnings;
use YAML::XS;

    my $yamlFileName = shift // "hoge.yaml";

    my $yaml = YAML::XS::LoadFile($yamlFileName);
    my $question = $yaml->{question};
    my $question_sbs = $yaml->{question_sbs};

    print "start----\n";
    showSel($question_sbs,$question);

    print "-----\n";

while (1){
#    終了条件2
    last if @{$question->[-1]} eq grep { $_ >= 0 } @{$question->[-1]}; 

    my ($pe_column,) = map $_->[0] ,sort { abs $b->[1] <=>  abs $a->[1]}
                       grep { $_->[1] < 0} 
                             map [$_,$question->[-1]->[$_]], (0..(scalar(@{$question->[-1]})-1));
                                
    my ($pe_row,) =  map $_->[0], sort { $a->[1] <=> $b->[1]} 
                     map [$_,(($question->[$_]->[0])/($question->[$_]->[$pe_column]))],
                        grep { $question->[$_]->[$pe_column] >0 } (0..(@{$question})-2);
   
    if (@$question == grep {$question->[$_]->[$pe_column] <= 0} (0..(@{$question})-1)){
        print "-----There is no optimal solution to this problem\n";
        exit;
    } 

    showSel($question_sbs,$question);
    print "row is $pe_row column is $pe_column\n";
    print "PE is =>$question->[$pe_row]->[$pe_column]\n";
    my $PE =$question->[$pe_row]->[$pe_column];
    print "Do----\n";

    # タブローの入れ替え
    ($question_sbs->[1]->[$pe_row],$question_sbs->[0]->[$pe_column]) =($question_sbs->[0]->[$pe_column],$question_sbs->[1]->[$pe_row]);

    # 以前のPEの列の要素を保存
    my @pe_clomns=getColumnNumbers($question,$pe_column);

    # PEの行の要素をPEで割る
     for (@{$question->[$pe_row]}){
            $_/=$PE;
         }

    for my $now_row(0..@{$question}-1){
        if ( $now_row == $pe_row){
            shift @pe_clomns;
            next;
        }

        my $before = shift @pe_clomns;

        for  (my $i =0;$i <@{$question->[$now_row]};$i++){
            $question->[$now_row]->[$i]-=$question->[$pe_row]->[$i]*$before;
        }
    }

    showSel($question_sbs,$question);
    print "-------\n";
}

    print "Fin___\n";

    showSel($question_sbs,$question);

sub showSel{
    my ($question_sbs,$question) = @_;
    print ("   ");
    print join ("\t|  -",@{$question_sbs->[0]})."\n";
    for (my $i = 0; $i < @$question; $i++) {
        print "$question_sbs->[1]->[$i]\t|";
        print join ("\t|   ",@{$question->[$i]})."\n";
    }
}

sub getColumnNumbers {
    my ($question,$column) = @_;

    my @rev = ();
    for  (0..@$question-1){
        push @rev,$question->[$_]->[$column];
    }
    return @rev;
}

