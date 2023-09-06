#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _s sizeof

typedef struct _node Node;
struct _node { int value; Node* next, * previous; };

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
    Node* start = Init(0, NULL, NULL);

    Insert(start, 56);
    Insert(start, 326);
    Insert(start, 56);

    Reverse(start);

    Print(start);
}

Node* Init(int value, Node* next, Node* previous) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = next;
    newNode->previous = previous;
    return newNode;
}

void _insert(Node* _src, Node* _new) {
    _new->next = _src->next;
    _new->previous = _src;

    if (_src->next) _src->next->previous = _new;
    _src->next = _new;
}

void InsertAt(Node* _node, int value, int offset) {
    Node* temp = _node;
    for (int i = 0; temp->next && (offset < 0 || i < offset); temp = temp->next, i++);
    _insert(temp, Init(value, NULL, NULL));
}

void Insert(Node* _node, int value) {
    InsertAt(_node, value, -1);
}

Node* FindValue(Node* _node, int val) {
    for (Node* temp = _node; temp; temp = temp->next) {
        if (temp->value == val) return temp;
    }
    return NULL;
}

Node* FindAt(Node* _node, int index) {
    if (index >= Length(_node)) return NULL;
    Node* temp = _node;
    for (int i = 0; i < index; i++) temp = temp->next;
    return temp;
}

void _delete(Node* _node) {
    if (_node->previous) _node->previous->next = _node->next;
    if (_node->next) _node->next->previous = _node->previous;
    free(_node);
}

void DeleteAt(Node* _node, int index) {
    Node* nodeToDelete = FindAt(_node, index);
    if (nodeToDelete) {
        _delete(nodeToDelete);
    }
}

void DeleteVal(Node* _node, int val) {
    Node* temp;
    while ((temp = FindValue(_node, val)) != NULL) {
        _delete(temp);
    }
}

void DeleteAll(Node* _node) {
    Node* temp;
    while (_node->next != NULL) {
        temp = _node->next;
        _delete(_node);
        _node = temp;
    }
}

int Length(Node* _node) {
    int length = 0;
    Node* temp = _node;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

void PrintNode(Node* _node) {
    printf("Address: %p\nValue: %d\nPrevious: %p\nNext: %p\n_________________________________\n", _node, _node->value, _node->previous, _node->next);
}

void Print(Node* _node) {
    for (Node* temp = _node; temp != NULL; temp = temp->next) {
        PrintNode(temp);
    }
}

void _swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Reverse(Node* _node) {
    Node* s, * e;
    for (s = e = _node; s->previous || e->next; s = s->previous ? s->previous : s, e = e->next ? e->next : e);
    int len = Length(s);
    if (len > 2 && len % 2) {
        for (; s != e; s = s->next, e = e->previous) {
            _swap(&s->value, &e->value);
        }
    } else if (len > 2 && len % 2 == 0) {
        for (; s->previous != e; s = s->next, e = e->previous) {
            _swap(&s->value, &e->value);
        }
    } else if (len == 2) {
        _swap(&s->value, &e->value);
    }
}
