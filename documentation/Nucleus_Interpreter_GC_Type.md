# The Nucleus Interpreter GC Type System
The dynamic type system registers

- basic types
You cn create a basic type by calling the function `Nucleus_Interpreter_GC_getOrCreateBasicType`.
- reference types
You can create a reference type by calling the function `Nucleus_Interpreter_GC_getOrCreateReferenceType`,
- array types
You can create foreign types by calling the function ``Nucleus_Interpreter_getOrCreateArrayType`.
- foreign types
You can create a foreign type by calling the function `Nucleus_Interpreter_getOrCreateForeignType`.



The GC prefixes any GC object with a GC tag (Nucleus_Interpreter_GC_Tag).

 _GC Object_s (Nucleus_Interpreter_GC_Object).

- *flags*: A combination of bit flags.
The most prominent ones are *Nucleus_GC_Object_Flags_SCALAR* and *Nucleus_GC_Object_Flags_ARRAY*.

If `Nucleus_GC_Object_Flags_ARRAY == o->flags & Nucleus_GC_Object_Flags_ARRAY` is true, then the
`[size:Nucleus_Integer][GC_Object][payload]`
_GC_Object` allocat

- *numberOfLocks*: The number of locks on the GC object.
This number is always non-negative. A positive value indicates that the GC may not deallocate this GC object.
_GC Object_s come in three kinds:

The first object is the _Foreign GC Object_.


The type system provides information required
When the GC allocates a GC object, this object has a type associated.

The type (of the GC object) denotes
- the visitor
- the finalizer

Furthermore it denotes wether the GC object is an array or is not an array.

If the type (of the GC object) denotes that the GC object is an array, then it - in addition to the above - denotes
- the size, in Bytes, (of an element of the array)
- the type of the elements (of the array)

If the type (of the GC object) denotes that the GC object is notan array, then it - in addition to the above - denotes
- the size, in Bytes, of the GC object

```
struct GC_Type
{
    uint8_t flags; //
    GC_Finalizer *finalizer;
    GC_Visitor *visitor;
};