/*
 *
 * (C) Copyright IBM Corp. 1998-2004 - All Rights Reserved
 *
 */

#ifndef __INDICREARRANGEMENTPROCESSOR_H
#define __INDICREARRANGEMENTPROCESSOR_H

/**
 * \file
 * \internal
 */

#include "LETypes.h"
#include "MorphTables.h"
#include "SubtableProcessor.h"
#include "StateTableProcessor.h"
#include "IndicRearrangement.h"

U_NAMESPACE_BEGIN

class LEGlyphStorage;

class IndicRearrangementProcessor : public StateTableProcessor
{
public:
    virtual void beginStateTable();

    virtual ByteOffset processStateEntry(LEGlyphStorage &glyphStorage, le_int32 &currGlyph, EntryTableIndex index);

    virtual void endStateTable();

    void doRearrangementAction(LEGlyphStorage &glyphStorage, IndicRearrangementVerb verb) const;

    IndicRearrangementProcessor(const MorphSubtableHeader *morphSubtableHeader);
    virtual ~IndicRearrangementProcessor();

    /**
     * ICU "poor man's RTTI", returns a UClassID for the actual class.
     *
     * @stable ICU 2.8
     */
    virtual inline UClassID getDynamicClassID() const { return getStaticClassID(); }

    /**
     * ICU "poor man's RTTI", returns a UClassID for this class.
     *
     * @stable ICU 2.8
     */
    static inline UClassID getStaticClassID() { return (UClassID)&fgClassID; }

protected:
    le_int32 firstGlyph;
    le_int32 lastGlyph;

    const IndicRearrangementStateEntry *entryTable;
    const IndicRearrangementSubtableHeader *indicRearrangementSubtableHeader;

private:

    /**
     * The address of this static class variable serves as this class's ID
     * for ICU "poor man's RTTI".
     */
    static const char fgClassID;
};

U_NAMESPACE_END
#endif
