////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CHECKBOX_H__
#define __GUI_CHECKBOX_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ToggleButton.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a control that a user can select and clear.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.checkbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CheckBox: public ToggleButton
{
protected:
    /// From UIElement
    //@{
    void OnKeyDown(const KeyEventArgs& e) override;
    //@}

    NS_DECLARE_REFLECTION(CheckBox, ToggleButton)
};

}

#endif
