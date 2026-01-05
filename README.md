# Minimal Shell

This lightweight Unix shell uses tokenization, command parsing, fork, and exec to allow users to run simple POSIX commands.

## Table of Contents
1. [Motivation](#motivation)
2. [Usage](#usage)
3. [Limitations and Future Work](#limitations-and-future-work)

## Motivation

Inspired by EECS 201, Computer Science Pragmatics at the University of Michigan, I wanted to learn more about shells and how computers actually run programs. So, I built a simple shell! 

## Usage

To use the shell, first clone the repository. Navigate to the project directory and enter
```bash
make
./shell
```
into your terminal to launch the shell. To exit the shell, enter
```shell
exit
```

## Limitations and Future Work

As of now, the shell only supports standalone commands. In the future, I would like to implement
- I/O redirection
- Pipelining
- Background Execution
- Job control
- Signal Handling

