#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "filesystem.h"

#define LOCK_FILE "./lockfile"

int lock_fd; // дескриптор файла блокировки

// Функция для проверки единственности сервера с помощью /proc
void CheckUniqueServer();

