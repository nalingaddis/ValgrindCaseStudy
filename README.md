# Valgrind Case Study

Nalin Gaddis - UNC CS Dept - 2021

## Objective

*To explore applications of Valgrind in automated grading of parallel and distributed C programs for courses like **Distributed Computing** and **Operating Systems**.*

## The Model Assignment

The model assignment used for testing of the grading tools developed is inspired by previously assigned **Operating Systems** homeworks. In this assignment students are tasked with processing text inputted via `stdin` and performing the following operations:

1. Replace all newline characters (`'\n'`) with space characters (`' '`)
2. Replace all double asterisks (`'**'`) with carrots (`'^'`)
3. Only print the process string in *complete* lines of 80 characters

with all output being printed to `stdout`. Futhermore the students were challenged to implement this assignment in the following ways:

1. Simple serial implementation
2. Parallel implementation using `pthreads` and a bounded buffer controlled by `semaphores`. Four threads are used to:
    1. Read from `stdin`
    2. Replace newline characters
    3. Replace double asterisks
    4. Buffer and print output

3. Parallel implementation using processes and `pipes` for inter-process communication. Four child processes are created to mirror the 4 tasks outlined in method 2

This model assignment highlights how simple input/output analysis is not sophisticated enough to determine if each assignment has been correctly implemented since all three assignments (if done correct) produce the same output.

## Contents

### src/

The `src/` directory contains example implementations for each of the three versions of the assignment.

### wrappers/

The `wrappers/` directory contains the code implementing Valgrind wrappers for each version of the assignment.

### tests/

The `tests/` directory contains test files for the assignment implements.

### Dockerfile

To maintain a consistent development environment across operating system, a docker image is used for student (and instructor) development. The Dockerfile can be found [here](https://github.com/nalingaddis/ValgrindCaseStudy/blob/master/Dockerfile).

### Makefile

The provided [Makefile](https://github.com/nalingaddis/ValgrindCaseStudy/blob/master/Makefile) is used to easily compile all instructor and student code with proper linking.

### Trac<span>e.s</span>h

The `trace.sh` file takes in a version of the assignment to test and writes the traces generated from Valgrind in the `traces/` directory.
