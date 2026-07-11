# Сервис регистрации

Проект реализует базовый сервис регистрации пользователей на C++ с валидацией входных данных, проверкой конфликтов по email и username, ограничением по роли и обработкой регистрационных запросов.

## Возможности

- Проверка обязательных полей и формата email
- Запрет регистрации с ролью admin
- Ограничение размера метаданных
- Проверка дубликатов по email и username
- Обработка JSON-запросов и HTTP-ответов
- Хеширование паролей и генерация идентификаторов пользователей

## Структура проекта

- src/registration_logic.{hpp,cpp} — правила валидации
- src/registration_service.{hpp,cpp} — бизнес-логика регистрации
- src/http_handler.{hpp,cpp} — обработка входящих запросов
- src/http_server.{hpp,cpp} — запуск HTTP-сервера
- src/json_parser.{hpp,cpp} — разбор JSON-тела запроса
- src/password_hasher.{hpp,cpp} — хеширование паролей
- src/user_repository.{hpp,cpp} — хранение пользователей
- src/uuid_generator.{hpp,cpp} — генерация идентификаторов
- tests/test_validation.cpp — набор проверок для основных сценариев

## Сборка и запуск

Откройте PowerShell и выполните:

```powershell
cd C:\Users\alwaz\Desktop\task
cmake -S . -B build
cmake --build build --config Debug
```

Запуск тестов:

```powershell
cd C:\Users\alwaz\Desktop\task\build
.\auth_service_tests.exe
```

Запуск сервиса:

```powershell
cd C:\Users\alwaz\Desktop\task\build
.\auth_service.exe
```

## Ожидаемый результат

Программа обрабатывает сценарии успешной регистрации и ошибок для повторного email, повторного username, запрещённой роли и слишком большого набора метаданных.
