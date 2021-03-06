/* viscustom.cpp
 *
 * This class encapsulates the visualisation of name data.
 *
 * (C) Alistair Jewers Feb 2017
 */

#include "visname.h"
#include "settings.h"

/* Constructor
 * Initialise all setttings
 */
VisName::VisName(void) {
    setType(VisType::NAME);
    setEnabled(true);
    setSelectedOnly(true);
    settingsDialog = NULL;
}

/* toString
 * Generate a string describing all settings.
 */
QString VisName::toString(void) {
    QString str = "Name. ";

    if (selectedOnly) {
        str = str + "\t\t[Selected robot only. ]";
    } else {
        str = str + "\t\t[All robots. ]";
    }

    return str;
}

/* render
 * Render this visualisation for one robot.
 */
void VisName::render(cv::Mat image, RobotData *robot, bool selected) {
    if (!isEnabled() || (selectedOnly && !selected)) {
        return;
    }

    cv::Scalar colour = Settings::instance()->isRobotColourEnabled() ? robot->getColour() : cv::Scalar(255, 255, 255);

    int x = image.cols * robot->getPos().x;
    int y = image.rows * robot->getPos().y;

    putText(image,
            robot->getName().toStdString(),
            cv::Point(x + 12, y),
            cv::FONT_HERSHEY_SIMPLEX,
            0.3,
            colour);
}

/* getSettingsDialog
 * Return a pointer to the settings dialog for this visualisation.
 */
QDialog* VisName::getSettingsDialog(void) {
    if (settingsDialog != NULL) {
        delete settingsDialog;
    }

    settingsDialog = new NameSettingsDialog(this);
    return settingsDialog;
}

/* setSelectedOnly
 * Enables or disables the selected robot only setting
 */
void VisName::setSelectedOnly(bool enable) {
    selectedOnly = enable;
}

/* getSelectedOnly
 * Return the current state of the selected robot only setting
 */
bool VisName::getSelectedOnly(void) {
    return selectedOnly;
}
