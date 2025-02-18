### Cleanup
[X] move non-constructor functions from structures module to elsewhere
    - moved to elements_common module
[X] correct error type for flux discrepancy calculation calls
[ ] better utilize element configs in the element configs VTABLE constant so that element structs might be smaller.
    - this allows the node and element structs to have the same size, so you get better arena utilization