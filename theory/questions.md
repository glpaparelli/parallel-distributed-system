## Questions 2023

#### 1) Amdahl's Law: what is it and how can you derivate the fomula
**Amdahal Law is** **a** **crucial principle in parallel theory** **used to make predictions about the theoretical speedup** obtainable when multiple processing unit are used. 

It states that if a program has a portion $f$ of non parallelizable then the speedup is limited to $\frac{1}{f}$, no matter how many processing unit you have at your disposal. 

To prove it we assume, as stated that a program is divided in a portion $f$ of non parallelizable work and the remaining portion $1-f$ of parallelizable worksquare
Hence the best theoretical solution is that the time to sequentially compute the parallelizable work is scaled down to $$\frac{(1-f)T_{seq}}{n}$$Then we have that: 
$$speedup(n) = \frac{T_{seq}}{T_{par}} = \frac{T_{seq}}{f\cdot T_{seq} + (1-f)\frac{T_{seq}}{n}} = \frac{T_{seq}}{T_{seq}(f + \frac{1-f}{n})} = \frac{1}{f + \frac{1-f}{n}}$$
And we obtain that: $$\text{lim}_{n \rightarrow \infty} \frac{1}{f + \frac{1-f}{n}} = \frac{1}{f}$$
Which means that, with **the processing unit tending to infinite, the speedup is limited by the sequential portion of the work** $\square$ 
#### 2) Gustafsson's Law: what is it and how can you derivate the formula
**Gustafson Law is another crucial principle of parallel theory** and it addresses the shortcomings of Amdahal's law. 

Amdahal's law assume that the problem size remains constant, while **Gustafson recognize that programmers tends to exploit the resources they have by also increasing the workload/size of the problem.** 

Say that we have: 
- $n$ workers
- $f$ non-parallelizable work
- $1-f$ parallelizable work

Gustafsson found that the speedup gained using parallelism is $$speedup(n) = f + n(1-f) = f + n - nf = n - f(n-1)$$Basically **Gustafsson propose that the size of the problem grows proportionally to the number of processing units: in the same time we can solve a bigger instance of the problem.**
#### 3) What is the Actor Model?
**The actor model is model of concurrent computation that treats an actor as the basic building block of concurrent computation.** 

The actor model adopts the philosophy that everything is an actor. 
This is similar to the everything is an object philosophy used by some object-oriented programming languages.

**In response to a message it receives, an actor can:** 
- make local decisions
- create more actors
- send more messages
- determine how to respond to the next message received. 

Actors may modify their own private state, but can only affect each other indirectly through messaging (removing the need for lock-based synchronization)

The actor model is characterized by inherent concurrency of computation within and among actors, dynamic creation of actors, inclusion of actor addresses in messages, and interaction only through direct asynchronous message passing with no restriction on message arrival order.

The said communication is also **one-way asynchronous**: once a message has been sent, it is the responsibility of the receiver.
Because of the indeterminism, it's important that the actions are **quasi-commutative**: the order in which messages are sent between actors must not affect the final outcome of the system.

Note that due to the said features, the Actor model supports **fault-tolerance** (actors can be restarted/moved to another machine) and **scalability** (new actors can be created).
#### 4) What's Spark? Are there other frameworks? Talk about GraphX
Apache Spark is 

#### 5) Questions about the rewriting rules concerning the map fusion and what other metrics can be adopted

#### 6) Stream and Data Parallel characteristics

#### 7) Collective communication in MPI and HDFS

#### 9) how I would implement the decoding of the file: I replied that I could make a pipeline, in which the first stage, automaton type that recognizes the prefixes, the second stage decode, the third write in append, etc.

#### 10) asked in MPI how I could distribute: I did an analysis related to the file size, the structures in play and their size, the possibilities using mpi_reduce, map_reduce, broadcast etc...

#### 11) Advantages of using map fusion (mostly in a distributed system)

#### 12) In which occasions map fusion could be a bad choice

#### 13) Scatter and Gather in MPI

#### 14) What Is the role of the communicator in MPI

#### 15) Why rank in MPI are integer values

#### 16) Spark Shared Variables

#### 17) Map Fusion's relation with Spark's transformations

#### 19) Job Stealing

#### 20) Formulate a dynamic scheduling technique which finds compromises between Job Stealing and Auto Scheduling

#### 21) How to use MPI to implement the PageRank?

#### 22) What's Macro Data Flow?

#### 23) What's Vectorization and what are the 4 conditions for loops?

## GitHub (2017 - 2021)

#### 1) Map fusion, difference between equivalence rules `comp(map(f), map(g)) == map(comp(f, g))` and `pipe(map(f), map(g)) == map(comp(f, g))`. How many resources are needed for each of those cases?

#### 4) Autonomic farm management. How can I implement autonomic management in FastFlow? Can I implement `farmout(pipe(s1, s2, s3))` at runtime in FastFlow? (No) Would it change anything if the library was not header####based but was in a `.so` file? (No because it depends on the FastFlow API).

#### 5) Macro Data Flow with examples

#### 6) Building blocks for Streaming and Data Parallelism

#### 7) Point to point and collective communication in fast flow. When to use collective communication

#### 8) Service time, latency, efficiency and example where to use what metrics

#### 9) Why didn't you use a manager and have the emitter do everything? Do you have more data movements with the manager? Does the emitter have any earnings if there is a manager?

#### 10) Why do you start immediately with a fixed number of workers? Wouldn't it have been better to have him work one and then figure out how many workers they need dynamically?

#### 11) It would have been right to do an analysis of the time it takes to make a switch of the number of workers in order to understand how often to change

#### 12) If I have two maps, which optimizations can I do? If I do map fusion then do I have a profit? Do I always have it?

#### 13) If I put a map inside a farm, what profit do I have if I increase the number of workers on the map or if I increase the number of workers in the farm? If I remove the map and leave the farm increasing the workers does something change? How does efficiency change? If I remove everything and leave only a sequential node, does something change? How does the efficiency vary (becomes 1)?

#### 14) Difference between work span model and amdahl law, he wanted to know that nodes must have the same execution time

#### 15) How is the speedup calculated?

#### 17) What should I add to a farm that takes into account both time and energy consumption (considering that both depend on the nw)? I have to take into account the degree of parallelism and the frequency of the processor. In the collector I can calculate the service time Ts. I can vary the number of workers and see how the energy changes as the nw increases. More worker = less CPU usage time with more consumption. I can stop when it becomes inconvenient to increase the nw for overhead

#### 18) Types of patterns

## Huffman Coding Related Questions
#### 1) How could you use the Actor Model for the counting part of the Huffman Project?

#### 2) What kind of refactoring rule I could have done on the project (huffman): I answered with mapfusion and I argued