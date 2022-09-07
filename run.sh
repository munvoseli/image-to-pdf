#!/bin/sh

# this isn't really inteded for other people to use
# i just put it on github bc i didn't want to lose it
# requires pdflatex or xelatex
# other things might work too

if [ "$1" = "" ]
then
	echo "Usage: ./run.sh lskdfja.jpeg"
else
	# configure rotation and scaling yourself
	# meant for converting iphone images
	convert $1 -strip -scale 50% -rotate 90 out.jpeg &&\
	pdflatex impd.tex &&\
	mv impd.pdf out.pdf &&\
	echo "\033[32;1mSuccess\033[0m" &&\
	echo "file ready at \033[34;1mout.pdf\033[0m"
fi
