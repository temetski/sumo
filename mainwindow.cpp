#include "mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication> // Required for qApp
#include <QLCDNumber>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout> // For layout on toolbar
#include "qtopenglviewwidget.h" // Include the new OpenGL widget header
#include <QSettings>
#include <QFileInfo> // For QFileInfo

// Define constants used in this file, e.g., for recent files
const QString RECENT_FILES_GROUP = "RecentFiles";
const int MAX_RECENT_FILES_DISPLAY = 5; // Max recent files to show in menu


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the central widget (placeholder for now)
    // QWidget *centralWidget = new QWidget(this);
    // setCentralWidget(centralWidget);
    openGLViewWidget = new QtOpenGLViewWidget(this);
    setCentralWidget(openGLViewWidget);
    // Later, pass GUINet and GUIVisualizationSettings to openGLViewWidget
    // openGLViewWidget->setNet(mySimNet); // Example
    // openGLViewWidget->setVisualizationSettings(myVisSettings); // Example


    createActions();
    createMenus();
    createToolbars();

    // Optional: Set an initial window title and size
    setWindowTitle(tr("Simulation Application"));
    resize(800, 600);

    // Optional: Add a status bar
    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    // Destructor: Qt handles child widget deletion automatically
}

void MainWindow::newFile()
{
    // Placeholder for new file action
    QMessageBox::information(this, tr("Action Triggered"), tr("New File: Not implemented yet."));
}

void MainWindow::openFile()
{
    // Placeholder for open file action
    QMessageBox::information(this, tr("Action Triggered"), tr("Open File: Not implemented yet."));
}

void MainWindow::saveFile()
{
    // Placeholder for save file action
    QMessageBox::information(this, tr("Action Triggered"), tr("Save File: Not implemented yet."));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simulation Application"),
            tr("This is a placeholder for the application's about dialog."));
}

// Slot implementations for synchronizing simulation delay controls
// void MainWindow::updateSimDelayControls(double value) // Already defined later
// void MainWindow::updateSimDelaySpinBox(int value) // Already defined later

void MainWindow::createActions()
{
    // File menu actions
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    // openAct was removed, specific open actions like openConfigAct are used instead.
    // openAct = new QAction(tr("&Open..."), this);
    // openAct->setShortcuts(QKeySequence::Open);
    // openAct->setStatusTip(tr("Open an existing file"));
    // connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, qApp, &QApplication::quit); // Use qApp for global quit

    // Edit menu actions (placeholders)
    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the selected content to the clipboard"));
    // connect(cutAct, &QAction::triggered, ...); // Add slot later

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the selected content to the clipboard"));
    // connect(copyAct, &QAction::triggered, ...); // Add slot later

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste content from the clipboard"));
    // connect(pasteAct, &QAction::triggered, ...); // Add slot later

    // Help menu actions
    onlineDocsAct = new QAction(tr("&Online Documentation"), this);
    onlineDocsAct->setStatusTip(tr("Open Online documentation."));
    connect(onlineDocsAct, &QAction::triggered, this, &MainWindow::showOnlineDocs);

    changelogAct = new QAction(tr("&Changelog"), this);
    changelogAct->setStatusTip(tr("Open Changelog."));
    connect(changelogAct, &QAction::triggered, this, &MainWindow::showChangelog);

    hotkeysAct = new QAction(tr("&Hotkeys"), this);
    hotkeysAct->setStatusTip(tr("Open Hotkeys."));
    connect(hotkeysAct, &QAction::triggered, this, &MainWindow::showHotkeys);

    tutorialAct = new QAction(tr("T&utorial"), this);
    tutorialAct->setStatusTip(tr("Open Tutorial."));
    connect(tutorialAct, &QAction::triggered, this, &MainWindow::showTutorial);

    feedbackAct = new QAction(tr("Send Feed&back"), this);
    feedbackAct->setStatusTip(tr("Open feedback dialog."));
    connect(feedbackAct, &QAction::triggered, this, &MainWindow::sendFeedback);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt); // Use qApp for global aboutQt

    hallOfFameAct = new QAction(tr("&Hall of Fame"), this);
    hallOfFameAct->setStatusTip(tr("Show Hall of Fame."));
    connect(hallOfFameAct, &QAction::triggered, this, &MainWindow::showHallOfFame);


    // --- File Menu Actions (from GUIApplicationWindow) ---
    openConfigAct = new QAction(tr("Open Simulation..."), this);
    openConfigAct->setShortcuts(QKeySequence::Open); // Or a more specific one if needed
    openConfigAct->setStatusTip(tr("Open a simulation (Configuration file)."));
    connect(openConfigAct, &QAction::triggered, this, &MainWindow::openConfiguration);

    openNetworkAct = new QAction(tr("Open Network..."), this);
    // openNetworkAct->setShortcuts(QKeySequence::Open); // Needs a different shortcut
    openNetworkAct->setStatusTip(tr("Open a network."));
    connect(openNetworkAct, &QAction::triggered, this, &MainWindow::openNetwork);

    openShapesAct = new QAction(tr("Open Shapes..."), this);
    openShapesAct->setStatusTip(tr("Load POIs and Polygons for visualization."));
    connect(openShapesAct, &QAction::triggered, this, &MainWindow::openShapes);

    openEdgeDataAct = new QAction(tr("Open EdgeData..."), this);
    openEdgeDataAct->setStatusTip(tr("Load edge related data for visualization."));
    connect(openEdgeDataAct, &QAction::triggered, this, &MainWindow::openEdgeData);

    reloadAct = new QAction(tr("&Reload"), this);
    reloadAct->setShortcuts(QKeySequence::Refresh);
    reloadAct->setStatusTip(tr("Reloads the simulation / the network."));
    connect(reloadAct, &QAction::triggered, this, &MainWindow::reloadSimulation);

    quickReloadAct = new QAction(tr("&Quick-Reload"), this);
    // quickReloadAct->setShortcut(tr("Ctrl+0")); // Example for custom shortcut
    quickReloadAct->setStatusTip(tr("Reloads the simulation (but not network)."));
    connect(quickReloadAct, &QAction::triggered, this, &MainWindow::quickReloadSimulation);

    saveConfigAct = new QAction(tr("Save Configuration..."), this);
    // saveConfigAct->setShortcuts(QKeySequence::SaveAs); // Or a more specific one
    saveConfigAct->setStatusTip(tr("Save current options as a configuration file."));
    connect(saveConfigAct, &QAction::triggered, this, &MainWindow::saveConfiguration);

    closeSimAct = new QAction(tr("&Close Simulation"), this);
    // closeSimAct->setShortcuts(QKeySequence::Close); // Might conflict
    closeSimAct->setStatusTip(tr("Close the simulation."));
    connect(closeSimAct, &QAction::triggered, this, &MainWindow::closeSimulation);

    // --- Edit Menu Actions (from GUIApplicationWindow) ---
    editSelectedAct = new QAction(tr("Edit Selected..."), this);
    editSelectedAct->setStatusTip(tr("Opens a dialog for editing the list of selected items."));
    connect(editSelectedAct, &QAction::triggered, this, &MainWindow::editSelected);

    selectLanesByPermissionAct = new QAction(tr("Select Lanes by Permission..."), this);
    selectLanesByPermissionAct->setStatusTip(tr("Opens a menu for selecting a vehicle class by which to selected lanes."));
    connect(selectLanesByPermissionAct, &QAction::triggered, this, &MainWindow::selectLanesByPermission);

    editBreakpointsAct = new QAction(tr("Edit Breakpoints..."), this);
    editBreakpointsAct->setStatusTip(tr("Opens a dialog for editing breakpoints."));
    connect(editBreakpointsAct, &QAction::triggered, this, &MainWindow::editBreakpoints);

    editViewSchemeAct = new QAction(tr("Edit Visualization..."), this);
    editViewSchemeAct->setStatusTip(tr("Opens a dialog for editing visualization settings."));
    connect(editViewSchemeAct, &QAction::triggered, this, &MainWindow::editViewScheme);

    editViewportAct = new QAction(tr("Edit Viewport..."), this);
    editViewportAct->setStatusTip(tr("Opens a dialog for editing viewing area, zoom and rotation."));
    connect(editViewportAct, &QAction::triggered, this, &MainWindow::editViewport);

    openNeteditAct = new QAction(tr("Open Network in netedit..."), this);
    openNeteditAct->setStatusTip(tr("Opens current network in NETEDIT."));
    connect(openNeteditAct, &QAction::triggered, this, &MainWindow::openNetedit);

    // --- Settings Menu Actions (stub) ---
    appSettingsAct = new QAction(tr("Application Settings..."), this);
    connect(appSettingsAct, &QAction::triggered, this, &MainWindow::appSettings);

    toggleGamingModeAct = new QAction(tr("Gaming Mode"), this);
    toggleGamingModeAct->setCheckable(true);
    connect(toggleGamingModeAct, &QAction::triggered, this, &MainWindow::toggleGamingMode);

    toggleFullScreenAct = new QAction(tr("Full Screen Mode"), this);
    toggleFullScreenAct->setCheckable(true);
    // toggleFullScreenAct->setShortcuts(QKeySequence::FullScreen); // Standard shortcut
    connect(toggleFullScreenAct, &QAction::triggered, this, &MainWindow::toggleFullScreen);


    // --- Locate Menu Actions (stub) ---
    locateJunctionAct = new QAction(tr("Locate Junction..."), this);
    connect(locateJunctionAct, &QAction::triggered, this, &MainWindow::locateJunction);

    locateEdgeAct = new QAction(tr("Locate Edge..."), this);
    connect(locateEdgeAct, &QAction::triggered, this, &MainWindow::locateEdge);
    // ... other locate actions initialization

    // --- Simulation Menu Actions (from GUIApplicationWindow) ---
    startSimAct = new QAction(tr("&Run"), this);
    // startSimAct->setShortcut(tr("Ctrl+R")); // Example, might conflict
    startSimAct->setStatusTip(tr("Start/Resume the simulation."));
    connect(startSimAct, &QAction::triggered, this, &MainWindow::startSimulation);

    stopSimAct = new QAction(tr("&Stop"), this);
    // stopSimAct->setShortcut(tr("Ctrl+P")); // Example, might conflict
    stopSimAct->setStatusTip(tr("Halt the simulation."));
    connect(stopSimAct, &QAction::triggered, this, &MainWindow::stopSimulation);

    stepSimAct = new QAction(tr("S&tep"), this);
    // stepSimAct->setShortcut(tr("Ctrl+T")); // Example, might conflict
    stepSimAct->setStatusTip(tr("Perform one simulation step."));
    connect(stepSimAct, &QAction::triggered, this, &MainWindow::stepSimulation);

    saveStateAct = new QAction(tr("Save State..."), this);
    saveStateAct->setStatusTip(tr("Save the current simulation state to a file."));
    connect(saveStateAct, &QAction::triggered, this, &MainWindow::saveSimState);

    loadStateAct = new QAction(tr("Load State..."), this);
    loadStateAct->setStatusTip(tr("Load simulation state for the current network from file."));
    connect(loadStateAct, &QAction::triggered, this, &MainWindow::loadSimState);


    // --- Window Menu Actions (stub) ---
    newViewAct = new QAction(tr("New 2D View"), this);
    connect(newViewAct, &QAction::triggered, this, &MainWindow::openNewView);

#ifdef HAVE_OSG
    newOSGViewAct = new QAction(tr("New 3D View"), this);
    connect(newOSGViewAct, &QAction::triggered, this, &MainWindow::openNewOSGView);
#endif
    // tileHorizontalAct, tileVerticalAct, cascadeAct will be standard QWorkspace/QMdiArea actions if used.
    // closeCurrentWindowAct also standard for MDI.
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct); // Keep for "New Window" or similar
    // fileMenu->addAction(openAct); // Removed
    fileMenu->addAction(openConfigAct);
    fileMenu->addAction(openNetworkAct);
    fileMenu->addAction(openShapesAct);
    fileMenu->addAction(openEdgeDataAct);
    fileMenu->addSeparator();
    fileMenu->addAction(reloadAct);
    fileMenu->addAction(quickReloadAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveConfigAct);
    // fileMenu->addAction(saveAct); // Original save, decide if needed alongside Save Configuration
    fileMenu->addSeparator();
    fileMenu->addAction(closeSimAct);
    fileMenu->addSeparator();

    // Recent Networks and Configs
    QMenu *recentNetworksMenu = fileMenu->addMenu(tr("Recent Networks"));
    recentNetworksMenu->setObjectName("recentNetworksMenu"); // For finding it later
    updateRecentFilesMenu(recentNetworksMenu, "recentNetworks", "openRecentNetwork", recentNetworkActions, MAX_RECENT_FILES_DISPLAY);
    QAction *clearRecentNetworksAct = recentNetworksMenu->addAction(tr("Clear Recent Networks"));
    connect(clearRecentNetworksAct, &QAction::triggered, this, [this](){ clearRecentFiles("recentNetworks"); });


    QMenu *recentConfigsMenu = fileMenu->addMenu(tr("Recent Configurations"));
    recentConfigsMenu->setObjectName("recentConfigsMenu"); // For finding it later
    updateRecentFilesMenu(recentConfigsMenu, "recentConfigs", "openRecentConfig", recentConfigActions, MAX_RECENT_FILES_DISPLAY);
    QAction *clearRecentConfigsAct = recentConfigsMenu->addAction(tr("Clear Recent Configurations"));
    connect(clearRecentConfigsAct, &QAction::triggered, this, [this](){ clearRecentFiles("recentConfigs"); });

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editSelectedAct);
    editMenu->addAction(selectLanesByPermissionAct);
    editMenu->addSeparator();
    editMenu->addAction(editBreakpointsAct);
    editMenu->addAction(editViewSchemeAct);
    editMenu->addAction(editViewportAct);
    editMenu->addSeparator();
    editMenu->addAction(openNeteditAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    settingsMenu->addAction(appSettingsAct);
    settingsMenu->addAction(toggleGamingModeAct);
    settingsMenu->addAction(toggleFullScreenAct);

    locateMenu = menuBar()->addMenu(tr("&Locate"));
    locateMenu->addAction(locateJunctionAct);
    locateMenu->addAction(locateEdgeAct);
    // ... add other locate actions

    simulationMenu = menuBar()->addMenu(tr("Simulatio&n"));
    simulationMenu->addAction(startSimAct);
    simulationMenu->addAction(stopSimAct);
    simulationMenu->addAction(stepSimAct);
    simulationMenu->addSeparator();
    simulationMenu->addAction(saveStateAct);
    simulationMenu->addAction(loadStateAct);


    QMenu *windowMenu = menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction(newViewAct);
#ifdef HAVE_OSG
    windowMenu->addAction(newOSGViewAct);
#endif
    // Add other window management actions (tile, cascade) if using QMdiArea

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(onlineDocsAct);
    helpMenu->addAction(changelogAct);
    helpMenu->addAction(hotkeysAct);
    helpMenu->addAction(tutorialAct);
    helpMenu->addSeparator();
    helpMenu->addAction(feedbackAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    helpMenu->addAction(hallOfFameAct);
}

void MainWindow::createToolbars()
{
    fileToolBar = addToolBar(tr("File"));
    // fileToolBar->addAction(newAct); // Decide if "New Window" goes to toolbar
    // fileToolBar->addAction(openAct); // Removed
    fileToolBar->addAction(openConfigAct);
    fileToolBar->addAction(openNetworkAct);
    fileToolBar->addAction(reloadAct);
    // fileToolBar->addAction(saveConfigAct); // Maybe too much for a toolbar

    simulationToolBar = addToolBar(tr("Simulation"));
    simulationToolBar->addAction(startSimAct);
    simulationToolBar->addAction(stopSimAct);
    simulationToolBar->addAction(stepSimAct);
    simulationToolBar->addSeparator();

    // Time Display LCD
    timeDisplayLCD = new QLCDNumber(this);
    timeDisplayLCD->setSegmentStyle(QLCDNumber::Flat);
    timeDisplayLCD->setDigitCount(8); // HH:MM:SS
    timeDisplayLCD->display("00:00:00");
    simulationToolBar->addWidget(new QLabel(tr("Time: ")));
    simulationToolBar->addWidget(timeDisplayLCD);
    simulationToolBar->addSeparator();

    // Simulation Delay Controls
    simDelayLabel = new QLabel(tr("Delay (ms):"), this);
    simulationToolBar->addWidget(simDelayLabel);

    simDelaySpinBox = new QDoubleSpinBox(this);
    simDelaySpinBox->setRange(0, 10000.0); // Max 10 seconds delay
    simDelaySpinBox->setSingleStep(10.0);
    simDelaySpinBox->setValue(0.0);
    simDelaySpinBox->setDecimals(0); // Show as integer for ms
    simulationToolBar->addWidget(simDelaySpinBox);

    simDelaySlider = new QSlider(Qt::Horizontal, this);
    simDelaySlider->setRange(0, 1000); // 0 to 1000 ms, can be scaled if needed
    simDelaySlider->setValue(0);
    simulationToolBar->addWidget(simDelaySlider);

    // Connect delay controls
    connect(simDelaySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateSimDelayControls);
    connect(simDelaySlider, &QSlider::valueChanged, this, &MainWindow::updateSimDelaySpinBox);


    viewToolBar = addToolBar(tr("View"));
    viewToolBar->addAction(newViewAct);
#ifdef HAVE_OSG
    viewToolBar->addAction(newOSGViewAct);
#endif

    // Example of adding another toolbar
    // editToolBar = addToolBar(tr("Edit"));
    // editToolBar->addAction(cutAct);
    // editToolBar->addAction(copyAct);
    // editToolBar->addAction(pasteAct);
}

// ------------------- New Slot Implementations (Placeholders) -------------------

void MainWindow::openConfiguration() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open Configuration: Not implemented yet."));
    // Placeholder: Simulate opening a file
    // In a real scenario, this would come from a QFileDialog
    QString filePath = "/path/to/dummy.sumocfg"; // Example path
    addRecentFile("recentConfigs", filePath);
}

void MainWindow::openNetwork() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open Network: Not implemented yet."));
    // Placeholder: Simulate opening a file
    QString filePath = "/path/to/dummy.net.xml"; // Example path
    addRecentFile("recentNetworks", filePath);
}

void MainWindow::openShapes() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open Shapes: Not implemented yet."));
}

void MainWindow::openEdgeData() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open Edge Data: Not implemented yet."));
}

void MainWindow::reloadSimulation() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Reload Simulation: Not implemented yet."));
}

void MainWindow::quickReloadSimulation() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Quick Reload Simulation: Not implemented yet."));
}

void MainWindow::saveConfiguration() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Save Configuration: Not implemented yet."));
}

void MainWindow::closeSimulation() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Close Simulation: Not implemented yet."));
}

void MainWindow::editSelected() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Edit Selected: Not implemented yet."));
}

void MainWindow::selectLanesByPermission() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Select Lanes by Permission: Not implemented yet."));
}

void MainWindow::editBreakpoints() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Edit Breakpoints: Not implemented yet."));
}

void MainWindow::editViewScheme() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Edit View Scheme: Not implemented yet."));
}

void MainWindow::editViewport() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Edit Viewport: Not implemented yet."));
}

void MainWindow::openNetedit() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open Netedit: Not implemented yet."));
}

void MainWindow::startSimulation() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Start Simulation: Not implemented yet."));
}

void MainWindow::stopSimulation() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Stop Simulation: Not implemented yet."));
}

void MainWindow::stepSimulation() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Step Simulation: Not implemented yet."));
}

void MainWindow::saveSimState() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Save Simulation State: Not implemented yet."));
}

void MainWindow::loadSimState() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Load Simulation State: Not implemented yet."));
}

void MainWindow::appSettings() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Application Settings: Not implemented yet."));
}

void MainWindow::toggleGamingMode() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Toggle Gaming Mode: Not implemented yet. Current state: %1.").arg(toggleGamingModeAct->isChecked()));
}

void MainWindow::toggleFullScreen() {
    if (toggleFullScreenAct->isChecked()) {
        showFullScreen();
    } else {
        showNormal();
    }
    QMessageBox::information(this, tr("Action Triggered"), tr("Toggle Full Screen: Not implemented yet. Current state: %1.").arg(toggleFullScreenAct->isChecked()));
}

void MainWindow::locateJunction() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Locate Junction: Not implemented yet."));
}

void MainWindow::locateEdge() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Locate Edge: Not implemented yet."));
}

void MainWindow::openNewView() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open New 2D View: Not implemented yet."));
}

#ifdef HAVE_OSG
void MainWindow::openNewOSGView() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Open New 3D View: Not implemented yet."));
}
#endif

void MainWindow::showOnlineDocs() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Show Online Docs: Not implemented yet."));
}

void MainWindow::showChangelog() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Show Changelog: Not implemented yet."));
}

void MainWindow::showHotkeys() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Show Hotkeys: Not implemented yet."));
}

void MainWindow::showTutorial() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Show Tutorial: Not implemented yet."));
}

void MainWindow::sendFeedback() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Send Feedback: Not implemented yet."));
}

void MainWindow::showHallOfFame() {
    QMessageBox::information(this, tr("Action Triggered"), tr("Show Hall of Fame: Not implemented yet."));
}

// ------------------- Recent File Handling -------------------

// const QString RECENT_FILES_GROUP = "RecentFiles"; // Moved to top
// const int MAX_RECENT_FILES_DISPLAY = 5; // Moved to top

void MainWindow::addRecentFile(const QString& listName, const QString& filePath) {
    QSettings settings;
    QStringList files = settings.value(RECENT_FILES_GROUP + "/" + listName).toStringList();
    files.removeAll(filePath); // Remove if already exists to move to top
    files.prepend(filePath);
    while (files.size() > getRecentFiles(listName, 100).count()) { // Keep a longer internal list
        files.removeLast();
    }
    settings.setValue(RECENT_FILES_GROUP + "/" + listName, files);

    if (listName == "recentNetworks") {
        updateRecentFilesMenu(fileMenu->findChild<QMenu*>("recentNetworksMenu"), "recentNetworks", "openRecentNetwork", recentNetworkActions, MAX_RECENT_FILES_DISPLAY);
    } else if (listName == "recentConfigs") {
        updateRecentFilesMenu(fileMenu->findChild<QMenu*>("recentConfigsMenu"), "recentConfigs", "openRecentConfig", recentConfigActions, MAX_RECENT_FILES_DISPLAY);
    }
}

QStringList MainWindow::getRecentFiles(const QString& listName, int maxItems) const {
    QSettings settings;
    QStringList files = settings.value(RECENT_FILES_GROUP + "/" + listName).toStringList();
    while (files.size() > maxItems) {
        files.removeLast();
    }
    return files;
}

void MainWindow::clearRecentFiles(const QString& listName) {
    QSettings settings;
    settings.remove(RECENT_FILES_GROUP + "/" + listName);
    if (listName == "recentNetworks") {
        updateRecentFilesMenu(fileMenu->findChild<QMenu*>("recentNetworksMenu"), "recentNetworks", "openRecentNetwork", recentNetworkActions, MAX_RECENT_FILES_DISPLAY);
    } else if (listName == "recentConfigs") {
        updateRecentFilesMenu(fileMenu->findChild<QMenu*>("recentConfigsMenu"), "recentConfigs", "openRecentConfig", recentConfigActions, MAX_RECENT_FILES_DISPLAY);
    }
}


void MainWindow::createRecentFileActions(QMenu* menu, const QString& listName, QList<QAction*>& actionList, const char* slotPrefix, int maxItems) {
    if (!menu) return;

    // Clear existing actions from the menu and the list
    for (QAction *action : actionList) {
        menu->removeAction(action);
        action->deleteLater(); // Important to delete them
    }
    actionList.clear();

    QStringList files = getRecentFiles(listName, maxItems);

    for (int i = 0; i < files.size(); ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
        QAction *action = new QAction(text, this);
        action->setData(files[i]); // Store file path in action's data

        // Construct slot name like "openRecentNetwork1()"
        QString slotName = QString(slotPrefix) + QString::number(i + 1);
        // This direct connect might be problematic if slots don't exist by these exact names.
        // A more robust way is to connect to a single slot and use sender() or lambda.
    connect(action, &QAction::triggered, this, &MainWindow::openRecentFileTriggered);

        menu->addAction(action);
        actionList.append(action);
    }

    menu->setEnabled(!files.isEmpty());
}


void MainWindow::updateRecentFilesMenu(QMenu* menu, const QString& listName, const char* slotPrefix, QList<QAction*>& actionList, int maxItems) {
    createRecentFileActions(menu, listName, actionList, slotPrefix, maxItems);
}


void MainWindow::openRecentFileTriggered() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString filePath = action->data().toString();
        // Here, you would call the actual file opening logic,
        // distinguishing between network and config if necessary, or have
        // separate trigger handlers if slots were specific.
        QMessageBox::information(this, tr("Open Recent File"), tr("Attempting to open: %1\n(Actual opening logic not implemented yet.)").arg(filePath));
        // Example: if (filePath.endsWith(".sumocfg")) openConfigurationFile(filePath);
        // else if (filePath.endsWith(".net.xml")) openNetworkFile(filePath);
    }
}

// Specific handlers for numbered recent file actions are simple relays.
// Connecting directly to openRecentFileTriggered in createRecentFileActions is cleaner.
// These can be removed if all dynamic actions connect directly to openRecentFileTriggered.
// For now, they are kept as they were part of the previous structure.
void MainWindow::openRecentNetwork1() { openRecentFileTriggered(); }
void MainWindow::openRecentNetwork2() { openRecentFileTriggered(); }
void MainWindow::openRecentNetwork3() { openRecentFileTriggered(); }
void MainWindow::openRecentNetwork4() { openRecentFileTriggered(); }
void MainWindow::openRecentNetwork5() { openRecentFileTriggered(); }
void MainWindow::openRecentConfig1()  { openRecentFileTriggered(); }
void MainWindow::openRecentConfig2()  { openRecentFileTriggered(); }
void MainWindow::openRecentConfig3()  { openRecentFileTriggered(); }
void MainWindow::openRecentConfig4()  { openRecentFileTriggered(); }
void MainWindow::openRecentConfig5()  { openRecentFileTriggered(); }


// ------------------- Event Processing Placeholder -------------------

void MainWindow::processEvents() {
    myEventQueueMutex.lock();
    while (!myEventQueue.isEmpty()) {
        GUIEvent* event = myEventQueue.dequeue();
        // Process event based on its type (similar to GUIApplicationWindow::eventOccurred)
        // e.g., switch (event->getOwnType()) { ... }
        QMessageBox::information(this, tr("Event Processed"), tr("Dequeued event of type: %1").arg(event->getOwnType()));
        delete event; // Assuming events are dynamically allocated
    }
    myEventQueueMutex.unlock();
}


// Slot implementations for synchronizing simulation delay controls
void MainWindow::updateSimDelayControls(double value) {
    // Prevent feedback loop by temporarily blocking signals if values are already the same
    if (simDelaySlider->value() != static_cast<int>(value)) {
        bool oldState = simDelaySlider->blockSignals(true);
        simDelaySlider->setValue(static_cast<int>(value));
        simDelaySlider->blockSignals(oldState);
    }
}

void MainWindow::updateSimDelaySpinBox(int value) {
    // Prevent feedback loop
    if (simDelaySpinBox->value() != static_cast<double>(value)) {
        bool oldState = simDelaySpinBox->blockSignals(true);
        simDelaySpinBox->setValue(static_cast<double>(value));
        simDelaySpinBox->blockSignals(oldState);
    }
}
