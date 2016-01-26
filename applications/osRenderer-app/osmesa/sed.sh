#!/bin/sh -

for file in *.C
do
  cat $file | sed -e 's/\#include \"/\#include \"booga\/glosmesa\//g' > /Home/user2/matthey/booga/framework/glosmesa/src/$file
done
