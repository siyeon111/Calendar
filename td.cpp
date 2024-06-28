
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// �ʿ��� ���̺귯���� �����մϴ�.

#include <stdio.h>

// �������� �Ǻ��ϴ� �Լ�
int is_leap_year(int year)
{
    // �������� ���θ� �Ǻ��մϴ�.
    // ���� ����: 1) year�� 0���� Ŀ�� �մϴ�.
    //           2) year�� 4�� ������ �������� �մϴ�.
    //           3) year�� 100���� ������ �������� �ʰų� 400���� ������ �������� �մϴ�.
    if ((year > 0) && !(year % 4) && ((year % 100) || !(year % 400)))
        return 1; // �����̸� 1�� ��ȯ�մϴ�.
    return 0; // ������ �ƴϸ� 0�� ��ȯ�մϴ�.
}

// AD 1�� 1�� 1�Ϻ��� year������ ���� ������ ����ϴ� �Լ�
int count_leaps(int year) {
    // year������ ���� ������ ����մϴ�.
    // 4�⸶�� ������ �߻��ϳ�, 100�� ����� ������ ���ܵǰ�, �ٽ� 400�� ����� ������ ���Ե˴ϴ�.
    return (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

// AD 1�� 1�� 1�Ϻ��� ������ �������� ����ϴ� �Լ�
int count_days(int year) {
    // year������ �� ���� ����մϴ�.
    // ������ ����Ͽ� 365�Ͽ� ���� ������ ���մϴ�.
    return (year - 1) * 365 + count_leaps(year);
}

// �� �� ���� ������ ��ȯ�ϴ� �Լ�
int count_years(int days) {
    // �־��� �� ���� �ش��ϴ� ������ ����մϴ�.
    // ���� ������ ����Ͽ� ������ ����մϴ�.
    return (1 + (days - count_leaps(days / 365)) / 365);
}

// Ư�� ������ ���� �� ���� ��ȯ�ϴ� �Լ�
int get_days_of_the_month(int year, int month) {
    // �� ���� �� ���� �����մϴ�.
    static int days_of_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int days = days_of_month[month - 1]; // �ش� ���� �� ���� �����ɴϴ�.

    // �����̸鼭 2���� ���, 1���� ���մϴ�.
    if (is_leap_year(year) && month == 2)
        days++;

    return days; // �ش� ������ ���� �� �� ���� ��ȯ�մϴ�.
}

// AD 1�� 1�� 1�Ϻ��� Ư�� ��¥������ �� �� ���� ��ȯ�ϴ� �Լ�
int get_total_days(int year, int month, int day) {
    int total_days = count_days(year); // �ش� ���� ���������� �� �� ���� �����ɴϴ�.

    // �ش� �� ���������� �� ���� ���մϴ�.
    for (int m = 1; m < month; ++m) {
        total_days += get_days_of_the_month(year, m);
    }

    total_days += day; // �ش� ��¥�� ���մϴ�.

    return total_days; // �� �� ���� ��ȯ�մϴ�.
}

// �־��� ��¥�� ������ ��ȯ�ϴ� �Լ�
int get_weekday(int year, int month, int day) {
    // Ư�� ��¥������ �� �� ���� 7�� ���� �������� ���Ϸ� ��ȯ�մϴ�.
    return get_total_days(year, month, day) % 7;
}

// �޷��� ����ϴ� �Լ�
void draw_calendar(int year, int month) {
    int days = get_days_of_the_month(year, month); // �ش� ���� �� ���� �����ɴϴ�.
    int day = 1 - get_weekday(year, month, 1); // �ش� ���� ù ���� ������ �����ɴϴ�.

    int i, end;

    // ������ ����մϴ�.
    printf("%6s%6s%6s%6s%6s%6s%6s\n", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat");
    printf("--------------------------------\n");

    end = days - day + 1; // ����� ��¥�� �������� ����մϴ�.
    // �ش� ���� �� ��¥�� ����մϴ�.
    for (i = 0; i < end; ++i) {
        if (day < 1)
            printf("%6s", " "); // ��¥�� 1���� ������ ������ ����մϴ�.
        else
            printf("%6d", day); // ��¥�� ����մϴ�.

        ++day; // ���� ���� �̵��մϴ�.

        if (i % 7 == 6)
            printf("\n"); // �� �ְ� ������ ���� �ٲߴϴ�.
    }
    printf("\n");
}

// ���� ���� Ŭ����

struct event {
    string date; // ������ ��¥�� �����ϴ� ����
    string description; // ������ ������ �����ϴ� ����
};

class Todo {
private:
    vector<event> events; // ������ �����ϴ� ����

public:
    // ������ �߰��ϴ� �޼���
    void addEvent(string date, string description) {
        event newevent = { date, description }; // ���ο� ���� ��ü�� �����մϴ�.
        events.push_back(newevent); // ������ ������ ���Ϳ� �߰��մϴ�.
        cout << "������ �߰��Ǿ����ϴ�." << endl; // �߰� �Ϸ� �޽����� ����մϴ�.
    }

    // ������ �����ϴ� �޼���
    void deleteEvent(int index) {
        // �ε����� ��ȿ���� Ȯ���մϴ�.
        if (index >= 0 && index < events.size()) {
            events.erase(events.begin() + index); // �ش� �ε����� ������ �����մϴ�.
            cout << "������ �����Ǿ����ϴ�." << endl; // ���� �Ϸ� �޽����� ����մϴ�.
        }
        else {
            cout << "�߸��� �ε����Դϴ�." << endl; // �߸��� �ε����� ��� ���� �޽����� ����մϴ�.
        }
    }

    // ������ ����ϴ� �޼���
    void displayEvents() {
        // ������ ��� �ִ��� Ȯ���մϴ�.
        if (events.empty()) {
            cout << "������ �����ϴ�." << endl; // ������ ��� ������ ������ ���ٴ� �޽����� ����մϴ�.
        }
        else {
            cout << "���� ���:" << endl; // ���� ��� ����� ����մϴ�.
            // ���� ������ �� ��Ҹ� ����մϴ�.
            for (int i = 0; i < events.size(); ++i) {
                cout << i + 1 << ". ��¥: " << events[i].date << ", ����: " << events[i].description << endl;
            }
        }
    }

    // �޷��� ����ϴ� �޼���
    void displayCalendar(int year, int month) {
        draw_calendar(year, month); // �ش� ������ ���� �ش��ϴ� �޷��� ����մϴ�.
    }
};

int main() {
    Todo manager; // ���� ���� ��ü�� �����մϴ�.
    int choice; // ����� ���� ������ �����մϴ�.
    string date, description; // �Է� ���� ��¥�� ���� ���� ������ �����մϴ�.

    // �޴��� �ݺ��ؼ� ǥ���մϴ�.
    while (true) {
        cout << "\n���� ���� ��" << endl; // �޴� ����� ����մϴ�.
        cout << "1. ���� �߰�" << endl; // ���� �߰� �޴��� ����մϴ�.
        cout << "2. ���� ����" << endl; // ���� ���� �޴��� ����մϴ�.
        cout << "3. ���� ��� ǥ��" << endl; // ���� ��� ǥ�� �޴��� ����մϴ�.
        cout << "4. ����" << endl; // ���� �޴��� ����մϴ�.
        cout << "����: "; // ���� �ȳ� �޽����� ����մϴ�.
        cin >> choice; // ����� �Է��� �޽��ϴ�.

        switch (choice) { // ������� ���ÿ� ���� �б��մϴ�.
        case 1: // ����ڰ� 1�� ������ ���
            cout << "��¥ �Է� (YYYY MM DD): "; // ��¥ �Է� �ȳ� �޽����� ����մϴ�.
            int year, month, day; // ����, ��, ���� ������ ������ �����մϴ�.
            int scanned_items; // ��ĵ�� �׸� ���� ������ ������ �����մϴ�.
            // ����ڰ� ��ȿ�� ��¥�� �Է��� ������ �ݺ��մϴ�.
            do {
                scanned_items = scanf_s("%d %d %d", &year, &month, &day); // ����, ��, ���� ��ĵ�մϴ�.
                // �Է��� �ùٸ��� ���� ��� �Ǵ� �ش� ��¥�� �������� �ʴ� ���
                if (scanned_items != 3 || year <= 0 || month < 1 || month > 12 || day < 1 || day > get_days_of_the_month(year, month)) {
                    cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl; // �߸��� �Է� �޽����� ����մϴ�.
                    while (getchar() != '\n'); // �Է� ���۸� ���ϴ�.
                }
            } while (scanned_items != 3 || year <= 0 || month < 1 || month > 12 || day < 1 || day > get_days_of_the_month(year, month));
            manager.displayCalendar(year, month); // �Է� ���� ������ ���� �ش��ϴ� �޷��� ����մϴ�.
            cout << "���� �Է�: "; // ���� �Է� �ȳ� �޽����� ����մϴ�.
            cin.ignore(); // �Է� ���۸� ���ϴ�.
            getline(cin, description); // ���� ������ �Է��մϴ�.
            manager.addEvent(to_string(year) + "-" + to_string(month) + "-" + to_string(day), description); // �Է� ���� ������ �߰��մϴ�.
            break; // switch ���� �����մϴ�.
        case 2: // ����ڰ� 2�� ������ ���
            int index; // ������ ������ �ε����� ������ ������ �����մϴ�.
            manager.displayEvents(); // ���� ���� ����� ����մϴ�.
            cout << "������ ���� ��ȣ �Է�: "; // ������ ���� ��ȣ �Է� �ȳ� �޽����� ����մϴ�.
            cin >> index; // ����ڰ� ������ ������ �ε����� �Է��մϴ�.
            manager.deleteEvent(index - 1); // �Է��� �ε����� �ش��ϴ� ������ �����մϴ�.
            break; // switch ���� �����մϴ�.
        case 3: // ����ڰ� 3�� ������ ���
            manager.displayEvents(); // ���� ���� ����� ����մϴ�.
            break; // switch ���� �����մϴ�.
        case 4: // ����ڰ� 4�� ������ ���
            cout << "���α׷��� �����մϴ�." << endl; // ���� �ȳ� �޽����� ����մϴ�.
            return 0; // ���α׷��� �����մϴ�.
        default: // �߸��� ������ ���
            cout << "�߸��� �����Դϴ�. �ٽ� �������ּ���." << endl; // �߸��� ���� �ȳ� �޽����� ����մϴ�.
        }
    }

    return 0; // ���α׷��� �����մϴ�.
}


