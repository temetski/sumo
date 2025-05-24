#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declaration for QtOpenGLViewWidget
class QtOpenGLViewWidget;

#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QStringList>
#include "guievent_qt.h" // Include the new GUIEvent placeholder


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QToolBar;
// Forward declarations for Qt classes
class QLCDNumber;
class QLabel;
class QDoubleSpinBox;
class QSlider;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    void createToolbars();

    // Menus
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *settingsMenu; // New
    QMenu *locateMenu;   // New
    QMenu *simulationMenu; // New (was myControlMenu in FOX)
    QMenu *helpMenu;

    // Toolbars
    QToolBar *fileToolBar;     // For file operations
    QToolBar *simulationToolBar; // For simulation control (play, pause, step)
    QToolBar *viewToolBar;       // For view-related actions (new view, etc.)
    // QToolBar *editToolBar; // Can be added if needed for cut/copy/paste etc.

    // Actions
    QAction *newAct; // Re-evaluate: FOX 'New Window' is different from 'New File'
    // QAction *openAct; // Replaced by more specific open actions below
    QAction *saveAct; // Keep for now, might be Save As...

    // --- File Menu Actions (from GUIApplicationWindow) ---
    QAction *openConfigAct;
    QAction *openNetworkAct;
    QAction *openShapesAct;
    QAction *openEdgeDataAct;
    QAction *reloadAct;
    QAction *quickReloadAct;
    QAction *saveConfigAct;
    QAction *closeSimAct;
    QAction *exitAct; // Already present, ensure it's connected to qApp->quit()

    // --- Edit Menu Actions (from GUIApplicationWindow) ---
    QAction *editSelectedAct;
    QAction *selectLanesByPermissionAct; // Placeholder for now
    QAction *editBreakpointsAct;
    QAction *editViewSchemeAct;
    QAction *editViewportAct;
    QAction *openNeteditAct;
    QAction *cutAct; // Already present
    QAction *copyAct; // Already present
    QAction *pasteAct; // Already present

    // --- Settings Menu Actions (stub) ---
    QAction *appSettingsAct;
    QAction *toggleGamingModeAct;
    QAction *toggleFullScreenAct;

    // --- Locate Menu Actions (stub) ---
    QAction *locateJunctionAct;
    QAction *locateEdgeAct;
    // ... other locate actions can be added later

    // --- Simulation Menu Actions (from GUIApplicationWindow) ---
    QAction *startSimAct;
    QAction *stopSimAct;
    QAction *stepSimAct;
    QAction *saveStateAct;
    QAction *loadStateAct;

    // --- Window Menu Actions (stub, some already present) ---
    QAction *newViewAct; // For new 2D view
#ifdef HAVE_OSG
    QAction *newOSGViewAct; // For new 3D view
#endif
    QAction *tileHorizontalAct;
    QAction *tileVerticalAct;
    QAction *cascadeAct;
    QAction *closeCurrentWindowAct; // For MDI child

    // --- Help Menu Actions (from GUIApplicationWindow) ---
    QAction *onlineDocsAct;
    QAction *changelogAct;
    QAction *hotkeysAct;
    QAction *tutorialAct;
    QAction *feedbackAct;
    QAction *aboutAct; // Already present
    QAction *aboutQtAct; // Already present
    QAction *hallOfFameAct;

    // Simulation Time and Delay Controls
    QLCDNumber *timeDisplayLCD;
    QLabel *simDelayLabel;
    QDoubleSpinBox *simDelaySpinBox;
    QSlider *simDelaySlider;

    // Central OpenGL View Widget
    QtOpenGLViewWidget *openGLViewWidget;

    // Qt equivalents for event handling
    QQueue<GUIEvent*> myEventQueue;
    QMutex myEventQueueMutex;
    QWaitCondition myEventQueueWaitCondition;

private slots:
    void newFile(); // Keep, can be repurposed for "New Window" or similar if needed
    void openFile(); // Keep, can be repurposed for "Open Other..."
    void saveFile(); // Keep, can be repurposed for "Save Other..."
    void about();    // Keep

    // Slots for FOX actions
    void openConfiguration();
    void openNetwork();
    void openShapes();
    void openEdgeData();
    void reloadSimulation();
    void quickReloadSimulation();
    void saveConfiguration();
    void closeSimulation();
    // void exitApplication(); // connect to qApp->quit() directly

    void editSelected();
    void selectLanesByPermission();
    void editBreakpoints();
    void editViewScheme();
    void editViewport();
    void openNetedit();

    void startSimulation();
    void stopSimulation();
    void stepSimulation();
    void saveSimState();
    void loadSimState();

    // Placeholder slots for other menus
    void appSettings();
    void toggleGamingMode();
    void toggleFullScreen();
    void locateJunction();
    void locateEdge();
    void openNewView();
#ifdef HAVE_OSG
    void openNewOSGView();
#endif
    void showOnlineDocs();
    void showChangelog();
    void showHotkeys();
    void showTutorial();
    void sendFeedback();
    void showHallOfFame();

    // Slot for synchronizing simulation delay controls
    void updateSimDelayControls(double value);
    void updateSimDelaySpinBox(int value);

    // Recent file handling
    void addRecentFile(const QString& listName, const QString& filePath);
    QStringList getRecentFiles(const QString& listName, int maxItems = 10) const;
    void updateRecentFilesMenu(QMenu* menu, const QString& listName, const char* slotPrefix, QList<QAction*>& actionList, int maxItems = 5);
    void clearRecentFiles(const QString& listName);

    // Slots to open recent files
    void openRecentNetwork1();
    void openRecentNetwork2();
    void openRecentNetwork3();
    void openRecentNetwork4();
    void openRecentNetwork5();
    void openRecentConfig1();
    void openRecentConfig2();
    void openRecentConfig3();
    void openRecentConfig4();
    void openRecentConfig5();

    void openRecentFileTriggered(); // Generic slot to handle actual opening

    // Placeholder for event processing
    void processEvents();

private:
    // Helper for recent file actions
    QList<QAction*> recentNetworkActions;
    QList<QAction*> recentConfigActions;
    void createRecentFileActions(QMenu* menu, const QString& listName, QList<QAction*>& actionList, const char* slotPrefix, int maxItems); // Helper to populate recent file menu actions
};

#endif // MAINWINDOW_H
