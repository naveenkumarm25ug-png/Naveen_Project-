#include<stdio.h>
Person* create_person(const char *name, int age)
{
    Person *p = malloc(sizeof(Person));

    if (p == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy((*p).name, name);
    (*p).age = age;

    (*p).father = NULL;
    (*p).mother = NULL;

    return p;
}
```
