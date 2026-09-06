Simple Shell Project for Holberton

Description

Simple Shell is a Unix command-line interpreter written in C as a team project for Holberton School.

The goal of the project is to recreate some of the core behaviour of a Unix shell while developing an understanding of processes, system calls, command parsing, environment variables, **PATH** resolution, process creation, and program execution.

The shell reads commands from standard input, separates commands into arguments, searches for executable programs using the **PATH** environment variable, creates child processes using fork(), executes programs using execve(), and waits for those processes to finish.

The finished shell program is contained within the Shell directory. The Exercises directory contains smaller exercises and experimental programs used to learn and test individual concepts before they were implemented into the main shell.

Requirements

To compile and run Simple Shell, the following are required:

A Linux or Unix-like operating system **GCC** or another compatible C compiler The C standard library Support for **POSIX** system calls and functions Basic familiarity with terminal commands

Installation

Clone the repository:

git clone [https://github.com/Buiscy/holbertonschool-simple_shell.git](https://github.com/Buiscy/holbertonschool-simple_shell.git)

Enter the project directory:

cd holbertonschool-simple_shell/Shell

Compile the shell:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 Shell.c Functions.c -o hsh

Run the shell:

./hsh

Features

Simple Shell currently supports:

Interactive command input Non-interactive input through pipes or redirected standard input Execution of programs using execve() Commands with arguments Searching for executable commands through **PATH** Execution of commands using absolute or relative paths Waiting for child processes to finish Preservation of external command exit statuses Command-not-found handling End-of-file handling Detection of interactive and non-interactive operation using isatty() A current-working-directory prompt in interactive mode Optional startup banner Optional debug mode Environment variable display Changing the current working directory

Built-in Commands

exit

Exits the shell.

The shell preserves the status of the most recently executed command.

Example:

exit

env

Displays the current environment variables.

Example:

env

cd

Changes the current working directory.

A directory can be supplied directly:

cd /tmp

Relative paths are also supported:

cd ..

When cd is used without an argument, the shell searches the environment for **HOME** and attempts to change to that directory:

cd

The shell also recognises:

cd -

This uses the **OLDPWD** environment variable as the requested destination when available.

clear

Clears the interactive terminal display.

Example:

clear

debug

Toggles additional debugging information while the shell is running.

Debug information can include the input received by the shell, parsed arguments, resolved executable paths, and process exit statuses.

Example:

debug

### Shell Options

-ss

Starts the shell without displaying the startup banner.

Example:

./hsh -ss

-debug

Starts the shell with debugging information enabled.

Example:

./hsh -debug

Usage

### Interactive Mode

Run:

./hsh

When standard input is connected to a terminal, the shell operates interactively and displays a prompt containing the current working directory.

Example:

/home/user/project$> ls -l

The shell executes the command and then displays another prompt.

Non-Interactive Mode

Commands can also be passed to the shell through standard input.

Example:

echo *ls -l* | ./hsh

An absolute path can also be used:

echo */bin/pwd* | ./hsh

Multiple commands may be provided on separate lines:

printf */bin/pwd\n/bin/ls\n* | ./hsh

In non-interactive mode, the startup banner and normal interactive prompt are not displayed.

### Command Examples

Execute a command using **PATH**:

ls

Execute a command with arguments:

ls -l /tmp

Execute a program using its absolute path:

/bin/ls -l

Display the current directory:

/bin/pwd

Display environment variables:

env

Change directory:

cd /tmp

Move to the parent directory:

cd ..

Change to **HOME**:

cd

Attempt to return to **OLDPWD**:

cd -

Exit the shell:

exit

### How Command Execution Works

When a line is entered, Simple Shell follows the following general process:

The shell reads a line from standard input using getline(). The newline is removed from the input. The input is separated into a command and arguments using tokenisation.

For example:

ls -l /tmp

becomes conceptually:

args[0] = *ls* args[1] = *-l* args[2] = */tmp* args[3] = **NULL**

The shell checks whether the command is one of its built-in commands. If the command contains a slash, the shell attempts to execute that path directly. Otherwise, the shell searches through each directory contained in the **PATH** environment variable. access() is used to determine whether a possible command path is executable. Once an executable is found, fork() creates a child process. The child process calls execve() to replace itself with the requested program. The parent process waits for the child using waitpid(). The child's exit status is returned to the shell. In interactive mode, another prompt is displayed and the process repeats.

Interactive and Non-Interactive Behaviour

Simple Shell uses isatty() to determine whether standard input is connected to a terminal.

When running interactively:

The startup banner may be displayed. The current working directory is shown in the prompt. The shell waits for commands continuously.

When running non-interactively:

The banner is not printed. The interactive prompt is not printed. Commands are read directly from standard input. The shell exits when it reaches end-of-file.

**PATH** Handling

If a command does not contain a slash, Simple Shell searches for it using the **PATH** environment variable.

For example:

ls

may resolve to:

/usr/bin/ls

The shell checks each directory contained in **PATH** until an executable matching the requested command is found.

If **PATH** is not present, the shell can still execute commands that contain an explicit path, such as:

/bin/ls

### Exit Status

The shell records the exit status of external programs after they finish.

A successfully executed program returns the status provided by that program.

If a command cannot be located, the shell uses status **127**.

Built-in commands also return a status to the main shell loop.

### Project Structure

holbertonschool-simple_shell/

**README**.md Main project documentation.

**AUTHORS** Lists contributors to the project.

man_1_simple_shell Manual page for Simple Shell.

Shell/ Contains the completed shell implementation.

Shell/Shell.c Contains the main program loop, command handling, built-in dispatch, **PATH** searching, and execution control.

Shell/Functions.c Contains supporting functions used by the shell, including tokenisation, prompt handling, directory-changing logic, and process execution.

Shell/main.h Contains header files and function prototypes shared by the shell source files.

Exercises/ Contains smaller programs and exercises used to learn and test individual shell concepts before integrating them into the final program.

### Implementation Details

Some of the important functions and system calls used by the project include:

getline() Reads command input from standard input.

strtok() Separates the input line into command arguments and separates **PATH** into individual directories.

access() Checks whether a possible executable path can be executed.

fork() Creates a child process.

execve() Replaces the child process with the requested executable.

waitpid() Allows the parent shell to wait for the child process and retrieve its termination status.

chdir() Changes the current working directory for the shell process.

getcwd() Retrieves the shell's current working directory.

isatty() Determines whether the shell is operating interactively.

malloc() and free() Manage dynamically allocated memory used during command resolution.

### Known Limitations

Simple Shell is an educational shell and is not intended to provide all of the functionality available in shells such as Bash or sh.

Current limitations include:

Pipes using | are not implemented. Input and output redirection using <, >, and >> are not implemented. Logical operators such as && and || are not implemented. Command separators such as ; are not implemented. Background command execution using & is not implemented. Shell variable expansion such as $**HOME** is not implemented as command-line syntax. Wildcard expansion is not implemented. Quoting and advanced command parsing are not implemented. Command history is not implemented. Tab completion is not implemented. **PWD** and **OLDPWD** environment maintenance is currently limited. The shell supports a smaller collection of built-in commands than a full Unix shell.

### Learning Objectives

This project was created to develop practical understanding of:

How a Unix shell operates The difference between functions and system calls Process IDs and parent process IDs Process creation with fork() Executing programs with execve() Waiting for child processes Working with **PATH** Reading and manipulating environment variables Command parsing and argument arrays Interactive versus non-interactive programs End-of-file handling Dynamic memory management Exit statuses and process termination

Authors

This project was completed as a team project by:

### Michael Lerovski

[**14804**@holbertonstudents.com](mailto:**14804**@holbertonstudents.com)

### Aaron Regterschot

[Aaron.Regterschot@gmail.com](mailto:Aaron.Regterschot@gmail.com)

Manual

A manual page is included with the project as:

man_1_simple_shell

It can be viewed from the repository using:

man ./man_1_simple_shell

License

This project was created for educational purposes as part of the Holberton School Simple Shell project.

The source code may be viewed, studied, modified, and used for learning purposes.