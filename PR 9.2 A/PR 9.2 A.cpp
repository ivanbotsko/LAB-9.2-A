#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Speciality { CS, INF, ME, PI, TN };
string specialityStr[] = { "Комп'ютерні науки", "Інформатика", "Механіка і енергетика", "Програмна інженерія", "Технології наносистем" };

struct Student {
    string surname;
    unsigned course;
    Speciality speciality;
    int physics;
    int math;
    int informatics;
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N:  "; cin >> N;
    int menuItem;
    int idx;
    string surname;
    unsigned course;
    double avgGrade;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    do {
        cout << endl << endl << endl;
        cout << "Оберіть опцію:" << endl << endl;
        cout << " [1] - Вивести список студентів" << endl;
        cout << " [2] - Відсортувати за середнім балом" << endl;
        cout << " [3] - Вивести відсортований список" << endl;
        cout << " [4] - Пошук студента" << endl;
        cout << " [0] - Вийти з програми" << endl << endl;
        cout << "Введіть номер опції:"; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Print(s, N);
            break;
        case 2:
            Sort(s, N);
            Print(s, N);
            break;
        case 3:
            IndexSort(s, N);
            PrintIndexSorted(s, IndexSort(s, N), N);
            break;
        case 4:

            cout << "Введіть прізвище студента: "; cin >> surname;
            cout << "Введіть курс: "; cin >> course;
            cout << "Введіть середній бал: "; cin >> avgGrade;

            idx = BinSearch(s, N, surname, course, avgGrade);
            if (idx != -1)
                cout << "Студент " << surname << " знайдений на " << course << " курсі." << endl;
            else
                cout << "Студент " << surname << " не знайдений на " << course << " курсі." << endl;
            break;
        case 0:
            break;
        default:
            cout << "Некоректний ввід! "
                "Будь ласка, введіть коректний номер опції" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(Student* s, const int N) {
    int speciality;
    for (int i = 0; i < N; i++) {
        cout << "Введіть дані " << i + 1 << " - го студента : " << endl;
        cin.get(); // очистка буфера вводу для коректного зчитування рядка
        cin.sync(); // "скидання" стану, щоб уникнути зависання вводу

        cout << " Прізвище: "; getline(cin, s[i].surname);
        cout << " Курс: "; cin >> s[i].course;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Механіка і енергетика, 3 - Програмна інженерія, 4 - Технології наносистем): ";
        cin >> speciality;
        s[i].speciality = (Speciality)speciality;
        cout << " Оцінка з фізики: "; cin >> s[i].physics;
        cout << " Оцінка з математики: "; cin >> s[i].math;
        cout << " Оцінка з інформатики: "; cin >> s[i].informatics;
        cout << endl;
    }
}

void Print(Student* s, const int N) {
    cout << "====================================================================================================" << endl;
    cout << "| " << setw(2) << "№" << " |" << setw(15) <<  "Прізвище" << " |" << setw(6) << "Курс" << " |" << setw(25) << "Спеціальність"  << " |" << setw(8) << "Фізика" << " |" << setw(13) << "Математика" << " |" << setw(15) << "Інформатика" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[i].surname
            << "| " << setw(5) << s[i].course << " "
            << "| " << setw(25) << specialityStr[s[i].speciality]
            << "| " << setw(8) << s[i].physics
            << "| " << setw(12) << s[i].math << " "
            << "| " << setw(15) << s[i].informatics << " |" << endl;
    }
    cout << "====================================================================================================" << endl;
    cout << endl;
}

void Sort(Student* s, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((s[i1].course > s[i1 + 1].course)
                || (s[i1].course == s[i1 + 1].course && s[i1].physics + s[i1].math + s[i1].informatics > s[i1 + 1].physics + s[i1 + 1].math + s[i1 + 1].informatics)
                || (s[i1].course == s[i1 + 1].course && s[i1].physics + s[i1].math + s[i1].informatics == s[i1 + 1].physics + s[i1 + 1].math + s[i1 + 1].informatics && s[i1].surname < s[i1 + 1].surname)) {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
}

int* IndexSort(Student* s, const int N) {
    int* I = new int[N]; // Зберігаємо індекси масиву
    for (int i = 0; i < N; i++)
        I[i] = i; // Ініціалізуємо індекси початковими значеннями

    // Сортування індексів масиву
    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;

        // Порівнюємо значення з елементами, що передують
        while (j >= 0 && (
            s[I[j]].course > s[value].course ||
            (s[I[j]].course == s[value].course &&
                s[I[j]].physics + s[I[j]].math + s[I[j]].informatics > s[value].physics + s[value].math + s[value].informatics ||
                (s[I[j]].course == s[value].course &&
                    s[I[j]].physics + s[I[j]].math + s[I[j]].informatics == s[value].physics + s[value].math + s[value].informatics &&
                    s[I[j]].surname > s[value].surname)
                ))) {
            I[j + 1] = I[j];
            j--;
        }

        I[j + 1] = value;
    }

    return I;
}

void PrintIndexSorted(Student* s, int* I, const int N) {
    cout << "====================================================================================================" << endl;
    cout << "| " << setw(2) << "№" << " |" << setw(15) << "Прізвище"  << " |" << setw(6) << "Курс" << " |" << setw(25) << "Спеціальність"  << " |" << setw(8) << "Фізика" << " |" << setw(13) << "Математика" << " |" << setw(15) << "Інформатика" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[I[i]].surname
            << "| " << setw(5) << s[I[i]].course << " "
            << "| " << setw(25) << specialityStr[s[I[i]].speciality]
            << "| " << setw(8) << s[I[i]].physics
            << "| " << setw(12) << s[I[i]].math << " "
            << "| " << setw(15) << s[I[i]].informatics << " |" << endl;
    }
    cout << "====================================================================================================" << endl;
    cout << endl;
    cout << "====================================================================================================" << endl;
    cout << endl;
}

int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        double avg = (s[m].physics + s[m].math + s[m].informatics) / 3.0;
        if (s[m].surname == surname && s[m].course == course && avg == avgGrade)
            return m;
        if ((s[m].surname < surname)
            || (s[m].surname == surname && s[m].course < course)
            || (s[m].surname == surname && s[m].course == course && avg < avgGrade)) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
