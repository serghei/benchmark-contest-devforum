#!/usr/bin/perl

$time_start = time();

open(my $fin, "<", "random_numbers.txt")
    or die "Nu s-a putut deschide fisierul random_numbers.txt";

open(my $fout, ">", "result.txt")
    or die "Nu s-a putut crea fisierul result.txt";

$num = 0;

while (my $buf = <$fin>)
{
    chomp $buf;
    my($token1, $token2, $token3) = split(/\t/, $buf);

    $result = $token1 / $token2;
    $buf_result = sprintf "%0.8f", $result;

    if($token3 != $buf_result)
    {
        printf "Eroare: nu corespunde rezultatul!\n%s / %s\n%s != %s\n", $token1, $token2, $token3, $buf_result;
        exit(1);
    }

    print $fout $token1, "\t", $token2, "\t", $buf_result, "\n";

    $num++;
}

close($fout);
close($fin);

$time_end = time();
printf "Au procesate %d de perechi de numere aleatoare în %d secunde.\n", $num, ($time_end - $time_start);
