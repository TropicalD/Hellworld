/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2022 - Raw Material Software Limited

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 7 End-User License
   Agreement and JUCE Privacy Policy.

   End User License Agreement: www.juce.com/juce-7-licence
   Privacy Policy: www.juce.com/juce-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

/**
    An abstract base class which can be implemented by components that function as
    text editors.

    This class allows different types of text editor component to provide a uniform
    interface, which can be used by things like OS-specific input methods, on-screen
    keyboards, etc.

    @tags{GUI}
*/
class JUCE_API  TextInputTarget
{
public:
    //==============================================================================
    /** */
    TextInputTarget() = default;

    /** Destructor. */
    virtual ~TextInputTarget() = default;

    /** Returns true if this input target is currently accepting input.
        For example, a text editor might return false if it's in read-only mode.
    */
    virtual bool isTextInputActive() const = 0;

    /** Returns the extents of the selected text region, or an empty range if
        nothing is selected,
    */
    virtual Range<int> getHighlightedRegion() const = 0;

    /** Sets the currently-selected text region. */
    virtual void setHighlightedRegion (const Range<int>& newRange) = 0;

    /** Sets a number of temporarily underlined sections.
        This is needed by MS Windows input method UI.
    */
    virtual void setTemporaryUnderlining (const Array<Range<int>>& underlinedRegions) = 0;

    /** Returns a specified sub-section of the text. */
    virtual String getTextInRange (const Range<int>& range) const = 0;

    /** Inserts some text, overwriting the selected text region, if there is one. */
    virtual void insertTextAtCaret (const String& textToInsert) = 0;

    /** Returns the current index of the caret. */
    virtual int getCaretPosition() const = 0;

    /** Returns the position of the caret, relative to the component's origin. */
    Rectangle<int> getCaretRectangle() const        { return getCaretRectangleForCharIndex (getCaretPosition()); }

    /** Returns the bounding box of the character at the given index. */
    virtual Rectangle<int> getCaretRectangleForCharIndex (int characterIndex) const = 0;

    /** Returns the total number of codepoints in the string. */
    virtual int getTotalNumChars() const = 0;

    /** Returns the index closest to the given point.

        This is the location where the cursor might be placed after clicking at the given
        point in a text field.
    */
    virtual int getCharIndexForPoint (Point<int> point) const = 0;

    /** Returns the bounding box for a range of text in the editor. As the range may span
        multiple lines, this method returns a RectangleList.

        The bounds are relative to the component's top-left and may extend beyond the bounds
        of the component if the text is long and word wrapping is disabled.
    */
    virtual RectangleList<int> getTextBounds (Range<int> textRange) const = 0;

    /** A set of possible on-screen keyboard types, for use in the
        getKeyboardType() method.
    */
    enum VirtualKeyboardType
    {
        textKeyboard = 0,
        numericKeyboard,
        decimalKeyboard,
        urlKeyboard,
        emailAddressKeyboard,
        phoneNumberKeyboard,
        passwordKeyboard
    };

    /** Returns the target's preference for the type of keyboard that would be most appropriate.
        This may be ignored, depending on the capabilities of the OS.
    */
    virtual VirtualKeyboardType getKeyboardType()       { return textKeyboard; }
};

} // namespace juce
