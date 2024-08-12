/*To demonstrate the use of ERRORS and ISEEK*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void print_error(char *context) {
    printf("%s: %s\n", context, strerror(errno));
}

int main() {
    int fd;
    off_t offset;
    char *filename = "test1.txt";

    // Attempt to open a file (might fail with ENOENT if file does not exist)
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        print_error("Failed to open file");
        return 1;
    }

    // Try seeking to a position in the file
    offset = lseek(fd, 100, SEEK_SET);
    if (offset == (off_t) -1) {
        if (errno == EACCES) {
            print_error("Permission denied while seeking");
        } else if (errno == ENOMEM) {
            print_error("Insufficient memory to complete the seek operation");
        } else {
            print_error("Failed to seek in file");
        }
        close(fd);
        return 1;
    }

    // Attempt to open more files to trigger EMFILE or ENFILE (for demonstration, this part might not always trigger the errors)
    int file_descriptors[1024];
    for (int i = 0; i < 1024; i++) {
        file_descriptors[i] = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (file_descriptors[i] == -1) {
            if (errno == EMFILE) {
                print_error("Too many open files in this process");
            } else if (errno == ENFILE) {
                print_error("Too many open files in the system");
            } else {
                print_error("Failed to open file");
            }
            break;
        }
    }

    // Close the file descriptors that were opened
    for (int i = 0; i < 1024 && file_descriptors[i] != -1; i++) {
        close(file_descriptors[i]);
    }

    // Close the originally opened file
    close(fd);

    return 0;
}
