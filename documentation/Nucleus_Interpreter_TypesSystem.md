# Nucleus: Interpreter - Types

The following types

- `Nucleus_Interpreter_Boolean`,
- `Nucleus_Interpreter_Integer`,
- `Nucleus_Interpreter_Object`,
- `Nucleus_Interpreter_Real`,
- `Nucleus_Interpreter_String`,
- `Nucleus_Interpreter_Symbol`, and
- `Nucleus_Interpreter_Void`

are built-in the interpreter.

`Nucleus_Interpreter_Boolean`, `Nucleus_Interpreter_Integer`, `Nucleus_Interpreter_Real`, `Nucleus_Interpreter_Symbol`,
and `Nucleus_Interpreter_Void` are pass-by-value types, `Nucleus_Interpreter_String` and `Nucleus_Interpreter_Object`
are pass-by-pointer types. pass-by-value means that the values are passed around, pass-by-pointer means that pointers to
the objects are passed around.

The union of all types is represented by `Nucleus_Interpreter_Value` which is an `union` type.

**Possible Implementation**
```
typedef union Nucleus_Interpreter_Value`
{
    Nucleus_Interpreter_Boolean booleanValue;
    Nucleus_Interpreter_Integer integerValue;
    Nucleus_Interpreter_Object *objectValue;
    Nucleus_Interpreter_Real realValue;
    Nucleus_Interpreter_String *stringValue;
    Nucleus_Interpreter_Symbol symbolValue;
    Nucleus_Interpreter_Void voidValue;
} Nucleus_Interpreter_Value;
```

`Nucleus_Interpreter_TaggedValue` is a `struct` type combines a tag and a `Nucleus_Interpreter_Value`.

**Possible Implementation**
```
typedef struct Nucleus_Interpreter_TaggedValue`
{
    Nucleus_Interpreter_Tag tag;
    Nucleus_Interpreter_Value value;
} Nucleus_Interpreter_TaggedValue;
```

A tag is an `enum` type with the enumeration elements
- `Nucleus_Interpreter_Tag_Boolean`,
- `Nucleus_Interpreter_Tag_Integer`,
- `Nucleus_Interpreter_Tag_Object`,
- `Nucleus_Interpreter_Tag_Real`,
- `Nucleus_Interpreter_Tag_String`,
- `Nucleus_Interpreter_Tag_Symbol`, and
- `Nucleus_Interpreter_Tag_Void`


**Possible Implementation**
```
typedef enum Nucleus_Interpreter_Tag
{
    Nucleus_Interpreter_Tag_Boolean = /* implementation details */,
    Nucleus_Interpreter_Tag_Integer = /* implementation details */,
    Nucleus_Interpreter_Tag_Object = /* implementation details */,
    Nucleus_Interpreter_Tag_Real = /* implementation details */,
    Nucleus_Interpreter_Tag_String = /* implementation details */,
    Nucleus_Interpreter_Tag_Symbol = /* implementation details */,
    Nucleus_Interpreter_Tag_Void = /* implementation details */,
} Nucleus_Interpreter_Tag;
```

## `Nucleus_Interpreter_Boolean`
The type `Nucleus_Interpreter_Boolean` is the C representation of the `Boolean` type.
The symbolic constants `Nucleus_Interpreter_Boolean_TrueConstant` and `Nucleus_Interpreter_Boolean_FalseConstant`
represent the values of the constant variables _`Boolean.True`_ and _`Boolean.False`_.

```
typedef /* implementation details */ Nucleus_Interpreter_Boolean;
#define Nucleus_Interpreter_Boolean_TrueConstant /* implementation details */
#define Nucleus_Interpreter_Boolean_FalseConstant /* implementation details */
```

## `Nucleus_Interpreter_Integer`
The type `Nucleus_Interpreter_Integer` is the C representation of the *Integer* type.
The symbolic constants `Nucleus_Interpreter_Integer_LeastConstant` and `Nucleus_Interpreter_Integer_GreatestConstant`
represent the values of the constant variables _`Integer.Least`_ and _`Integer.Greatest`_.

```
typedef /* implementation details */ Nucleus_Interpreter_Integer;
#define Nucleus_Interpreter_Integer_Least /* implementation details */
#define Nucleus_Interpreter_Integer_Greatest /* implementation details */
```

## `Nucleus_Interpreter_Real`
The type `Nucleus_Interpreter_Real` is the C representation of the *Real* type.
The symbolic constants `Nucleus_Interpreter_Real_LeastConstant` and `Nucleus_Interpreter_Real_GreatestConstant` represent
the values of the constant variables _`Real.Least`_ and _`Real.Greatest`_.

```
typedef /* implementation details */ Nucleus_Interpreter_Real;
#define Nucleus_Interpreter_Real_LeastConstant /* implementation details */
#define Nucleus_Interpreter_Real_GreatestConstant /* implementation details */
```

## `Nucleus_Interpreter_Void`
The type `Nucleus_Interpreter_Void` is the C representation of the `Void` type.
The symbolic constants `Nucleus_Interpreter_Void_VoidConstant` represents the single value `void` of the type `Void`.
`void` is only equal to itself.

| data specifier      | description |
|---------------------|-------------|
| `${Boolean}` | print a _`Boolean`_ value. A single argument is required, a `Nucleus_Interpreter_Boolean` value.     |
| `${Integer}` | print an _`Integer`_ value. A single argument is required, a `Nucleus_Interpreter_Integer` value.    |
| `${Real}`    | print a _`Real`_ value. A single argument is required, a `Nucleus_Interpreter_Real` value.           |
| `${String}`  | print a _`String`_ value. A single argument is required, a `Nucleus_Interpreter_String` value.       |
| `${Symbol}`  | print a _`Symbol`_ value. A single argument is required, a `Nucleus_Interpreter_Symbol` value.       |
| `${Object}`  | print an _`Object`_ value. A single argument is required, a `Nucleus_Interpreter_Object` value.      |
