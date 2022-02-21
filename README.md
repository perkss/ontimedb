# OnTimeDB

Scalable and fast data store optimised for time series data such as financial data, events, metrics for real time
analysis

OnTimeDB is a time series data written in C to be extremely efficient and scalable.

## Running with CMake

Build
`cmake -S . -B build`

`cmake --build build`

Install
`cmake --build . --target install`

Run the tests Be sure to build first if changes
`cmake --build build`
Then run the tests
`cmake --build build --target test`

## Design and Implementation

Please check the [Wiki](https://github.com/perkss/ontimedb/wiki) for detailed information.

We are currently in the design phase and we wish for ideas and contributions on the design. Please get involved.

### Storage

### Replication

### Consistency

#### Conflict Free Resolution Data Type

### Leader Election

## Contributing

Please read the [contributing](CONTRIBUTING.md) section. 
