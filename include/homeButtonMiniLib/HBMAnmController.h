#ifndef HOME_BUTTON_MINI_LIB_ANM_CONTROLLER_H
#define HOME_BUTTON_MINI_LIB_ANM_CONTROLLER_H
#include <homeButtonMiniLib/HBMFrameController.h>
#include <homeButtonMiniLib/HBMTypes.h>

#include <nw4r/lyt.h>

namespace homebutton {

class GroupAnmController : public FrameController {
public:
    GroupAnmController();
    virtual ~GroupAnmController(); // at 0x8

    void do_calc();

public:
    nw4r::lyt::Group* mpGroup;             // at 0x20
    nw4r::lyt::AnimTransform* mpAnimGroup; // at 0x24
};

} // namespace homebutton

#endif
