#ifndef NW4R_SND_BANK_H
#define NW4R_SND_BANK_H
#include <nw4r/snd/snd_BankFile.h>
#include <nw4r/snd/snd_NoteOnCallback.h>
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace snd {
namespace detail {

// Forward declarations
class Channel;

class Bank {
public:
    Bank(const void* pData);
    ~Bank();

    void SetWaveDataAddress(const void* pData) {
        mWaveDataAddress = pData;
    }

    Channel* NoteOn(const NoteOnInfo& rInfo) const;

private:
    BankFileReader mBankReader;   // at 0x0
    const void* mWaveDataAddress; // at 0xC
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
