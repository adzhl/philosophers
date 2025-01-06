# Philosophers: Dining Philosophers Problem in C

A simulation of the famous Dining Philosophers Problem using POSIX threads and semaphores. This project explores key concepts like process synchronization, resource sharing, and deadlock prevention.

---

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [How It Works](#how-it-works)

---

## Introduction

The Dining Philosophers Problem is a classic concurrency problem that illustrates the challenges of process synchronization. Five philosophers sit at a round table, alternating between eating and thinking. They share a limited number of resources (forks) and must coordinate to avoid deadlocks and resource starvation. This project implements a solution to the problem using multithreading and semaphores.

---

## Features

- Simulates philosopher behavior: eating, thinking, and waiting.
- Implements thread synchronization with semaphores and mutexes.
- Avoids deadlocks through careful resource management.
- Configurable runtime options (e.g., number of philosophers, time limits).

---

## Requirements

- GCC compiler
- POSIX-compatible operating system
- C standard libraries

---

## Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/adzhl/philosophers.git
   ```

2. Navigate to the project directory:

   - Mandatory
   ```bash
   cd philo
   ```
   - Bonus
   ```bash
   cd philo_bonus
   ```

3. Compile the project:
   ```bash
   make
   ```

---

## Usage

Run the executable with the following arguments:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Example:
```bash
./philo 5 800 200 200 [7]
```

This command simulates 5 philosophers, each with the following parameters:
- **Time to die**: 800 milliseconds
- **Time to eat**: 200 milliseconds
- **Time to sleep**: 200 milliseconds

---

## How It Works

### Technical Overview

- **Threads**: Each philosopher is represented as a separate thread.
- **Semaphores**: Used to manage access to shared resources (forks).
- **Synchronization**: Ensures that no two philosophers can use the same fork simultaneously.
- **Deadlock Prevention**: Implements strategies to avoid circular wait conditions.

### Flowchart
```
+-------------------+
| Initialize setup  |
+-------------------+
          |
          v
+-------------------+
| Start simulation  |
+-------------------+
          |
          v
+-------------------+
| Philosophers      |
| eat, think, wait  |
+-------------------+
          |
          v
+-------------------+
| Simulation ends   |
+-------------------+
```

