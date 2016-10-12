# GC 1
GC 1 is a garbage collector supported by Nucleus: Interpreter.

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


## GC 2

The GC is a tracing, precise, incremental mark and sweep garbage collector.
It has three phases:
- Premark
- Mark
- Sweep

In the premark phase, roots are identified.
In the mark phase, all objects reachable from the roots are identified.
In the sweep phase, all objects **not** reachable from the roots are destroyed.

These three phases may be executed without the mutator interfering.

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

## Mutator
The GC is incremental which means that in the mark phase, only a certain amount of gray objects
are visisted and colored black. The GC will stop marking after a certain limit and the mutator
may run. Obviously, there might be new roots and the reachability relations might have changed.

To support this, the mutator has to provide some support:

- When the object reachability relations change, such that a black objects now refers to a white object,
  the white object needs to be colored gray.
- When the mutator makes a non-root objects into a root objects,
  and these objects are white, then these objects are colored gray.
