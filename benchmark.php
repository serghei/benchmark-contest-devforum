#!/usr/bin/php
<?php

$time_start = time();

$fin = @fopen("random_numbers.txt", "r");

if(!$fin)
{
    echo "Nu s-a putut deschide fisierul random_numbers.txt\n";
    exit(1);
}

$fout = @fopen("result.txt", "w");

if(!$fout)
{
    echo "Nu s-a putut crea fisierul result.txt";
    fclose($fin);
    exit(2);
}

$num = 0;

for(; !feof($fin); $num++)
{
    $buf = fgets($fin);

    if(!$buf)
        break;

    list($token1, $token2, $token3) = explode("\t", $buf);

    $result = (double)$token1 / (double)$token2;

    $buf_result = sprintf("%0.8f", $result);

    if($buf_result == $token3)
    {
        fprintf("Eroare: nu corespunde rezultatul!\n%s != %s", token3, buf_result);
        exit(3);
    }

    fprintf($fout, "%s\t%s\t%s\n", $token1, $token2, $buf_result);
}

fclose($fout);
fclose($fin);

$time_end = time();
printf("Au procesate %d de perechi de numere aleatoare în %d secunde.\n", $num, ($time_end - $time_start));
