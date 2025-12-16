#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define func

typedef enum {
    Log_Level_Info,
    Log_Level_Error,
} Log_Level;

static inline void print_log(Log_Level level, char *fmt, char *filename, int line_number, ...) {
    char buf[1<<12];
    va_list args;
    va_start(args, line_number);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    switch (level) {
        case Log_Level_Info: {
            fprintf(stdout, "Info (%s:%d): %s\n", filename, line_number, buf);
        } break;
        case Log_Level_Error: {
            fprintf(stdout, "ERROR (%s:%d): %s\n", filename, line_number, buf);
        } break;
    }
}
#define print_error(str, ...) print_log(Log_Level_Error, str, __FILE__, __LINE__, ##__VA_ARGS__)
#define print_info(str, ...) print_log(Log_Level_Info, str, __FILE__, __LINE__, ##__VA_ARGS__)

#define array_count(x) ((sizeof(x)/sizeof(*(x))))

#define kabarr_max(a, b) ((a) > (b) ? (a) : (b))

#define KABARR_DEFAULT_CAPACITY 64
#define kabarr_grow(arr, expected_capacity)                                         \
    do {                                                                            \
        if (!(arr)->items) {                                                        \
            size_t count = kabarr_max(expected_capacity, KABARR_DEFAULT_CAPACITY);  \
            (arr)->items = malloc(count*sizeof(*(arr)->items));                     \
            assert((arr)->items);                                                   \
            (arr)->capacity = count;                                                \
        }                                                                           \
        if (expected_capacity > (arr)->capacity) {                                  \
            size_t new_capacity = kabarr_max(expected_capacity, 2*(arr)->capacity); \
            void *temp = realloc((arr)->items, new_capacity*sizeof(*(arr)->items)); \
            assert(temp);                                                           \
            (arr)->items = temp;                                                    \
            (arr)->capacity = new_capacity;                                         \
        }                                                                           \
    } while(0)

#define kabarr_append(arr, item) kabarr_append_many(arr, &(item), 1)

#define kabarr_append_many(arr, new_items, item_count)                      \
    do {                                                                    \
        kabarr_grow(arr, (arr)->count + item_count);                        \
        size_t items_size = (item_count)*sizeof(*(arr)->items);             \
        memcpy((arr)->items + (arr)->count, new_items, items_size);         \
        (arr)->count += item_count;                                         \
    } while(0)

#define kabarr_remove_unordered(arr, index)                                                     \
    do {                                                                                        \
        memcpy((arr)->items + index, (arr)->items + (arr)->count - 1, sizeof(*(arr)->items))    \
        --(arr)->count;                                                                         \
    } while(0)

#define kabarr_free(arr)                    \
    do {                                    \
        if ((arr)->items) {                 \
            free((arr)->items);             \
            memset(arr, 0, sizeof(*(arr))); \
        }                                   \
    } while(0)
