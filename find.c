#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define RESET_COLOR   "\x1b[0m"
#define RED_COLOR     "\x1b[31m"
#define GREEN_COLOR   "\x1b[32m"

void printTree(const char *path, int indent,const char *target) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    if (!(dir = opendir(path))) {
        return;
    }

    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);

        if (stat(filePath, &fileStat) >= 0 && S_ISDIR(fileStat.st_mode)) {
            printf("%*s%s/\n", indent, "", entry->d_name);
            printTree(filePath, indent + 2,target);
        } else {
            if (strcmp(target,entry->d_name)==0) {
              printf(GREEN_COLOR "%*s%s\n" RESET_COLOR, indent,"",entry->d_name );
            }else{
            printf("%*s%s\n", indent, "", entry->d_name);
      }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = argv[1];
    const char *target = argv[2];
    printTree(path, 0,target);

    return 0;
}

