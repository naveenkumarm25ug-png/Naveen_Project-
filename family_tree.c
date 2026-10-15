#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;


Person* create_person(const char *name, int age) {
    Person *p = (Person*) malloc(sizeof(Person));
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    p->age = age;
    p->father = NULL;
    p->mother = NULL;
    return p;
}


void read_person_info(const char *role, char *name_out, int *age_out) {
    printf("Enter details for %s:\n", role);
    printf("  Name: ");
    fgets(name_out, 50, stdin);
    
    name_out[strcspn(name_out, "\n")] = 0;

    printf("  Age: ");
    scanf("%d", age_out);
    
    
    while (getchar() != '\n');
    printf("\n");
}


int main() {
    char temp_name[50];
    int temp_age;
    Person *people[7];

   
    read_person_info("Paternal Grandfather", temp_name, &temp_age);
    people[0] = create_person(temp_name, temp_age);

    read_person_info("Paternal Grandmother", temp_name, &temp_age);
    people[1] = create_person(temp_name, temp_age);

    read_person_info("Maternal Grandfather", temp_name, &temp_age);
    people[2] = create_person(temp_name, temp_age);

    read_person_info("Maternal Grandmother", temp_name, &temp_age);
    people[3] = create_person(temp_name, temp_age);

    read_person_info("Father", temp_name, &temp_age);
    people[4] = create_person(temp_name, temp_age);

    read_person_info("Mother", temp_name, &temp_age);
    people[5] = create_person(temp_name, temp_age);

    read_person_info("Yourself", temp_name, &temp_age);
    people[6] = create_person(temp_name, temp_age);

    
    

    return 0;
}