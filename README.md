# Webtop

## Метрики в оригинальном `top`
- PID: Shows task’s unique process id.
- USER: User name of owner of task.
- PR: The process’s priority. The lower the number, the higher the priority.
- NI: Represents a Nice Value of task. A Negative nice value implies higher priority, and positive Nice value means lower priority.
- VIRT: Total virtual memory used by the task.
- RES: How much physical RAM the process is using, measured in kilobytes.
- SHR: Represents the Shared Memory size (kb) used by a task.
- %CPU: Represents the CPU usage.
- %MEM: Shows the Memory usage of task.
- TIME+: CPU Time, the same as ‘TIME’, but reflecting more granularity through hundredths of a second.
- COMMAND: The name of the command that started the process.


| Основа - чтение данных из `proc/` и `sys/`  

## Структура 

Приложение состоит из нескольких классов

- SystemMonitor - основа и ядро обработки данных от системы
    - ProcessCollector 
    - CpuCollector 
    - MemoryCollector 
- Serializer - единый интерфейс для де- сериализации данных в JSON