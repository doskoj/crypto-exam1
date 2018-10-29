# Cryptography I Makeup Exam 1

This assignement consists of two programs, one to for the solution to problem 2, and one for the solution for problem 3.

## Program Details
The programs are written in C++, and provide utilities to aid with the solving of the assigned problems.

### Problem 2
The program for problem 2 is [problem2.cpp](problem2.cpp). While this is not required by the assignment, it was a useful coding exercise and provides a number of useful utilities for solving the problem, as well as checking answers.

#### Usage
The program is compiled by using 
```
$ g++ problem2.cpp -o problem2.exe
```
and run with
```
$ ./problem2
```
This opens a command line interface that allows the user to input several commands.

##### Adding Points
```
> add <x1>,<y1> <x2>,<y2>
```
This will calculate the addition of the two points input with x and y values separated by only a comma, and the two points separated by a space. The addition will be performed on the curve hardcoded into the program (as all the questions deal with the same curve).

##### Multiplying a Point
```
> mul <x>,<y> <factor>
```
The program will multiply the given point by a factor by computing repeated addition of the point with itself.

##### Inverting a Number
```
> invert <n> <modulous>
```
The program calculates the inverse of the input ```n``` with respect to the modulous, or gives an error if it is not invertable.

##### Exiting
```
> exit
```

### Problem 3
The program for problem 3 is [problem3.cpp](problem3.cpp). This program is a simple implementation to test the primality of large numbers, and factor them if they are not prime.

#### Primality Testing
The primality is tested using the Miller-Rabin Primality test. The test takes in the number to check, as well as an accuracy factor, which determines how many times the test is run, allowing more confidence while taking longer time. While the program can prove a number to be not prime, it can not prove a number to be prime, only fail to prove that it is not. As the accuracy increases, the likelyhood of this being correct increases as well.

#### Factoring
The non-prime numbers are factored using Pollard's Rho algorithm. This algorithm returns a single non-trivial factor to a non prime number (if the test is successful). So, this function works in a reccursive manner, where once it finds a factor, it tests the primality of the factor, and attempts to factor it, as well as the result when dividing the original number by that found factor. This allows the program to find all the prime factors of a non-prime number.

#### Usage
The program is compiled with
```
$ g++ problem3.cpp -o problem3.exe
```
From here the test is run as such
```
$ ./problem3 <number> <accuracy>
```
This defines the number to be tested (and factored if it is composite) and the accuracy value that determines how many tests to be run for the Miller-Rabbin test.

## Authors

* **Jacob Doskocil** 