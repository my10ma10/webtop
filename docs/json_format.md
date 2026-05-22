```json
{
    "timestamp": 1716391200,

    "cpu": {
        "total_usage_percent": 23.5,

    "cores": [
        {
            "id": 0,
            "usage_percent": 31.2
        },
        {
            "id": 1,
            "usage_percent": 18.4
        }
    ]
  },

  "memory": {
    "total_kb": 16384000,
    "used_kb": 8245000,
    "available_kb": 10200000,
    "free_kb": 8139000,
    "usage_percent": 50.3
  },

  "processes": [
    {
        "pid": 1,
        "user": "root",
        "command": "systemd",

        "state": "S",

        "priority": 0,
        "nice": -1,

        "cpu_percent": 0.1,
        "memory_percent": 0.3,

        "virtual_memory_kb": 225280,
        "resident_memory_kb": 11432,
        "shared_memory_kb": 231240,

        "threads": 1,

        "uptime_seconds": 52341,

        "total_cpu_time_seconds": 12.53
    },

    {
        "pid": 2481,
        "user": "username",
        "command": "firefox",

        "state": "R",

        "cpu_percent": 4.2,
        "memory_percent": 7.1,

        "priority": 20,
        "nice": 0,

        "virtual_memory_kb": 4123456,
        "resident_memory_kb": 1162340,
        "shared_memory_kb": 12564,

        "threads": 42,

        "uptime_seconds": 1832,

        "total_cpu_time_seconds": 324.91
    }
  ]
}

```