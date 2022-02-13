# OnTimeDB

Scalable and fast data store optimised for time series data such as financial data, events, metrics for real time
analysis

OnTimeDB is a time series data written in C to be extremely efficient and scalable.

## Running with Bazel

`bazel build`

`bazel run bin:ontimedb`

Run the main tests
`bazel test --test_output=all test:ontimedb_test`

Run the library tests
`cd OnTimeDbLib`
`bazel test --test_output=all test:ontimedblib_test`

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
