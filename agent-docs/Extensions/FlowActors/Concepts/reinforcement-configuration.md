# Configuring Fight Reinforcement (Concept)

$KB:flow:concept:reinforcement-configuration
keywords: reinforcement fight actors timer threshold rounds cohorts refill fullSpawn completion

## How reinforcement is configured

Attach one `UFlowNodeAddOn_Reinforcement` addon to a `UFlowNode_FightActors` node. Its `Params`
property controls the delay before a requested pass, automatic request policy, spawn method, and
productive-round limit. The fight node's `CompletionRule` separately decides when its terminal
output can fire.

These examples are sanitized FlowAgent v2 patches. They use only the official FlowActors classes and
contain no project actor classes or assets. Replace each example fight-node GUID with the GUID of a
Fight Actors node in the target graph. The addon can be attached whether or not other addons already
exist; these patches do not replace the node's other addons.

FlowAgent property values use Unreal export text inside JSON strings. The outer document is JSON,
while `Params` is a parenthesized struct value and its enum fields use enum value names.

## Defeat threshold with a finite refill budget

This patch requests a refill when the rounded alive-plus-pending population reaches 25 percent or
less of the fight's initial eligible count. Each request waits a random one to two seconds, then
refills missing cohort slots. At most two productive reinforcement rounds are allowed. The fight
finishes after all actors are defeated and that finite budget is exhausted.

```json
{
  "formatVersion": 2,
  "mode": "Patch",
  "ops": [
    {
      "kind": "UpsertNode",
      "guid": "11111111111111111111111111111111",
      "properties": {
        "CompletionRule": "AllActorsDefeatedAndReinforcementsExhausted"
      }
    },
    {
      "kind": "UpsertAddon",
      "newAlias": "reinforcement",
      "parentGuid": "11111111111111111111111111111111",
      "type": "/Script/FlowActorsRuntime.FlowNodeAddOn_Reinforcement",
      "properties": {
        "Params": "(StartDelayTimeRange=(Min=1.0,Max=2.0),MaxReinforcementRounds=2,ReinforceMethod=RefillSpawnAllCohorts,AutoReinforcementTrigger=WhenAnyActorDefeated,AutoReinforcementPercentAlive=25,bShuffleCohortSpawnOrderEachReinforcementRound=false,bEnableAutoReinforcement=true)"
      }
    }
  ]
}
```

The finite-exhaustion completion rule requires a positive `MaxReinforcementRounds` and a spawning
reinforcement method. A round counts only when its pass queues at least one actor. If the fight
should end as soon as the actors are defeated and no pass is scheduled or running, keep the default
`AllActorsDefeatedWithNoReinforcementsScheduled` completion rule instead.

## Timer-driven full-spawn rounds

This patch requests a full spawn of every cohort on a random ten-to-fifteen-second cadence, with a
one-second request delay and a limit of three productive rounds. A full spawn requests each cohort's
configured count again, even when some of its earlier actors remain alive, so the active population
can exceed the cohort counts. The default completion rule waits for all actors and any scheduled or
active reinforcement pass to finish.

```json
{
  "formatVersion": 2,
  "mode": "Patch",
  "ops": [
    {
      "kind": "UpsertAddon",
      "newAlias": "reinforcement",
      "parentGuid": "22222222222222222222222222222222",
      "type": "/Script/FlowActorsRuntime.FlowNodeAddOn_Reinforcement",
      "properties": {
        "Params": "(StartDelayTimeRange=(Min=1.0,Max=1.0),AutoReinforcementTimeRange=(Min=10.0,Max=15.0),MaxReinforcementRounds=3,ReinforceMethod=FullSpawnAllCohorts,AutoReinforcementTrigger=WhenTimerExpires,AutoReinforcementPercentAlive=0,bShuffleCohortSpawnOrderEachReinforcementRound=false,bEnableAutoReinforcement=true)"
      }
    }
  ]
}
```

`AutoReinforcementTimeRange` is used only with `WhenTimerExpires`; the editor hides it for the
defeat-threshold trigger. `AutoReinforcementPercentAlive` is used only with
`WhenAnyActorDefeated`. Setting `bEnableAutoReinforcement` to `false` disables automatic requests,
but the addon still accepts the `Request Reinforce` input. Its `Enable Auto-Reinforce` and
`Disable Auto-Reinforce` inputs can change automatic request behavior at runtime.

## Request lifecycle

An automatic request comes from either the defeat threshold or the addon's timer. A graph can also
connect an exec signal to `Request Reinforce`; this works even when automatic requests are disabled.
An accepted request waits for `StartDelayTimeRange` before starting its pass. A zero delay starts on
the next tick. Requests received while a pass is scheduled or starting are dropped rather than
queued.

The addon counts a round only when a reinforcement pass queues at least one actor. An empty refill
pass and `NoSpawning` do not consume the round limit. A limit of zero permits unlimited productive
rounds. With timer-driven requests, the addon arms the next cadence after it starts the previous pass;
it does not wait for those actors to be defeated.

## Completion rules

Choose the fight node's `CompletionRule` to match who owns the end of the fight:

- `AllActorsDefeatedWithNoReinforcementsScheduled` (the default) emits completion after all tracked
  actors are defeated and no reinforcement pass is scheduled or starting. An idle timer waiting to
  request another pass does not block completion.
- `AllActorsDefeatedAndReinforcementsExhausted` waits for a finite reinforcement limit to be
  exhausted. Use a positive `MaxReinforcementRounds` and a spawning `ReinforceMethod`; validation
  rejects an unlimited limit or `NoSpawning` with this rule.
- `WhenDefeatAndDisableAutoReinforceIsTriggered` gives completion to the graph. Fire the fight
  node's `Defeat And Disable Auto-Reinforce` input when the owning objective or sequence ends.

## Choose a spawn method

`ReinforceMethod` controls how a reinforcement pass selects work:

- `FullSpawnAllCohorts` requests the configured count from every cohort, including already living
  actors.
- `FullSpawnSingleCohort` requests the configured count from the first cohort able to queue actors.
- `RefillSpawnAllCohorts` replaces missing actor slots across all cohorts.
- `RefillSpawnSingleCohort` refills the first cohort with a missing slot.
- `RefillSpawnSingleActor` replaces one missing slot in the first eligible cohort.
- `NoSpawning` queues no actors and cannot produce a productive round.

`bShuffleCohortSpawnOrderEachReinforcementRound` shuffles the cohort order for later passes. It
does not change the initial spawn order. For exact live pin and property shapes, query
`FindFlowNodeTypes` for the enabled asset class before authoring.

## See also

- $KB:flow:concept:spawn-and-fight-actors
- $KB:flow:guide:flowactors-index
