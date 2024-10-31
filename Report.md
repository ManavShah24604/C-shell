
---

# Basic Linux C-Shell

Extract the `.zip` file and then run:

```bash
$ make
$ ./a.out
```

## Main Files

- **main.c** - Contains driver code
- **header.h** - Includes all function definitions

---

# Features

### Part 1: Command Prompt, `cd`, `echo`, `pwd`

**Files**:
- `cd.c`
- `echo.c`
- `pwd.c`

---

### Part 2: `ls` Command

**Files**:
- `ls.c`

**Functionality**:
- Handles the `ls` command, listing all files and sub-directories.
- Implemented functionality of multiple flags like -l and -a. 
- **Colors Implemented**:
  - **Directory**: Blue
  - **Executables**: Green
  - **Simple Files**: White

---

### Part 3: History

**Files**:
- `history.c`
- `history.txt`

**Functionality**:
- `history.txt` stores the last 20 commands.
- Displays the last 10 commands executed when the `history` command is called.

---

### Part 4, 6: Foreground / Background Processes

**Files**:
- `bg_fg.c`

**Functionality**:
- Supports multiple foreground and background processes.
- Allows running the `pinfo` command on each process.

---

### Part 5: `pinfo` Command

**Files**:
- `pinfo.c`

**Functionality**:
- Displays information for a specified PID.
- Defaults to the current process if no PID is provided.

---

### Part 7: `discover` Command

**Files**:
- `discover.c`

**Functionality**:
- Mimics the terminal’s `find` command.
- **Note**: Avoid testing this command in large directories like Desktop or Downloads to prevent SEG errors.

---

### Part 8: IO Redirection

**Files**:
- `io.c`

**Functionality**:
- Handles input-output redirection.
- **Important**: Ensure proper spacing for all commands in this section.

---

### Part 9: Autocomplete

**Files**:
- `main2.c`

**Functionality**:
- Autocompletes filenames in the current directory, following the method outlined in the project PDF.

---

### Part 10: Signals

**Files**:
- Multiple files handle this functionality.

**Functionality**:
- Ignores `Ctrl + Z` and `Ctrl + C` when no foreground process is active, except for `a.out`.

---

### Part 11: `fg` and `bg` Commands

#### Background Process Management
C-Shell includes comprehensive management for background processes. When a command is executed in the background using the & operator, the shell tracks the process and allows users to monitor or control it through built-in commands like jobs, fg, bg, and sig. This feature enhances multitasking capabilities within the shell, providing users with a more flexible and powerful environment for handling multiple processes simultaneously.

**Files**:
- `fg.c`

**Functionality**:
- Implements `fg` and `bg` commands as specified in the project PDF.

---

This structure should make it easier for users to follow each feature's purpose and functionality while keeping the content engaging and easy to navigate.