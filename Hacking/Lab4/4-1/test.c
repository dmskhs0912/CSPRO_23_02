#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_NAME_LEN 32

typedef struct item {
  char name[MAX_NAME_LEN]; // 32
  char *description; // 8
  int descr_len; // 4
  int price; // 4
  void (*print_info)(struct item *i);
} item;

typedef struct tv {
  char name[MAX_NAME_LEN]; // 32
  char *description; // 8
  int descr_len; // 4
  int price; // 4
  void (*print_info)(struct item *i); // 8
  char typ[8]; // 8
  size_t size; // 8
  int warranty; // 4
} tv;

typedef struct pc {
  char name[MAX_NAME_LEN]; // 32
  char *description; // 8
  int descr_len; // 4
  int price; // 4
  void (*print_info)(struct item *i); // 8
  char cpu[8]; // 8
  int ram; // 4
  int disk; // 4
} pc;

int main()
{
  item *i = (item*)malloc(56);
  printf("%p %p\n", i, i->name);
  return 0;
}