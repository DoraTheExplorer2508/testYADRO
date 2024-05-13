# Тестовое задание
## Запуск программы (MinGW)
Склонировать репозиторий

```
git clone https://github.com/DoraTheExplorer2508/testYadro
```

Перейти в директорию

```
cd testYadro
```

Скомпилировать файлы

```
g++ -o main Main.cpp CompClub.cpp
```

Запуск

```
./main file1.txt
```

## Тесты

`file1` - Тестовый файл из задания.

![image](https://github.com/DoraTheExplorer2508/testYadro/assets/71318362/4ca23e7f-9fd9-46f6-9b55-623cf5a4a3b3)


`file2` - Неккоректные входные данные.

![image](https://github.com/DoraTheExplorer2508/testYadro/assets/71318362/f1d8f7fb-d07c-4c48-bf7e-dd6a11d8a703)


`file3` - Тест со сменой столов и неинициализированным клиентом.

![image](https://github.com/DoraTheExplorer2508/testYadro/assets/71318362/729c21d1-8e10-4636-8dcd-915c66df1e54)

`file4` - Видно сортировку в алфавитном порядке в конце рабочего дня.

![image](https://github.com/DoraTheExplorer2508/testYadro/assets/71318362/fde9dec0-5cc8-4efb-9151-5452aaa70b5a)

`file5` - Наглядная работа очереди. Если есть свободные места, то выдается ошибка (`09:52 13 ICanWaitNoLonger!`). Если мест нет, заполняется очередь. Если очередь больше, чем число столов, то клиент уходит (`11:45 11 client7`). Если освобождается стол, то его занимает первый клиент в очереди (`14:56 12 client5 2`).

![image](https://github.com/DoraTheExplorer2508/testYadro/assets/71318362/8ffa311f-2413-419e-9161-a2b2e2628bfb)




