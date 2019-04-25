#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct circular_buffer_t {
        int *ptr;
        int begin;
        int end;
        int capacity;
        unsigned char full:1;
}buffer;

int create(struct circular_buffer_t *cb, int N);
int create_circular_buffer(struct circular_buffer_t **cb, int N);
void destroy(struct circular_buffer_t *cb);
void destroy_circular_buffer(struct circular_buffer_t **cb);

int push_back(struct circular_buffer_t *cb, int value);
int pop_front(struct circular_buffer_t *cb, int *err_code);
int pop_back(struct circular_buffer_t *cb, int *err_code);
int empty(const struct circular_buffer_t *cb);
int full(const struct circular_buffer_t *cb);

void display(const struct circular_buffer_t *cb);

int create(struct circular_buffer_t *cb, int N)
{
    if(cb == NULL || N <= 0)
    {
        return 1;
    }

    if((cb->ptr = (int*) malloc(N*sizeof(int))) == NULL)
    {
        return 2;
    }

    cb->begin = 0;
    cb->end = 0;
    cb->capacity = N;
    cb->full = 0;

    return 0;
}

int create_circular_buffer(struct circular_buffer_t **cb, int N)        // KON
{
	if(cb == NULL || N <= 0)
	{
		return 1;
	}
	if((*cb = (struct circular_buffer_t*) malloc(sizeof(struct circular_buffer_t))) == NULL)
    {
        return 2;
    }

    if(create(*cb, N))
    {
        destroy_circular_buffer(cb);
        return 2;
    }

    (*cb)->begin = 0;
    (*cb)->end = 0;
    (*cb)->capacity = N;
    (*cb)->full = 0;

    return 0;
}

void destroy(struct circular_buffer_t *cb)                                 // KON
{
    if(cb != NULL && cb->ptr != NULL)
    {
        free(cb->ptr);
    }
}

void destroy_circular_buffer(struct circular_buffer_t **cb)
{
    if(cb == NULL)
    {
        return;
    }
    if((*cb)->ptr != NULL)
    {
        free((*cb)->ptr);
    }
        free(*cb);
}

int push_back(struct circular_buffer_t *cb, int value)
{
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0 || cb->ptr == NULL || (cb->end >= cb->capacity) || (cb->begin >= cb->capacity))
    {
        return 1;
    }

    if(cb->full != 0)
    {
        *(cb->ptr+cb->end) = value;
        cb->begin = (cb->begin + 1) % cb->capacity;     // zwiekszenie begin
        cb->end = (cb->end + 1) % cb->capacity;
        return 0;
    }

    *(cb->ptr+cb->end) = value;
    cb->end = (cb->end + 1) % cb->capacity;

    if(cb->begin == cb->end)
    {
        cb->full = 1;
    }

    return 0;
}

int pop_front(struct circular_buffer_t *cb, int *err_code)
{
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0 || cb->ptr == NULL || (cb->end >= cb->capacity) || (cb->begin >= cb->capacity))
    {
        if(err_code == NULL)
        {
            return 0;
        }
        *err_code = 1;
        return 0;
    }
    if(cb->full == 0 && (cb->begin == cb->end))
    {
        if(err_code == NULL)
        {
            return 1;
        }
        *err_code = 2;
        return 0;
    }

    int zwr = *(cb->ptr+cb->begin);

    cb->begin = (cb->begin + 1) % cb->capacity;

    cb->full = 0;

    if(err_code != NULL)
        *err_code = 0;
    return zwr;
}

int pop_back(struct circular_buffer_t *cb, int *err_code)
{
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0 || cb->ptr == NULL || (cb->end >= cb->capacity) || (cb->begin >= cb->capacity))
    {
        if(err_code == NULL)
        {
            return 0;
        }
        *err_code = 1;
        return 0;
    }
    if(cb->full == 0 && (cb->begin == cb->end))
    {
        if(err_code == NULL)
        {
            return 0;
        }
        *err_code = 2;
        return 0;
    }

    cb->end--;

    if(cb->end < 0)
        cb->end = cb->capacity-1;

    cb->full = 0;

    if(err_code != NULL)
        *err_code = 0;
    return *(cb->ptr+cb->end);
}

int empty(const struct circular_buffer_t *cb)                               // KON
{
    if(cb == NULL)
    {
        return -1;
    }

    if(cb->full == 0 && (cb->begin == cb->end))
    {
        return 1;
    }

    return 0;
}

int full(const struct circular_buffer_t *cb)                                // KON
{
    if(cb == NULL)
    {
        return -1;
    }

    return cb->full;
}

void display(const struct circular_buffer_t *cb)
{
    if(cb != NULL && !empty(cb) && cb->begin >= 0 && cb->end >= 0 && cb->capacity > 0 && cb->ptr != NULL && (cb->end < cb->capacity) && (cb->begin < cb->capacity))
    {
        int i;
        for(i = 0; ; i++)
        {
            if(((cb->begin+i+1) % cb->capacity) == cb->end)
                break;
            printf("%d ", *(cb->ptr+((cb->begin+i) % cb->capacity)));
        }
        printf("%d ", *(cb->ptr+((cb->begin+i) % cb->capacity)));
    }
}

int main(void)
{
	int N;
    int value_add = 0;
    int ret_create_cb = 0;

	printf("Podaj wielkosc bufora: ");
	scanf("%d", &N);

	if(N <= 0)
	{
		printf("Error");
		return 1;
	}

	struct circular_buffer_t *pbuffer = &buffer;

	if((ret_create_cb = create_circular_buffer(&pbuffer, N)) == 1)
    {
        printf("Error");
        return 1;
    }else if(ret_create_cb == 2)
    {
        printf("Failed to allocate memory");
        return 2;
    }

	int choice;
	int err_code = 0;
    int bufor;

	do
    {
        printf("Podaj, jaka operacje chcesz wykonac(0-6): ");
        scanf("%d", &choice);

        if(choice == 0);
        else if(choice == 1)
        {
            printf("Podaj wartosc, jaka ma zostac dodana: ");
            scanf("%d", &value_add);
            push_back(pbuffer, value_add);
        }else if(choice == 2)
        {
            bufor = pop_back(pbuffer, &err_code);
            if(err_code)
            {
                printf("Buffer is empty\n");
            }else
            {
                printf("%d\n", bufor);
            }
        }else if(choice == 3)
        {
            int bufor;
            bufor = pop_front(pbuffer, &err_code);
            if(err_code)
            {
                printf("Buffer is empty\n");
            }else
            {
                printf("%d\n", bufor);
            }
        }else if(choice == 4)
        {
            if(empty(pbuffer))
            {
                printf("Buffer is empty\n");
            }else
            {
                display(pbuffer);
                printf("\n");
            }
        }else if(choice == 5)
        {
            printf("%d\n", empty(pbuffer));
        }else if(choice == 6)
        {
            printf("%d\n", full(pbuffer));
        }else
        {
            printf("Incorrect input\n");
        }
    }while(choice);

    destroy_circular_buffer(&pbuffer);
	return 0;
}
