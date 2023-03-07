# pipex
Pipex project for Codam.
The objective of this project is to emulate the workings of the shell's pipe operator.

The program should be executed as shown:

# Mandatory
./pipex infile cmd1 cmd2 outfile

# Bonus
./pipex infile cmd1 cmd2 ... outfile \
or \
./pipex here_doc cmd1 cmd2 ... outfile


Where infile is the file you want to read your input from. \
Here_doc also functions as your input, but it read from the standard input, instead of a file.
And outfile is the file you want the output to be written to.

