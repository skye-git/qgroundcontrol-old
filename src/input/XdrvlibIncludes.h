/* This is a helper header file to go around multiple issues when using the
 * 3dconnexion magellan driver (xdrvlib) for linux.
 */

#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xos.h>
//#include <X11/Xatom.h>
//#include <X11/keysym.h>
#ifdef Success
#undef Success              // Eigen library doesn't work if Success is defined
#endif //Success
extern "C"
{
#include "xdrvlib.h"
}
#ifdef None
#undef None
#endif
#ifdef Bool
#undef Bool                 // Xlib defines Bool as int. HUD and others have memebers called Status
#endif
#ifdef Status
#undef Status               // Xlib defines Status as int. qquickwidget and others have memebers called Status
#endif
