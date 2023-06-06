#include <cmath>

using namespace std;

int Hope = 0;
struct Stack{
    double number;
    char znac;
    Stack* next;
};
Stack *top1, *top2;

void push(Stack * & t, double numb, char zn) {
    Stack *p = (Stack*)malloc(sizeof(Stack));
    (*p).number = numb;
    (*p).znac = zn;
    (*p).next = t;
    t = p;
}

Stack pop(Stack * &t) {
    Stack a = (*t);
    t = (*t).next;
    return a;
}

int priority(char ch) {
    if (ch == '+' || ch == '-') {
        return 1;
    }
    if (ch == '*' || ch == '/') {
        return 2;
    }
    if (ch == '(') {
        return 0;
    }
    if (ch == '^') {
        return 3;
    }
    if (ch == 'S' || ch == 'C' || ch == 'T' || ch == 'K' || ch == 'L') {
        return 5;
    }
}
void apply(char znac) {
    double num1 = pop(top1).number;
    double num2;
    if (znac == '-' || znac == '+'|| znac == '*' || znac == '/' || znac == '^') {
        num2 = pop(top1).number;
        }
    double c;
    if (znac == '+') {
        c = num1 + num2;
    }
    if (znac == '-') {
        c = num2 - num1;
    }
    if (znac == '*') {
        c = num1 * num2;
    }
    if (znac == '/') {
        if (abs(num1) < 0.00001) {
            Hope ++;
        }
        c = num2 / num1;
    }
    if (znac == 'S') {
        c = sin(num1);
    }
    if (znac == 'C') {
        c = cos(num1);
    }
    if (znac == 'T') {
        c = tan(num1);
    }
    if (znac == '^') {
        c = pow(num2, num1);
    }
    if (znac == 'K') {
        if (num1 < 0) {
            Hope ++;
        }
        c = sqrt(num1);
    }
    if (znac == 'L') {
        if (num1 <= 0) {
            Hope ++;
        }
        c = log(num1);
    }
    push(top1, c, '@');
}

void replace_all(string & plot, string want, string word) {
    int pos = plot.find(word);
    while (pos != string::npos) {
        plot.replace(pos, word.size() , want);
        pos = plot.find(word);
        }
    }

int calc(string S, double & ans) {
    string SS;
    int balance = 0;
    for (int j = 0; j < S.size(); j++) {
        // кол-во скобок
        if (S[j] == '(') {
            balance = balance + 1;
        }
        if (S[j] == ')') {
            balance = balance - 1;
        }
        if (balance < 0) {
            return -1;
        }
    }
    if (balance != 0) {
        return -1;
    }
    for (int j = 0; j < S.size() - 1; j++) {
       // скобка и знак стоят в упор ВНИМАНИЕ ВОЗМОЖНО НЕ РАБОТАЕТ СО СТЕПЕНЯМИ
        if (((S[j] == '(') && (S[j + 1] == '/' || S[j + 1] == '*')) ||
           ((S[j] == '*' || S[j] == '/') && S[j + 1] == ')') || ((S[j + 1] == ')')
           && (S[j] == '+' || S[j] == '-' || S[j] == '^'))) {
            return -1;
            }
    }
    // деление на ноль
   /*
    for (int j = 0; j < S.size() - 1; j++) {
        if ((S[j] == '/') && (S[j + 1] == '0')) {
            return -1;
        }
    }
    */
    for (int j = 0; j < (S.size() - 1); j++) {
       // знак и знак стоят в упор
        if ((S[j] == '+' || S[j] == '-' || S[j] == '*' || S[j] == '/') &&
        ((S[j + 1] == '+' || S[j + 1] == '-' || S[j + 1] == '*' || S[j + 1] == '/'))) {
            return -1;
            }
    }
    for (int j = 0; j < (S.size() - 1); j++) {
       // Тоже самое но для степеней
        if ((S[j] == '^') &&
        ((S[j + 1] == '+' || S[j + 1] == '*' || S[j + 1] == '/' || S[j + 1] == '-'))) {
            return -1;
            }
    }
    for (int j = 0; j < (S.size() - 1); j++) {
        if (S[j] == '/' && S[j+1] == '^') {
            return -1;
            }
    }
    // начало или конец строки это знак
    if (S[0] == '*' || S[0] == '/' || S[0] == '^' || S[S.size() - 1] == '*'
    || S[S.size() - 1] == '/'
    || S[S.size() - 1] == '+' || S[S.size() - 1] == '-' || S[S.size() - 1] == '^'
    || S[S.size() - 1] == '.') {
            return -1;
    }
    // убрать лишние минусы из строки

    if (S[0] == '-') {
        SS = "0";
    }

    for (int j = 0; j < (S.size() - 1); j++) {
        if ((S[j] == '(') && (S[j + 1] == '-')) {
            SS = SS + "(0";
        } else {
            SS = SS + S[j];
        }
    }
    SS = SS + S[S.size() - 1];
    S = SS;

    // Замена знаков сложных операций на буквы

    replace_all(S, "S", "sin");
    replace_all(S, "C", "cos");
    replace_all(S, "T", "tg");
    replace_all(S, "K", "sqrt");
    replace_all(S, "L", "ln");

    int warning = 0;
    for (int j = 0; j < (S.size() - 1); j++) {
        if (S[j] >= '0' && S[j] <= '9') {
            warning = warning + 1;
            }
    }
    if (warning == 0) {
        return -1;
    }

    // Сакральная строка. Волшебным образом ретерн тут исправляет баг, но сам ретерн и ломает функцию в нуле
    for (int j = 0; j < S.size(); j++) {
        if (S[j] >= 'a' && S[j] <= 'z') {
            return -1;
        }
    }

        // основная программа

    for (int i = 0; i < S.size(); i++) {
        if (S[i] >= '0' && S[i] <= '9') {

            double b = 0;
            int tet = 1;
            while (S[i] <= '9' && S[i] >= '0') {
                b = b * 10 + (S[i] - '0');
                i++;
            }

            if (S[i] == '.') {
                i++;
                while (S[i] <= '9' && S[i] >= '0') {
                    b = b + (S[i] - '0') / pow(10, tet);
                    i++;
                    tet++;
                }
            }
            //printf("b=%f   ", b);
            push(top1, b, '@');
        }


        if (S[i] == '(') {
            push(top2, 0, S[i]);
        }
        if (S[i] == ')') {
            while ((*top2).znac != '(') {
                apply(pop(top2).znac);
            }
        pop(top2);
        }
        if (S[i] =='+' || S[i] == '-' || S[i] == '*' || S[i] == '/' || S[i] == 'S' ||
        S[i] == 'C' || S[i] == 'T' || S[i] == 'K' || S[i] == 'L' || S[i] == '^') {
            if (top2 != 0) {
                while (top2 != 0 && priority((*top2).znac) >= priority(S[i])) {
                    apply(pop(top2).znac);
                }
                push(top2, 0, S[i]);
            } else {
                push(top2, 0, S[i]);
            }
        }
    }
    while (top2 != 0) {
        apply(pop(top2).znac);
    }
    if (Hope != 0) {
        Hope = 0;
        return -1;
    }
    ans = (*top1).number;
    while (top1 != 0) {
        pop(top1).number;
    }
    return 0;
}
