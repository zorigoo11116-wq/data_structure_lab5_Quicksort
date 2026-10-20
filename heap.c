#include "DS.h"

static void swim(Heap *p, int);
static void sink(Heap *p, int);

/*
  Хоёр зурвасын чухлыг харьцуулах функц.
  b нь илүү чухал бол 1, бусад үед 0-ыг буцаах функц.
  Өөрөөр хэлбэл a < b үйлдэл юм.
*/
int less(const Msg *a, const Msg *b)
{
        if (b->priority < a->priority) return 1;
        if (b->priority == a->priority && b->time < a->time) return 1;
        return 0;
}
void insert(Heap *p, const Msg x)
{
        p->h_arr[++p->h_len] = x;
        swim(p, p->h_len);
}
static void swim(Heap *p, int k)
{
        while (k > 1 && less(&p->h_arr[k / 2], &p->h_arr[k])) {
                Msg t = p->h_arr[k / 2];
                p->h_arr[k / 2] = p->h_arr[k];
                p->h_arr[k] = t;
                k /= 2;
        }
}
static void sink(Heap *p, int k)
{
        while (2 * k <= p->h_len) {
                int j = 2 * k;
                if (j < p->h_len && less(&p->h_arr[j], &p->h_arr[j + 1]))
                        j++;
                if (!less(&p->h_arr[k], &p->h_arr[j]))
                        break;
                Msg t = p->h_arr[k];
                p->h_arr[k] = p->h_arr[j];
                p->h_arr[j] = t;
                k = j;
        }
}
Msg delMin(Heap *p)
{
        Msg top;
        if (p->h_len == 0) {            /* хоосон heap: юу ч гаргахгүй */
                top.text[0] = '\0';
                top.priority = 0;
                top.time = -1;
                return top;
        }
        top = p->h_arr[1];
        p->h_arr[1] = p->h_arr[p->h_len--];
        sink(p, 1);
        return top;
}