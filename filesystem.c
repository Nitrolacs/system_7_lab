#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>

#define MOUNT_FILE "/proc/mounts" // Файл с информацией о смонтированных файловых системах
#define THRESHOLD 90 // Порог заполнения диска в процентах

int CheckDiskFull()
{
    FILE *fp; // Указатель на файл
    char line[256]; // Буфер для чтения строки из файла
    char device[256]; // Буфер для хранения имени устройства
    char mount_point[256]; // Буфер для хранения точки монтирования
    struct statvfs buf; // Структура для хранения данных о файловой системе
    unsigned long free_space; // Свободное пространство на диске в байтах
    unsigned long total_space; // Общее пространство на диске в байтах
    int usage; // Процент заполнения диска

    char buffer[256]; // буфер для хранения пути к текущей директории
    char* directory; // указатель для хранения результата функции getcwd()

    directory = getcwd(buffer, sizeof(buffer)); // вызов функции getcwd()
    if (directory == NULL)
    { // проверка на ошибку
        perror("getcwd"); // вывод сообщения об ошибке
        return 1; // завершение программы с кодом ошибки
    }
    printf("Текущая директория: %s\n", buffer); // вывод пути к текущей директории

    // Открываем файл с информацией о смонтированных файловых системах
    fp = fopen(MOUNT_FILE, "r");
    if (fp == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Читаем файл построчно
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Разбиваем строку на токены по пробелам и получаем имя устройства и точку монтирования
        sscanf(line, "%s %s", device, mount_point);

        // Проверяем, совпадает ли точка монтирования с директорией с log файлами или ее родителем
        if (strcmp(mount_point, directory) == 0 || strcmp(mount_point, "/") == 0)
        {
            // Закрываем файл
            fclose(fp);

            // Получаем данные о файловой системе по точке монтирования
            if (statvfs(mount_point, &buf) == -1)
            {
                perror("Ошибка получения данных о файловой системе");
                return 1;
            }

            // Вычисляем свободное и общее пространство на диске в байтах
            free_space = buf.f_bsize * buf.f_bavail;
            total_space = buf.f_bsize * buf.f_blocks;

            // Вычисляем процент заполнения диска
            usage = 100 * (total_space - free_space) / total_space;

            // Выводим информацию о диске и его заполнении
            printf("Устройство: %s\n", device);
            printf("Точка монтирования: %s\n", mount_point);
            printf("Свободное пространство: %lu байт\n", free_space);
            printf("Общее пространство: %lu байт\n", total_space);
            printf("Процент заполнения: %d%%\n", usage);

            // Проверяем, превышает ли заполнение порог
            if (usage > THRESHOLD)
            {
                printf("Предупреждение: диск заполнен более чем на %d%%\n", THRESHOLD);
                // Выполняем другие действия по необходимости
                // ...
            }

            return 0;
        }
    }

    // Если не нашли нужный диск, выводим сообщение об ошибке
    printf("Не найден диск с log файлами\n");
    return 1;
}


