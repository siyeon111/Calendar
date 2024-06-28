
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 필요한 라이브러리를 포함합니다.

#include <stdio.h>

// 윤년인지 판별하는 함수
int is_leap_year(int year)
{
    // 윤년인지 여부를 판별합니다.
    // 윤년 조건: 1) year가 0보다 커야 합니다.
    //           2) year가 4로 나누어 떨어져야 합니다.
    //           3) year가 100으로 나누어 떨어지지 않거나 400으로 나누어 떨어져야 합니다.
    if ((year > 0) && !(year % 4) && ((year % 100) || !(year % 400)))
        return 1; // 윤년이면 1을 반환합니다.
    return 0; // 윤년이 아니면 0을 반환합니다.
}

// AD 1년 1월 1일부터 year까지의 윤년 개수를 계산하는 함수
int count_leaps(int year) {
    // year까지의 윤년 개수를 계산합니다.
    // 4년마다 윤년이 발생하나, 100의 배수인 연도는 제외되고, 다시 400의 배수인 연도는 포함됩니다.
    return (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

// AD 1년 1월 1일부터 몇일이 지났는지 계산하는 함수
int count_days(int year) {
    // year까지의 일 수를 계산합니다.
    // 윤년을 고려하여 365일에 윤년 개수를 더합니다.
    return (year - 1) * 365 + count_leaps(year);
}

// 총 일 수를 연도로 변환하는 함수
int count_years(int days) {
    // 주어진 일 수에 해당하는 연도를 계산합니다.
    // 윤년 개수를 고려하여 연도를 계산합니다.
    return (1 + (days - count_leaps(days / 365)) / 365);
}

// 특정 연도와 월의 일 수를 반환하는 함수
int get_days_of_the_month(int year, int month) {
    // 각 월의 일 수를 정의합니다.
    static int days_of_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int days = days_of_month[month - 1]; // 해당 월의 일 수를 가져옵니다.

    // 윤년이면서 2월인 경우, 1일을 더합니다.
    if (is_leap_year(year) && month == 2)
        days++;

    return days; // 해당 연도와 월의 총 일 수를 반환합니다.
}

// AD 1년 1월 1일부터 특정 날짜까지의 총 일 수를 반환하는 함수
int get_total_days(int year, int month, int day) {
    int total_days = count_days(year); // 해당 연도 이전까지의 총 일 수를 가져옵니다.

    // 해당 월 이전까지의 일 수를 더합니다.
    for (int m = 1; m < month; ++m) {
        total_days += get_days_of_the_month(year, m);
    }

    total_days += day; // 해당 날짜를 더합니다.

    return total_days; // 총 일 수를 반환합니다.
}

// 주어진 날짜의 요일을 반환하는 함수
int get_weekday(int year, int month, int day) {
    // 특정 날짜까지의 총 일 수를 7로 나눈 나머지를 요일로 반환합니다.
    return get_total_days(year, month, day) % 7;
}

// 달력을 출력하는 함수
void draw_calendar(int year, int month) {
    int days = get_days_of_the_month(year, month); // 해당 월의 일 수를 가져옵니다.
    int day = 1 - get_weekday(year, month, 1); // 해당 월의 첫 날의 요일을 가져옵니다.

    int i, end;

    // 요일을 출력합니다.
    printf("%6s%6s%6s%6s%6s%6s%6s\n", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat");
    printf("--------------------------------\n");

    end = days - day + 1; // 출력할 날짜의 마지막을 계산합니다.
    // 해당 월의 각 날짜를 출력합니다.
    for (i = 0; i < end; ++i) {
        if (day < 1)
            printf("%6s", " "); // 날짜가 1보다 작으면 공백을 출력합니다.
        else
            printf("%6d", day); // 날짜를 출력합니다.

        ++day; // 다음 날로 이동합니다.

        if (i % 7 == 6)
            printf("\n"); // 한 주가 끝나면 줄을 바꿉니다.
    }
    printf("\n");
}

// 일정 관리 클래스

struct event {
    string date; // 일정의 날짜를 저장하는 변수
    string description; // 일정의 설명을 저장하는 변수
};

class Todo {
private:
    vector<event> events; // 일정을 저장하는 벡터

public:
    // 일정을 추가하는 메서드
    void addEvent(string date, string description) {
        event newevent = { date, description }; // 새로운 일정 객체를 생성합니다.
        events.push_back(newevent); // 생성한 일정을 벡터에 추가합니다.
        cout << "일정이 추가되었습니다." << endl; // 추가 완료 메시지를 출력합니다.
    }

    // 일정을 삭제하는 메서드
    void deleteEvent(int index) {
        // 인덱스가 유효한지 확인합니다.
        if (index >= 0 && index < events.size()) {
            events.erase(events.begin() + index); // 해당 인덱스의 일정을 삭제합니다.
            cout << "일정이 삭제되었습니다." << endl; // 삭제 완료 메시지를 출력합니다.
        }
        else {
            cout << "잘못된 인덱스입니다." << endl; // 잘못된 인덱스일 경우 오류 메시지를 출력합니다.
        }
    }

    // 일정을 출력하는 메서드
    void displayEvents() {
        // 일정이 비어 있는지 확인합니다.
        if (events.empty()) {
            cout << "일정이 없습니다." << endl; // 일정이 비어 있으면 일정이 없다는 메시지를 출력합니다.
        }
        else {
            cout << "일정 목록:" << endl; // 일정 목록 헤더를 출력합니다.
            // 일정 벡터의 각 요소를 출력합니다.
            for (int i = 0; i < events.size(); ++i) {
                cout << i + 1 << ". 날짜: " << events[i].date << ", 일정: " << events[i].description << endl;
            }
        }
    }

    // 달력을 출력하는 메서드
    void displayCalendar(int year, int month) {
        draw_calendar(year, month); // 해당 연도와 월에 해당하는 달력을 출력합니다.
    }
};

int main() {
    Todo manager; // 일정 관리 객체를 생성합니다.
    int choice; // 사용자 선택 변수를 선언합니다.
    string date, description; // 입력 받을 날짜와 일정 설명 변수를 선언합니다.

    // 메뉴를 반복해서 표시합니다.
    while (true) {
        cout << "\n일정 관리 앱" << endl; // 메뉴 헤더를 출력합니다.
        cout << "1. 일정 추가" << endl; // 일정 추가 메뉴를 출력합니다.
        cout << "2. 일정 삭제" << endl; // 일정 삭제 메뉴를 출력합니다.
        cout << "3. 일정 목록 표시" << endl; // 일정 목록 표시 메뉴를 출력합니다.
        cout << "4. 종료" << endl; // 종료 메뉴를 출력합니다.
        cout << "선택: "; // 선택 안내 메시지를 출력합니다.
        cin >> choice; // 사용자 입력을 받습니다.

        switch (choice) { // 사용자의 선택에 따라 분기합니다.
        case 1: // 사용자가 1을 선택한 경우
            cout << "날짜 입력 (YYYY MM DD): "; // 날짜 입력 안내 메시지를 출력합니다.
            int year, month, day; // 연도, 월, 일을 저장할 변수를 선언합니다.
            int scanned_items; // 스캔된 항목 수를 저장할 변수를 선언합니다.
            // 사용자가 유효한 날짜를 입력할 때까지 반복합니다.
            do {
                scanned_items = scanf_s("%d %d %d", &year, &month, &day); // 연도, 월, 일을 스캔합니다.
                // 입력이 올바르지 않은 경우 또는 해당 날짜가 존재하지 않는 경우
                if (scanned_items != 3 || year <= 0 || month < 1 || month > 12 || day < 1 || day > get_days_of_the_month(year, month)) {
                    cout << "잘못된 입력입니다. 다시 입력해주세요." << endl; // 잘못된 입력 메시지를 출력합니다.
                    while (getchar() != '\n'); // 입력 버퍼를 비웁니다.
                }
            } while (scanned_items != 3 || year <= 0 || month < 1 || month > 12 || day < 1 || day > get_days_of_the_month(year, month));
            manager.displayCalendar(year, month); // 입력 받은 연도와 월에 해당하는 달력을 출력합니다.
            cout << "일정 입력: "; // 일정 입력 안내 메시지를 출력합니다.
            cin.ignore(); // 입력 버퍼를 비웁니다.
            getline(cin, description); // 일정 설명을 입력합니다.
            manager.addEvent(to_string(year) + "-" + to_string(month) + "-" + to_string(day), description); // 입력 받은 일정을 추가합니다.
            break; // switch 문을 종료합니다.
        case 2: // 사용자가 2를 선택한 경우
            int index; // 삭제할 일정의 인덱스를 저장할 변수를 선언합니다.
            manager.displayEvents(); // 현재 일정 목록을 출력합니다.
            cout << "삭제할 일정 번호 입력: "; // 삭제할 일정 번호 입력 안내 메시지를 출력합니다.
            cin >> index; // 사용자가 삭제할 일정의 인덱스를 입력합니다.
            manager.deleteEvent(index - 1); // 입력한 인덱스에 해당하는 일정을 삭제합니다.
            break; // switch 문을 종료합니다.
        case 3: // 사용자가 3을 선택한 경우
            manager.displayEvents(); // 현재 일정 목록을 출력합니다.
            break; // switch 문을 종료합니다.
        case 4: // 사용자가 4를 선택한 경우
            cout << "프로그램을 종료합니다." << endl; // 종료 안내 메시지를 출력합니다.
            return 0; // 프로그램을 종료합니다.
        default: // 잘못된 선택인 경우
            cout << "잘못된 선택입니다. 다시 선택해주세요." << endl; // 잘못된 선택 안내 메시지를 출력합니다.
        }
    }

    return 0; // 프로그램을 종료합니다.
}


