
# C++ Redis Server: Custom Key-Value Store with RESP, Threads & Persistence

## 🚀 Overview

**RedisLite** is a simplified Redis clone built from scratch in C++ that supports socket-based client communication, multithreading, command parsing (RESP-like), persistence using custom RDB format, and a modular architecture using design patterns.

This project demonstrates in-depth understanding of:
- Low-level system programming
- Networking with TCP/IP sockets
- Concurrency & synchronization
- File I/O and persistence
- Data structure design
- Automation with shell scripts & Makefile
- Clean code practices and architecture

---

## 🧱 Features

### 🔌 Socket Programming
- TCP server using Winsock (Windows) / POSIX sockets (Linux)
- Handles multiple concurrent client connections using threads

### 📦 Supported Redis-like Commands

#### 🔁 Common
- `PING`, `ECHO`, `FLUSHALL`

#### 🔑 Key/Value
- `SET key val`
- `GET key`
- `DEL key`
- `KEYS *`
- `EXPIRE key seconds`
- `RENAME old new`

#### 📋 List Operations
- `LPUSH key val [val ...]`
- `RPUSH key val [val ...]`
- `LPOP key`, `RPOP key`
- `LREM key count value`
- `LSET key index val`
- `LINDEX key index`
- `LLEN key`
- `LGET key`

#### 🧩 Hash Operations
- `HSET key field value`
- `HGET key field`
- `HGETALL key`
- `HEXISTS key field`
- `HDEL key field`
- `HKEYS`, `HVALS`, `HLEN`, `HMSET`

### 🧵 Multithreading
- Each client is handled in a separate thread using `std::thread`
- Shared database protected using `std::mutex` to avoid data races

### 💾 Persistence
- RDB-like custom persistence with periodic dumps to disk (every 300s)
- Supports `DUMP` and `LOAD` with mutex synchronization

### 📜 Parsing Protocol
- Partial RESP (REdis Serialization Protocol) parser implemented
- Falls back to whitespace parsing for simpler commands

### 📶 Signal Handling
- Graceful shutdown using `SIGINT` (Ctrl+C), saving state before exit

### 🧩 Architecture & Design
- Modular class-based design:
  - `RedisServer`
  - `RedisCommandHandler`
  - `RedisDatabase` (Singleton)
- Follows OOP principles and best practices

---

## 🛠️ Installation
This project uses a simple Makefile. Ensure you have a C++17 (or later) compiler.
- `make`
- `make clean`

```bash
# from project root
make
```

Or compile manually:
```bash
g++ -std=c++17 -pthread -Iinclude src/*.cpp -o my_redis_server
```

---

### 🔧 Requirements
- C++17 compatible compiler (e.g., `g++`, MSYS2 with `g++` and `make`)
- Git Bash or Linux Shell
- Redis CLI (optional, for testing)

### 📦 Build

```bash
# Clone the repository
git clone https://github.com/debesh008/Cpp-Redis-Server.git
cd redis



## 🧪 Usage

### ▶️ Start Server

```bash
./my_redis_server 8000
```

### 💬 Use redis-cli (must be installed)

```bash
redis-cli -p 8000
> PING
PONG
> SET mykey "Debesh"
OK
> GET mykey
Debesh
```

---

## 🔁 Test Script

```bash
chmod +x test.sh
bash test.sh
```

The script will:
- Clear the DB
- Run all supported commands
- Validate responses

---

## 📚 Concepts Demonstrated

- ✅ Socket Programming 
- ✅ Multithreading with `std::thread`
- ✅ Synchronization using `std::mutex`
- ✅ Singleton Pattern
- ✅ File handling with binary I/O
- ✅ Command parsing using `istringstream`, string streams
- ✅ Makefile-based build automation
- ✅ Signal handling with `SIGINT`
- ✅ Modular C++ design

---


## 📂 Project Structure

```
redis/
├── src/
│   ├── main.cpp
│   ├── RedisServer.cpp 
│   ├── RedisCommandHandler.cpp 
│   ├── RedisDatabase.cpp
│   ├── dump.my_rdb  # Auto-generated file
├── test.sh #shell script for automated testing of commands
├── Makefile
├── include/
│   ├── RedisServer.h
│   ├── RedisCommandHandler.h
│   ├── RedisDatabase.h
└── README.md
```

---


## Commands & Operations

---

### Common Commands

- **PING**  
  *Use case:* Before embarking on any data operations, an application can send a `PING` to ensure that the Redis server is alive and responsive—like knocking on a door before entering.

- **ECHO**  
  *Use case:* A debugging tool or simple utility to test network connectivity by having the server repeat a message. It can also be used in logging systems to trace commands.

- **FLUSHALL**  
  *Use case:* When resetting a cache or starting fresh, `FLUSHALL` clears all stored keys. This is useful during development or when you need to wipe out stale data completely.

---

### Key/Value Operations

- **SET**  
  *Use case:* Caching user session information or configuration settings. For example, store a user token with `SET session:123 "user_data"`.

- **GET**  
  *Use case:* Retrieve stored configuration or session data. For instance, fetch the user session with `GET session:123`.

- **KEYS**  
  *Use case:* List all keys or keys matching a pattern (e.g., `KEYS session:*`) to analyze cache usage or to perform maintenance tasks.

- **TYPE**  
  *Use case:* Check what type of value is stored at a key—useful when the data structure can vary, such as determining if a key holds a string, list, or hash.

- **DEL / UNLINK**  
  *Use case:* Remove keys that are no longer valid. This might be used to evict a stale cache entry after a user logs out or when cleaning up expired data.

- **EXPIRE**  
  *Use case:* Set a timeout on keys for caching. For example, cache product details for 3600 seconds so that the cache automatically evicts old data.

- **RENAME**  
  *Use case:* When restructuring keys during a migration or data reorganization, use `RENAME` to change the key’s name without losing its data.

---

### List Operations

- **LGET**  
  *Use case:* Returns all elements of a list at a given key (much like LRANGE key 0 -1 in real Redis).

- **LLEN**  
  *Use case:* Check the number of items in a message queue. For instance, determine how many tasks are pending in a job queue.

- **LPUSH / RPUSH**  
  *Use case:* Add items to a list. This is common in task queues or message brokers—`LPUSH` can be used to add a high-priority task at the beginning, while `RPUSH` appends regular tasks at the end.

- **LPOP / RPOP**  
  *Use case:* Remove items from a list. For example, dequeue a task from the beginning with `LPOP` or remove the last entry with `RPOP` in a double-ended queue.

- **LREM**  
  *Use case:* Remove specific elements from a list. For instance, eliminate duplicate notifications or remove a cancelled task from a list.

- **LINDEX**  
  *Use case:* Retrieve an element at a specific index. Useful when you need to inspect a particular item in a task queue without removing it.

- **LSET**  
  *Use case:* Update an element at a given position. This might be used in a real-time messaging app where you need to modify a message that is stored in a list.

---

### Hash Operations

- **HSET**  
  *Use case:* Store multiple fields for an object. For example, a user profile with `HSET user:1000 name "Alice" age "30" email "alice@example.com"`.

- **HGET**  
  *Use case:* Retrieve a specific field from a hash. For instance, fetching the email of a user with `HGET user:1000 email`.

- **HEXISTS**  
  *Use case:* Check if a particular field exists in a hash. For example, verify if a user profile has an "address" field.

- **HDEL**  
  *Use case:* Remove a field from a hash. Use it to delete outdated information, like removing a phone number when a user updates their profile.

- **HGETALL**  
  *Use case:* Retrieve all fields and values of a hash. This is useful when you need the full data set of an object, such as fetching an entire user profile.

- **HKEYS / HVALS**  
  *Use case:* List all fields (HKEYS) or all values (HVALS) in a hash, which is useful for displaying summary information or iterating through all data points in an object.

- **HLEN**  
  *Use case:* Determine the number of fields in a hash. For example, quickly checking how many attributes are stored in a user profile.

- **HMSET** 
  *Use case:* Set multiple fields in a hash at once. This can be useful for batch updates or initializing an object with several properties simultaneously.

---


