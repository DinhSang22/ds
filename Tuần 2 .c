#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#define _s sizeof

typedef struct _node Node;
struct _node { int value; Node* next, * preivous; };

Node* Init(int value, Node* next, Node* previous);

void _insert(Node* _src, Node* _new);
void Insert(Node* _node, int value);
void InsertAt(Node* _node, int value, int offset);

Node* FindValue(Node* _node, int val);
Node* FindAt(Node* _node, int index);

void _delete(Node* _node);
void DeleteAt(Node* _node, int index);
void DeleteVal(Node* _node, int val);
void DeleteAll(Node* _node);

int Length(Node* _node);
void PrintNode(Node* _node);
void Print(Node* _node);

void _swap(int* a, int* b);
void Reverse(Node* _node);

int main() {
    Node* start = Init(0, 0, 0);

    Insert(start, 56);
    Insert(start, 326);
    Insert(start, 56);

    Reverse(start);

    Print(start);
}

// Khoi tao phan tu
Node* Init(int value, Node* next, Node* previous) { return memcpy(malloc(_s(Node)), &(Node) { value, next, previous }, _s(Node)); }

// Them phan tu
void _insert(Node* _src, Node* _new) {
    _new->next = _src->next, _new->preivous = _src;

    if (_src->next) _src->next->preivous = _new;
    _src->next = _new;
}
void InsertAt(Node* _node, int value, int offset) {
    Node* temp = _node;
    for (int i = 0;temp->next && (offset < 0 || i < offset); temp = temp->next, i++);
    _insert(temp, Init(value, 0, 0));
}
void Insert(Node* _node, int value) { InsertAt(_node, value, -1); }

// Lay phan tu
Node* FindValue(Node* _node, int val) {
    for (Node* temp = _node;temp;temp = temp->next) if (temp->value == val) return temp;
    return NULL;
}
Node* FindAt(Node* _node, int index) {
    if (index > Length(_node)) return NULL;
    Node* temp = _node;
    for (int i = 0; i < index;i++) temp = temp->next;
    return temp;
}

// Xoa phan tu
void _delete(Node* _node) {
    if (_node->preivous) _node->preivous->next = _node->next;
    if (_node->next) _node->next->preivous = _node->preivous;
    free(_node);
}
void DeleteAt(Node* _node, int index) { _delete(FindAt(_node, index)); }
void DeleteVal(Node* _node, int val) { for (Node* temp = FindValue(_node, val);temp != NULL;temp = FindValue(_node, val)) _delete(temp); }
void DeleteAll(Node* _node) {
    for (Node* i = _node, *j = _node->next;i;i = j) {
        j = j->next;
        free(i);
    }
    _node = Init(0, 0, 0);
}

// Lay kich thuoc
int Length(Node* _node) {
    int i = 0;
    for (Node* temp = _node; temp; temp = temp->next, i++);
    return i;
}

// In danh sach lien ket
void PrintNode(Node* _node) { printf("Address: %p\nValue: %d\nPrevious: %p\nNext: %p\n_________________________________\n", _node, _node->value, _node->preivous, _node->next); }
void Print(Node* _node) { for (Node* temp = _node;temp;temp = temp->next) PrintNode(temp); }

// Dao nguoc
void _swap(int* a, int* b) { int z = *a; *a = *b, * b = z; }
void Reverse(Node* _node) {
    Node* s, * e;
    for (s = e = _node; s->preivous || e->next; s = s->preivous ? s->preivous : s, e = e->next ? e->next : e);
    int len = Length(s);
    if (len > 2 && len % 2) for (;s != e;s = s->next, e = e->preivous) _swap(&s->value, &e->value);
    else if (len > 2 && len % 2 == 0) for (;s->preivous != e;s = s->next, e = e->preivous) _swap(&s->value, &e->value);
    else if (len == 2) _swap(&s->value, &e->value);
}