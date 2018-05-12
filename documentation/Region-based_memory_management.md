# Arenas
An arena contains objects or references to these. For example, there are arena for array, locks, strings,
and foreign objects. For examples, the string area contains strings (objects) and the lock area contains
lock (referencs to objects).

From the perspective of the GC, an arena is an object which supports the *premark* and the *sweep* callback.
The GC invokes the first callback for all arenas to determine the root objects. The second callback is invoked
by the GC when the arena may sweep its objects for black/dead objects.

Regions are usually optimized for their particular type of object/task they perform.
For example, the string arenas performs string interning to conserve memory.

# The locks arena
There is a special arena for locks. It does not contain objects but rather references to objects.
Any object for which this arena has a reference to is a root object.
As locks are used infrequently, this form of ulterior reference counting is cheaper than interior
reference counting as the former does not require storing a reference count along with each object.

## References

- [Region-based memory management - Wikipedia](https://en.wikipedia.org/wiki/Region-based_memory_management)