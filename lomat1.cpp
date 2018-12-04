//�������� ���������� �� ������� Slovoed'a.
//����� ������� ������ ���������� ������� ����� ��� ��������� dictionary
//� ��� ��������, ��� ����� ��� ����������
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

const int quantity = 15; //���������� ����, ��������� �� �����
const int LengthWord = 43;//���������� ��������� � ������ -3
unsigned int TestSort = NULL;//�������� �� ����������
unsigned char UpFirst, UpSecond, DownFirst, DownSecond;//������� � ������ ������� ���������� ����� ���������

struct RecordWords { //��������� (������) � ����������� � �������� �������
    char FirstWord[LengthWord];
    char SecondWord[LengthWord];
};

int menu();
void TextColor(int color); //����� ����� ������
void gotoxy(int PosX, int PosY); //������� ������� �� ����������� �������
void OutputWord(char NameFile[], char NameDictionary[]); //����� �������
void AboutApplication();//���������� � ����������
void AddWord(char NameFile[], char FirstName[], char SecondName[]); //���������� �����
void InputWord(char InpWord[LengthWord], unsigned char Down, unsigned char Up, int position, int length);//���� �����
void SortingInFile(char NameFile[], int Down, int Up);//���������� ����� � �����
void Zeroing();//�������, ��������� ���� \n �� ������



int main()
{
    SetConsoleCP(1251); //��������� ������� �������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); //��������� ������� �������� win-cp 1251 � ����� ������
    int button;
    system("mode con cols=120 lines=60"); //������ ����
    while (button != 6){
        button = menu();
        switch(button){
        case 1:
            if (TestSort != 1){
                SortingInFile("dictionary\\dictionaryRus.txt", 224, 255);
                TestSort = 1;
            }
            OutputWord("dictionary\\dictionaryRus.txt", "������-����������");
            break;
        case 2:
            if (TestSort != 2){
                SortingInFile("dictionary\\dictionaryEng.txt", 97, 122);
                TestSort = 2;
            }
            OutputWord("dictionary\\dictionaryEng.txt", "�����-�������");
            break;
        case 3:
            DownFirst = 97;
            UpFirst = 122;
            DownSecond = 224;
            UpSecond = 255;

            AddWord("dictionary\\dictionaryEng.txt", "����������", "�������");
            break;
        case 4:
            DownFirst = 224;
            UpFirst = 255;
            DownSecond = 97;
            UpSecond = 122;
            AddWord("dictionary\\dictionaryRus.txt", "�������", "����������");
            break;
        case 5:
            AboutApplication();
            break;

        }
    }

    return 0;
}

void AboutApplication()//���������� � ����������
{
    system("cls");
    printf("!!!��������� Slovoed!!!\n\n");
    printf("� ���� ��������� ����, ��� �� ������ �� ����, 2 �������:\n");
    printf("������-���������� � �����-�������. ���� ������������ ������� �������� ����� � ���,\n");
    printf("�� �� �������� ������ ��� �������, ������ ��������������� ������ ����.\n");
    printf("��� �� � ��������� ���� ������� ������� ���� ��������������� �������.\n\n");
    printf("������ ��������� ����������� �������� 2 ����� ������ ���-41:\n");
    printf("������ ������\n������� ������\n��������� �����\n\n");
    printf("����� �����, ������� Esc");
    while(getch() != 27);
}

void Zeroing(struct RecordWords &ZeroingRecord)//�������, ��������� ���� \n �� ������
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

void SortingInFile(char NameFile[], int Down, int Up)//���������� ����� � �����
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
                printf("�� ������ ������� ���� �� ������\n");
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
                printf("�� ������ ������� ���� �� ������\n");
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

void OutputWord(char NameFile[], char NameDictionary[]) //����� �������
{
    system("cls");
    int counter = 1, j, check = 0 , button1;
    long position;
    struct RecordWords str[quantity];
    FILE *dictionary, *vol; //�������� ��������� �� ����
    char key = 0, MoveKey = 0;
    bool out = true;

    if ((dictionary = fopen(NameFile, "r")) == NULL){
            printf("�� ������ ������� ���� �� ������ � ������\n");
            exit(1);
        }

    fseek(dictionary, 0, SEEK_END);
    position = ftell(dictionary);

    if (position > 0){
        while (key != 27){
            fseek(dictionary, 0,0);
            for (int i = 1; i <= counter ; i++){ //���� ��� ��������� ������� �� ������������ ����� � ����� ��� �������� �������
                j = 0;
                while(!feof(dictionary) && j <= quantity - 1){ //���������� ������ �� �����-�������
                    fgets(str[j].FirstWord, sizeof(str[j].FirstWord), dictionary);
                    fgets(str[j].SecondWord, sizeof(str[j].SecondWord), dictionary);
                    j++;
                }
            }
            check = 0;
            gotoxy(51, check + 1);
            printf("%s �������", NameDictionary);
            gotoxy(0, check + 2);
            for (int i = 0; i < 120; i++)
                printf("_");
            while(check < j){ //����� ���� �� �����
                gotoxy(59 - strlen(str[check].FirstWord),check + 5);
                printf("%s",str[check].FirstWord);
                gotoxy(60,check + 5);
                printf("-  %s", str[check].SecondWord);
                check++;
            }

            gotoxy(50, check + 6);
            printf("<%4i-� ��������   >\n", counter);
            printf("\n��� ��������� ������ ������� ������� V(������������ � ������� �������. ��� ������� ������ Enter)");
            printf("\n��� ������ ������� Esc\n");

            key = getch();

            if ((key == 77) && !feof(dictionary)){ //�������� ������� ������
                system("cls");
                counter += 1;
            }

            else if ((key == 75) && counter >= 2){ //�������� ������� �����
                system("cls");
                counter -= 1;
            }

            else if (key == 'V' || key == 'v' || key == '�'|| key == '�'){
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
        printf("!!!� ���� ������� ����� �����������!!!\n");
        system("pause");
    }
    fclose(dictionary);
}

void InputWord(char InpWord[LengthWord], unsigned char Down, unsigned char Up, int position, int length)//���� �����
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

void AddWord(char NameFile[], char FirstName[], char SecondName[]) // ���������� ����� � �������
{
    FILE *dictionary; //��������� �� ����
    char key;
    struct RecordWords str;
    long position;
    int length;

    do{
    system("cls");

    if((dictionary = fopen (NameFile, "a")) == NULL){
        printf("�� ������ ������� ����\n");
        exit(1);
    }

    length = strlen("�������  �����: ");
    length += strlen(FirstName);
    printf("������� %s �����: ", FirstName);
    InputWord(str.FirstWord, DownFirst, UpFirst, 0, length);
    length = strlen("�������  �����: ");
    length += strlen(SecondName);
    printf("������� %s �����: ", SecondName);
    InputWord(str.SecondWord, DownSecond, UpSecond, 1, length);

    fseek(dictionary, 0, 2);
    position = ftell(dictionary);

    if (position > 0)
        fprintf(dictionary,"\n%s\n%s", str.FirstWord, str.SecondWord);
    else fprintf(dictionary, "%s\n%s", str.FirstWord, str.SecondWord);

    fclose(dictionary);

    printf("������� Y, ����� �����...");
    key = getch();
    }while (key != 'Y' && key != 'y' && key != '�' && key != '�'); //���� ����, ���� ������ Y
    system("cls");
    TestSort = NULL;
}

int menu()//����
{
    char key = ' ';
    int change = 1;
    system("cls");

    while (key != (char)13){  //(char)13 = Enter

        gotoxy(0, 0);
        printf("������-���������� �������\n");
        printf("�����-������� �������\n");
        printf("���������� ���� � �����-������� �������\n");
        printf("���������� ���� � ������-���������� �������\n");
        printf("� ����������\n");
        printf("�����\n");

        gotoxy(0, change - 1);
        TextColor(3);
        switch(change)
        {
            case 1:
                printf("������-���������� �������\n");
                break;
            case 2:
                printf("�����-������� �������\n");
                break;
            case 3:
                printf("���������� ���� � �����-������� �������\n");
                break;
            case 4:
                printf("���������� ���� � ������-���������� �������\n");
                break;
            case 5:
                printf("� ����������\n");
                break;
            case 6:
                printf("�����\n");
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

void TextColor(int color) //����� ����� ������
{
    HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hndl, color);
}

void gotoxy(int PosX, int PosY) //������� ������� �� ����������� �������
{
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    position.X=PosX;
    position.Y=PosY;
    SetConsoleCursorPosition(hConsole, position);
}


