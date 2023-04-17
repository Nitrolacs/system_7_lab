# Практическая работа №7. Использование средств управления устройствами и файловой системой  /proc
Седьмая практическая работа по дисциплине Системное программирование
## Цель работы
Изучение особенностей средств управления специфичными объектами файловых систем в GNU/Linux.
## Задачи
1. Ознакомиться с краткими теоретическими сведениями по управлению устройствами и файловой системой /proc в ОС GNU/Linux.
2. Модифицировать результаты выполнения ЛР 6 добавлением использования программных средств для работы со специфичными объектами файловой системы. Обеспечить сборку обеих частей программы, как отдельно, так и полностью, с использованием инструментального набора GNU Autotools. Серверная и клиентская часть при запуске настраиваются аргументами командной строки. Для обработки аргументов командной строки рекомендовано использование функций семейства getopt. Запретить передачу аргументов командной строки через перенаправление стандартных потоков ввод-вывода. Один из аргументов командной строки - вывод справки по аргументам командной строки для серверной и клиентской частей программы, соответственно. Справка также должна выводиться в том случае, если не задан ни один из аргументов командной строки. Еще один аргумент - включает и отключает проверку заполнения "дисков", на которых хранятся log-файлы. Обе части должны разворачиваться в виртуальной файловой системе (ВФС). Изначально ВФС отсутствует.
3. Используя изученные механизмы, разработать и отладить:
- серверную часть. Должен создаваться только единственный экземпляр процесса-сервера, при попытке запуска других экземпляров процесса выводится сообщение об ошибке.
- клиентскую часть
4. Составить общее описание результатов, инструкции по сборке и использованию программы, а также инструкцию по получению документации, сформировать архив формата tar.gz и представить на проверку с исходными текстами программы.
## Вариант задания
Вариант 20. Клиент принимает от пользователя коэффициенты квадратного уравнения (ax2+bx+c=0) или кубического уравнения (ax3+bx2+cx+d=0), каждый из которых не равен нулю или единице, и отсылает их серверу. Сервер принимает коэффициенты и выводит на экран разложение кубического или квадратного уравнения на множители.