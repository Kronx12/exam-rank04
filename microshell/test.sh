./bash_test.sh > ../f1 2> ../f2
./microshell_test.sh > ../f11 2> ../f22
diff ../f1 ../f11
diff ../f2 ../f22
rm ../f1 ../f2
rm ../f11 ../f22