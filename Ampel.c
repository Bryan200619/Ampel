#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef enum {
    AUTO_GRUEN,
    AUTO_GELB,
    ROT_VOR_FUSSGRUEN,
    FUSS_GRUEN,
    ROT_VOR_AUTOGRUEN,
    AUTO_ROT_GELB
} Zustand;

Zustand naechster_zustand(Zustand aktuell, int *anforderung)
{
    switch (aktuell) {
        case AUTO_GRUEN:
            return *anforderung ? AUTO_GELB : AUTO_GRUEN;
        case AUTO_GELB: return ROT_VOR_FUSSGRUEN;
        case ROT_VOR_FUSSGRUEN:
            *anforderung = 0;
            return FUSS_GRUEN;
        case FUSS_GRUEN: return ROT_VOR_AUTOGRUEN;
        case ROT_VOR_AUTOGRUEN: return AUTO_ROT_GELB;
        case AUTO_ROT_GELB: return AUTO_GRUEN;
    }
    return ROT_VOR_AUTOGRUEN;
}

void zeige_ampel(Zustand aktuell, int anforderung)
{
    const char *lampen[] = {
        "[.] [.] [O]     [O] [.]   ",
        "[.] [O] [.]     [O] [.]   ",
        "[O] [.] [.]     [O] [.]   ",
        "[O] [.] [.]     [.] [O]   ",
        "[O] [.] [.]     [O] [.]   ",
        "[O] [O] [.]     [O] [.]   "
    };
    printf("%s%s\n", lampen[aktuell], anforderung ? "BITTE WARTEN" : "-");
    fflush(stdout);
}

int main(void)
{
    const unsigned int dauer_ms[] = {5000, 2000, 1000, 5000, 3000, 1000};
    Zustand aktuell = ROT_VOR_AUTOGRUEN;
    int anforderung = 0;
    ULONGLONG phasenstart = GetTickCount64();

    puts("T = Taster, Q = Ende (ohne Enter). [O] an, [.] aus.");
    puts("AUTO            FUSS      TASTER\n R   Y   G       R   G");
    zeige_ampel(aktuell, anforderung);

    while (1) {
        if (_kbhit()) {
            int taste = _getch();
            if (taste == 0 || taste == 224) {
                (void)_getch();
            } else if (taste == 'q' || taste == 'Q') {
                break;
            } else if ((taste == 't' || taste == 'T') && aktuell != FUSS_GRUEN && !anforderung) {
                anforderung = 1;
                zeige_ampel(aktuell, anforderung);
            }
        }

        ULONGLONG jetzt = GetTickCount64();
        if (jetzt - phasenstart >= dauer_ms[aktuell]) {
            Zustand danach = naechster_zustand(aktuell, &anforderung);
            if (danach != aktuell) {
                aktuell = danach;
                phasenstart = jetzt;
                zeige_ampel(aktuell, anforderung);
            }
        }
        Sleep(20);
    }
    return 0;
}
//
// Created by tamol on 27.11.2026.
//
