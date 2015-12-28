This is a really gross attempt to try to build a face extractor.

I started out by setting up the stock OpenCV Haar Cascade face data
set, in facefinder.cpp, ran that on my entire image library. Did a
little grepping and Emacs magic, and took create_images.pl to turn
that, via ImageMagick, into thumbnails. Now I'm in the process of
going through those 18k thumbnails and classifying them, so that I can
go back and train my own Haar cascade.