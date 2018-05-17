#include "Nucleus/Interpreter/GC/OnVisit.h"

#include "Nucleus/Interpreter/TS.h"
#include "Nucleus/Interpreter/GC/Object.h"
#include "Nucleus/Interpreter/GC/Arena.h"
#include "Nucleus/Interpreter/Context.h"

Nucleus_Interpreter_NonNull() static void
onMarkArray
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() static void
onMarkForeignObject
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag
    );

Nucleus_Interpreter_NonNull() static void
onMark
    (
        Nucleus_Interpreter_Context *context
    );

Nucleus_Interpreter_NonNull() static void
onMarkArray
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag
    )
{
    Nucleus_Interpreter_GC *gc = &(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc);
    Nucleus_Interpreter_Type *type = Nucleus_Interpreter_GC_Tag_getType(context, tag);
    Nucleus_Interpreter_Type *elementType = type->arrayType.elementType;
    if (Nucleus_Interpreter_isArrayType(elementType) || Nucleus_Interpreter_isForeignType(elementType))
    {
        void **elements =  tag2Address(tag);
        for (size_t i = 0, n = tag2ArrayTag(tag)->length; i < n; ++i)
        {
            void *element = elements[i];
            if (NULL != element)
            {
                Nucleus_Interpreter_GC_Tag *elementTag = address2Tag(element);
                if (Nucleus_Interpreter_GC_Tag_isWhite(elementTag))
                {
                    elementTag->next = gc->gray;
                    gc->gray = elementTag;
                    Nucleus_Interpreter_GC_Tag_setGray(elementTag);
                }
            }
        }
    }
    Nucleus_Interpreter_GC_Tag_setBlack(tag);
}

Nucleus_Interpreter_NonNull() static void
onMarkForeignObject
    (
        Nucleus_Interpreter_Context *context,
        Nucleus_Interpreter_GC_Tag *tag
    )
{
    Nucleus_Interpreter_GC *gc = &(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc);
    Nucleus_Interpreter_Type *type = Nucleus_Interpreter_GC_Tag_getType(context, tag);
    do
    {
        if (type->foreignType.visitForeignObject)
        {
            type->foreignType.visitForeignObject(context, tag2Address(tag));
        }
        type = type->foreignType.parentType;
    } while (NULL != type);
    Nucleus_Interpreter_GC_Tag_setBlack(tag);
}

Nucleus_Interpreter_NonNull() static void
onMark
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_GC *gc = &(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc);
#if DEBUG
    if (gc->state != Nucleus_Interpreter_GC_State_Mark)
    {
        fprintf(stderr, "%s:%d: internal error\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
#endif
    while (gc->gray)
    {
        Nucleus_Interpreter_GC_Tag *tag = gc->gray; gc->gray = tag->gray;
        Nucleus_Interpreter_Type *type = Nucleus_Interpreter_GC_Tag_getType(context, tag);
        if (type)
        {
            if (Nucleus_Interpreter_isArrayType(type))
            {
                onMarkArray(context, tag);
            }
            else if (Nucleus_Interpreter_isForeignType(type))
            {
                onMarkForeignObject(context, tag);
            }
        }
        Nucleus_Interpreter_GC_Tag_setBlack(tag);
    }
}

Nucleus_Interpreter_NonNull() void
Nucleus_Interpreter_GC_onRun
    (
        Nucleus_Interpreter_Context *context
    )
{
    Nucleus_Interpreter_GC *gc = &(NUCLEUS_INTERPRETER_PROCESSCONTEXT(context)->gc);
    do
    {
        if (gc->state == Nucleus_Interpreter_GC_State_Idle)
        {
            gc->state = Nucleus_Interpreter_GC_State_Premark;
        }
        else if (gc->state == Nucleus_Interpreter_GC_State_Premark)
        {
			Nucleus_Size i, n;
			Nucleus_Collections_PointerArray_getSize(&gc->arenas, &n); // Return value can be ignored.
			for (i = 0; i < n; ++i)
			{
				Nucleus_Interpreter_GC_Arena *arena = NULL;
				Nucleus_Collections_PointerArray_at(&gc->arenas, i, (void **)&arena); // Return value can be ignored.
				Nucleus_Interpreter_GC_Arena_premark(context, arena);

			}
            gc->state = Nucleus_Interpreter_GC_State_Mark;
        }
        else if (gc->state == Nucleus_Interpreter_GC_State_Mark)
        {
            onMark(context);
            gc->state = Nucleus_Interpreter_GC_State_Sweep;
        }
        if (gc->state == Nucleus_Interpreter_GC_State_Sweep)
        {
			Nucleus_Size i, n;
			Nucleus_Collections_PointerArray_getSize(&gc->arenas, &n); // Return value can be ignored.
			for (i = 0; i < n; ++i)
			{
				Nucleus_Interpreter_GC_Arena *arena = NULL;
				Nucleus_Collections_PointerArray_at(&gc->arenas, i, (void **)&arena); // Return value can be ignored.
				Nucleus_Interpreter_GC_Arena_sweep(context, arena);

			}
            gc->state = Nucleus_Interpreter_GC_State_Idle;
        }
    } while (gc->state == Nucleus_Interpreter_GC_State_Idle);
}
