/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2023 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GNEToolDialog.h
/// @author  Pablo Alvarez Lopez
/// @date    Jun 2022
///
// Dialog for tools
/****************************************************************************/
#pragma once
#include <config.h>

#include <utils/options/OptionsCont.h>

#include "GNEToolDialogElements.h"

// ===========================================================================
// class declarations
// ===========================================================================

class GNEApplicationWindow;
class GNETool;

// ===========================================================================
// class definitions
// ===========================================================================

/**
 * @class GNEToolDialog
 * @brief Abstract dialog for tools
 */
class GNEToolDialog : protected FXDialogBox {
    /// @brief FOX-declaration
    FXDECLARE(GNEToolDialog)

    /// @brief declare friend class
    friend class GNEToolDialogElements;

public:
    /// @brief Constructor
    GNEToolDialog(GNEApplicationWindow* GNEApp);

    /// @brief destructor
    ~GNEToolDialog();

    /// @brief open window
    void openDialog(GNETool* tool);

    /// @name FOX-callbacks
    /// @{

    /// @brief event after press run button
    long onCmdRun(FXObject*, FXSelector, void*);

    /// @brief event after press cancel button
    long onCmdCancel(FXObject*, FXSelector, void*);

    /// @brief event after press reset button
    long onCmdReset(FXObject*, FXSelector, void*);

    /// @}

protected:
    /// @brief FOX needs this
    GNEToolDialog();

    /// @brief build arguments
    void buildArguments();

    /// @brief adjust parameter column
    void adjustParameterColumn();

    /// @brief vertical frame for contents
    FXVerticalFrame* myContentFrame = nullptr;

private:
    /// @brief pointer to GNEApplicationWindow
    GNEApplicationWindow* myGNEApp;

    /// @brief tool
    GNETool* myTool = nullptr;

    /// @brief parameter label
    FXLabel* myParameterLabel = nullptr;

    /// @brief separator
    FXSeparator* mySeparator = nullptr;

    /// @brief buttons frame
    FXHorizontalFrame* myButtonsFrame = nullptr;

    /// @brief list of arguments
    std::vector<GNEToolDialogElements::Argument*> myArguments;

    /// @brief Invalidated copy constructor.
    GNEToolDialog(const GNEToolDialog&) = delete;

    /// @brief Invalidated assignment operator.
    GNEToolDialog& operator=(const GNEToolDialog&) = delete;
};

