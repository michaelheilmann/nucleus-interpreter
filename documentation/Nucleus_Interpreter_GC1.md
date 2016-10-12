# GC
This describes the garbage collection algorithm currently implemented in the Nucleus Interpreter.

## GC 1

The GC is a tracing, precise, non-incremental, mark and sweep garbage collector.
It has three phases:
- Premark
- Mark
- Sweep

In the premark phase, roots are identified.
In the mark phase, all objects reachable from the roots are identified.
In the sweep phase, all objects **not** reachable from the roots are destroyed.

These three phases have to be executed without the mutator interfering.

## Premark phase

For each heap `premark` is invoked.
As a result, all root objects are either
- black or
- gray.

## Mark phase
As long as there are gray objects, visit each object and color it black.

## Sweep phase.
For each heap `sweep` is invoked.
As a result, each white object on a heap is destroyed.
