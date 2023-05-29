#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void deleteDirectory(const char *dirPath) {
    DIR *dir;
    struct dirent *entry;
    char filePath[1024];

    dir = opendir(dirPath);

    if (dir == NULL) {
        printf("Error opening directory: %s\n", dirPath);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);

        if (entry->d_type == DT_DIR) {
            deleteDirectory(filePath);  // Recursively delete subdirectories
        } else {
            remove(filePath);  // Delete files
        }
    }

    closedir(dir);

    if (rmdir(dirPath) != 0) {
        printf("Error deleting directory: %s\n", dirPath);
    } else {
        printf("Directory deleted: %s\n", dirPath);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    const char *dirPath = argv[1];
    deleteDirectory(dirPath);

    return 0;
}
