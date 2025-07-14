PIPEX is a program designed to replicate the behavior of shell pipelines (|) and redirections (<, >). It allows the execution of multiple commands connected by pipes, handling input and output redirection seamlessly, just like a Unix shell.

The project focuses on inter-process communication using UNIX pipes, managing file descriptors, and system calls such as fork, execve, pipe, and dup2.

Features:

-Simulates shell pipeline functionality by connecting commands with pipes.

-Supports input (<) and output (>) redirection.

Manages multiple processes through fork.

Utilizes low-level system calls for process control and communication.

Demonstrates core UNIX programming concepts including IPC and file descriptor manipulation.
