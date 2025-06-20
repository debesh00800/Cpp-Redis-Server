
#ifndef REDIS_DATABASE_H
#define REDIS_DATABASE_H
#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;

class RedisDatabase{
public:
    //get the singletob instance
    static RedisDatabase& getInstance();

    //persistane : dump and load the database from a file.
    mutex db_mutex;
    unordered_map<string,string> kv_store;
    unordered_map<string,vector<string>> list_store;
    unordered_map<string,unordered_map<string,string>> hash_store;
    unordered_map<string, chrono::steady_clock::time_point> expiry_map;

    bool dump(const string& filename);
    bool load(const string& filename);

    bool flushAll();

    // Key/Value Operations
    void set(const string& key, const string& value);
    bool get(const string& key, string& value);
    vector<string> keys();
    string type(const string& key);
    bool del(const string& key);
    bool expire(const string& key, int seconds);
      void purgeExpired();
    bool rename(const string& oldKey, const string& newKey);

    std::vector<std::string> lget(const std::string& key);
    ssize_t llen(const std::string& key);
    void lpush(const std::string& key, const std::string& value);
    void rpush(const std::string& key, const std::string& value);
    bool lpop(const std::string& key, std::string& value);
    bool rpop(const std::string& key, std::string& value);
    int lrem(const std::string& key, int count, const std::string& value);
    bool lindex(const std::string& key, int index, std::string& value);
    bool lset(const std::string& key, int index, const std::string& value);

    // Hash Operations
    bool hset(const std::string& key, const std::string& field, const std::string& value);
    bool hget(const std::string& key, const std::string& field, std::string& value);
    bool hexists(const std::string& key, const std::string& field);
    bool hdel(const std::string& key, const std::string& field);
    std::unordered_map<std::string, std::string> hgetall(const std::string& key);
    std::vector<std::string> hkeys(const std::string& key);
    std::vector<std::string> hvals(const std::string& key);
    ssize_t hlen(const std::string& key);
    bool hmset(const std::string& key, const std::vector<std::pair<std::string, std::string>>& fieldValues);

    private:
    RedisDatabase()=default;
    ~RedisDatabase()=default;
    RedisDatabase(const RedisDatabase&)=delete;
    RedisDatabase& operator=(const RedisDatabase&)=delete;

    



};

#endif