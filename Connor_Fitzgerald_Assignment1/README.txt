You will use this exact Makefile for your Homework 1.
Failure to do so will result in deduction of points.

To compile on terminal type
  make clean
  make all

To delete executables and object file type
  make clean

To run:

./test_points2

^^In that case you will provide input from standard input.

To run with a given file that is redirected to standard input:

./test_points2 < test_input_file.txt

--------------------------------------------------------------
Completed: Everything
Notes: The expected output has an extra newline after the input sections
       can't easily be accounted for as the missing newlines are in test_point2.cc
       not in point2.h
