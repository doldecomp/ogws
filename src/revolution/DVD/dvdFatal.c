#include <revolution/DVD.h>
#include <revolution/OS.h>
#include <revolution/SC.h>

static funcptr_t FatalFunc = NULL;

const char* const __DVDErrorMessage[] = {
    // clang-format off

    // SC_LANG_JP
    "\n\n\nエラーが発生しました。\n\n"
    "イジェクトボタンを押してディスクを取り出してか\n"
    "ら、本体の電源をOFFにして、本体の取扱説明書の\n"
    "指示に従ってください。",

    // SC_LANG_EN
    "\n\n\nAn error has occurred.\n"
    "Press the Eject Button, remove the\n"
    "Game Disc, and turn the power off.\n"
    "Please read the Wii operations manual\n"
    "for more information.",

    // SC_LANG_DE
    "\n\n\nEin Fehler ist aufgetreten.\n"
    "Dr\xFC""cke den Ausgabeknopf, entnimm die\n"
    "Game Disc und schalte die Wii-Konsole\n"
    "aus. Bitte lies die Bedienungsanleitung der\n"
    "Wii-Konsole, um weitere Informationen zu\n"
    "erhalten.",

    // SC_LANG_FR
    "\n\n\nUne erreur est survenue.\n"
    "Appuyez sur le bouton EJECT, retirez\n"
    "le disque de jeu et \xE9teignez la console.\n"
    "Veuillez vous r\xE9""f\xE9rer au mode d'emploi\n"
    "de la console pour de plus amples\n"
    "informations.",

    // SC_LANG_SP
    "\n\n\nSe ha producido un error.\n"
    "Pulsa el Bot\xF3n EJECT, saca el disco y\n"
    "apaga la consola. Consulta el manual de\n"
    "instrucciones de la consola Wii para\n"
    "obtener m\xE1s informaci\xF3n.",
    
    // SC_LANG_IT
    "\n\n\nSi \xE8 verificato un errore.\n"
    "Premi il pulsante EJECT, estrai il disco\n"
    "di gioco e spegni la console. Per maggiori\n"
    "informazioni consulta il manuale di\n"
    "istruzioni della console Wii.",
    
    // SC_LANG_NL
    "\n\n\nEr is een fout opgetreden.\n"
    "Druk op de ejectknop, verwijder de\n"
    "speldisk en zet het systeem uit. Lees\n"
    "de Wii-handleiding voor meer informatie."

    // clang-format on
};

void __DVDShowFatalMessage(void) {
    const char* msg;
    GXColor bgColor = {0, 0, 0, 0};
    GXColor textColor = {255, 255, 255, 0};

    if (SCGetLanguage() == SC_LANG_JP) {
        OSSetFontEncode(OS_FONT_ENCODE_SJIS);
    } else {
        OSSetFontEncode(OS_FONT_ENCODE_ANSI);
    }

    msg = (SCGetLanguage() > SC_LANG_NL) ? __DVDErrorMessage[SC_LANG_EN]
                                         : __DVDErrorMessage[SCGetLanguage()];

    OSFatal(textColor, bgColor, msg);
}

BOOL DVDSetAutoFatalMessaging(BOOL enable) {
    BOOL enabled;
    BOOL old;

    enabled = OSDisableInterrupts();

    old = (FatalFunc != NULL);

    if (enable) {
        FatalFunc = __DVDShowFatalMessage;
    } else {
        FatalFunc = NULL;
    }

    OSRestoreInterrupts(enabled);
    return old;
}

BOOL __DVDGetAutoFatalMessaging(void) {
    return FatalFunc != NULL;
}

void __DVDPrintFatalMessage(void) {
    if (FatalFunc != NULL) {
        FatalFunc();
    }
}
