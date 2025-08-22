# Cache System for Proxy Servers  

This project implements a **cache system for proxy servers** in **C**, using **linked list structures** for efficient data storage and retrieval. The cache system improves data access speed by storing frequently requested media and managing cache size dynamically.  

## 📌 Features  
- **Cache Management**: Add and remove media files to/from the cache.  
- **Linked List Structure**: Cache entries and domain frequency lists are managed with doubly linked lists.  
- **Domain Frequency Tracking**: Each media keeps track of request frequencies per domain, sorted by frequency (and alphabetically for ties).  
- **Automatic Eviction**: When cache size exceeds the limit, the least recently used (LRU) media items are evicted.  
- **Search and Delete**: Find media in cache or remove it by name.  
- **Cache Information**: Print current cache status, including memory usage, media count, and domain request frequencies.  

## 📂 Project Structure  
```
├── main.c      # Example usage of the cache system
├── the3.c      # Implementation of cache functions
├── the3.h      # Header file with structures and function declarations
```

## ⚙️ Compilation & Run  

### Compile  
```bash
gcc main.c the3.c -o cache_system
```

### Run  
```bash
./cache_system < input.txt
```

- `input.txt` should include cache configuration and initial media information in the following format:  
  ```
  <cache_limit> <media_count>
  <media_name> <media_size> <domain1> <freq1> <domain2> <freq2> ...
  <media_name> <media_size> <domain1> <freq1> <domain2> <freq2> ...
  ```
  Example:
  ```
  1000 2
  video1 200 tr 5 en 2
  video2 400 tr 1 en 4
  ```

## 🛠 Example Usage  
`main.c` demonstrates how to:  
1. **Create a cache**  
2. **Add a new media request**  
3. **Delete media**  
4. **Print cache contents**  

Example (from `main.c`):  
```c
Cache* cache;
Media media1;

/* Create the cache */
cache = createCache();

/* Add new media */
media1.name = "newVideo";
media1.size = 300;
addMediaRequest(cache, media1, "tr");

/* Delete a media */
deleteMedia(cache, "video2");

/* Print cache status */
printCache(cache);
```

## 📖 Data Structures  
- **Cache**: Doubly linked list of `CacheNode` (media items).  
- **CacheNode**: Holds media information and a frequency list for domains.  
- **DomainFreqList**: Doubly linked list of domain frequency nodes.  
- **DomainFreqNode**: Stores request frequency of a media by domain.  

## 🚀 Future Improvements  
- Add support for different cache replacement policies (e.g., LFU, FIFO).  
- Implement persistence to save/load cache from files.  
- Optimize memory management and error handling.  
