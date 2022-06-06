To compile on terminal type
  make clean
  make all

To delete executables and object file type
  make clean

To run:
./create_and_test_hash words.txt query_words.txt quadratic
./create_and_test_hash words.txt query_words.txt linear
./create_and_test_hash words.txt query_words.txt double <R VALUE>
./spell_check <document file> <dictionary file>

i. All parts were completed

ii. Had an issue with using std::ifstream vs std::fstream. When used
std::ifstream I had very strange issues that the strings would overlap each other.

EX:
string = "think"
std::cout << string << "CO" << std::ednl; --> COink

iii. Instructions provided above.

iv. Used provided input and output files.


Tested R-values:

1:
r_value: 1
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.953148
total_collisions: 23965

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 2
zebra Found 2
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 6
panacea Found 1
pnca Not_Found 1

10:
r_value: 10
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.785427
total_collisions: 19748

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 2
zebra Found 1
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 5
panacea Found 1
pnca Not_Found 1

25:
r_value: 25
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.773376
total_collisions: 19445

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 6
zebra Found 1
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 4
panacea Found 2
pnca Not_Found 1

50:
r_value: 50
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.763473
total_collisions: 19196

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 6
zebra Found 1
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 2
panacea Found 1
pnca Not_Found 1

75:
r_value: 75
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.753212
total_collisions: 18938

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 2
zebra Found 1
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 2
panacea Found 2
pnca Not_Found 1

100:
r_value: 100
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.758104
total_collisions: 19061

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 2
zebra Found 1
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 2
panacea Found 1
pnca Not_Found 1

121:
r_value: 121
number_of_elements: 25143
size_of_table: 55609
load_factor: 0.452139
average_collisions: 0.766734
total_collisions: 19278

alone Found 1
binary Found 1
catastrophe Found 1
dog Found 1
family Found 1
loath Found 1
oath Found 5
zebra Found 1
bikini Found 1
zucchiniaa Not_Found 1
lwa Not_Found 2
panacea Found 1
pnca Not_Found 1
