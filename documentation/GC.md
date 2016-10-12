# GC
Nucleus: Interpreter has two kinds of garbage collectors. [GC 1](GC1.md) is a tracing, precise, non-incremental, mark
and sweep garbage collector. [GC 2](GC2.md) is a tracing, precise, incremental, mark and sweep garbage collector.

The garbage collector to be used is determined at compile-time by specifying the `Nucleus-Interpreter-GC` option
when invoking cmake with the values `1` (for GC 1) or `2` (for GC 2). For example, to enable GC 2 enter

```
cmake -DNucleus-Interpreter-GC=2 -DWith-Debug-Information=ON CMakeLists.txt
```

The default value of the option is `1`.
