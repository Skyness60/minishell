#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void) {
    const char *directory_path = ".";
    DIR *dir = opendir(directory_path);

    if (dir == NULL) {
        perror("opendir failed");
        return EXIT_FAILURE;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}