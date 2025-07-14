pipex is a program designed to replicate the behavior of shell pipelines (|) and redirections (<, >). It allows the execution of multiple commands connected by pipes, handling input and output redirection seamlessly, just like a Unix shell.

The project focuses on inter-process communication using UNIX pipes, managing file descriptors, and system calls such as fork, execve, pipe, and dup2.

