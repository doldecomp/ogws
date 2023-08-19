#include <revolution/DVD.h>
#include <string.h>

BOOL DVDCompareDiskID(const DVDDiskID* id1, const DVDDiskID* id2) {
    // Compare game name
    if (id1->game[0] != '\0' && id2->game[0] != '\0' &&
        strncmp(id1->game, id2->game, sizeof(id1->game)) != 0) {
        return FALSE;
    }

    // Compare company name
    if (id1->company[0] == '\0' || id2->company[0] == '\0' ||
        strncmp(id1->company, id2->company, sizeof(id1->company)) != 0) {
        return FALSE;
    }

    // Compare disk number
    if (id1->disk != 0xFF && id2->disk != 0xFF && id1->disk != id2->disk) {
        return FALSE;
    }

    // Compare version number
    if (id1->version != 0xFF && id2->version != 0xFF &&
        id1->version != id2->version) {
        return FALSE;
    }

    return TRUE;
}
