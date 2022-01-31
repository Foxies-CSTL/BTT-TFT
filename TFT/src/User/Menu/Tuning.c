#include "Tuning.h"
#include "includes.h"

const MENUITEMS TuningItems = {
  // title
  LABEL_TUNING,
  // icon                          label
  {
    {ICON_PID,                     LABEL_PID},
    {ICON_TUNE_EXTRUDER,           LABEL_TUNE_EXTRUDER},
    #if DELTA_PROBE_TYPE == 0  // if not Delta printer
      {ICON_PROBE_OFFSET,            LABEL_H_OFFSET},
    #else
      {ICON_PROBE_OFFSET,            LABEL_P_OFFSET},
    #endif
    {ICON_NULL,                    LABEL_NULL},
    {ICON_NULL,                    LABEL_NULL},
    {ICON_NULL,                    LABEL_NULL},
    {ICON_NULL,                    LABEL_NULL},
    {ICON_BACK,                    LABEL_BACK},
  }
};

void menuTuning(void)
{
  KEY_VALUES key_num = KEY_IDLE;

  menuDrawPage(&TuningItems);

  while (MENU_IS(menuTuning))
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        OPEN_MENU(menuPid);
        break;

      case KEY_ICON_1:
        OPEN_MENU(menuTuneExtruder);
        break;

      case KEY_ICON_2:
        #if DELTA_PROBE_TYPE == 0  // if not Delta printer
          storeCmd("M206\n");
          zOffsetSetMenu(false);  // use Probe Offset menu
          OPEN_MENU(menuZOffset);
        #else
          setDialogText(LABEL_WARNING, LABEL_DISCONNECT_PROBE, LABEL_CONTINUE, LABEL_CANCEL);
          showDialog(DIALOG_TYPE_ALERT, NULL, NULL, NULL);
          storeCmd("M851\n");
          zOffsetSetMenu(true);  // use Probe Offset menu
          OPEN_MENU(menuZOffset);      
        #endif
        break;

      case KEY_ICON_7:
        CLOSE_MENU();
        break;

      default:
        break;
    }

    loopProcess();
  }
}
