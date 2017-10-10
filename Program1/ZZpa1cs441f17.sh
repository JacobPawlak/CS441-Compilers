#!/bin/bash
# Testing Script for CS441 Program 1 −− this is for pa1cs441f17 # Assumes there is a sub directory 
#called myTests
# within the same directory as this script

echo ”Beginning Testing”
#printf −v varname "%(%Y−%m−%d−%H%M%S)T"
#echo ”Current time : ”$varname
#echo ”test results logged in test_results$varname . txt”
#echo ”Current time : ”$varname >> test_results$varname . txt 
#echo ”TESTING RESULTS:” >> test_results$varname.txt
for file in ./myTests/*.branch
do
	echo "TESTING: $file"
	#echo ”−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−”>> test_results$varname . txt 
	#echo ”RESULTS for $file :” >> test_results.txt
	./pa1cs441f17 < "$file" >> test_results.out
	#>> test_results.txt
	#echo ”Note: if no input then unsuccessful parsing” >> test results$varname . txt
done
