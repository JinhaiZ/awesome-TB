# System Programming

## 1. System Call

Display information about a file given in argument.

[Read code](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/1_1-status.c)

## 2. Environment Variables

Access to environment variables, if executed without arguments. If you give as argument
an environment variable, this program will return the value of this variable.

[Read code](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/2_1-environ.c)

## 3. Fork and Execution 

- **petit_shell** : Allow you to execute a command without options inside this shell. 
	
- **moyen_shell** : It's an improved shell. It allows you to execute a command with 
options.

[Read code 1](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/3_1-petit_shell.c)
|
[Read code 2](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/3_4-moyen_shell.c)

## 4. Signals

Example about how to manipulate signals, and give them handler. In this case, <Ctrl-C> 
can display two different messages. <Ctrl-]> will commute between this two different 
messages.

[Read code](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/5_1-zomb.c)

## 5. Processus

Examples about processus zombies and how to deal with them. 

[Read code 1](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/5_1-zomb.c)
|
[Read code 2](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/5_2-zomb_exit.c)

## 6. File Control fcntl()

Read input in a non-blocking processus (increase CPU uses) if excecuted with option
"true". Without this option, the function **read()** is in block mode, the processs will
wait untill the user write characters. 

[Read code](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/6_1-read_on_delay.c)

## 7. Pipe

Create a pipe where two different processus can communicate. 

[Read code](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/7_1_pipe.c)

## 8. Shell Control

Create password. 

[Read code](https://github.com/Nairolf21/awesome-TB/blob/master/F2B205/TP1-ProgSystem/8_1-mypass.c)

**NOTE** : This program need to be completed
