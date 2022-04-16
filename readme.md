# Scythe

## Synopsis

Scythe is a garbage collector that runs in linear time, is predictable, and never pauses the world.

## Specification

Programs are made up of multiple processes, where each process has a callstack and executes the most recent state of its callstack. Processes may launch other processes, as well as potentially share objects in memory with these new processes. Processes can add new states to their callstacks (such as during function calls), again potentially sharing objects in memory.

There are two types of objects:

1. *Collections*: Objects that may contain references to other objects (such as arrays, linked lists, or maps). A collection may contain more than one reference to the same object. Each collection must be able to be entirely scanned within linear time.
2. *Singulars*: Objects that cannot contain references to other objects.

For each state of each callstack, we maintain three different listings of objects:

1. *Owned objects*: Objects that can be deallocated immediately upon termination of the state.
2. *Borrowed objects*: Objects that cannot be deallocated immediately upon termination of the state.
3. *Collected objects*: Objects that might not be able to be immediately deallocated upon termination of the state.

If an object belongs to a listing of owned objects, it may not belong in any listing of collected objects, only belong to a single listing of owned objects, and can belong in any number of listings of borrowed objects.

All objects that belong to at least one listing of borrowed objects must also belong to a listing of owned objects.

Each object that belongs to at least one listing of collected objects maintains a unique counter that represents the sum of the number of listings of collected objects that the object belongs to and the number of belongings to collections throughout the program that the object has.

Whenever a state terminates, it immediately deallocates all of its owned objects, then subtracts the counter for each object within its collected objects. If a counter is zero after subtraction, then that object is deallocated.

Deallocation of singulars is obvious. Deallocation of a collection requires scanning it and deallocating each found object before deallocating the collection itself in the obvious way. Deallocation may be recursive.

Any operation that adds an object to a collection must increment the object's counter if it has one. This counter must be incremented for each time the object is added to the collection. Any operation that removes objects from collections must do the inverse.

If you add an owned object to a collected collection, then the object must become collected. If you add a collected object to an owned collection, then the collection must become collected.

## Examples

All of the following example programs are written in Go.

```
package main
import "fmt"

func main() {
	foo := 42
	fmt.Println(foo)
}
```

In this program, `foo` is owned by `main()`, hence, when `main()` terminates, `foo` will be deallocated.

```
package main
import "fmt"

func getFoo() *int {
	foo := 42
	return &foo
}

func main() {
	foo := getFoo()
	fmt.Println(*foo)
}
```

Object | Owner | Counter
--- | --- | ---
`foo` || 2
