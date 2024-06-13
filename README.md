# Бот для получения оценок

> Пока что тут информация об установке и шаблоне, но когда-нибудь будет полноценное руководство

## Что сейчас происходит

1. Используется библиотека [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp)
2. Используется БД sqlite3 (о взаимодействии можно почитать [тут](https://sqlite.org/c3ref/intro.html))
3. Используется CMake
4. Используется Google Test ([репозиторий](https://github.com/google/googletest), [документация](https://google.github.io/googletest/))
5. Используется [clang-format](https://clang.llvm.org/docs/ClangFormat.html) ([google codestyle](https://google.github.io/styleguide/cppguide.html))

Бот (на данной версии) умеет отвечать сообщением на комаду `/start` и искать в определенной табличке базы по ключу страны, выбранной пользователем

## Зависимости, установка
1. Нужно рекурсивно склонировать этот репозиторий - `git clone --recursive https://github.com/diduk001/formulas_bot`
2. Нужно поставить зависимости-библиотеки (пишу под Ubuntu): `sudo apt-get install libssl-dev libboost-system-dev libcurl4-openssl-dev libsqlite3-dev`
3. Нужно поставить CMake
4. Нужно поставить библиотеку GTest, о том, как это сделать, написано [в доке](https://www.sqlitetutorial.net/sqlite-sample-database/)

## Компиляция и сборка
0. Поставить нужный токен в `./include/constants.h`
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`
5. `./formulas_bot`

## Тестирование
Нужно проделать все то же самое, что и в компиляции и сборке, но в конце указать исполняемый файл по имени файла теста

## Разработка

- Все основное происходит в main.cpp, все основное масштабное - в сторонних файлах в include/
- Тесты пишутся в tests/ . Хочется, чтобы они писались
- Все взаимодействие происходит через форки и PRы, когда-нибудь я накручу github actions

База chinook.db лежит [здесь](https://www.sqlitetutorial.net/wp-content/uploads/2018/03/chinook.zip), а ее схема - [тут](https://www.sqlitetutorial.net/sqlite-sample-database/)