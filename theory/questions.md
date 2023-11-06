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
**Apache Spark is a unified analytics engine for large-scale data processing.** 
It is based on the Hadoop Approach: it does support MapReduce, but also SQL queries, data streaming, machine learning and graph algorithms. 

**The main component is the driver program**, which runs the `main()` and creates the `SparkContext`, which is the entry point to any Spark functionality. 
**The driver program is responsible for dividing the work into tasks and schedule them across the clusters.** 

**Spark support two kinds of shared variables** across tasks: 
- **broadcast**: read-only variables that are cached on each machine
- **accumulators**: write-only variables that can only be increased

As said Spark has been influenced by Hadoop, which is a framework that allows for the distributed processing of large data sets across clusters of computers using simple programming models. 
##### GraphX
**GraphX is a distributed graph processing framework built on top of Spark.** 
It supports the most common graph operations (vertices/edges counting, reverse, subgraphing, ...) and has built-in algorithms (PageRank, Connected Components, Shortest Path, ...)

GraphX is implemented using the concept **TLAV** (Think Like a Vertex) and it leverages two models: 
- Bulk Synchronous Parallel (BSP) Model
- Actor Model 
###### Think Like a Vertex
The vertex is the primary unit of computation, it maintains a state (label, attributes, ...) and it can send messages to its neighbours, which can in turn update their state with the info received with those messages. 
###### Actor Model
See before
###### Bulk Synchronous Parallel Model
The BSP Model is a parallel computing model that divides the computation into supersteps, where each superstep consists in: 
- a computation phase
- a communication phase
- a synchronization phase
Thanks to the last phase no superstep can overlap. 

**Mind that BSP model adopt the TLAV philosophy:** the compute units are the vertices, they can communicate and exchange messages with each other and synchronize at the end of every superstep. 
#### 5) Stream and Data Parallelism
We can outline two approaches to parallelism: 
**Data Parallelism:** parallelism resulting from the division of an initial task in subtask, each subtask is then computed in parallel and the results are combined to obtain the result of the original task. 
It is effective to reduce the latency of a program. 

**Stream Parallelism:** parallelism resulting from the parallel execution of different tasks available at different times on an input stream. 
It is effective to increase throughput. 
#### 7) Collective communication in MPI and HDFS

#### 9) how I would implement the decoding of the file: I replied that I could make a pipeline, in which the first stage, automaton type that recognizes the prefixes, the second stage decode, the third write in append, etc.

#### 10) asked in MPI how I could distribute: I did an analysis related to the file size, the structures in play and their size, the possibilities using mpi_reduce, map_reduce, broadcast etc...

#### 11) Advantages of using Map Fusion
An idea to improve a composition of sequences of map-reduce comes from the theoretical result named map fusion, which it aims to move as less data as possible to give the final result. 

The map operation applies a function to every element of a collection of data, producing another collection of data. 
If we have a series of map operations we have a sequence of intermediate collections that are formally useless to store. 
To reduce this problem we can, if possible, fuse some maps, in order to not store/pass the intermediate collection. 

As an example consider the following code: 
```
numbers = [1,2,3,4]
result = numbers.map(_ +1).map(_ *2)
```
The consecutive applications of `map` are inefficient and they can be fused to obtain: 
```
numbers = [1,2,3,4]
result = numbers.map(x -> (x+1)*2)
```

**The advantages are then clear:** 
- **less space required** (in no instance the intermediate collection is stored)
- **less time used** (there is no waste of time creating and deallocating the intermediate collection)
- **less communication overhead** if the process is parallel and/or distributed (the intermediate collection is never sent to anyone as it never exists)
#### 13) Scatter and Gather in MPI
- `MPI_Scatter(...)` distribute a message (e.g. an array) among multiple processes
- `MPI_Gather(...)` the inverse of `MPI_Bcast(...)`, a process receives `n` messages from other processes
	- `MPI_Bcast(...)` broadcast message(s) to all the processes

#### 14) What is the Role of the Communicator in MPI
In the Message Passing Interface we have three main entities: 
- **Communicator**
- **Group**
- **Process**

The **Communicator** is an object that encompasses a group of processes that have the ability to communicate with one another, achieving point-to-point communication. 
A **Group** is a group of processes. 
A **Process** has a rank (ID) and they can send/receive messages to/from other processes by providing a rank and a tag to uniquely identify the message. 
#### 15) Why rank in MPI are integer values

#### 16) Spark Shared Variables
Spark supports two kinds of shared variables across tasks: 
- **broadcast:** Read-only variables that are cached on each machine. Broadcast variables allow programmers to reduce the communication cost, for example they can be used to give a copy of a large input dataset to each node
- **accumulators:** Write-only variables that can only be increased by the tasks. They can be used for reduce operations, so that the driver can retrieve the final result.
#### 17) Map Fusion's relation with Spark's Transformations
A transformation can be applied on a RDD in order to generate a new RDD.
A sequence of transformations behaves exactly as a sequence of mappings, so fusing them can improve performances.
#### 19) Job Stealing
**Job stealing is a popular technique of scheduling tasks between processing elements. 
Basically a PE can take tasks from other PEs if they don't have anything to do anymore.** 

To use this approach we need: 
1) **a way to assign activities to PEs**
2) **a way to list the PEs that still have something to compute** so that PEs can know who they can steal from
	1) one approach is to have a centralized entity to which PEs can report updates. Easy to implement but it can be a SPOF and be a bottleneck
	2) the best approach is to steal at random: the idle PE will choose randomly which PE will be his victim, and hopefully he will have something to be stolen
3) **a protocol for the stealing**: the victim must handle the stealing request and also be able to handle more PEs trying to steal tasks at the same time

**This technique can be very effective but it is difficult to implement** as there are many aspects to be defined and handled, and there is the concrete risk to spend too much on the stealing and too low on the executing the tasks. 
#### 20) Formulate a dynamic scheduling technique which finds compromises between Job Stealing and Auto Scheduling

#### 21) How to use MPI to implement the PageRank?

#### 22) What's Macro Data Flow?

#### 23) What's Vectorization and What are the 4 Conditions for Loops?
**Vectorization is a way to exploit data-level parallelism by performing the same operation on multiple data elements simultaneously.** 

It is an optimization technique where scalar code is transformed into vectorized code that can take advantage of SIMD (Single Instruction, Multiple Data) instructions. 
Many CPUs have "vector" or "SIMD" instruction sets which apply the same operation simultaneously to two, four or more pieces of data. 
Vectorization is the process of rewriting a loop so that instead of processing a single element of an array N times the CPU processes (say) 4 elements of the array simultaneously N/4 times. 

There are two ways to vectorize a program: 
- manual vectorization: explicitly write vector instructions using built-in language constructs
- auto vectorization: the compiler can optimize the code automatically by identifying the loops that can be vectorized. 

To be vectorized the loops must satisfy the following requirements: 
1) known number of iterations beforehand
2) no external call in the body of the loop
3) no conditional branches
4) no overlapping pointers

#### 24) CAP Theorem and PACELC Theorem
## GitHub (2017 - 2021)

#### 4) Autonomic farm management. How can I implement autonomic management in FastFlow? Can I implement `farmout(pipe(s1, s2, s3))` at runtime in FastFlow? (No) Would it change anything if the library was not header####based but was in a `.so` file? (No because it depends on the FastFlow API).

#### 6) Building Blocks for Streaming and Data Parallelism

#### 7) Point to point and collective communication in fast flow. When to use collective communication

#### 8) Define Service Time, Latency, and Efficiency. In which context each metric is more meaningful?
- **Service Time:** also known as throughput, is the time between the delivery of two successive output (or alternative, the time between the acceptance of two consecutive inputs)
	- high-performance computing systems wants the service time to be as low as possible
- **Latency:** the time between the reception of an input and the deliver of the output
	- real-time systems where responsiveness is critical requires a low latency
- **Efficiency:** the ration between the ideal parallel execution time and the actual execution time (basically it is the speedup divided by the number of worker). It is useful to identify the optimal number of processors to use for a given task
#### 10) Why do you start immediately with a fixed number of workers? Wouldn't it have been better to have him work one and then figure out how many workers they need dynamically?

#### 13) If I put a map inside a farm, what profit do I have if I increase the number of workers on the map or if I increase the number of workers in the farm? If I remove the map and leave the farm increasing the workers does something change? How does efficiency change? If I remove everything and leave only a sequential node, does something change? How does the efficiency vary (becomes 1)?

#### 14) Difference between the Work-Span Model and the Amdahl's Law 
he wanted to know that nodes must have the same execution time
???

#### 15) How is the Speedup Calculated?
The speedup is a derived performance indicator and it is defined as the ration between the best known sequential execution time (on the target architecture at hand) and the parallel execution time. 
The speedup is a function of $n$, where $n$ is the parallelism degree of the parallel program: 
$$speedup(n) = \frac{T_{seq}}{T_{par}(n)}$$
#### 17) What should I add to a farm that takes into account both time and energy consumption (considering that both depend on the nw)? 
I have to take into account the degree of parallelism and the frequency of the processor. In the collector I can calculate the service time Ts. I can vary the number of workers and see how the energy changes as the nw increases. More worker = less CPU usage time with more consumption. I can stop when it becomes inconvenient to increase the nw for overhead

??
#### 18) Types of Patterns

## Huffman Project Related Questions
#### 1) How could you use the Actor Model for the counting part of the Huffman Project?

#### 2) What kind of refactoring rule I could have done on the project (huffman): I answered with mapfusion and I argued