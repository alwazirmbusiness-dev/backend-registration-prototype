# Прототип регистрации

Этот проект представляет собой простой прототип логики регистрации пользователя на C++.

## Что делает проект

- Проверяет данные пользователя перед регистрацией
- Возвращает успешный или ошибочный результат
- Показывает примеры работы валидации через тесты

## Структура проекта

- src/registration_logic.cpp — реализация правил валидации
- src/registration_logic.hpp — объявления структур и логики
- tests/test_validation.cpp — тесты с примерами успешной и неуспешной регистрации

## Как собрать и запустить

Откройте PowerShell и выполните команды:

```powershell
cd C:\Users\alwaz\Desktop\task\build

$gpp = "C:\Users\alwaz\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.MCF.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\g++.exe"

& $gpp ..\tests\test_validation.cpp ..\src\registration_logic.cpp -std=c++17 -I..\src -static -o test_validation.exe
.\test_validation.exe
```

## Что ожидается на выходе

Программа покажет несколько сценариев:

- успешная регистрация
- ошибка из-за существующего email
- ошибка из-за существующего username
- ошибка из-за запрещённой роли

## Примечание

Это учебный прототип, а не полноценный сервер или готовое приложение для продакшена.
