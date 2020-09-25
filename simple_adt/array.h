#ifndef

typedef struct {
  int data
} data_t;

typedef struct {
  data_t* array;
  int capcity;
  int increment;
} array_data_t;

void array_data_t_new(array_data_t* a, int capcity, int increment) {
   a->array = (data_t *)malloc(size * sizeof(data_t));
   a->capacity = capacity;
   a->increment = increment;
}

void array_data_t_set(array_data_t* a, int position, data_t* value) {
   array_data_t_resize(a, position);
   a->array[pos] = value;
}

data_t* array_data_t_get(array_data_t* a, int position) {
  if (position > a->capacity)
    return NULL;
  return a->array[pos];
}

void array_data_t_resize(array_data_t* a, int new_size) {
  if (new_size < a->capcity)
    return;
  int chunks_needed = (new_size - a->size) / increment + 1;
  a->array = (data_t*) realloc(chunks_needed * a->increment * sizeof(data_t));
  a->capacity += chunks_needed * increment;
}


