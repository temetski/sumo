#ifndef GUIEVENT_QT_H
#define GUIEVENT_QT_H

#include <QString> // For message content, as an example

// Basic placeholder for GUIEvent
// This will need to be expanded based on the actual members and methods
// used from GUIEvent in GUIApplicationWindow::eventOccurred and related event handlers.
class GUIEvent
{
public:
    // Mirroring types from GUIApplicationWindow.h eventOccurred() and its handlers
    // These might need specific data members associated with them.
    enum GUIEventType {
        SIMULATION_LOADED,
        SIMULATION_STEP,
        MESSAGE_OCCURRED,
        WARNING_OCCURRED,
        ERROR_OCCURRED,
        DEBUG_OCCURRED,     // Assuming these were distinct message types
        GLDEBUG_OCCURRED,   // Assuming these were distinct message types
        STATUS_OCCURRED,    // Assuming these were distinct message types
        ADD_VIEW,
        CLOSE_VIEW,
        SIMULATION_ENDED
        // Add other event types if discovered
    };

    GUIEventType type;
    QString message; // Example: for MESSAGE_OCCURRED, etc.
    // For SIMULATION_LOADED, you might need pointers to net, begin/end times etc.
    // For now, keeping it simple.

    explicit GUIEvent(GUIEventType eventType) : type(eventType) {}
    GUIEvent(GUIEventType eventType, const QString& msg) : type(eventType), message(msg) {}


    GUIEventType getOwnType() const { return type; }
    QString getMsg() const { return message; } // Example getter
};

// Specific event classes could inherit from GUIEvent if they carry more data
// For example:
// class GUIEvent_SimulationLoaded : public GUIEvent {
// public:
//     GUINet* myNet;
//     SUMOTime myBegin;
//     // ... other data
//     GUIEvent_SimulationLoaded(...) : GUIEvent(SIMULATION_LOADED), myNet(net), ... {}
// };

#endif // GUIEVENT_QT_H
