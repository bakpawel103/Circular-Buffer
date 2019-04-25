# Circular-Buffer

Functions: <br>
  - int create(struct circular_buffer_t *cb, int N); <br>
  - int create_circular_buffer(struct circular_buffer_t **cb, int N); <br>
  - void destroy(struct circular_buffer_t *cb); <br>
  - void destroy_circular_buffer(struct circular_buffer_t **cb); <br><br>
  - int push_back(struct circular_buffer_t *cb, int value); <br>
  - int pop_front(struct circular_buffer_t *cb, int *err_code); <br>
  - int pop_back(struct circular_buffer_t *cb, int *err_code); <br>
  - int empty(const struct circular_buffer_t *cb); <br>
  - int full(const struct circular_buffer_t *cb); <br><br>
  - void display(const struct circular_buffer_t *cb); <br>
