//Создание приложения на подобие Slovoed'a.
//Перед началом работы необходимо создать папку под названием dictionary
//в том каталоге, где лежит код приложения
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

const int quantity = 15; //Количество слов, выводимых на экран
const int LengthWord = 43;//Количество элементов в строке -3
unsigned int TestSort = NULL;//Проверка на сортировку
unsigned char UpFirst, UpSecond, DownFirst, DownSecond;//Верхние и нижние границы диапазонов кодов алфавитов

struct RecordWords { //Структура (запись) с английскими и русскими словами
    char FirstWord[LengthWord];
    char SecondWord[LengthWord];
};

int menu();
void TextColor(int color); //Смена цвета текста
void gotoxy(int PosX, int PosY); //Перевод курсора на определённую позицию
void OutputWord(char NameFile[], char NameDictionary[]); //Вывод словаря
void AboutApplication();//Информация о приложении
void AddWord(char NameFile[], char FirstName[], char SecondName[]); //Добавление строк
void InputWord(char InpWord[LengthWord], unsigned char Down, unsigned char Up, int position, int length);//Ввод строк
void SortingInFile(char NameFile[], int Down, int Up);//Сортировка строк в файле
void Zeroing();//Функция, убирающая знак \n из строки



int main()
{
    SetConsoleCP(1251); //установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); //установка кодовой страницы win-cp 1251 в поток вывода
    int button;
    system("mode con cols=120 lines=60"); //Размер окна
    while (button != 6){
        button = menu();
        switch(button){
        case 1:
            if (TestSort != 1){
                SortingInFile("dictionary\\dictionaryRus.txt", 224, 255);
                TestSort = 1;
            }
            OutputWord("dictionary\\dictionaryRus.txt", "Русско-английский");
            break;
        case 2:
            if (TestSort != 2){
                SortingInFile("dictionary\\dictionaryEng.txt", 97, 122);
                TestSort = 2;
            }
            OutputWord("dictionary\\dictionaryEng.txt", "Англо-русский");
            break;
        case 3:
            DownFirst = 97;
            UpFirst = 122;
            DownSecond = 224;
            UpSecond = 255;

            AddWord("dictionary\\dictionaryEng.txt", "английскую", "русскую");
            break;
        case 4:
            DownFirst = 224;
            UpFirst = 255;
            DownSecond = 97;
            UpSecond = 122;
            AddWord("dictionary\\dictionaryRus.txt", "русскую", "английскую");
            break;
        case 5:
            AboutApplication();
            break;

        }
    }

    return 0;
}

void AboutApplication()//Информация о приложении
{
    system("cls");
    printf("!!!Программа Slovoed!!!\n\n");
    printf("В этой программе есть, как вы поняли по меню, 2 словаря:\n");
    printf("Русско-английский и англо-русский. Если пользователь захочет добавить слова в них,\n");
    printf("то он спокойно сможет это сделать, выбрав соответствующие пункты меню.\n");
    printf("Так же в программе есть функция озвучки фраз соответсвующего словаря.\n\n");
    printf("Данную программу разработали студенты 2 курса группы ТМП-41:\n");
    printf("Хромов Никита\nБодягин Михаил\nМаневский Раман\n\n");
    printf("Чтобы выйти, нажмите Esc");
    while(getch() != 27);
}

void Zeroing(struct RecordWords &ZeroingRecord)//Функция, убирающая знак \n из строки
{
    bool check[2];
    int i = 0;

    check[0] = true;
    check[1] = true;

    while ((check[0] || check[1]) && i < LengthWord){
                if (ZeroingRecord.FirstWord[i] == '\n'){
                    ZeroingRecord.FirstWord[i] = 0;
                    check[0] = false;
                }
                if (ZeroingRecord.SecondWord[i] == '\n'){
                    ZeroingRecord.SecondWord[i] = 0;
                    check[1] = false;
                }
                i++;
        }
}

void SortingInFile(char NameFile[], int Down, int Up)//Сортировка строк в файле
{
    int counter = 0, j, i;
    long position;
    FILE *dictionary;
    struct RecordWords *list_1, *list_2, temp_1, temp_2;

    list_1 = (struct RecordWords*)malloc(0 * sizeof(struct RecordWords));
    list_2 = (struct RecordWords*)malloc(0 * sizeof(struct RecordWords));

    dictionary = fopen(NameFile, "a");
    fseek(dictionary, 0 , SEEK_END);
    position = ftell(dictionary);
    fclose(dictionary);

    if (position > 0) {
        if ((dictionary = fopen(NameFile, "r")) == NULL){
                printf("Не удаётся открыть файл на чтение\n");
                exit(1);
        }

        while(!feof(dictionary)){

            list_1 = (struct RecordWords*)realloc(list_1, (counter + 1) * sizeof(struct RecordWords));
            list_2 = (struct RecordWords*)realloc(list_2, (counter + 1) * sizeof(struct RecordWords));
            fgets(list_1[counter].FirstWord, sizeof(list_1[counter].FirstWord), dictionary);
            fgets(list_1[counter].SecondWord, sizeof(list_1[counter].SecondWord), dictionary);
            Zeroing(list_1[counter]);
            list_2[counter] = list_1 [counter];
            for (int i = 0; i < LengthWord - 2; i++)
                if (list_2[counter].FirstWord[i] >= (Down - 32) && list_2[counter].FirstWord[i] <= (Up - 32) )
                    list_2[counter].FirstWord[i] += 32;
            counter++;
        }
        counter--;

        for (int i = 1; i <= counter; i++){
            temp_1 = list_1[i];
            temp_2 = list_2[i];
            j = i - 1;

            while (j >= 0 && temp_2.FirstWord[0] < list_2[j].FirstWord[0]){
                list_1[j + 1] = list_1[j];
                list_2[j + 1] = list_2[j];
                j--;
            }
            list_1[j + 1] = temp_1;
            list_2[j + 1] = temp_2;
        }
        fclose(dictionary);
        if ((dictionary = fopen(NameFile, "w")) == NULL){
                printf("Не удаётся открыть файл на запись\n");
                exit(1);
        }

        fprintf(dictionary, "%s\n%s", list_1[0].FirstWord, list_1[0].SecondWord);
        for (int i = 1; i <= counter; i++)
            fprintf(dictionary, "\n%s\n%s", list_1[i].FirstWord, list_1[i].SecondWord);

        fclose(dictionary);
    }
    free(list_1);
    free(list_2);
}

void OutputWord(char NameFile[], char NameDictionary[]) //Вывод словаря
{
    system("cls");
    int counter = 1, j, check = 0 , button1;
    long position;
    struct RecordWords str[quantity];
    FILE *dictionary, *vol; //Создание указателя на файл
    char key = 0, MoveKey = 0;
    bool out = true;

    if ((dictionary = fopen(NameFile, "r")) == NULL){
            printf("Не удаётся открыть файл на чтение в выводе\n");
            exit(1);
        }

    fseek(dictionary, 0, SEEK_END);
    position = ftell(dictionary);

    if (position > 0){
        while (key != 27){
            fseek(dictionary, 0,0);
            for (int i = 1; i <= counter ; i++){ //Цикл для прокрутка каретки до определённого места в файле для листания страниц
                j = 0;
                while(!feof(dictionary) && j <= quantity - 1){ //Извлечение данных из файла-словаря
                    fgets(str[j].FirstWord, sizeof(str[j].FirstWord), dictionary);
                    fgets(str[j].SecondWord, sizeof(str[j].SecondWord), dictionary);
                    j++;
                }
            }
            check = 0;
            gotoxy(51, check + 1);
            printf("%s словарь", NameDictionary);
            gotoxy(0, check + 2);
            for (int i = 0; i < 120; i++)
                printf("_");
            while(check < j){ //Вывод слов на экран
                gotoxy(59 - strlen(str[check].FirstWord),check + 5);
                printf("%s",str[check].FirstWord);
                gotoxy(60,check + 5);
                printf("-  %s", str[check].SecondWord);
                check++;
            }

            gotoxy(50, check + 6);
            printf("<%4i-я страница   >\n", counter);
            printf("\nДля включения режима озвучки нажмите V(Перемещаться с помощью стрелок. Для озвучки нажать Enter)");
            printf("\nДля выхода нажмите Esc\n");

            key = getch();

            if ((key == 77) && !feof(dictionary)){ //Листание страниц вправо
                system("cls");
                counter += 1;
            }

            else if ((key == 75) && counter >= 2){ //Листание страниц влево
                system("cls");
                counter -= 1;
            }

            else if (key == 'V' || key == 'v' || key == 'м'|| key == 'М'){
                button1 = 0;
                while (key != 13)
                    {
                        gotoxy(55 - strlen(str[button1].FirstWord) + 2, button1 + 5);
                        printf(">");
                        key = getch();
                        gotoxy(55 - strlen(str[button1].FirstWord) + 2, button1 + 5);
                        switch(key){
                        case 80:
                            button1++;
                            break;

                        case 72:
                            button1--;
                            break;
                        }
                        printf(" ");
                        if (button1 == -1)
                            button1 = j - 1;
                        else if(button1 == j)
                            button1 = 0;
                    }
                Zeroing(str[button1]);
                vol = fopen("dictionary\\vol.vbs", "w");
                fprintf(vol, "CreateObject(\"SAPI.SpVoice\").Speak\"%s" , str[button1].FirstWord);
                fprintf(vol, "\"");
                fclose(vol);
                system("start dictionary\\vol.vbs");
            }

        }
    }
    else {
        printf("!!!В этом словаре слова отсутствуют!!!\n");
        system("pause");
    }
    fclose(dictionary);
}

void InputWord(char InpWord[LengthWord], unsigned char Down, unsigned char Up, int position, int length)//Ввод строк
{
    unsigned char inp = 0;
    int i = -1;
    bool space = true;

    while (inp != 13 || i < 0){

        inp = getch();
        if (i < LengthWord - 3){
            if (inp >= Down && inp <= Up || (inp >= Down - 32 && inp <= Up - 32))
            {
                i++;
                space = true;
                if (i == 0 && (inp >= Down && inp <= Up) )
                    InpWord[i] = inp - 32;
                else InpWord[i] = inp;
                gotoxy(length + i, 0 + position);
                printf("%c", InpWord[i]);

            }
            else if (i != -1)
                switch(inp)
                {
                    case 33: case 44: case 39: case 63: case 46: // !, ",", ' , ?, .,
                        i++;
                        InpWord[i] = inp;
                        gotoxy(length + i, 0 + position);
                        printf("%c", InpWord[i]);
                        break;
                    case 32:
                        if (space && i != LengthWord - 4){
                            space = false;
                            i++;
                            InpWord[i] = inp;
                            gotoxy(length + i, 0 + position);
                            printf("%c", InpWord[i]);
                        }
                        break;

                }


        }
         if (i >= 0 && inp == 8){
            gotoxy(length + i, 0 + position);
            if (InpWord[i] == 32)
                space = true;
            InpWord[i] = 0;
            printf(" ");
            i--;
        }

    }
    gotoxy(0, 1 + position);
    InpWord[i + 1] = '\0';
}

void AddWord(char NameFile[], char FirstName[], char SecondName[]) // Добавление строк в словарь
{
    FILE *dictionary; //Указатель на файл
    char key;
    struct RecordWords str;
    long position;
    int length;

    do{
    system("cls");

    if((dictionary = fopen (NameFile, "a")) == NULL){
        printf("Не удаётся открыть файл\n");
        exit(1);
    }

    length = strlen("Введите  фразу: ");
    length += strlen(FirstName);
    printf("Введите %s фразу: ", FirstName);
    InputWord(str.FirstWord, DownFirst, UpFirst, 0, length);
    length = strlen("Введите  фразу: ");
    length += strlen(SecondName);
    printf("Введите %s фразу: ", SecondName);
    InputWord(str.SecondWord, DownSecond, UpSecond, 1, length);

    fseek(dictionary, 0, 2);
    position = ftell(dictionary);

    if (position > 0)
        fprintf(dictionary,"\n%s\n%s", str.FirstWord, str.SecondWord);
    else fprintf(dictionary, "%s\n%s", str.FirstWord, str.SecondWord);

    fclose(dictionary);

    printf("Нажмите Y, чтобы выйти...");
    key = getch();
    }while (key != 'Y' && key != 'y' && key != 'Н' && key != 'н'); //Ввод слов, пока нажата Y
    system("cls");
    TestSort = NULL;
}

int menu()//Меню
{
    char key = ' ';
    int change = 1;
    system("cls");

    while (key != (char)13){  //(char)13 = Enter

        gotoxy(0, 0);
        printf("Русско-английский словарь\n");
        printf("Англо-русский словарь\n");
        printf("Добавление слов в англо-русский словарь\n");
        printf("Добавление слов в русско-английский словарь\n");
        printf("О приложении\n");
        printf("Выход\n");

        gotoxy(0, change - 1);
        TextColor(3);
        switch(change)
        {
            case 1:
                printf("Русско-английский словарь\n");
                break;
            case 2:
                printf("Англо-русский словарь\n");
                break;
            case 3:
                printf("Добавление слов в англо-русский словарь\n");
                break;
            case 4:
                printf("Добавление слов в русско-английский словарь\n");
                break;
            case 5:
                printf("О приложении\n");
                break;
            case 6:
                printf("Выход\n");
                break;
        }

        TextColor(15);

        key = getch();
        switch(key){
        case 80:
            change++;
            break;

        case 72:
            change--;
            break;
        }

        if (change == 0)
            change = 6;
        else if(change == 7)
            change = 1;

    }
    return change;
}

void TextColor(int color) //Смена цвета текста
{
    HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hndl, color);
}

void gotoxy(int PosX, int PosY) //Перевод курсора на определённую позицию
{
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    position.X=PosX;
    position.Y=PosY;
    SetConsoleCursorPosition(hConsole, position);
}


