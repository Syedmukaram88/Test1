#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void processInfo(const char *relationship, pid_t pid, pid_t ppid, pid_t child_pid) {
    printf("Process Relationship: %s\n", relationship);
    printf("PID: %d, PPID: %d, Child PID: %d\n\n", pid, ppid, child_pid);
}

int main() {
    pid_t child1, child2;

    // Create the first child process
    child1 = fork();
    
	if (child1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // First child process
        pid_t child_pid = fork();
        
        
        if (child_pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            // Grandchild process
            processInfo("Grandchild", getpid(), getppid(), -1);
            exit(EXIT_SUCCESS);
        } else {
            // First child process
            processInfo("Child", getpid(), getppid(), child_pid);
            wait(NULL); // Wait for grandchild process to finish
            exit(EXIT_SUCCESS);
        }
    } else {
        // Parent process
        child2 = fork();
        if (child2 < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (child2 == 0) {
            // Second child process
            processInfo("Child", getpid(), getppid(), -1);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            processInfo("Parent", getpid(), getppid(), child1);
            wait(NULL); // Wait for the first child process to finish
            wait(NULL); // Wait for the second child process to finish
        }
    }

    return 0;
}
