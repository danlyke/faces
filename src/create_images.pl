#!/usr/bin/perl -w
use warnings;
use strict;

my %image_counts;
while (<>)
{
    if (/(-crop .*?) '(.*)'/)
    {
        my ($geom,$img) = ($1,$2);
        $image_counts{$img} //=0;
        my $dest = $img;
        $dest =~ s/^.*images\///;
        $dest =~ s/\//_/g;
        $dest =~ s/(\.jpg)/.$image_counts{$img}$1/;
        system("convert -strip $geom '$img' '../face_images/$dest'\n");
        $image_counts{$img}++;
    }
}
