typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person *create_person(const char *name, int age);
void read_person_info(const char *role, char *name_out, int *age_out);
void link_parents(Person *child, Person *father, Person *mother);
void print_family_relationships(const Person *me);
void free_family_tree(Person *people[], int count);

Person *create_person(const char *name, int age)
{
    Person *person = malloc(sizeof(Person));

    if (person == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    snprintf(person->name, sizeof(person->name), "%s", name);
    person->age = age;
    person->father = NULL;
    person->mother = NULL;

    return person;
}

void read_person_info(const char *role, char *name_out, int *age_out)
{
    char line[100];
    char *end;
    long age;

    printf("Enter name for %s: ", role);
    if (fgets(name_out, 50, stdin) == NULL) {
        fprintf(stderr, "Error reading name.\n");
        exit(EXIT_FAILURE);
    }

    name_out[strcspn(name_out, "\n")] = '\0';

    printf("Enter age for %s: ", role);
    while (fgets(line, sizeof(line), stdin) != NULL) {
        age = strtol(line, &end, 10);

        while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
            end++;
        }

        if (end != line && *end == '\0' && age >= 0 && age <= 150) {
            *age_out = (int)age;
            return;
        }

        printf("Please enter a valid age (0-150): ");
    }

    fprintf(stderr, "Error reading age.\n");
    exit(EXIT_FAILURE);
}

void link_parents(Person *child, Person *father, Person *mother)
{
    if (child != NULL) {
        child->father = father;
        child->mother = mother;
    }
}
void print_family_relationships(const Person *me)
{
    if (me == NULL) {
        printf("Family tree is empty.\n");
        return;
    }

    printf("\n=== FAMILY TREE RELATIONSHIPS ===\n\n");
    printf("1. YOURSELF:\n");
    printf("   - Name: %s | Age: %d\n\n", me->name, me->age);

    printf("2. PARENTS:\n");
    if (me->father != NULL) {
        printf("   - Father: %s | Age: %d\n", me->father->name, me->father->age);
    } else {
        printf("   - Father: Unknown\n");
    }

    if (me->mother != NULL) {
        printf("   - Mother: %s | Age: %d\n\n", me->mother->name, me->mother->age);
    } else {
        printf("   - Mother: Unknown\n\n");
    }

    printf("3. PATERNAL GRANDPARENTS (via Father's relation):\n");
    if (me->father != NULL && me->father->father != NULL) {
        printf("   - Grandfather: %s | Age: %d\n",
               me->father->father->name, me->father->father->age);
    } else {
        printf("   - Grandfather: Unknown\n");
    }

    if (me->father != NULL && me->father->mother != NULL) {
        printf("   - Grandmother: %s | Age: %d\n\n",
               me->father->mother->name, me->father->mother->age);
    } else {
        printf("   - Grandmother: Unknown\n\n");
    }

    printf("4. MATERNAL GRANDPARENTS (via Mother's relation):\n");
    if (me->mother != NULL && me->mother->father != NULL) {
        printf("   - Grandfather: %s | Age: %d\n",
               me->mother->father->name, me->mother->father->age);
    } else {
        printf("   - Grandfather: Unknown\n");
    }

    if (me->mother != NULL && me->mother->mother != NULL) {
        printf("   - Grandmother: %s | Age: %d\n",
               me->mother->mother->name, me->mother->mother->age);
    } else {
        printf("   - Grandmother: Unknown\n");
    }
}
void free_family_tree(Person *people[], int count)
{
    int i;

    /* Free each allocated Person exactly once. */
    for (i = 0; i < count; i++) {
        free(people[i]);
        people[i] = NULL;
    }
}

