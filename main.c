//Bibliothèque

#include "src/tools/tools.h"
#include "src/menu/menu.h"

//Fonctions

void gotoligcol(int a, int b) {
    COORD coord;
    coord.X = a;
    coord.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void afficherSequenceSnoopy(const wchar_t* sequence, int delay) {
    int length = wcslen(sequence);
    for (int i = 0; i < length; ++i) {
        wprintf(L"%lc", sequence[i]);
        Sleep(delay);
    }
}

void logo() {
    const wchar_t* snoopySequence =
            L" .-.     .--.      .---. .----..-.   .-..--.  .-. .-..----..-. .-..----.\n"
            L"} |    / {} \\     } }}_}} |__} \\ \\_/ // {} \\ |  \\{ || }`-'{ {_} |} |__}\n"
            L"} '--./  /\\  \\    | } \\ } '__}  \\   //  /\\  \\| }\\  {| },-.| { } }} '__}\n"
            L"`----'`-'  `-'    `-'-' `----'   `-' `-'  `-'`-' `-'`----'`-' `-'`----'\n"
            L"    .----. .----.         .----..-. .-. .---.  .---. .-.-..-.  .-.\n"
            L"    } {-. \\} |__}        { {__-`|  \\{ |/ {-. \\/ {-. \\| } }}\\ \\/ /\n"
            L"    } '-} /} '__}        .-._} }| }\\  {\\ '-} /\\ '-} /| |-\'  `-\\ }\n"
            L"    `----' `----'        `----' `-' `-' `---'  `---' `-'      `-'";

    afficherSequenceSnoopy(snoopySequence, 1);
}

int main() {

    _setmode(_fileno(stdout), _O_U16TEXT);

    COULEUR(BLEU_FONCE, NOIR);

    logo();
    wprintf(L" \n");
    wprintf(L" \n");
    wprintf(L" \n");
    wprintf(L"Appuyez sur une touche pour continuer...");
    // Reste du code
    _getch();
    system("cls");
    menu();

    return 0;
}