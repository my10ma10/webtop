# Webtop

**Webtop** — программа мониторинга состояние системы Linux с отображением статистики в браузере, реализованная через WebUI

Аналоги: `top`, `htop`

Основной источник данных — виртуальные файлы в `/proc` системы Linux.

## Архитектура

В проекте разделяется ответственность между модулями сбора данных, их сериализацией и отображением в браузере.

### Основные компоненты

#### `SystemMonitor`

* Центральный компонент системы. Отвечает за координацию сборщиков данных (collector'ов), агрегацию SystemSnapshot, формирование итоговой структуры состояния системы


#### `ProcessCollector`

* Отвечает за сбор информации о процессах
* Источник данных - `/proc/[pid]/stat`


#### `CpuCollector`

* Отвечает за получение информации о загрузке CPU
* Источник данных - `/proc/stat`


#### `MemoryCollector`

* Отвечает за состояние памяти
* Источник данных - `/proc/meminfo`


#### `Serializer`

* Унифицированный слой сериализации данных из структур в JSON для передачи фронтенду
* Реализация основана на `nlohmann/json`.


## Формат данных 

* В программе
    * Структуры ([здесь](src/collectors/structs.hpp) и [здесь](src/process_info/process_info.hpp))
* При передаче во фронтенд - JSON
    * Смотреть в [docs/json_format.md](docs/json_format.md)


## Требования

* Linux
* C++20+
* CMake 3.16+
* Наличие браузера


## Зависимости

* [webui](https://github.com/webui-dev/webui.git)
* [nlohmann/json](https://github.com/nlohmann/json)


## Сборка

```bash
cmake -S . -B build
cmake --build build
```

## Запуск

```bash
./build/src/webtop
```

## Работа утилиты 

Скриншот работы программы

<img width="1252" height="447" alt="image" src="https://github.com/user-attachments/assets/e5620645-caf0-4cb2-80f3-07aae7b830a8" />


