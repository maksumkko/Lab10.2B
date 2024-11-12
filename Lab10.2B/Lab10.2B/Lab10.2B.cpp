#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "����������� ", "��������������", "����'����� �����", "����'������ ��������", "��������� ������������" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;

    union Grade {
        int grade_programming;  // for "����'����� �����"
        int grade_numerical_methods;  // for "�����������"
        int grade_pedagogy;  // for other specialties
    } grade_third;  // third grade depending on the speciality

    double average_grade() const {
        double total = grade_physics + grade_math;
        if (speciality == KN) {
            total += grade_third.grade_programming;
        }
        else if (speciality == ITIS) {
            total += grade_third.grade_numerical_methods;
        }
        else {
            total += grade_third.grade_pedagogy;
        }
        return total / 3.0;
    }
};

void Create(Students* S, const int N);
void count_good_grades(Students* S, int N, int& count_math, int& count_physics, int& count_info, int& count_physics_5);
void Print(Students* S, const int N);
void Print_students_without_threes(Students* S, const int N);
void sort_students(Students* S, int N);
int binary_search(const Students* S, int N, const string& surname, Speciality speciality, double average);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    sort_students(S, N);
    Print(S, N);

    int count_math = 0;
    int count_physics = 0;
    int count_info = 0;
    int count_physics_5 = 0;

    count_good_grades(S, N, count_math, count_physics, count_info, count_physics_5);

    cout << "ʳ������ ��������, �� �������� '5' � ������: " << count_physics_5 << endl;

    cout << "��������, �� ������� ��� ����� (�� '������' �� '�����'):" << endl;
    Print_students_without_threes(S, N);

    string search_surname;
    Speciality search_speciality;
    double search_average;

    cout << "������ ������� ��� ������: "; cin >> search_surname;
    cout << "������ ������������ (0 - �����������, 1 - ��������������, 2 - ����'����� �����, 3 - ����'������ ��������, 4 - ��������� ������������): ";
    int speciality_input;
    cin >> speciality_input;
    search_speciality = (Speciality)speciality_input;
    cout << "������ ������� ���: "; cin >> search_average;

    int index = binary_search(S, N, search_surname, search_speciality, search_average);

    if (index != -1) {
        cout << "������� ��������� �� �������: " << index + 1 << endl;
    }
    else {
        cout << "������� �� ���������." << endl;
    }

    delete[] S;
    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "����� ��������: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "�������: "; getline(cin, S[i].surname); cout << endl;
        cout << "����: "; cin >> S[i].course; cout << endl;
        cout << "������������(0 - �����������, 1 - ��������������, 2 - ����'����� �����," << endl;
        cout << "3 - ����'������ ��������, 4 - ��������� ������������): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "������ � ������: "; cin >> S[i].grade_physics; cout << endl;
        cout << "������ � ����������: "; cin >> S[i].grade_math; cout << endl;

        // Get the third grade based on speciality
        if (S[i].speciality == KN) {
            cout << "������ � �������������: "; cin >> S[i].grade_third.grade_programming; cout << endl;
        }
        else if (S[i].speciality == ITIS) {
            cout << "������ � ��������� ������: "; cin >> S[i].grade_third.grade_numerical_methods; cout << endl;
        }
        else {
            cout << "������ � ���������: "; cin >> S[i].grade_third.grade_pedagogy; cout << endl;
        }

        cout << endl;
    }
}

void count_good_grades(Students* S, int N, int& count_math, int& count_physics, int& count_info, int& count_physics_5)
{
    count_math = 0;
    count_physics = 0;
    count_info = 0;
    count_physics_5 = 0;

    for (int i = 0; i < N; i++) {
        if (S[i].grade_math == 4) {
            count_math++;
        }
        if (S[i].grade_physics == 4) {
            count_physics++;
        }
        if (S[i].speciality != KN && S[i].speciality != ITIS && S[i].grade_third.grade_pedagogy == 4) {
            count_info++;
        }
        if (S[i].grade_physics == 5) {
            count_physics_5++;
        }
    }
}

void Print(Students* S, const int N)
{
    cout << "==================================================================================================================" << endl;
    cout << "|  �  |   �������   |  ����  |     ������������     |  Գ����  |  ����������  |  �����������  |  ������� ���  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        double avg = S[i].average_grade();
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(10) << left << S[i].grade_physics;
        cout << "|" << setw(14) << left << S[i].grade_math;
        cout << "|" << setw(15) << left;

        if (S[i].speciality == KN) {
            cout << S[i].grade_third.grade_programming;
        }
        else if (S[i].speciality == ITIS) {
            cout << S[i].grade_third.grade_numerical_methods;
        }
        else {
            cout << S[i].grade_third.grade_pedagogy;
        }

        cout << "|" << setw(15) << left << fixed << setprecision(2) << avg << "|" << endl;
    }
    cout << "====================================================================================================================" << endl << endl;
}

void Print_students_without_threes(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        if (S[i].grade_physics > 3 && S[i].grade_math > 3 &&
            (S[i].speciality == KN ? S[i].grade_third.grade_programming > 3 :
        (S[i].speciality == ITIS ? S[i].grade_third.grade_numerical_methods > 3 :
        S[i].grade_third.grade_pedagogy > 3)))
        {
            cout << S[i].surname << endl;
        }
    }
}

void sort_students(Students* S, int N)
{
    sort(S, S + N, [](const Students& a, const Students& b) {
        if (a.speciality != b.speciality) {
            return a.speciality < b.speciality;
        }
        if (a.average_grade() != b.average_grade()) {
            return a.average_grade() > b.average_grade();
        }
        return a.surname < b.surname;
        });
}

int binary_search(const Students* S, int N, const string& surname, Speciality speciality, double average)
{
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        const Students& student = S[mid];

        if (student.speciality < speciality ||
            (student.speciality == speciality && student.average_grade() < average) ||
            (student.speciality == speciality && student.average_grade() == average && student.surname < surname)) {
            left = mid + 1;
        }
        else if (student.speciality > speciality ||
            (student.speciality == speciality && student.average_grade() > average) ||
            (student.speciality == speciality && student.average_grade() == average && student.surname > surname)) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1; // not found
}