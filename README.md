*This project has been created as part of the 42 curriculum by alamtafe.*

# get_next_line

## Description

**get_next_line** is a project from the 42 curriculum. Its goal is to write a C function that reads a file descriptor and returns one line at a time.

The function must return a line including the newline character (`\n`), if one is present. When the end of the file is reached, it returns the remaining content if there is any. Once there is no more content to read, it returns `NULL`.

The project introduces important concepts in C programming, including:
- File descriptors and the `read()` system call.
- Static variables.
- Dynamic memory allocation.
- Buffer management.
- Memory handling and avoiding memory leaks.

## Instructions

### Compilation

The project can be compiled with or without a custom `BUFFER_SIZE`.

**Using the default buffer size:**

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

**Using a custom buffer size:**

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

The default `BUFFER_SIZE` is defined in the header file. If a value is provided through `-D BUFFER_SIZE`, that value takes priority.

### Execution

Run the compiled program:

```bash
./a.out
```

The function prototype is:

```c
char *get_next_line(int fd);
```

Example:

```c
int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Algorithm

### General approach

The algorithm uses a buffer to read the file in chunks instead of reading the entire file at once.

A static variable stores the remaining content between function calls. This allows the function to continue reading from where it stopped during the previous call.

### Step-by-step explanation

1. **Initialize the state:** When the function is called for the first time, memory is allocated to store the line being built.

2. **Read from the file descriptor:** The `read()` function reads up to `BUFFER_SIZE` bytes into a temporary buffer.

3. **Append the content:** The data read is appended to the stored line. If the allocated memory is not large enough, it is reallocated to provide more capacity.

4. **Search for a newline:** The algorithm checks whether the accumulated content contains `\n`.
   - If no newline is found, it reads another chunk.
   - If a newline is found, it stops reading.

5. **Separate the line:** The accumulated content is divided into two parts:
   - The first part contains the line to return, including `\n`.
   - The second part contains the remaining content, which is kept for the next function call.

6. **Handle EOF:** If `read()` returns `0`, the end of the file has been reached. The function returns the remaining content if it is not empty. Otherwise, it returns `NULL`.

7. **Handle errors:** If an allocation or read operation fails, the allocated memory is cleaned up to avoid memory leaks.

### Why this algorithm?

This algorithm was selected because it reads only the necessary amount of data and does not require loading the entire file into memory.

Using a static variable makes it possible to preserve the remaining content between calls. Dynamic allocation allows the stored line to grow when needed, even when a line is longer than `BUFFER_SIZE`.

Separating the returned line from the remaining content avoids losing data that was already read beyond the newline.

### Bonus: Multiple file descriptors

The bonus implementation supports reading from multiple file descriptors independently.

Instead of using a single static state, it uses an array of states. Each file descriptor has its own stored content and capacity.

This allows calls to `get_next_line()` on different file descriptors to preserve their respective reading states without mixing their data.

## Resources

### Documentation and references

- [42 get_next_line subject](https://cdn.intra.42.fr/pdf/pdf/XXXXX/en.subject.pdf)
- [Linux read() manual](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux malloc() manual](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [C documentation – Static variables](https://en.cppreference.com/w/c/language/static.html)

### AI usage

AI (ChatGPT) was used as a learning and assistance tool during this project.

It helped with:
- Understanding file descriptors, the `read()` system call, and static variables.
- Understanding dynamic memory allocation and reallocation.
- Discussing the algorithm and possible approaches to handling buffers and lines.
- Debugging memory-related problems and interpreting Valgrind reports.
- Understanding edge cases, including EOF, invalid file descriptors, and different buffer sizes.
- Reviewing code logic and improving understanding of memory management.

The AI was mainly used for explanations, guidance, debugging, and learning the concepts involved in the project.