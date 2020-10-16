It's an oldie but a goodie. The dining philosophers.

The organization of this code is inspired, oddly, by the version Thomas W. Christopher and I developed in our HPJPC Book for the Sun Java Series of books.

`diner_t` is the "runnable". It therefore keeps a `pthread_t` instance as part of its implementation.
`fork_t` is the shared resource. It threfore keeps a `pthread_mutex_t` instance as part of its implementation.

You can run this code with and without going into deadlock.

To run the version that goes into deadlock, just do:

```
./bin/diner-demo
```

To run the version that avoids deadlock using resource enumeration (i.e. reordering the forks so there is no cycle of locks), try:

```
DINING_POLICY=avoid_deadlock ./bin/diner-demo
```

To see the original version in Java, see https://github.com/LoyolaChicagoCode/hpjpc-source-java/tree/master/src/main/java/info/jhpc/textbook/chapter03.

