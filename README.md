to compile:
```
cd ./src
make
```

to run:
```
./main
```

or

```
./main nameFilePath courseFilePath outputFilePath
```

finally to clean:
```
make clean
```

FOR TESTING:
1. Put each test in ```./tests/testfiles/[your_test_name]/```
2. ```[your_test_name]``` directory must contain the following files: ```courses.txt```, ```names.txt```, ```student_expected.txt```
3. ```courses.txt``` and ```names.txt``` format follows the one given in the project outlline
4. ```student_expected.txt``` follows the following format: ```id firstName lastName course1,test1,test2,test3 course1,test1,test2,test3 ...```
5. Each token is delimited by whitespace. Course names and test grades are delimited by commas

TO COMPILE TESTING MODULE: 
```
cd ./tests
make
```

to run:
```
./test_suite
```

finally to clean:
```
make clean
```
