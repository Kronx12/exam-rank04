./test/bash_test.sh > ../f1 2> ../f2
./test/microshell_test.sh > ../f11 2> ../f22
./test/microshell_test_other.sh > ../f111 2> ../f222
./test/microshell_test_other_two.sh > ../f1111 2> ../f2222
vim -d ../f1 ../f11 ../f111 ../f1111
vim -d ../f2 ../f22 ../f222 ../f2222
rm ../f1 ../f2
rm ../f11 ../f22
rm ../f111 ../f222
rm ../f1111 ../f2222