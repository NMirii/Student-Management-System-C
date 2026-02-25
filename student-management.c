#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct student_data
{
    int id;
    char name[50];
    char surname[50];
    int age;
} student;

int next_id = 1;

bool is_valid_name(const char *text)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)text[i]))
        {
            return false;
        }
    }
    return true;
}

bool is_valid_age(int age)
{
    if (age <= 0 || age > 120)
        return false;
    return true;
}

void add_part(student students[], int *count)
{
    students[*count].id = next_id++;

    while (1)
    {
        printf("Ad: ");
        scanf("%49s", students[*count].name);
        if (is_valid_name(students[*count].name))
        {
            break;
        }
        else
        {
            printf("Yanlış ad! Yalnız hərflərdən ibarət olmalıdır.\n");
        }
    }

    while (1)
    {
        printf("Soyad: ");
        scanf("%49s", students[*count].surname);
        if (is_valid_name(students[*count].surname))
        {
            break;
        }
        else
        {
            printf("Yanlış soyad! Yalnız hərflərdən ibarət olmalıdır.\n");
        }
    }
    while (1)
    {
        printf("Yaş: ");
        if (scanf("%d", &students[*count].age) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Yanlış giriş! Yalnız ədəd daxil edin.\n");
            continue;
        }

        if (is_valid_age(students[*count].age))
            break;

        printf("Yanlış yaş! Yalnız ədəd daxil edin.\n");
    }
    (*count)++;

    printf("Tələbə əlavə olundu! ID: %d\n", students[*count - 1].id);
}

void delete_part(student students[], int id, int *count)
{
    int found = -1;

    for (int i = 0; i < *count; i++)
    {
        if (students[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Bu ID ilə tələbə tapılmadı!\n");
        return;
    }

    for (int i = found; i < *count - 1; i++)
    {
        students[i] = students[i + 1];
    }
    (*count)--;

    printf("Tələbə (ID %d) silindi!\n", id);
}

void show_part(student students[], int count)
{
    if (count == 0)
    {
        printf("Siyahıda tələbə yoxdur!\n");
        return;
    }

    printf("-------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-20s | %-5s |\n", "ID", "Name", "Surname", "Age");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("| %-5d | %-20s | %-20s | %-5d |\n",
               students[i].id,
               students[i].name,
               students[i].surname,
               students[i].age);
    }

    printf("-------------------------------------------------------------------\n");
}

void update_part(student students[], int id, int count)
{
    int found = -1;

    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Bu ID ilə tələbə tapılmadı!\n");
        return;
    }

    while (1)
    {
        printf("Ad: ");
        scanf("%49s", students[found].name);
        if (is_valid_name(students[found].name))
        {
            break;
        }
        else
        {
            printf("Yanlış ad! Yalnız hərflərdən ibarət olmalıdır.\n");
        }
    }

    while (1)
    {
        printf("Soyad: ");
        scanf("%49s", students[found].surname);
        if (is_valid_name(students[found].surname))
        {
            break;
        }
        else
        {
            printf("Yanlış soyad! Yalnız hərflərdən ibarət olmalıdır.\n");
        }
    }
    while (1)
    {
        printf("Yaş: ");
        if (scanf("%d", &students[found].age) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Yanlış giriş! Yalnız ədəd daxil edin.\n");
            continue;
        }

        if (is_valid_age(students[found].age))
            break;

        printf("Yanlış yaş! Yalnız ədəd daxil edin.\n");
    }
    printf("Tələbə məlumatı uğurla yeniləndi!\n");
}

bool save_part(student students[], const char *filename, int count)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Fayl açıla bilmədi");
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%s,%d\n",
                students[i].id,
                students[i].name,
                students[i].surname,
                students[i].age);
    }

    fclose(file);
    return true;
}

bool load_part(student students[], const char *filename, int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        *count = 0;
        return true;
    }

    int idx = 0;
    int max_id = 0;

    while (1)
    {
        int id, age;
        char name[50], surname[50];
        int scan_count = fscanf(file, "%d,%49[^,],%49[^,],%d\n", &id, name, surname, &age);
        if (scan_count == EOF)
            break;
        if (scan_count != 4)
            continue;

        students[idx].id = id;
        strncpy(students[idx].name, name, sizeof(students[idx].name));
        students[idx].name[sizeof(students[idx].name) - 1] = '\0';
        strncpy(students[idx].surname, surname, sizeof(students[idx].surname));
        students[idx].surname[sizeof(students[idx].surname) - 1] = '\0';
        students[idx].age = age;

        if (id > max_id)
            max_id = id;

        idx++;
    }

    *count = idx;
    next_id = max_id + 1;
    if (next_id <= 1)
        next_id = 1;

    fclose(file);
    return true;
}

int main()
{
    student students[10000];
    int count = 0;
    int number;
    int id;

    load_part(students, "students.txt", &count);

    while (1)
    {
        printf("\n--- MENYU ---\n");
        printf("1. Tələbəni əlavə et\n");
        printf("2. Tələbəni sil\n");
        printf("3. Tələbənin məlumatlarını yenilə\n");
        printf("4. Tələbələri göstər\n");
        printf("5. Çıxış\n");
        printf("Seçim: ");
        int result = scanf("%d", &number);
        while ((result = scanf("%d", &number)) != 1 || number < 1 || number > 5)
        {
            if (result != 1)
            {
                while (getchar() != '\n')
                    ;
            }
            printf("Yanlış seçim! 1 ilə 5 arasında bir ədəd daxil edin: ");
        }
        switch (number)
        {
        case 1:
            add_part(students, &count);
            save_part(students, "students.txt", count);
            break;
        case 2:
            printf("Silinəcək tələbənin ID-si: ");
            scanf("%d", &id);
            delete_part(students, id, &count);
            save_part(students, "students.txt", count);
            break;
        case 3:
            printf("Yenilənəcək tələbənin ID-si: ");
            scanf("%d", &id);
            update_part(students, id, count);
            save_part(students, "students.txt", count);
            break;
        case 4:
            show_part(students, count);
            break;
        case 5:
            save_part(students, "students.txt", count);
            printf("Proqram bitdi!\n");
            return 0;
        default:
            printf("Yanlış seçim!\n");
        }
    }
}
