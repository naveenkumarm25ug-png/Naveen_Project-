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

void link_parents(Person *child, Person *father, Person *mother){
    if (child != NULL){
        child->father = father;
        child->mother = mother;
    }
}

void print_family_relationships(const Person *me)
{
    if (me == NULL)
        return;

    printf("=== FAMILY TREE RELATIONSHIPS ===\n\n");

    printf("1. YOURSELF:\n");
    printf("   - Name: %s | Age: %d\n\n", me->name, me->age);

    printf("2. PARENTS:\n");

    if (me->father)
        printf("   - Father: %s | Age: %d\n", me->father->name, me->father->age);

    if (me->mother)
        printf("   - Mother: %s | Age: %d\n\n",   me->mother->name, me->mother->age);

    printf("3. PATERNAL GRANDPARENTS (via Father's Pointers):\n");

    if (me->father && me->father->father)
        printf("   - Grandfather: %s | Age: %d\n", me->father->father->name, me->father->father->age);

    if (me->father && me->father->mother)
        printf("   - Grandmother: %s | Age: %d\n\n", me->father->mother->name, me->father->mother->age);

    printf("4. MATERNAL GRANDPARENTS (via Mother's Pointers):\n");

    if (me->mother && me->mother->father)
        printf("   - Grandfather: %s | Age: %d\n", me->mother->father->name, me->mother->father->age);

    if (me->mother && me->mother->mother)
        printf("   - Grandmother: %s | Age: %d\n", me->mother->mother->name, me->mother->mother->age);
}

void print_tree_visual(const Person *me) {
    if (me == NULL) return;

    printf("=== VISUAL FAMILY TREE ===\n\n");
    printf("%s (Age: %d)\n", me->name, me->age);

    if (me->father) {
        printf(" ├── Father: %s (Age: %d)\n", me->father->name, me->father->age);
        if (me->father->father) {
            printf(" │   ├── Grandfather: %s (Age: %d)\n", me->father->father->name, me->father->father->age);
        }
        if (me->father->mother) {
            printf(" │   └── Grandmother: %s (Age: %d)\n", me->father->mother->name, me->father->mother->age);
        }
    }

    if (me->mother) {
        printf(" └── Mother: %s (Age: %d)\n", me->mother->name, me->mother->age);
        if (me->mother->father) {
            printf("     ├── Grandfather: %s (Age: %d)\n", me->mother->father->name, me->mother->father->age);
        }
        if (me->mother->mother) {
            printf("     └── Grandmother: %s (Age: %d)\n", me->mother->mother->name, me->mother->mother->age);
        }
    }
}

void free_family_tree(Person *people[], int count){
    for(int i=0; i<count; i++){
        if(people[i] != NULL){
            free(people[i]);
            people[i] = NULL;
        }
    }
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

    link_parents(people[4], people[0], people[1]);
    link_parents(people[5], people[2], people[3]);
    link_parents(people[6], people[4], people[5]);

    print_family_relationships(people[6]);
    print_tree_visual(people[6]);
    free_family_tree(people, 7);

    return 0;
}