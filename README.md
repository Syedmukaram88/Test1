#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

unsigned long long sum_of_factorials(int n) {
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += factorial(i);
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);
    if (num <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    pid_t pid1, pid2;
    
    // First fork to calculate factorial
    pid1 = fork();
    
    if (pid1 == 0) {
        // Child process 1: Calculate factorial of num
        unsigned long long fact = factorial(num);
        printf("Child 1 PID: %d, PPID: %d, Child ID: %d\n", getpid(), getppid(), pid1);
        printf("Factorial of %d is %llu\n", num, fact);
        exit(0);  // Terminate the child process
    }
    
    // Second fork to calculate sum of factorials
    pid2 = fork();

    if (pid2 == 0) {
        // Child process 2: Calculate the summation of factorials from 1 to num
        unsigned long long sum_fact = sum_of_factorials(num);
        printf("Child 2 PID: %d, PPID: %d, Child ID: %d\n", getpid(), getppid(), pid2);
        printf("Sum of factorials from 1 to %d is %llu\n", num, sum_fact);
        exit(0);  // Terminate the child process
    }

    // Parent process waits for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Parent PID: %d, PPID: %d\n", getpid(), getppid());
    return 0;
}
