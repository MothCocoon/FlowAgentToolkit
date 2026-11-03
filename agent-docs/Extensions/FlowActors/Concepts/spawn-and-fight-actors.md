# Spawning Actors and Running Fights (Concept)

$KB:flow:concept:spawn-and-fight-actors
keywords: spawn actors fight cohort selector spawnRecord reinforcement defeat

## Choose the node

FlowActors provides two nodes over a shared actor-spawn runtime:

- **Spawn Actors** (`UFlowNode_SpawnActors`) runs a configured spawn pass and reports its individual
  spawn results and pass completion. Use it when later flow should not wait for the spawned actors
  to be defeated.
- **Fight Actors** (`UFlowNode_FightActors`) retains actor records, reports actor defeats, and emits
  a terminal output when its completion rule is satisfied. Use it when actor lifetime should gate
  later flow.

The shared base exposes the currently tracked `SpawnedActors` data output. Both nodes also support
defeating their tracked actors through an exec input.

## Select actors and spawn records

Both nodes use the same two-part spawn configuration:

- **What to Spawn** is an `FInstancedStruct` derived from `FFlowActorSpawnSelector`. It selects actor
  classes and counts. `FFlowActorSpawnSelector_ActorClass` is the built-in fixed-class selector.
- **Where to Spawn** is an instanced `UFlowActorSpawnRecord` template. A record resolves the spawn
  transform, acquires or reuses an actor, and owns its cleanup behavior. The default
  `UFlowDefaultActorSpawnRecord` acquires an ordinary deferred actor. Extensions can provide other
  records, such as the EQS-backed record from AIFlowActors.

Spawn attempts can wait on location queries and are scheduled by the shared spawning runtime. Use the
node's success, failure, and pass-complete outputs to handle those outcomes; do not assume every
configured actor was successfully spawned.

Spawn Actors has one selector and record template for its pass. Fight Actors composes one or more
cohorts. Attach a `UFlowNodeAddOn_FightActorsCohortFixedCount` for each distinct group; each cohort
owns its selector, count, and spawn-record template, while Fight Actors coordinates their shared
completion.

## Reinforcement and completion

Reinforcement is optional. Attach one `UFlowNodeAddOn_Reinforcement` when a fight should schedule
additional passes. Requests can come from an actor-defeat threshold, an automatic timer, or the
addon's `Request Reinforce` input. The addon provides a start delay and a productive-round limit.

Initial and reinforcement passes have separate spawn methods. Full-spawn methods request the
configured amount again, so surviving actors can make the total population exceed the configured
cohort counts. Refill methods replace missing cohort slots; single-cohort and single-actor variants
limit each pass to one eligible cohort or slot.

Fight Actors can finish when all actors are defeated and no reinforcement is scheduled or in
progress, when actors are defeated and a finite reinforcement addon is exhausted, or when the graph
fires the explicit defeat-and-disable input. Choose the rule that matches who owns completion.

The built-in `UFlowNode_FightActors` treats destruction of an actor owned by its spawn record as a
defeat signal. A project with a separate health, death, pooling, or encounter-lifetime system should
derive from `UFlowNode_FightActorsBase` and connect that system to the base fight lifecycle.

## Composition guidance

Use one Fight Actors node with reinforcement when the same configured cohorts recur. Use separate
Fight Actors nodes when groups have different selectors, spawn records, or graph gates; their defeat
outputs can sequence the groups or join through a Flow logic node.

Query `FindFlowNodeTypes` for the enabled asset class to inspect current pins and reflected
properties before authoring. The node catalog remains authoritative for exact pin names and
configuration fields.

## See also

- $KB:flow:guide:flowactors-index
- $KB:flow:guide:aiflowactors-index
- $KB:flow:guide:flowgraph-index
