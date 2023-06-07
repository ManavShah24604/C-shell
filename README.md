<!-- file is written in markdown format -->

```
Basic Linux C-Shell
```

```
Extract the .zip file and then:
$ make
$ ./a.out
```

Main Files :
```
main.c containing driver code
```
```

header.h includes all the function defintions 
```

# ****Part 1 : command_prompt , cd , echo , pwd****

```
Different Files :
```
```
cd.c
```
```
echo.c
```
```
pwd.c
```

# ****Part 2: ls****

```
Files :
```
```
ls.c
```
```
Handles ls command printing all files/sub-directories

Colors implemented:
Directory : (blue)
Executables : (green)
Simple File : (white)
```

# ****Part  8: history****

```
Files :
history.c history.txt
```
```
history.txt stores 20 commands and whenever history command is called it presents the 10 last commands which were executed
```
# ****Part 4, 6: Foreground / Background processes****

```
Files :
bg_fg.c 
```
```
Shell able to run multiple foreground and background processes, and not just one. Running pinfo on each of these works as well.

```

# ****Part 5: pinfo****

```
Files :
pinfo.c
```
```
You can enter the PID number of the process you want to know the information or else it would take the current process. 
```

# ****Part 7: discover****

```
Files :
discover.c
```
```
This commands works similar to the find command of the terminal. 
Request : Don't test this command on Desktop or Downloads folder i.e on a very big folder because printing all the files gives SEG error 
```

# ****Part 8: IO Redirection****

```
Files :
io.c
```
```
This command does input-output re-direction. 
Please enter proper spacing in all the commands of this section. 
```

# ****Part 9: Autocomplete****

```
Files :
main2.c
```
```
This command auto-completes the name in the current-directory. 
I have implemented this in the same way given in the pdf. 
```
# ****Part 10: Signals ****

```
Files :
multiple files 
```
```
ctrl z and ctrl c wouldn't be printed if there is no current foreground process working except a.out. 
```

# ****Part 11: fg and bg****

```
Files :
fg.c 
```
```
This commands get implemented in the same way as given in the pdf. 
```


